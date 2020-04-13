/*This is the main program which will take input of filename from the commandline and call the handler function to execute further. */
#include"Header.h"
#include"Handler.c"

int main(int argc,int* argv[]){
  char* filename;
  if ( argc != 2 ){
        printf( "missing filename");
        return(1);
    }
    else{
        Handler((char*)argv[1]);
    }
    return 0;
}
