test: test.c
	gcc -o test -g -O0 test.c -lm


clean:
	-rm -f test