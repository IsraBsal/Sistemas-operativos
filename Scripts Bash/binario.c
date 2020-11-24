#include<stdlib.h>

main(int argc, char **argv){
    int i, n;

    n = atoi(argv[1]);

    for(i=0;i<(n-1);i++){
        switch(fork()){
            case 0:
                break;
            default:
                switch(fork()){
                    case 0:
                        break;
                    default:
                        sleep(2000);
                        break;
                }
        }
    }
    sleep(2000);
}