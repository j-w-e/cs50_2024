CC= clang
CFLAGS = -ferror-limit=1 -gdwarf-4 -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow -g
# LDLIBS = -lcrypt -lcs50 -lm

EXE = max
BUILD = build/

SRCS = max.c cs50.c
OBJS = $(SRCS:.c=.o)


$(EXE): $(OBJS)
		mkdir -p $(BUILD)
		$(CC) $(CFLAGS) -o $(BUILD)$@ $(OBJS) $(LDLIBS)


clean:
		rm *.o build/*
