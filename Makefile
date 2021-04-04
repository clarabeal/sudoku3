DOC_DIR = doc
SRC_DIR = src
OBJ_DIR = obj

INCLUDE_DIR = -Isrc -Isrc/core -Isrc/txt

all : bin/test bin/main_txt

bin/main_txt : obj/txt/main_txt.o obj/core/Sauvegarde.o obj/txt/TXT_Classique.o obj/txt/TXT_PasAPas.o obj/core/Jeu.o obj/core/Grille.o obj/core/Carre.o obj/core/Colonne.o obj/core/Ligne.o obj/core/TabCases2DTas.o obj/core/Case.o
	g++ -g -Wall obj/txt/main_txt.o obj/core/Sauvegarde.o obj/txt/TXT_Classique.o obj/txt/TXT_PasAPas.o obj/core/Jeu.o obj/core/Grille.o obj/core/Carre.o obj/core/Colonne.o obj/core/Ligne.o obj/core/TabCases2DTas.o obj/core/Case.o -o bin/main_txt

bin/test : obj/core/Test.o obj/core/Jeu.o obj/core/Grille.o obj/core/Carre.o obj/core/Colonne.o obj/core/Ligne.o obj/core/TabCases2DTas.o obj/core/Case.o
	g++ -g -Wall obj/core/Test.o obj/core/Jeu.o obj/core/Grille.o obj/core/Carre.o obj/core/Colonne.o obj/core/Ligne.o obj/core/TabCases2DTas.o obj/core/Case.o -o bin/test

obj/txt/main_txt.o : src/txt/main_txt.cpp src/core/Sauvegarde.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/txt/main_txt.cpp -o obj/txt/main_txt.o

obj/core/Sauvegarde.o : src/core/Sauvegarde.cpp src/core/Sauvegarde.cpp src/txt/TXT_Classique.h src/txt/TXT_PasAPas.h src/txt/TXT_1vs1.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/core/Sauvegarde.cpp -o obj/core/Sauvegarde.o

obj/txt/TXT_Classique.o : src/txt/TXT_Classique.cpp src/txt/TXT_Classique.h src/core/Jeu.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/txt/TXT_Classique.cpp -o obj/txt/TXT_Classique.o

obj/txt/TXT_PasAPas.o : src/txt/TXT_PasAPas.cpp src/txt/TXT_PasAPas.h src/core/Jeu.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/txt/TXT_PasAPas.cpp -o obj/txt/TXT_PasAPas.o 

obj/txt/TXT_1vs1.o : src/txt/TXT_1vs1.cpp src/txt/TXT_1vs1.h src/core/Jeu.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/txt/TXT_1vs1.cpp -o obj/txt/TXT_1vs1.o 

obj/core/Test.o : src/core/Test.cpp src/core/Jeu.h 
	g++ -g -Wall -c $(INCLUDE_DIR) src/core/Test.cpp -o obj/core/Test.o

obj/core/Jeu.o : src/core/Jeu.cpp src/core/Jeu.h src/core/Grille.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/core/Jeu.cpp -o obj/core/Jeu.o

obj/core/Grille.o : src/core/Grille.cpp src/core/Grille.h src/core/Carre.h src/core/Colonne.h src/core/Ligne.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/core/Grille.cpp -o obj/core/Grille.o

obj/core/Carre.o : src/core/Carre.h src/core/Carre.cpp src/core/TabCases2DTas.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/core/Carre.cpp -o  obj/core/Carre.o

obj/core/Colonne.o : src/core/Colonne.h src/core/Colonne.cpp src/core/TabCases2DTas.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/core/Colonne.cpp -o obj/core/Colonne.o

obj/core/Ligne.o : src/core/Ligne.h src/core/Ligne.cpp src/core/TabCases2DTas.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/core/Ligne.cpp -o obj/core/Ligne.o

obj/core/TabCases2DTas.o : src/core/TabCases2DTas.h src/core/TabCases2DTas.cpp src/core/Case.h
	g++ -g -Wall -c $(INCLUDE_DIR) src/core/TabCases2DTas.cpp -o obj/core/TabCases2DTas.o

obj/core/Case.o : src/core/Case.h src/core/Case.cpp
	g++ -g -Wall -c $(INCLUDE_DIR) src/core/Case.cpp -o obj/core/Case.o

clean:
	rm $(OBJ_DIR)/core/*.o $(OBJ_DIR)/txt/*.o $(OBJ_DIR)/sdl/*.o

veryclean: clean
	rm ./bin/*

