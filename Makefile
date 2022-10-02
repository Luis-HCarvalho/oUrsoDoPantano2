all: compile run clean

compile:
	@gcc -I ./headers/ *.c -o main.o $$(pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags) -std=c99
run:
	@./main.o
clean: 
	@rm main.o
