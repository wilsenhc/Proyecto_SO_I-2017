compilador = gcc
MAIN = jacobi.c
MAIN_EJ = JACOBI
entrada = caso10000.in
salida = out.txt
CASOS = entradas.c
CASOS_EJ = CASOS

CASOENUNCIADO = casoEnunciado.txt
CASO10 = caso10.in
CASO100 = caso100.in
CASO1000 = caso1000.in
CASO10000 = caso10000.in

all: compile

compile: principal casos_prueba

compile_test: debug generar_casos

debug:
	$(compilador) $(MAIN) -D DEBUG -g -o $(MAIN_EJ) -lm -l pthread -O3 -Wno-unused-result

principal:
	$(compilador) $(MAIN) -o $(MAIN_EJ) -lm -l pthread -O3 -Wno-unused-result

casos_prueba:
	$(compilador) $(CASOS) -o $(CASOS_EJ) -lm

generar_casos: casos_prueba
	./$(CASOS_EJ) 10 > caso10.in
	./$(CASOS_EJ) 100 > caso100.in
	./$(CASOS_EJ) 1000 > caso1000.in
	./$(CASOS_EJ) 10000 > caso10000.in

test_enunciado:
	./$(MAIN_EJ) 1 < $(CASOENUNCIADO)
	./$(MAIN_EJ) 2 < $(CASOENUNCIADO)
	./$(MAIN_EJ) 4 < $(CASOENUNCIADO)

test_10:
	./$(MAIN_EJ) 1 < $(CASO10)
	./$(MAIN_EJ) 2 < $(CASO10)
	./$(MAIN_EJ) 4 < $(CASO10)

test_100:
	./$(MAIN_EJ) 1 < $(CASO100)
	./$(MAIN_EJ) 2 < $(CASO100)
	./$(MAIN_EJ) 4 < $(CASO100)
	./$(MAIN_EJ) 8 < $(CASO100)

test_1000:
	./$(MAIN_EJ) 1 < $(CASO1000)
	./$(MAIN_EJ) 2 < $(CASO1000)
	./$(MAIN_EJ) 4 < $(CASO1000)
	./$(MAIN_EJ) 8 < $(CASO1000)

test_10000:
	./$(MAIN_EJ) 1 < $(CASO10000)
	./$(MAIN_EJ) 2 < $(CASO10000)
	./$(MAIN_EJ) 4 < $(CASO10000)
	./$(MAIN_EJ) 8 < $(CASO10000)

clean:
	rm *.in
	rm $(MAIN_EJ)
	rm $(CASOS_EJ)