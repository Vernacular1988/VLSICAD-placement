# Copyright (c) 2002 ACM/SIGDA

TARGET		= place

SRCS		= $(wildcard *.c)
OBJS		= $(SRCS:.cpp=.o)
HDRS		= $(wildcard *.h)
INCLUDES	=

CC		= gcc

# specify appropriate C compiler flags here:
CFLAGS		= -g $(INCLUDES)
LDFLAGS		=
LIBPATHS	=
LIBS		= -lm


$(TARGET) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBPATHS) $(LIBS)

OBJS: $(HDRS)

.PHONY:	clean test

test:	$(TARGET) 
	./$(TARGET) ./test1
	./$(TARGET) ./test2
	./$(TARGET) ./test3

clean : 
	rm -f *.o $(TARGET)
