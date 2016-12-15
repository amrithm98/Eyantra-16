#include <stdio.h>

int main() {
	FILE *fp,*n;
	fp = fopen("input","r");
	n = fopen("output","w");
	int x,y,z;
	float a,b,c[100];
	fscanf(fp,"%d",&x);
	fprintf(n,"%d,",x);
	for (int i = 0; i < x; i++) {
		fscanf(fp,"%d,%d",&y,&z);
		fprintf(n,"%d,%d,",y,z);
	}
	fprintf(n,"\n");
	fscanf(fp,"%d",&x);
	fprintf(n,"%d,",x);
	for (int i = 0; i < x; i++) {
		fscanf(fp,"%d %d %f",&y,&z,&c[i]);
		fprintf(n,"%d,%d,",y,z);
	}
	fprintf(n,"\n");
	for (int i = 0; i < x; i++) {
		fprintf(n,"%f,",c[i]);
	}
	return 0;
}
