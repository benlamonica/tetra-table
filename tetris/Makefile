CC=clang++
SOURCES=display/TerminalTetrisDisplay.cpp \
	display/TetrisDisplay.cpp \
	input/KeyboardTetrisInput.cpp \
	input/TetrisInput.cpp \
	main.cpp \
	pieces/I.cpp \
	pieces/J.cpp \
	pieces/L.cpp \
	pieces/O.cpp \
	pieces/S.cpp \
	pieces/T.cpp \
	pieces/TetrisPiece.cpp \
	pieces/Z.cpp \
	Tetris.cpp \
	util/CursesUtil.cpp
EXECUTABLE=tetra-table
CFLAGS=-std=c++11 -stdlib=libc++
LDFLAGS=-lcurses
OBJECTS=$(SOURCES:.cpp=.o)
 
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

