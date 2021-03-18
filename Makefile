DOC_DIR = doc/
SRC_DIR = src/


$(DOC_DIR)html/index.html : $(DOC_DIR)sudoku3.doxy $(SRC_DIR)Case.h $(SRC_DIR)Case.cpp $(SRC_DIR)Grille.h $(SRC_DIR)Grille.cpp
	doxygen $(DOC_DIR)sudoku3.doxy