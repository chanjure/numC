import numpy as np
import matplotlib.pyplot as plt

result_dir = "./results/"
plots_dir = "./results/plots/"

f_LCG = open(result_dir+"lcg.dat", "r")
f_MRG = open(result_dir+"mrg.dat", "r")

lcg = []
mrg = []

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

f_LCG.close()
f_MRG.close()
