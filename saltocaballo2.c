#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

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
  int n;
  int i, j, k;
  int **tablero;
  int soluciones=0, total=0;
  pid_t pid;

  if(argc!=2){
  
     printf("Error, ejectutar como ./ejecutable <Tam tablero>, por ejemplo:\n./saltos 7\n");
  }
     
  n= atoi(argv[1]);

  tablero = (int **)malloc(sizeof(int *)*n);
  for(i=0;i<n;i++)
     tablero[i]=(int *)malloc(sizeof(int)*n);
  
  pid=fork();
  for(j=0;j<n;j++){
    for(k=0;k<n;k++){
      if(pid==0){
        //printf("pid %d\n",getppid());
        inicializa(tablero,n);
        tablero[j][k] = 1;
        soluciones=backtrackCaballos(tablero,j,k,2,n);
        total=total+soluciones;
        printf("Soluciones en %d %d con pid %d = %d\n",j,k,getpid(),soluciones);
        printf("Parcial de soluciones de todo el tablero = %d con pid %d \n",total,getpid());
        char cadena[200];
        sprintf(cadena,"Soluciones en %d %d con pid %d = %d\n",j,k,getpid(),soluciones);
        FILE *fp;
 	    fp = fopen ( "fichero.txt", "a+" );
        fwrite(cadena,sizeof(char),sizeof(cadena),fp);
        pid=fork();
        sleep(1);
      }
    }
  }
  //printf("Total de soluciones %d con pid %d\n",total,getpid());
  
  return 0;
}
