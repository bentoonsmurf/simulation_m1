all: comp_file_dattente
	./exec
	 R CMD BATCH "draw.R"

comp:
	gcc rand.c -o exec -lm 

comp_file_dattente:
	gcc file_dattente.c -o exec 
