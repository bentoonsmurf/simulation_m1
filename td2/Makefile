compile :
	gcc loi_exp.c -lm

run : compile
	./a.out

runR : compile
	./a.out
	Rscript essai.R
	ristretto plot.jpg &

clear :
	rm a.out
	rm donnee
	rm plot.jpg
