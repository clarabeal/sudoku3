CORE = core/Case.cpp core/TabCases2DTas.cpp core/Carre.cpp core/Colonne.cpp core/Ligne.cpp core/Grille.cpp core/Jeu.cpp
TXT = txt/TXT_1vs1.cpp txt/TXT_PasAPas.cpp txt/TXT_Classique.cpp txt/Sauvegarde.cpp txt/main_txt.cpp
SDL = sdl/sdlClassique.cpp sdl/main_sdl.cpp

SRCS_TXT = $(CORE) $(TXT)
OBJS_TXT = $(SRCS_TXT:%.cpp=$(OBJ_DIR)/%.o)

SRCS_SDL = $(CORE) $(SDL)
OBJS_SDL = $(SRCS_SDL:%.cpp=$(OBJ_DIR)/%.o)

FINAL_TARGET_TXT = sudoku_txt
FINAL_TARGET_SDL = sudoku_sdl

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CORE) $(TXT) $(SDL))
DEPENDANCES = $(patsubst %.cpp,$(DEP_DIR)/%.d,$(CORE) $(TXT) $(SDL))

ifeq ($(OS),Windows_NT)
	INCLUDE_DIR_SDL = 	-I extern/SDL2-w64/include

	LIBS_SDL = -Lextern/SDL2-w64/lib\
			-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll -lSDL2_mixer.dll

else
	INCLUDE_DIR_SDL = -I/usr/include/SDL2
	LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
endif

CC					= g++
CPPFLAGS			= -Wall -ggdb
DEPFLAGS 			= -MMD -MF $(DEP_DIR)/$*.d
BIN_DIR 			= bin
SRC_DIR 			= src
DEP_DIR 			= dep
DOC_DIR 			= doc
OBJ_DIR 			= obj
INCLUDE_DIR			= -Isrc -Isrc/core -Isrc/sdl2 -Isrc/txt


all: make_dir $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SDL)

sdl: make_dir $(BIN_DIR)/$(FINAL_TARGET_SDL)

make_dir:
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR) $(OBJ_DIR)/txt $(OBJ_DIR)/sdl $(OBJ_DIR)/core
	test -d $(DEP_DIR) || mkdir -p $(DEP_DIR) $(DEP_DIR)/txt $(DEP_DIR)/sdl $(DEP_DIR)/core
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)

$(BIN_DIR)/$(FINAL_TARGET_TXT): $(OBJS_TXT)
	$(CC) $+ -o $@

$(BIN_DIR)/$(FINAL_TARGET_SDL): $(OBJS_SDL)
	$(CC) $+ -o $@ $(LIBS_SDL)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $(INCLUDE_DIR) $(INCLUDE_DIR_SDL) $< -o $@ $(DEPFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/core/*.o $(OBJ_DIR)/txt/*.o $(OBJ_DIR)/sdl/*.o

veryclean: clean
	rm -rf $(DEP_DIR) $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SDL)


-include $(DEPENDANCES)