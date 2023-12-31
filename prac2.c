//Crida de llibreries
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Constant
#define N 512

//Variables globals
float Mat[N][N];
float MatDD[N][N];
float V1[N];
float V2[N];
float V3[N];

//Funció predefinida per omplir la matriu
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

//Primera funció
void PrintVect(float vect[N], int from, int numel) {
        for(int i = from; i < numel+1; i++) {
                printf("%.7f ", vect[i]);
        }
        printf("\n");
}

//Segona funció
void PrintRow( float Mat[N][N], int row, int from, int numel ){
        for(int i = from; i < numel+1; i++) {
                printf("%.7f ", Mat[row][i]);
        }
        printf("\n");
}

//Tercera funció
void MultEscalar( float vect[N], float vectres[N], float alfa ){
        for(int i = 0; i < N; i++) {
                vectres[i] = alfa * vect[i];
        }
}

//Quarta funció
float Scalar( float vect1[N], float vect2[N] ){
        float sumatori = 0;
        for(int i = 0; i < N; i++) {
                sumatori +=  (vect1[i] * vect2[i]);
        }
        return sumatori;
}

//Cinquena funció
float Magnitude( float vect[N] ){
        float elevado = 0;
        float sumatori = 0;
        for(int i = 0; i < N; i++) {
                elevado = (vect[i]* vect[i]);
                sumatori = sumatori + elevado;
        }
        float modulo = sqrt(sumatori);
        return modulo;
}

//Sisena funció
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

//Setena funció
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

//Vuitena funció
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

//Novena funció
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

//Dècima funció
float NormFrobenius(float M[N][N]) {
        float sumatorio = 0;
        for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                        sumatorio += M[i][j] * M[i][j];
                }
        }
        return sqrt(sumatorio);
}

//Onzena funció
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

//Dotzena funció
int Jacobi(float M[N][N], float vect[N], float vectres[N], unsigned iter) {
        if (!DiagonalDom(M)) {
                return 0; // No se puede aplicar el método de Jacobi
        }

        float S[N][N];
        float T[N][N];
        float xk[N];
        int i, j, k;

        for (i = 0; i < N; i++) {
                xk[i] = vect[i];
        }

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        if (i == j) {
                                S[i][j] = M[i][j];
                                T[i][j] = 0.0;
                        } else {
                                S[i][j] = 0.0;
                                T[i][j] = -M[i][j];
                        }
                }
        }

        for (k = 0; k < iter; k++) {
                for (i = 0; i < N; i++) {
                        float sum = 0.0;
                        for (j = 0; j < N; j++) {
                                if (i != j) {
                                        sum += T[i][j] * xk[j];
                                }
                        }
                        vectres[i] = (1.0 / S[i][i]) * (vect[i] - sum);
                }
                for (i = 0; i < N; i++) {
                        xk[i] = vectres[i];
                }
        }

        return 1; // El método de Jacobi se ha aplicado con éxito
}


//Programa Principal
int main() {
        InitData();

        //Comprovació A
        printf("V1 del 0 al 9 i del 256 al 265:\n");
        PrintVect(V1, 0, 9);
        PrintVect(V1, 256, 265);
        printf("\n");

        printf("V2 del 0 al 9 i del 256 al 265:\n");
        PrintVect(V2, 0, 9);
        PrintVect(V2, 256, 265);
        printf("\n");

        printf("V3 del 0 al 9 i del 256 al 265:\n");
        PrintVect(V3, 0, 9);
        PrintVect(V3, 256, 265);
        printf("\n");


        //Comprovació B
        printf("Mat fila 0 i fila 100 del 0 al 9:\n");
        PrintRow(Mat, 0, 0, 9);
        PrintRow(Mat, 100, 0, 9);
        printf("\n");


        //Comprovació C
        printf("MatDD fila 0 i fila 100 del 0 al 9:\n");
        PrintRow(MatDD, 0, 0, 9);
        PrintRow(MatDD, 100, 95, 104);
        printf("\n");


        //Comprovación D
        float norma_infMat = Infininorm(Mat);
        printf("Infininorma de Mat = %.7f\n", norma_infMat);

        float norma_unoMat = OneNorm(Mat);
        printf("Norma ú de Mat = %.7f\n", norma_unoMat);

        float norma_frobeniusMat = NormFrobenius(Mat);
        printf("Norma de Frobenius de Mat = %.7f\n", norma_frobeniusMat);

        if (DiagonalDom(Mat)) {
                printf("La matriz Mat és diagonal dominant.\n");
        } else {
                printf("La matriz Mat no és diagonal dominant.\n");
        }
        printf("\n");

        float norma_infMatDD = Infininorm(MatDD);
        printf("Infininorma de MatDD = %.7f\n", norma_infMatDD);

        float norma_unoMatDD = OneNorm(MatDD);
        printf("Norma ú de MatDD = %.7f\n", norma_unoMatDD);

        float norma_frobeniusMatDD = NormFrobenius(MatDD);
        printf("Norma de Frobenius de MatDD = %.7f\n", norma_frobeniusMatDD);

        if (DiagonalDom(MatDD)) {
                printf("La matriz MatDD és diagonal dominant.\n");
        } else {
                printf("La matriz MatDD no és diagonal dominant.\n");
        }
        printf("\n");


        //Comprovació E
        printf("Escalar <V1,V2> = ");
        float escalar1 = Scalar(V1, V2);
        printf("%.7f ",escalar1);
        printf("\n");

        printf("Escalar <V1,V3> = ");
        float escalar2 = Scalar(V1, V3);
        printf("%.7f ",escalar2);
        printf("\n");

        printf("Escalar <V2,V3> = ");
        float escalar3 = Scalar(V2, V3);
        printf("%.7f ",escalar3);
        printf("\n");
        printf("\n");

        //Comprovació F
        printf("Magnitud V1 = ");
        float magnitud1 = Magnitude(V1);
        printf("%.7f ",magnitud1);
        printf("\n");

        printf("Magnitud V2 = ");
        float magnitud2 = Magnitude(V2);
        printf("%.7f ",magnitud2);
        printf("\n");

        printf("Magnitud V3 = ");
        float magnitud3 = Magnitude(V3);
        printf("%.7f ",magnitud3);
        printf("\n");
        printf("\n");


        //Comprovació G
        int ontogonal = Ortogonal(V1, V2);
        if (ontogonal == 1){
                printf("V1 i V2 són ontogonals\n");
        }
        if (ontogonal == 0){
                printf("V1 i V2 no són ontogonals\\n");
        }
        printf("\n");


        //Comprovació H
        float V3x2[N];
        MultEscalar(V3, V3x2, 2.0);
        printf("Els elements 0 al 9 i 256 al 265 del resultat de multiplicar V3x2.0 són:\n");
        PrintVect(V3x2, 0, 9);
        PrintVect(V3x2, 256, 265);
        printf("\n");

        //Comprovació I
        float vector_proyeccion[N];

        printf("Els elements 0 a 9 del resultat de la projecció de V1 sobre V2 són:");
        Projection(V1, V2, vector_proyeccion);
        printf("\n");
        for (int i = 0; i < 10; i++) {
                printf("%.7f ", vector_proyeccion[i]);
                        }
        printf("\n");

        printf("Els elements 0 a 9 del resultat de la projecció de V2 sobre V3 són:");
        Projection(V2, V3, vector_proyeccion);
        printf("\n");
        for (int i = 0; i < 10; i++) {
                printf("%.7f ", vector_proyeccion[i]);
                        }
        printf("\n");
        printf("\n");

        //Comprovació J
        float solucio1[N];
         int result1 = Jacobi(MatDD, V3, solucio1, 2);

        if (result1) {
                printf("Resultado de Jacobi:\n");
                PrintVect(solucio1, 0, 9);
                //for (int i = 0; i < N; i++) {
                //      printf("%f\n",solucio1[i]);
                //}
        } else {
                printf("La matriz no es diagonalmente dominante, no se puede aplicar Jacobi.\n");
        }

        float solucio1000[N];
        int result1000 = Jacobi(MatDD, V3, solucio1000, 1001);

        if (result1000) {
                printf("Resultado de Jacobi:\n");
                PrintVect(solucio1000, 0, 9);
                //for (int i = 0; i < N; i++) {
                //      printf("%f\n",solucio1000[i]);
                //}
        } else {
                printf("La matriz no es diagonalmente dominante, no se puede aplicar Jacobi.\n");
        }
