PROJECT_NAME = Tanks

BUILD = build
BIN = $(BUILD)/bin
RESOURCES_DIR = resources

ifeq ($(OS),Windows_NT)
	CC = $(MINGW_HOME)/bin/mingw32-g++.exe
	INCLUDEPATH = -I$(RESOURCES_DIR)/SDL/i686-w64-mingw32/include
	LFLAGS = -mwindows -O
	CFLAGS = -c -Wall
	LIBS = -L$(RESOURCES_DIR)/SDL/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	APP_RESOURCES = SDL/i686-w64-mingw32/bin/*.dll dll/*.dll font/prstartk.ttf png/texture.png levels
	RESOURCES = $(APP_RESOURCES) mingw_resources
else
	CC = g++
	INCLUDEPATH = -I src -I/usr/include/SDL2
	LFLAGS = -O -g
	CFLAGS = -c -Wall -std=c++17 -g
	LIBS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	APP_RESOURCES = font/prstartk.ttf png/texture.png levels
	RESOURCES = $(APP_RESOURCES)
endif

MODULES = engine app_state objects
MODULES_A = Component Entity System
MODULES_B = Common Components Entities Feature Manager Services Systems UIs
SRC_DIRS = src $(addprefix src/,$(MODULES)) $(wildcard src/ECS/*) $(wildcard src/Game/*) src/Math
BUILD_DIRS = $(BUILD) $(BIN) $(addprefix $(BUILD)/,$(MODULES)) $(addprefix $(BUILD)/ECS/,$(MODULES_A)) $(addprefix $(BUILD)/Game/,$(MODULES_B)) $(BUILD)/Math

SOURCES = $(foreach sdir,$(SRC_DIRS),$(wildcard $(sdir)/*.cpp))
OBJS = $(patsubst src/%.cpp,$(BUILD)/%.o,$(SOURCES))

vpath %.cpp $(SRC_DIRS)

all: print $(BUILD_DIRS) $(RESOURCES) compile

print:
	@echo
	@echo OS: $(OS)
	@echo MODULES: $(MODULES)
	@echo SRC_DIRS: $(SRC_DIRS)
	@echo BUILD_DIRS: $(BUILD_DIRS)
	@echo SOURCES: $(SOURCES)
	@echo RESOURCES: $(RESOURCES)
	@echo OBJS: $(OBJS)
	@echo INCLUDEPATH: $(INCLUDEPATH)
	@echo LIBSPATH: $(LIBSPATH)
	@echo LIBS: $(LIBS)
	@echo LFLAGS: $(LFLAGS)
	@echo

$(BUILD_DIRS): 
	mkdir -p $@

compile: $(OBJS)
	$(CC) $(OBJS) $(INCLUDEPATH) $(LIBSPATH) $(LIBS) $(LFLAGS) -o $(BIN)/$(PROJECT_NAME)

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDEPATH) $< -o $@

$(APP_RESOURCES):
	cp -R $(RESOURCES_DIR)/$@ $(BIN)

ifeq ($(OS),Windows_NT)

mingw_resources:
	cp $(MINGW_HOME)/bin/libstdc++-6.dll $(BIN)
	cp $(MINGW_HOME)/bin/libgcc_s_dw2-1.dll $(BIN)

endif

clean:
	rm -rf $(BUILD)
	rm -rf doc

doc:
	doxywizard Doxyfile
	doxygen

print:
    @echo BUILD_DIRS: $(BUILD_DIRS)


