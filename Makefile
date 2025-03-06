.PHONY: clean

out: calc case_all
	gcc calc.c -o calc
	calc | ./calc.c | out
case_add:casegen.c
	gcc casegen.c -o casegen
	./casegen add 100 > case_add
case_sub:casegen.c
	gcc casegen.c -o casegen
	./casegen sub 100 > case_sub
case_mul:casegen.c
	gcc casegen.c -o casegen
	./casegen mul 100 > case_mul
case_div:casegen.c
	gcc casegen.c -o casegen
	./casegen div 100 > case_div
case_all:casegen.c
	make case_add && make case_sub && make case_mul && make case_div
	cat case_add case_sub case_mul case_div > case_all
	
clean:
	rm -f out calc casegen case_* out
