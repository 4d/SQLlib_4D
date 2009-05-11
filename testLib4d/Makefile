CC=gcc -O0
AA=ar
CFLAGS=
LDFLAGS=-L../lib4d_sql/ -l4d_sql
SRC=test4d.c
OBJ=$(SRC:.c=.o)

all: testLib4d

testLib4d: $(OBJ)
	$(CC) -o testLib4d $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -f testLib4d

