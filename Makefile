all: $(plataform) run

linux:
	@gcc -I ./headers/ *.c -o main.o $$(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags) -std=c99	

macos:
	@gcc -I ./headers/ *.c -o main.o -lallegro -lallegro_main $$(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags) -std=c99

run:
	@./main.o
