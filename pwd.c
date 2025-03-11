#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define SIZE 1024

int pwd_main() {
  
    char buff[SIZE];
    if(getcwd(buff,SIZE) ==NULL){
        
        return errno;
    }
    if(write(1,buff,strlen(buff))<0) {
       write(2,"\033[1;31m Couldn't write the directory \033[0m \n",
       strlen("\033[1;31m Couldn't write the directory \033[0m \n"));
       return errno;
    }


    
}
