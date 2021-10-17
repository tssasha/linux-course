GENERATES = liboutput_static.a liboutput.so prog prog-a prog-so README
TRASH = *.o *~ o.*
CFLAGS = -fPIC

all: README prog
	make clean

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. $< -loutput -o $@

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

fun.o: outlib.h

README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)

test: prog prog-a prog-so
	./prog 2> res.txt
	./prog a >> res.txt
	./prog a b c >> res.txt
	./prog-a 2> res-a.txt
	./prog-a a >> res-a.txt
	./prog-a a b c >> res-a.txt
	$ LD_LIBRARY_PATH=`pwd` ./prog-so 2> res-so.txt
	$ LD_LIBRARY_PATH=`pwd` ./prog-so a >> res-so.txt
	$ LD_LIBRARY_PATH=`pwd` ./prog-so a b c >> res-so.txt
	cmp res.txt res-a.txt || true
	cmp res.txt res-so.txt || true
	cmp res-a.txt res-so.txt || true
	make clean