#include <stfat.h>
#include <stdio.h>
#include <stdlib.h>

static char* ReadFat32(char* filename)
{
    FILE* handle;

    handle = fopen(filename, "rb");
    if (handle == NULL)
    {
        return NULL;
    }

    signed long fsize;
    fseek(handle, 0, SEEK_END);
    fsize = ftell(handle);
    fseek(handle, 0, SEEK_SET);
    if (fsize == -1)
    {
        goto EXIT_CLOSE_FILE;
    }

    char* ptr;
    ptr = (char*)malloc(fsize + 1);
    if (ptr == NULL)
    {
        goto EXIT_CLOSE_FILE;
    }

    size_t bytes_read;
    bytes_read = fread(ptr, 1, fsize, handle);
    if ((signed)bytes_read != fsize)
    {
        goto EXIT_CLEAN_BUFFER;
    }

    fclose(handle);
    return ptr;

EXIT_CLEAN_BUFFER:
    free(ptr);
EXIT_CLOSE_FILE:
    fclose(handle);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <fat32.img>\n", argv[0]);
        return fatEVENT;
    }

    char* buffer;
    buffer = ReadFat32(argv[1]);
    if (buffer == NULL)
    {
        return fatEVENT;
    }
    
    fatInit(buffer);
    fatLogSctr(buffer);
        
    free(buffer);
    return fatSILENT;
}
