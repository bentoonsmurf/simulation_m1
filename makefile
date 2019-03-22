all: comp_file_dattente
	./exec

comp:
	gcc rand.c -o exec 

comp_file_dattente:
	gcc file_dattente.c -o exec 
