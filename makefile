compilador = gcc
MAIN = main.c
ejecutable = p
entrada = in.txt
salida = out.txt

all:
	$(compilador) -g $(MAIN) -o $(ejecutable) -lm -l pthread
run:
	./$(ejecutable) < $(entrada)
run_ddd:
	ddd ./$(ejecutable)
clean:
	rm -rf out.txt
