comp: 
	gcc -o cm -g *.c

test: comp
	./cm input 
	cc out.s
	./a.out
	./cm input2
	cc out.s
	./a.out
	./cm input3
	cc out.s
	./a.out
clean:
	rm -f out* *.o cm a.out
