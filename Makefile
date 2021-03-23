DOC_DIR = doc/
SRC_DIR = src/

all : bin/testHerve

bin/testHerve : obj/testHerve.o obj/Carre.o obj/Colonne.o obj/TabCases2DTas.o
    g++ -g -Wall obj/testHerve.o obj/Carre.o obj/Colonne.o obj/TabCases2DTas.o -o bin/testHerve

obj/testHerve.o : src/core/testHerve.cpp src/core/Carre.h src/core/Colonne.h src/core/TabCases2DTas.h
    g++ -g -Wall -c src/core/testHerve.cpp -o obj/testHerve.o

obj/Carre.o : src/core/Carre.h src/core/Carre.cpp
    g++ -g -Wall -c src/core/Carre.cpp -o  obj/Carre.o

obj/Colonne.o : src/core/Colonne.h src/core/Colonne.cpp
    g++ -g -Wall -c src/core/Colonne.cpp -o obj/Colonne.o

obj/TabCases2DTas.o : src/core/TabCases2DTas.h src/core/TabCases2DTas.cpp
    g++ -g -Wall -c src/core/TabCases2DTas.cpp -o obj/TabCases2DTas.o

clean:
	rm *.o

veryclean: clean
	rm *.out

$(DOC_DIR)html/index.html : $(DOC_DIR)sudoku3.doxy $(SRC_DIR)Case.h $(SRC_DIR)Case.cpp $(SRC_DIR)Grille.h $(SRC_DIR)Grille.cpp
	doxygen $(DOC_DIR)sudoku3.doxy