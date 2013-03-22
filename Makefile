all: main.o oDAO.o
	gcc -Llib -o oDAO main.o oDAO.o -llinkedlist -lodbc
	rm main.o
	rm oDAO.o

main.o:
	gcc -c main.c

oDAO.o:
	gcc -c oDAO.c

clean:
	rm *.o
