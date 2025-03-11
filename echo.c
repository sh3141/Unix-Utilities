#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LEN 100;
int echo_main(int argc, char *argv[]) {
    
    if(argc == 1){
        if(write(1,"\n",1)<0) {
            write(2,"\033[1;31m Couldn't write the output \033[0m \n",
            strlen("\033[1;31m Couldn't write the output \033[0m \n"));
            return errno;
        }
    }
    else{
        if(write(1,argv[1],strlen(argv[1]))<0) {
                write(2,"\033[1;31m Couldn't write the output \033[0m \n",
                 strlen("\033[1;31m Couldn't write the output \033[0m \n"));
                return errno;
            }
        for(int i=2;i<argc;i++){
            if(write(1," ",1)<0) {
                write(2,"\033[1;31m Couldn't write the output \033[0m \n",
                 strlen("\033[1;31m Couldn't write the output \033[0m \n"));
                return errno;
            }
            if(write(1,argv[i],strlen(argv[i]))<0) {
               write(2,"\033[1;31m Couldn't write the output \033[0m \n",
                strlen("\033[1;31m Couldn't write the output \033[0m \n"));
               return errno;
            }
        }
        if(write(1,"\n",1)<0) {
            write(2,"\033[1;31m Couldn't write the output \033[0m \n",
             strlen("\033[1;31m Couldn't write the output \033[0m \n"));
            return errno;
        }
    }
}
