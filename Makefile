# Specifiy the target
all: program1

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
program1: program1.o
	g++ program1.o -o program1

# Specify how the object files should be created from source files
program1.o: program1.cpp
	g++ -c program1.cpp


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o program1
