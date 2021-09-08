output: AVL.o
	g++ AVL.o -o output

AVL.o: AVL.cpp AVL.h
	g++ -c AVL.cpp

clean:
	rm *.o