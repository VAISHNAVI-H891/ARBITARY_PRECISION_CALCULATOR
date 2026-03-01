apc.out : main.o addition.o subtraction.o multiplication.o division.o modulus.o common.o
	gcc -o apc.out main.o addition.o subtraction.o multiplication.o division.o modulus.o common.o
	
main.o : main.c
	gcc -c main.c -o main.o

addition.o : addition.c
	gcc -c addition.c -o addition.o

subtraction.o :subtraction.c
	gcc -c subtraction.c -o subtraction.o

multiplication.o : multiplication.c
	gcc -c multiplication.c -o multiplication.o

division.o : division.c
	gcc -c division.c -o division.o

common.o :
	gcc -c common.c -o common.o

clean: 
	rm *.o apc.out