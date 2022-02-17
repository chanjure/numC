#include <iostream>
#include <limits.h>
#include "Rand.h"

int main(){
	
	double a, b;
	
	LCG lcg(123);
	MRG mrg(123);

	FILE *f_lcg = fopen("./results/lcg.dat", "w");
	FILE *f_mrg = fopen("./results/mrg.dat", "w");

	for(int i=0;i<1000;i++){
		// Generate using LCG
		a = lcg.uniform();
		//std::cout << "int" << a << std::endl;
		fprintf(f_lcg, "%f\n", a);

		b = mrg.uniform();
		//std::cout << "double" << b << std::endl;
		fprintf(f_mrg, "%f\n", b);
	}

	fclose(f_lcg);
	fclose(f_mrg);
	
//	printf("ullmax : %llu\n", ULLONG_MAX);
	return 0;
}
