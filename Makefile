all:
	g++ -Iinclude -Llib -o simple src/main.cpp src/glad.c -lmingw32 -lSDL3