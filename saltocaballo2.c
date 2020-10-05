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
  FILE *fp;

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
        //printf("Soluciones en %d %d con pid %d = %d\n",j,k,getpid(),soluciones);
        //printf("Parcial de soluciones de todo el tablero = %d con pid %d \n",total,getpid());
        char cadena[40];
        char cadena2[58];
        sprintf(cadena,"\nSoluciones en %d %d con pid %d = %d\n",j,k,getpid(),soluciones);
        sprintf(cadena2,"\nParcial de soluciones de todo el tablero = %d con pid %d \n",total,getpid());
        fp = fopen ( "fichero.txt", "r+" );
        fwrite(cadena,sizeof(char),sizeof(cadena),fp);
        fwrite(cadena2,sizeof(char),sizeof(cadena2),fp);
        pid=fork();
        //sleep(1);
      }
      /*else{
            char cadena1[88];
            sprintf(cadena1,"\nParcial de soluciones de todo el tablero = %d con pid %d SOY EL PAPA Y ESTO ES EL FINAL\n",total,getpid());
            fp = fopen ( "fichero.txt", "r+" );
            fwrite(cadena1,sizeof(char),sizeof(cadena1),fp);
            
        }*/
    }
  }
  //printf("Total de soluciones %d con pid %d\n",total,getpid());
  fclose(fp);
  return 0;
}
