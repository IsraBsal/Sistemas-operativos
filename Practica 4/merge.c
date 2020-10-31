#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <float.h>

#define true 1
#define false 0

int compInt(void *a, void *b) 
{
    if (*(int*)(a) > *(int*)(b)) { 
       return true; 
    }     
    return false; 
}

void intercambioInt(void *a, void *b) 
{
    int aux; 

    aux = *(int*)(a);
    *(int*)(a) = *(int*)(b); 
    *(int*)(b) = aux;
}

int compDouble(void *a, void *b) 
{
    if (*(double*)(a) > *(double*)(b)) { 
       return true; 
    }     
    return false; 
}

void intercambioDouble(void *a, void *b) 
{
    int aux; 

    aux = *(double*)(a);
    *(double*)(a) = *(double*)(b); 
    *(double*)(b) = aux;
}

//cambio
void merge(void *direccion,int l,int m,int r,size_t sbytes, int (*comp)(void *a, void *b), void (*intercambio)(void *a, void *b)){
    int i,j,k;//
    int n1=m-l+1;//
    int n2=r-m;//
    void *direccion1;//
    void *direccion2;//
    printf("%d sysbytes\n",sbytes);
    //if(sbytes==sizeof(int)){//
        int L[n1],R[n2];//
        direccion1=L;//
        direccion2=R;//
        //Copiamos los datos para los arreglos L y R
        for(i=0;i<n1;i++){//
            printf("Llenar arreglo L\n");//
            //L[i] = (char*)direccion+sbytes*(l+i);
            intercambio((char*)direccion1 + sbytes * i, (char*)direccion + sbytes * (l+i));//
        }
        for(j=0;j<n2;j++){//
            printf("Llenar arreglo R\n");//
            //R[j] = (char*)direccion+sbytes*(m+j+1);
            intercambio((char*)direccion2 + sbytes * j, (char*)direccion + sbytes * (m+j+1));//
        }
        printf("Arreglo L copia\n");
        for (int i = 0; i < n1; ++i) { 
           printf("%d ", L[i]); 
        }
        printf("\n\n");
        printf("Arreglo R copia\n");
        for (int i = 0; i < n2; ++i) { 
           printf("%d ", R[i]); 
        }
        printf("\n\n");
        void *max_integer;
        int max[1]={INT_MAX};
        max_integer=max;
        //L[n1] = INT_MAX;
        //R[n2] = INT_MAX;

        intercambio((char*)direccion1 + sbytes * (n1),(char*)max_integer + sbytes * (0));
        intercambio((char*)direccion2 + sbytes * (n2),(char*)max_integer + sbytes * (0));
        
        i=0;
        j=0;
       
        for(k=l;k<r;k++){
            if(comp((char*)direccion1 + sbytes * i, (char*)direccion2 + sbytes * j)){
                intercambio((char*)direccion + sbytes * k, (char*)direccion1 + sbytes * i);
                i=i+1;
            }
            else{
                intercambio((char*)direccion + sbytes * k, (char*)direccion2 + sbytes * j);
                j=j+1;
            }
        }
        printf("Termine intercambio ints\n");
    //}
    /*else{
        double L[n1],R[n2];
        direccion1=L;
        direccion2=R;
        //Copiamos los datos para los arreglos L y R
        for(i=0;i<n1;i++){
            printf("Llenar arreglo L\n");
            intercambio((char*)direccion1 + sbytes * i, (char*)direccion + sbytes * (l+i-2));
        }
        for(j=0;j<n2;j++){
            printf("Llenar arreglo R\n");
            intercambio((char*)direccion2 + sbytes * j, (char*)direccion + sbytes * (m+j-1));
        }

        intercambio((char*)direccion1 + sbytes * (n1), INT_MAX);
        intercambio((char*)direccion2 + sbytes * (n2), INT_MAX);
        printf("Termine intercambio doubles\n");
        i=0;
        j=0;
        
        for(k=l;k<r;k++){
            if(comp((char*)direccion1 + sbytes * i, (char*)direccion2 + sbytes * (j))){
                intercambio((char*)direccion + sbytes * k, (char*)direccion1 + sbytes * (i));
                i=i+1;
            }
            else{
                intercambio((char*)direccion + sbytes * k, (char*)direccion2 + sbytes * (j));
                j=j+1;
            }
        }
    }*/
}

//Merge bueno
void mergesort(void *direccion,int l,int r,size_t sbytes,int (*comp)(void *a, void *b), void (*intercambio)(void *a, void *b)){
    if(l<r){
        printf("Valor de l=%d\n",l);
        printf("Valor de r=%d\n",r);
        int m=floor((l+r)/2);
        mergesort(direccion,l,m,sbytes,comp,intercambio);
        mergesort(direccion,m+1,r,sbytes,comp,intercambio);
        merge(direccion,l,m,r,sbytes,comp,intercambio);//LLenar    
    }
}

int main()
{
    /*int array1[] = {3, 5, 8, 9, 1, 2, 4, 7, 6, 0}; 
    */int array1[] = {3, 0, 2, 1}; 
    int num_elementos1 = sizeof(array1)/sizeof(array1[0]); 
    void *direccion1;

    double array2[] = {3.0, 5.0, 8.0, 9.0, 1.0, 2.0, 4.0, 7.0, 6.0, 0.0}; 
    int num_elementos2 = sizeof(array2)/sizeof(array2[0]);;
    void *direccion2;

    //printf("Num elementos 1=%d\n",num_elementos1);
    //printf("Num elementos 2=%d\n",num_elementos2);

    if(fork()){

       direccion1 = array1;

       mergesort(direccion1,0, (num_elementos1)-1, sizeof(int), compInt, intercambioInt);

       for (int i = 0; i < num_elementos1; ++i) { 
           printf("%d ", array1[i]); 
       }
       printf("\n\n");
    }/*else{
       direccion2 = array2;

       mergesort(direccion2, 0,(num_elementos2)-1 ,sizeof(double), compDouble, intercambioDouble);

       for (int i = 0; i < num_elementos2; ++i) { 
          printf("%0.2lf ", array2[i]); 
       }
       printf("\n\n");
    }*/

    return 0;
}
