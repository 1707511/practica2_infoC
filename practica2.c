#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 

#define N 5

float  Mat[N][N]; 

float MatDD[N][N]; 

int V1[N]; 

int V2[N]; 

int V3[N]; 

void InitData(){
	int i,j;
	srand(4422543);
	for( i = 0; i < N; i++ )
		 for( j = 0; j < N; j++ ){
			  Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
			  if ( (abs(i - j) <= 3) && (i != j))
				    MatDD [i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX));
			  else if ( i == j )
				     MatDD [i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX)));
			  else MatDD[i][j] = 0.0;
			      }
	for( i = 0; i < N; i++ ){
		 V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
		 V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
		 V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
	}

}

void PrintVect(float vect[N], int from, int numel) {
	for(int i = from; i < from + numel; i++) {
	     	printf("%.2f ", vect[i]);
	       }
	        printf("\n");
	}
//falta añadirle algo al row
void PrintRow( float Mat[N][N], int row, int from, int numel ){
	for(int i = from; i < from + numel; i++) {
		 printf("%.2f ", Mat[row][i]);
			               }
	          printf("\n");
		        
			}

void MultEscalar( float vect[N], float vectres[N], float alfa ){
	for(int i = 0; i < N; i++) {
		
		vectres[i] = alfa * vect[i];
		 printf("%.2f ", vectres[i]);
		}
		 printf("\n");
	}

float Scalar( float vect1[N], float vect2[N] ){
	for(int i = 0; i < N; i++) {
		
		printf("%.2f ", (vect1[i] * vect2[i]));
				                 }
                 printf("\n");
		         }

float Magnitude( float vect[N] ){
	float elevado = 0;
	float sumatori = 0;
	for(int i = 0; i < N; i++) {
		elevado = (vect[i]* vect[i]);
		sumatori = sumatori + elevado;
		}
	float modulo = sqrt(sumatori);
	printf("%.2f ",(modulo));
	printf("\n");
	}
//da 1 y deberia dar 7,4


int Ortogonal( float vect1[N], float vect2[N] ){
	float producto = 0;
	for(int i = 0; i<N; i++){
		producto += vect1[i]*vect2[i];
	}
	if (producto == 0){
		
		return 1;
	}
	else{
		return 0;
	}

}

void Projection(float vect1[N], float vect2[N], float vectres[N]) { 
	    float producto = 0; 
	    float magnitud = 0; 
	    for (int i = 0; i < N; i++) {
		   producto += vect1[i] * vect2[i]; 
				   } 
	    for (int i = 0; i < N; i++) { 
		   magnitud += vect2[i] * vect2[i]; 
					    } 
	    magnitud = sqrt(magnitud);
	    for (int i = 0; i < N; i++) {
		    vectres[i] = (producto / magnitud) * vect2[i]; 
				 } 

} 

float Infininorm(float M[N][N]) {
	float max_sum = 0;
	for (int i = 0; i < N; i++) {
		float row_sum = 0;
		for (int j = 0; j < N; j++) {
			row_sum += fabs(M[i][j]);
		}
	       	if (row_sum > max_sum) {
		       	max_sum = row_sum;
		}
	}

	return max_sum;
}

float OneNorm(float A[N][N]) { 
	float max_norm = 0;
	for (int j = 0; j < N; j++){
		float column_sum = 0;
		for (int i = 0; i < N; i++) {
			column_sum += fabs(A[i][j]);
			}
		if (column_sum > max_norm) {
			max_norm = column_sum;
		}
	}
	return max_norm; 
}

float NormFrobenius(float M[N][N]) {
	float sumatorio = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sumatorio += M[i][j] * M[i][j];
				            }
				    }
	return sqrt(sumatorio);
}

int DiagonalDom(float M[N][N]) {
	for (int i = 0; i < N; i++) {
		float elemento_diagonal = fabs(M[i][i]);
		float fila_sum = 0;
		for (int j = 0; j < N; j++) {
			if (j != i) {
				fila_sum += fabs(M[i][j]);

			}
	        }
		if (elemento_diagonal < fila_sum) {
			return 0;
		}
	}
	return 1;
}

int main() {
	float vector[N] = {1.0, 2.0, 3.0, 4.0, 5.0};
	float vectP1[N] = {-2,2};
	float vectP2[N] = {2, 2};
		//int from = 1;
	//int numel = 5;
	//int row = 1;
	float vect1[N] = {1.0, 2.0, 3.0, 4.0, 5.0};

	float vectres[N];
	float  Mat[N][N] = {{1.0, 2.0, 3.0},{1.0, 2.0, 3.0},{1.0, 2.0, 3.0}};
	PrintVect(vector, 1, 4);
	PrintRow(Mat, 2, 0, 2);
	MultEscalar(vector, vectres, 2);
	Scalar(vect1, vector);
	Magnitude(vector);
	int X = Ortogonal(vectP1, vectP2);
	if (X == 1){
		printf("1\n");
	}
	if (X==0){
		printf("0\n");
	}
	float vector_proyeccion[N]; 
	Projection(vector, vect1, vector_proyeccion); 
	printf("Vector Proyección: "); 
	for (int i = 0; i < N; i++) {
	       	printf("%.2f ", vector_proyeccion[i]); 
		        } 
	printf("\n"); 
	float norma_inf = Infininorm(Mat);
	printf("La infini-norma de la matriz es: %.2f\n", norma_inf);
	float norma_uno = OneNorm(Mat); 
	printf("Norma uno de la matriz: %.2f\n", norma_uno);
        float norma_frobenius = NormFrobenius(Mat);	
	printf("La norma de Frobenius de la matriz es: %.2f\n", norma_frobenius);
	if (DiagonalDom(Mat)) {
		printf("La matriz es diagonal dominante.\n");
	} else {
		printf("La matriz no es diagonal dominante.\n");
	}

}

