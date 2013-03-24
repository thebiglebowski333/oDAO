all: main.o oDAO.o
	gcc -Llib -isystem /usr/include/mysql -o oDAO main.o oDAO.o -llinkedlist -lncurses `mysql_config --cflags --libs` 
	rm main.o
	rm oDAO.o

main.o:
	gcc -c main.c

oDAO.o:
	gcc -c oDAO.c

clean:
	rm *.o
