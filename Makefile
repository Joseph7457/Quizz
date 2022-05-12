COMPILATEUR = gcc
MAIN_FLAGS = `pkg-config --cflags --libs gtk+-2.0` -pg
QUIZZ_FLAGS = `pkg-config --cflags --libs gtk+-2.0` -lm -pg
DOXYGEN = doxygen


main: quizz
		$(COMPILATEUR)  main.c -o main modele_quizz.o $(MAIN_FLAGS)

quizz:
		$(COMPILATEUR) -c modele_quizz.c -o modele_quizz.o $(QUIZZ_FLAGS)

doc:
		$(DOXYGEN) doc_conf

clean:
	rm -f *.o
	rm -f quizz
	clear
