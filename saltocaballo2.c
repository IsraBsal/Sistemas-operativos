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
    int *total = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
               MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	int tid;
	int n;
    int i, j, k; //Contadores para irnos moviendo
    int **tablero;
   
    pid_t pid;
    FILE *fp; 
    
    if(argc!=2){
        printf("Error, ejectutar como ./ejecutable <Tam tablero>, por ejemplo:\n./saltos 7\n");
    }

	printf("Soy el proceso h1 %d \n",getpid());
    n= atoi(argv[1]);
    //Inicializa el tablero
    tablero = (int **)malloc(sizeof(int *)*n);
    for(i=0;i<n;i++)
     tablero[i]=(int *)malloc(sizeof(int)*n);
    //Termina inicializacion del tablero
	
    for(int hijos=0; hijos<n;hijos++){
	    tid=fork();

	    if(tid!=0){ //Parte del abanico que funciona
            //sleep(2);
            //wait();
            //printf("Totales %d",total);
        }
        
        else{
            printf("Soy el h%d: %d y mi papa es: %d \n",hijos+2,getpid(),getppid());
            //Codigo que debe ejecutar cada hijo
            for(j=0;j<n;j++){
                for(k=0;k<n;k++){
                
                    //printf("pid %d\n",getppid());
                    inicializa(tablero,n);
                    tablero[hijos][k] = 1;
                    soluciones=backtrackCaballos(tablero,hijos,k,2,n);
                    *total=*total+soluciones;
                    //printf("Soluciones en %d %d con pid %d = %d\n",j,k,getpid(),soluciones);
                    //printf("Parcial de soluciones de todo el tablero = %d con pid %d \n",total,getpid());
                    char cadena[40];
                    char cadena2[58];
                    sprintf(cadena,"\nSoluciones en %d %d con pid %d = %d\n",hijos,k,getpid(),soluciones);
                    sprintf(cadena2,"\nParcial de soluciones de todo el tablero = %d con pid %d \n",*total,getpid());
                    fp = fopen ( "fichero.txt", "a" );
                    fwrite(cadena,sizeof(char),sizeof(cadena),fp);
                    fwrite(cadena2,sizeof(char),sizeof(cadena2),fp);
                    fclose(fp);
                    //j++;
                    //sleep(2);
                    //exit(0);
                            

                }
                
                //sleep(2);
                exit(1);
                
                
            }
            
            


        }
	}

    printf("todas las soluciones= %d",*total);
    munmap(total, sizeof(int));
    //sleep(1);
    return 0;
}
