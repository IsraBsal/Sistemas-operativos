#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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



void ordenar(void *direccion, int num_elementos, size_t sbytes, int (*comp)(void *a, void *b), void (*intercambio)(void *a, void *b)) {

    int i,j;

   for(i=1;i<num_elementos; i++){
      for(j=0; j<num_elementos-i; j++)
      {

            if (comp((char*)direccion + sbytes * j, (char*)direccion + sbytes * (j+1))) {
                intercambio((char*)direccion + sbytes * j, (char*)direccion + sbytes * (j+1));

            }

      }
   }

}



int main()
{
    int array1[] = {3, 5, 8, 9, 1, 2, 4, 7, 6, 0}; 
    int num_elementos1 = 10; 
    void *direccion1;

    double array2[] = {3.0, 5.0, 8.0, 9.0, 1.0, 2.0, 4.0, 7.0, 6.0, 0.0}; 
    int num_elementos2 = 10;
    void *direccion2;

    if(fork()){

       direccion1 = array1;

       ordenar(direccion1, num_elementos1, sizeof(int), compInt, intercambioInt);

       for (int i = 0; i < num_elementos1; ++i) { 
           printf("%d ", array1[i]); 
       }
       printf("\n\n");
    }else{
       direccion2 = array2;

       ordenar(direccion2, num_elementos2, sizeof(double), compDouble, intercambioDouble);

       for (int i = 0; i < num_elementos2; ++i) { 
          printf("%0.2lf ", array2[i]); 
       }
       printf("\n\n");
    }

    return 0;
}
