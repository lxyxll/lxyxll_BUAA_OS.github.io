out:src/main.c src/output.c
	gcc -Isrc/include src/main.c src/output.c -o out/main
check:check.c
	gcc -c check.c -o check.o
run:out/main
	./out/main
clean:
	rm -rf check.o out/main
