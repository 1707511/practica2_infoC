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
//no funciona bien, compila pero da un resultado raro
float Magnitude( float vect[N] ){
        float elevado = 0;
        float sumatori = 0;
        for(int i = 0; i < N; i++) {
                elevado = pow(vect[i], 2);
                sumatori = sumatori + elevado;
                }
        float modulo = pow(sumatori, (1/2));
        printf("%.2f ",(modulo));
        printf("\n");
        }

int main() {
        float vector[N] = {1.0, 2.0, 3.0, 4.0, 5.0};
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

}
