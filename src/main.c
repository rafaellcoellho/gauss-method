#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.000001

double **allocateMatrix(int lines, int coluns)
{
	double **matrix;
	
	matrix = malloc(sizeof(double *) * lines);
	if(matrix == NULL)
		return NULL;
	
	for(int i=0; i<lines; i++){
		matrix[i] = malloc(sizeof(double) * coluns);
		if(matrix[i] == NULL){
			for(int j=0; j<i; j++)
				free(matrix[j]);
			free(matrix);
			return NULL;
		}
	}

	return matrix;
}

void readMatrix(double **matrix, int lines, int coluns)
{
	for(int i=0; i<lines; i++){
		for(int j=0; j<coluns; j++){
			printf("M[%d][%d]=",i+1,j+1);
			scanf("%lf", &matrix[i][j]);
		}
	}
}

void printMatrix(double **matrix, int lines, int coluns)
{
	for(int i=0; i<lines; i++){
		printf("\n");
		for(int j=0; j<coluns; j++){
			printf("%10.3lf", matrix[i][j]);
		}
	}
}

int sRetro(double **m, int n, double x[]){
	int i,j;
	int type = 0;
	double sum;
	for(i=n-1; i>=0; i--){
		sum = 0;
		for(j=i+1;j<n;j++){
			sum += m[i][j]*x[j];
		}
		if(m[i][i]==0){
			if(fabs(m[i][n]-sum) < EPSILON){
				x[i] = 0;
				type = 0;
			}else{
				return 2;
			}
		}else{
			x[i] = (m[i][j]-sum)/m[i][i];
		}
	}
	return type;
}

void swapLines(double **m, int n, int indexLine1, int indexLine2){
	double aux;
	for(int i=0; i<n;i++){
		aux = m[indexLine1][i];
		m[indexLine1][i] = m[indexLine2][i];
		m[indexLine2][i] = aux;
	}
}

void gaussianElimination(double **m, int n)
{
	int i,j,k;
	for(i=0;i<(n-1);i++){
		if(m[i][i] == 0){
			j = i+1;
			while(j<n && m[j][i]==0)
				j++;
			if(j<n){
				swapLines(m, n, j, i);
			}
		}else{
			for(j=i+1; j<n; j++){
				double mult = -m[j][i]/m[i][i];
				m[j][i]=0;
				for(k=0;k<n+1;k++)
					m[j][k] = m[j][k] + mult*m[i][k];
			}
		}
	}
}

int main(void)
{
	int n;
	double **m,*x;

	printf("Quantidade de variaveis: ");
	scanf("%d", &n);

	m = allocateMatrix(n, n+1);
	x = malloc(sizeof(double) * n);
	if(m==NULL || x==NULL){
		printf("Deu pau!\nFalta de Memoria\n");
		return 1;
	}

	readMatrix(m,n,n+1);
	printMatrix(m,n,n+1);

	gaussianElimination(m,n);
	printMatrix(m,n,n+1);
	// int type = sRetro(m,n,x);
	// if(type==2){
	// 	printf("\nSL IMCOMPATIVEL\n");
	// }else{
	// 	printf("\nSL %sDETERMINADO\n", type==1 ? "IN":"");
	// 	for(int i=0;i<n;i++){
	// 		printf("x[%d]=%10.3lf\n", i+1, x[i]);
	// 	}
	// }
	return 0;
}