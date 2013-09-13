.PHONY: all
LIB = -framework opengl -framework GLUT -l freeType
APP_NAME = runes
DEBUG = -g  # comment for none-debug mode
GCC = gcc $(DEBUG)

default: clear
	$(GCC) $(LIB) main.c -o $(APP_NAME)

clear:
	@$(RM) *.o
	@$(RM) $(APP_NAME)
debug:
	gdb $(APP_NAME)
