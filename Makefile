CC=clang++
SOURCES= \
	src/audio/TetraTableAudio.cpp \
	src/audio/NoSoundAudio.cpp \
	src/audio/SDLAudio.cpp \
	src/pieces/TetraTablePiece.cpp \
	src/pieces/I.cpp \
	src/pieces/J.cpp \
	src/pieces/L.cpp \
	src/pieces/O.cpp \
	src/pieces/S.cpp \
	src/pieces/T.cpp \
	src/pieces/Z.cpp \
	src/util/CursesUtil.cpp \
	src/util/SDLUtil.cpp \
	src/util/TimeUtil.cpp \
        src/util/Base64.cpp \
	src/display/TerminalDisplay.cpp \
	src/display/TetraTableDisplay.cpp \
        src/display/HyperionDisplay.cpp \
	src/input/KeyboardInput.cpp \
	src/input/TetraTableInput.cpp \
	src/input/SDLJoystickInput.cpp \
	src/main.cpp \
	src/TetraTable.cpp 

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

