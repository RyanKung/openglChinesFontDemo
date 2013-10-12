.PHONY: all
LIB = -framework opengl -framework GLUT -l freeType
APP_NAME = runes
DEBUG = -g  # comment for none-debug mode
GCC = gcc $(DEBUG)

default: main.o font.o
	rm -f runes.bmp
	$(GCC) $(LIB) main.o font.o -o $(APP_NAME)
	./$(APP_NAME)

main.o: main.c
	$(GCC) -c main.c

font.o: font.c font.h
	$(GCC) -c font.c

clear:
	@$(RM) *.o
	@$(RM) $(APP_NAME)
debug:
	gdb $(APP_NAME)
