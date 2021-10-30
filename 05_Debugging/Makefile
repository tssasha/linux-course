CFLAGS = -O0 -g
TRASH = *.out range

range:

test: test_1 test_2

test_%:
	gdb -x $@.gdb --args ./range | grep @@@ | tr -d "@" > $@.out
	rm -f gdb.txt
	cmp $@.out $@.txt

clean:
	rm -f $(TRASH)
