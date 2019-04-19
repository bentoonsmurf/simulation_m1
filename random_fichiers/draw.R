#pour executer le code : R CMD BATCH "draw.R"

modelname = "simulation_CST.data"
data=read.table(modelname)
attach(data);

temps=V1
Moyenne = V2

plot(temps,Moyenne,type="l",xlab="temps",ylab="E(N)",col="red")
