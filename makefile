compilador = gcc
MAIN = main.c
ejecutable = p
entrada = salida.txt
salida = out.txt
main2 = entradas.c

all:
	$(compilador) -pg $(MAIN) -o $(ejecutable) -lm -l pthread
run:
	./$(ejecutable) < $(entrada)
run_ddd:
	ddd ./$(ejecutable)
tiempo:
	time ./$(ejecutable) < $(entrada)
generar: generar_1
	./ejec > $(entrada)
generar_1:
	$(compilador) $(main2) -o ejec
clean:
	rm -rf out.txt
