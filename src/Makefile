CC=clang++
SOURCES= \
	audio/TetraTableAudio.cpp \
	audio/NoSoundAudio.cpp \
	audio/SDLAudio.cpp \
	pieces/TetraTablePiece.cpp \
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
	display/TerminalDisplay.cpp \
	display/TetraTableDisplay.cpp \
	input/KeyboardInput.cpp \
	input/TetraTableInput.cpp \
	input/SDLJoystickInput.cpp \
	main.cpp \
	TetraTable.cpp 

EXECUTABLE=dist/tetra-table
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

