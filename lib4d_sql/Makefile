CC=gcc -g -O0
AA=ar
CFLAGS=
LDFLAGS=
SRC=base64.c fourd.c fourd_interne.c fourd_result.c fourd_type.c utils.c communication.c sqlstate.c
OBJ=$(SRC:.c=.o)

all: lib4d_sql.a install

lib4d_sql.a: $(OBJ)
	$(AA) -rv lib4d_sql.a $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf *.lo
	rm -f lib4d_sql.a

install:
	cp lib4d_sql.a ./lib/
	cp fourd.h ./include/
