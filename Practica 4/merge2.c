//Hail CEUAMI
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>
#define true 1
#define false 0

/*Metodos desarrollados por el profesor*/
int compInt(void *a, void *b) 
{
    if (*(int*)(a) <= *(int*)(b)) { 
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
    if (*(double*)(a) <= *(double*)(b)) { 
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
/*------------------------------------------*/
int compChar(void *a, void *b) 
{
    if (*(char*)(a) <= *(char*)(b)) { 
       return true; 
    }     
    return false; 
}

void intercambioChar(void *a, void *b) 
{
    int aux; 

    aux = *(char*)(a);
    *(char*)(a) = *(char*)(b); 
    *(char*)(b) = aux;
}

int compLong(void *a, void *b) 
{
    if (*(long*)(a) <= *(long*)(b)) { 
       return true; 
    }     
    return false; 
}

void intercambioLong(void *a, void *b) 
{
    int aux; 

    aux = *(long*)(a);
    *(long*)(a) = *(long*)(b); 
    *(long*)(b) = aux;
}

/*--------------------------------------------*/


/**************************************************/

/*Metodos de ordenamiento*/
void merge(void *direccion,int l,int m,int r,size_t sbytes, int (*comp)(void *a, void *b), void (*intercambio)(void *a, void *b)){
    int i,j,k;
    int n1=(m-l+1); 
    int n2=(r-m);

    //Creando los arreglos temporales
    void *direccion1;
    void *direccion2;
    
    
    /*----------------------------*/
    
        char L[n1*sbytes],R[n2*sbytes];
        direccion1=L;
        direccion2=R;
        //Copiamos los datos para los arreglos L y R
        for(i=0;i<n1;i++){
            //printf("Llenar arreglo L\n");
            intercambio(direccion1 + sbytes * i, (char*)direccion + sbytes*(l+i));//cambiar a el arrelgo en tal posicion 
            }
        for(j=0;j<n2;j++){
            //printf("Llenar arreglo R\n");
            intercambio(direccion2 + sbytes * j, (char*)direccion + sbytes * (m+j+1));
        }
        /*-----------------------------------*/
        i=0;
        j=0;
        k=l;
        /*Comienza la mezcla de los arreglos de izquierda y derecha*/
        while (i<n1 && j<n2){
            if(comp(direccion1 + sbytes * i, direccion2 + sbytes * j)){
                //printf("Entre en if de la mezcla\n");
                intercambio((char*)direccion + sbytes * k, direccion1 + sbytes * i);
                i++;
            }
            else{
                //printf("Entre en else de la mezcla/n");
                intercambio((char*)direccion + sbytes * k, direccion2 + sbytes * j);
                j++;
            }
            k++;
        }
        /*Termina la mezcla*/

        /*Copiando el resto de elementos en el arreglo izquierdo si es que hay*/
        while (i<n1){
            intercambio((char*)direccion + sbytes * k,direccion1 + sbytes * i);
            i++;
            k++;
        }
        /*Copiando el resto de elementos en el arreglo derecho si es que hay*/
        while (j<n2){
            intercambio((char*)direccion + sbytes * k, direccion2 + sbytes * j);
            j++;
            k++;
        }
        /*------------*/
    
}

void mergesort(void *direccion,int l,int r,size_t sbytes,int (*comp)(void *a, void *b), void (*intercambio)(void *a, void *b)){
    if(l<r){
        int m=l+(r-l)/2;
        mergesort(direccion,l,m,sbytes,comp,intercambio);
        mergesort(direccion,m+1,r,sbytes,comp,intercambio);
        merge(direccion,l,m,r,sbytes,comp,intercambio);
    }
}
/*------------------------------------------------------*/

/*Comienza main*/
int main(){
    int array1[] = {3, 5, 8, 9, 1, 2, 4, 7, 6, 0}; 
    int num_elementos1 = 10; 
    void *direccion1;

    double array2[] = {3.0, 5.0, 8.0, 9.0, 1.0, 2.0, 4.0, 7.0, 6.0, 0.0}; 
    int num_elementos2 = 10;
    void *direccion2;

    long array3[] = {3, 5, 8, 9, 1, 2, 4, 7, 6, 0}; 
    int num_elementos3 = 10; 
    void *direccion3;

    char array4[] = {'e', 'd', 'b', 'a', 'c', 'g', 'f', 'i', 'h', 'j'}; 
    int num_elementos4 = 10; 
    void *direccion4;

    if(fork()){
        direccion1 = array1;
        mergesort(direccion1,0, (num_elementos1)-1, sizeof(int), compInt, intercambioInt);   
        for (int i = 0; i < num_elementos1; ++i) { 
           printf("%d ", array1[i]); 
        }
        printf("\n\n");

        direccion3 = array3;
        mergesort(direccion3,0, (num_elementos1)-1, sizeof(long), compLong, intercambioLong);   
        for (int i = 0; i < num_elementos1; ++i) { 
           printf("%ld ", array3[i]); 
        }
        printf("\n\n");

    }
    else{
        direccion2 = array2;
        mergesort(direccion2, 0,(num_elementos2)-1 ,sizeof(double), compDouble, intercambioDouble);
        for (int i = 0; i < num_elementos2; ++i) { 
          printf("%0.1lf ", array2[i]); 
        }
        printf("\n\n");

        direccion4 = array4;
        mergesort(direccion4,0, (num_elementos1)-1, sizeof(char), compChar, intercambioChar);   
        for (int i = 0; i < num_elementos1; ++i) { 
           printf("%c", array4[i]); 
        }
        printf("\n\n");
    }

    return 0;
}
