rm -rf ./results ./a.out
mkdir -p ./results
g++ -c main.C
g++ main.o ../../numC/*.o -lgsl -lblas -lm
nohup ./a.out > ./results/result.txt &
