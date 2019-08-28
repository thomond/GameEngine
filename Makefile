#OBJS specifies which files to compile as part of the project
OBJS = TestBed.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -fpermissive -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltmxlite

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = testbed

#This is the target that compiles our executable
all : src/$(OBJS)
	test -d bin|| mkdir bin
	$(CC) src/$(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/$(OBJ_NAME)
run : 
	cd bin && ./$(OBJ_NAME)
