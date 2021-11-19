#include<iostream>

// File io utills
void readfile(const char* fname, double** x, double** y, int n_x=7, int n_y=200){
	
	FILE *data;
	char buff[255];
	std::string X = "X";
	std::string data_str = "DATA";

	int count=0;
	double temp=0.;

	data = fopen(fname,"r");
	
	while(fscanf(data,"%s",buff)!=EOF){
		if(!X.compare(buff)){
			for(int i=0;i<n_x;i++){
				fscanf(data, "%lf", &temp);
				*(*(x+i)+0) = temp;
			}
			continue;
		}
		
		if(!data_str.compare(buff)){
			fscanf(data, "%s",buff);
			continue;
		}

		for(int i=0;i<n_x;i++){
			fscanf(data,"%lf",&temp);
			*(*(y+i)+count) = temp;
		}
		count++;
	}

	fclose(data);

	/*for(int i=0;i<7;i++) printf("%8.5f\n",*(*(x+i)+0));
	for(int i=0;i<7;i++){
		for(int j=0;j<200;j++) printf("%8.5f\t",*(*(y+i)+j));
		printf("\n");
	}*/
}
