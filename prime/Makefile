CC=cc
CFLAGS=-Wall
MAIN=main.c
TARGET=primecalc
OBJS=BitArray.o \
     Sieve.o

all : $(TARGET)

$(TARGET) : $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN) $(OBJS) $(CFLAGS)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c $<

Sieve.o : BitArray.o

clean :
	rm $(TARGET) $(OBJS)
