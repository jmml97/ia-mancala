
all:
	g++ -o Croqueta *.cpp -I./ -lm -std=c++11


clean:
	rm Croqueta

