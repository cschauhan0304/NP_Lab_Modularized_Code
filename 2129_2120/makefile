CC_Compiler = gcc

C_FLAGS = -Wall -g

EXECUTABLES = 2129_2120

OBJECT_FILES = student.o course.o parser.o main.o

Header_Files = student.h course.h parser.h

all: $(EXECUTABLES)

$(EXECUTABLES): $(OBJECT_FILES)
	$(CC_Compiler) $(C_FLAGS) -o $(EXECUTABLES) $(OBJECT_FILES)

main.o: main.c $(Header_Files)
	$(CC_Compiler) $(C_FLAGS) -c main.c

student.o: student.c $(Header_Files)
	$(CC_Compiler) $(C_FLAGS) -c student.c

course.o: course.c $(Header_Files)
	$(CC_Compiler) $(C_FLAGS) -c course.c

parser.o: parser.c $(Header_Files)
	$(CC_Compiler) $(C_FLAGS) -c parser.c

clean:
	rm -f $(OBJECT_FILES) $(EXECUTABLES)


