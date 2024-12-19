CC := gcc
CFLAGS := -Wall -Werror -Wextra
LDFLAGS :=

SOURCES += ./fatlib/stfat.c
SOURCES += ./debug/bpbman/bpbman.c
SOURCES += ./fatlib/lcnt.c
SOURCES += ./debug/regman/regman.c
SOURCES += ./main.c

INCLUDES += -I"./fatlib"
INCLUDES += -I"./debug/regman"
INCLUDES += -I"./debug/bpbman"
INCLUDES += -I"./debug/logger"

OUTPUT := a.out

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(OUTPUT)
	@echo
	@ls -lh $(OUTPUT)
	@size $(OUTPUT)

clean:
	rm -rf *.out