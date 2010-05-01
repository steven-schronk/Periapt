CC=gcc

CFLAGS_REL=-Wall -ansi -O0 -lglut
#CFLAGS_DBG=-Wall -Werror -pedantic -std=c99 -ansi -DDEBUG -g -O0 -ggdb3 -Wextra -Wno-missing-field-initializers
CFLAGS_DBG=-Wall -pedantic -std=c99 -ansi -DDEBUG -g -O0 -ggdb3 -Wextra -Wno-missing-field-initializers -lglut
CFLAGS_SML=-Wall -ansi -Os -lglut

OBJS=periapt.c
OUT=-o periapt

asmcompile: $(OBJS)
	$(CC) $(CFLAGS_REL) $(OUT) $^

asmlink: periapt.o
	gcc -o periapt periapt.o

asm: asmlink

small: $(OBJS)
	$(CC) $(CFLAGS_SML) $(OUT) $^ 

debug: $(OBJS)
	$(CC) $(CFLAGS_DBG) $(OUT) $^

clean:
	rm -f periapt *.o
