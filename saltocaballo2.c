#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>

int soluciones=0;
int desplazamiento[8][2]={{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,1},{2,-1}};

void mostrar(int **tablero,int n){

   int i,j;
   for(i=0;i<n;i++){
      for(j=0;j<n;j++){
         printf("%2d ",tablero[i][j]);
      }
      printf("\n");
   }
   printf("\n");
}

void inicializa(int **tablero,int n){

   int i,j;
   for(i=0;i<n;i++){
      for(j=0;j<n;j++){
         tablero[i][j]=0;
      }
   }
}

int backtrackCaballos(int **tablero, int x, int y, int salto, int n){

   int nx;
   int ny;
   int i;
   int *aux;
   int soluciones=0;
   if(salto==((n*n)+1)){
      //mostrar(tablero,n);
      return 1;
   }
            
   for(i=0;i<8;i++){
      aux=desplazamiento[i];
      nx = x + aux[0];
      ny = y + aux[1];
 
      if(nx>=0 && ny>=0 && nx<n && ny<n && tablero[nx][ny]<1){
         tablero[nx][ny]=salto;         
         soluciones=soluciones+backtrackCaballos(tablero, nx, ny, salto+1,n);
         tablero[nx][ny]=0;      
      }
   }
   return soluciones;

}


int main(int argc, char **argv){
   int total = 0;
   //Internas del padre
   int hijos;
   int parcial=0;
   int final=0;
   //-------------
	int tid;
	int n;
   int i, j, k; 
   int **tablero;
   
   pid_t pid;
   FILE *fp; 
    
   if(argc!=2){
      printf("Error, ejectutar como ./ejecutable <Tam tablero>, por ejemplo:\n./saltos 7\n");
   }

	//printf("Soy el proceso h1 %d \n",getpid());
   n= atoi(argv[1]);
    
   //Inicializa el tablero
   tablero = (int **)malloc(sizeof(int *)*n);
   for(i=0;i<n;i++)
      tablero[i]=(int *)malloc(sizeof(int)*n);
   //Termina inicializacion del tablero
	

   //Abanico para crear a los hijos de un solo padre
   for(int hijos=0; hijos<n;hijos++){
	    tid=fork();

	    if(tid!=0){ 
            //Para esperar a los hijos, es codigo que ejcuta el padre
         }
        else{
           //Codigo que realiza cada hijo
           for(k=0;k<n;k++){
               inicializa(tablero,n);
               tablero[hijos][k] = 1;
               soluciones=backtrackCaballos(tablero,hijos,k,2,n);
               total=total+soluciones;
            } 
            char suma[10];
            char archivo[9];
            sprintf(archivo,"%d.txt",hijos);//Para nombrar al archivo
            sprintf(suma,"%d",total);//para escribir el valor que calculo el hijo en su archivo
            fp = fopen ( archivo, "w" );
            fputs(suma,fp);//Escribimos
            fclose(fp);
            exit(1);
         }
            //Termina codigo que realiza cada hijo y se muere
	}
   //Termina abanico

   //Similiar a JOIN De hilos, esperamos a que terminen todos los hijos
   for(j=0;j<n;j++){
      wait(NULL);
   }
   //Termina Join

   //Leemos cada archivo que el hijo crea
   for ( int z = 0; z < n; z++){
      char archivo[10];
      sprintf(archivo,"%d.txt",z);
      fp=fopen(archivo,"r");
      rewind(fp);
      fscanf(fp,"%d",&parcial);
      final=final+parcial;
      //printf("Padre %d, valor que leo del archivo= %d\n",getpid(),final);
      fclose(fp);
   }
   //Terminamos de leer 
   
   //El papa imprime la solcuion despues deleer todos los archivos de los hijos
    printf("todas las soluciones= %d",final);
    return 0;
}
