# Name of the project
PROJ_NAME=Cave_Game

# .cpp files
CPP_SOURCE=$(wildcard ./src/*.cpp)

# .h files
H_SOURCE=$(wildcard ./include/*.h)

# Object files
OBJ=$(subst .cpp,.o,$(subst src,obj,$(CPP_SOURCE)))

# Compiler and linker
CC=g++

# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic  \
         -Iinclude  \
         -std=c++0x

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using g++ linker: $@'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./obj/%.o: ./src/%.cpp ./include/%.h
	@ echo 'Building target using g++ compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./obj/main.o: ./src/main.cpp $(H_SOURCE)
	@ echo 'Building target using g++ compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p obj

clean:
	@ $(RM) ./obj/*.o $(PROJ_NAME) *~
	@ rmdir obj

.PHONY: all clean
