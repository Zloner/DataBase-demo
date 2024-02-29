run:function.cpp database.cpp table.cpp main.cpp
	g++ -g $^ -o main
	
.PHONY:clean
clean:
	rm -f *.o main