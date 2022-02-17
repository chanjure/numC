import numpy as np
import matplotlib.pyplot as plt

result_dir = "./results/"
plots_dir = "./results/plots/"

f_LCG = open(result_dir+"lcg.dat", "r")
f_MRG = open(result_dir+"mrg.dat", "r")
f_CMRG = open(result_dir+"cmrg.dat", "r")
f_FIB = open(result_dir+"fib.dat", "r")

lcg = []
mrg = []
cmrg = []
fib = []

lines = f_LCG.readlines()
for line in lines:
	lcg.append(float(line))

plt.hist(lcg)
plt.savefig(plots_dir+"lcg.png")
plt.clf()

lines = f_MRG.readlines()
for line in lines:
	mrg.append(float(line))

plt.hist(mrg)
plt.savefig(plots_dir+"mrg.png")
plt.clf()

lines = f_CMRG.readlines()
for line in lines:
	cmrg.append(float(line))

plt.hist(cmrg)
plt.savefig(plots_dir+"cmrg.png")
plt.clf()

lines = f_FIB.readlines()
for line in lines:
	fib.append(float(line))

plt.hist(fib)
plt.savefig(plots_dir+"fib.png")
plt.clf()

f_LCG.close()
f_MRG.close()
f_CMRG.close()
f_FIB.close()
