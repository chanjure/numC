#include <iostream>
#include <limits.h>
#include "Rand.h"

int main(){
	
	double a, b, c, d;
	
	LCG lcg(1234);
	MRG mrg(1234);
	CMRG cmrg(1234);
	FIB fib(1234);

	FILE *f_lcg = fopen("./results/lcg.dat", "w");
	FILE *f_mrg = fopen("./results/mrg.dat", "w");
	FILE *f_cmrg = fopen("./results/cmrg.dat", "w");
	FILE *f_fib = fopen("./results/fib.dat", "w");

	for(int i=0;i<10000;i++){
		// Generate using LCG
		a = lcg.uniform();
		//std::cout << "int" << a << std::endl;
		fprintf(f_lcg, "%f\n", a);

		b = mrg.uniform();
		//std::cout << "double" << b << std::endl;
		fprintf(f_mrg, "%f\n", b);

		c = cmrg.uniform();
		fprintf(f_cmrg, "%f\n", c);

		d = fib.uniform();
		fprintf(f_fib, "%f\n", d);
	}

	fclose(f_lcg);
	fclose(f_mrg);
	fclose(f_cmrg);
	fclose(f_fib);
	
//	printf("ullmax : %llu\n", ULLONG_MAX);
	return 0;
}
