DOC_DIR = doc/
SRC_DIR = src/
OBJ_DIR = obj/

INCLUDE_DIR = -Isrc -Isrc/core -Isrc/txt

all : bin/testHerve bin/txt_classique

bin/txt_classique : obj/main_txt_classique.o obj/TXT_Classique.o obj/Jeu.o obj/Grille.o obj/Carre.o obj/Colonne.o obj/Ligne.o obj/TabCases2DTas.o obj/Case.o
	g++ -g -Wall obj/main_txt_classique.o obj/TXT_Classique.o obj/Jeu.o obj/Grille.o obj/Carre.o obj/Colonne.o obj/Ligne.o obj/TabCases2DTas.o obj/Case.o -o bin/txt_classique

bin/testHerve : obj/testHerve.o obj/Jeu.o obj/Grille.o obj/Carre.o obj/Colonne.o obj/Ligne.o obj/TabCases2DTas.o obj/Case.o
	g++ -g -Wall obj/testHerve.o obj/Jeu.o obj/Grille.o obj/Carre.o obj/Colonne.o obj/Ligne.o obj/TabCases2DTas.o obj/Case.o -o bin/testHerve

obj/main_txt_classique.o : src/txt/main_txt_classique.cpp src/txt/TXT_Classique.h
	g++ -g -Wall -c src/txt/main_txt_classique.cpp -o obj/main_txt_classique.obj

obj/TXT_Classique.o : src/txt/TXT_Classique.cpp src/txt/TXT_Classique.h src/core/Jeu.h
	g++ -g -Wall -c src/txt/TXT_Classique.cpp -o obj/TXT_Classique.o

obj/testHerve.o : src/core/testHerve.cpp src/core/Jeu.h 
	g++ -g -Wall -c src/core/testHerve.cpp -o obj/testHerve.o

obj/Jeu.o : src/core/Jeu.cpp src/core/Jeu.h src/core/Grille.h
	g++ -g -Wall -c src/core/Jeu.cpp -o obj/Jeu.o

obj/Grille.o : src/core/Grille.cpp src/core/Grille.h src/core/Carre.h src/core/Colonne.h src/core/Ligne.h
	g++ -g -Wall -c src/core/Grille.cpp -o obj/Grille.o

obj/Carre.o : src/core/Carre.h src/core/Carre.cpp src/core/TabCases2DTas.h
	g++ -g -Wall -c src/core/Carre.cpp -o  obj/Carre.o

obj/Colonne.o : src/core/Colonne.h src/core/Colonne.cpp src/core/TabCases2DTas.h
	g++ -g -Wall -c src/core/Colonne.cpp -o obj/Colonne.o

obj/Ligne.o : src/core/Ligne.h src/core/Ligne.cpp src/core/TabCases2DTas.h
	g++ -g -Wall -c src/core/Ligne.cpp -o obj/Ligne.o

obj/TabCases2DTas.o : src/core/TabCases2DTas.h src/core/TabCases2DTas.cpp src/core/Case.h
	g++ -g -Wall -c src/core/TabCases2DTas.cpp -o obj/TabCases2DTas.o

obj/Case.o : src/core/Case.h src/core/Case.cpp
	g++ -g -Wall -c src/core/Case.cpp -o obj/Case.o

clean:
	rm $(OBJ_DIR)*.o

veryclean: clean
	rm ./bin/*


$(DOC_DIR)html/index.html : $(DOC_DIR)sudoku3.doxy $(SRC_DIR)core/Case.h $(SRC_DIR)core/Case.cpp $(SRC_DIR)core/Grille.h $(SRC_DIR)core/Grille.cpp $(SRC_DIR)core/Carre.h $(SRC_DIR)core/Carre.cpp $(SRC_DIR)core/Colone.h $(SRC_DIR)core/Colonne.cpp $(SRC_DIR)core/Ligne.h $(SRC_DIR)core/Ligne.cpp $(SRC_DIR)core/TabCases2DTas.h $(SRC_DIR)core/TabCases2DTas.cpp
	doxygen $(DOC_DIR)sudoku3.doxy