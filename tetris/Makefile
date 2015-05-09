CC=clang++
SOURCES= \
	audio/TetrisAudio.cpp \
	audio/NoSoundAudio.cpp \
	audio/SDLAudio.cpp \
	pieces/TetrisPiece.cpp \
	pieces/I.cpp \
	pieces/J.cpp \
	pieces/L.cpp \
	pieces/O.cpp \
	pieces/S.cpp \
	pieces/T.cpp \
	pieces/Z.cpp \
	util/CursesUtil.cpp \
	util/SDLUtil.cpp \
	util/TimeUtil.cpp \
	display/TerminalTetrisDisplay.cpp \
	display/TetrisDisplay.cpp \
	input/KeyboardTetrisInput.cpp \
	input/TetrisInput.cpp \
	input/SDLJoystickTetrisInput.cpp \
	main.cpp \
	Tetris.cpp 

EXECUTABLE=tetra-table
CFLAGS=-std=c++11 -F /Library/Frameworks
LDFLAGS=-lcurses -lpthread -framework SDL2 -framework SDL2_mixer 
OBJECTS=$(SOURCES:.cpp=.o)
 
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	find . -name '*.o' -delete && find . -name '$(EXECUTABLE)' -delete 

