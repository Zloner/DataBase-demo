run:main.o database.o table.o
	g++ $^ -o main
%.o:%.c
	g++ -c $<

.PHONY:clean
clean:
	rm -f *.o main