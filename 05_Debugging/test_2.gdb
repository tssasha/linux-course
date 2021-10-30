set pagination off
set logging on

set $var = 0

break range.c:21 if $var++ >= 28 && $var <= 36
	command 1
	echo @@@
	printf "%d %d %d %d\n", start, stop, step, i
	continue
end

run -100 100 3

set logging off
quit