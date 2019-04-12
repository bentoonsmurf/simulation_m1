modelname = "data.data"
data =read.table(modelname)
attach(data)

x= V1
f1 = V2
f2 = V3

plot(x,f1,type="l",xlab="x",ylab="Fx(x)",col="red",main= "fonction de repartition ")
lines(x,f2,type="l",col="blue")
