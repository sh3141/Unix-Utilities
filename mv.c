#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define COUNT 100
int cp_main(int argc, char *argv[]) {
        if(argc !=3){
        fprintf(stderr, "\033[0m Usage: %s source file destination directory \033[0m",argv[0]);
        return errno;
        
    }
    int fd_src = open(argv[1],O_RDONLY);
    if(fd_src <0){
        write(2,"\033[1;31m Couldn't open the source file \033[0m\n",strlen("\033[1;31m Couldn't open the source file \033[0m\n"));
        return errno;
    }
    
    int fd_dest = open(argv[2],O_CREAT|O_WRONLY|O_TRUNC,0644);
    if(fd_dest <0){
        write(2,"\033[1;31m Couldn't open the destination file \033[0m\n",strlen("\033[1;31m Couldn't open the destination file \033[0m\n"));
        return errno;
    }
    
    
    char buff[COUNT];
    int bytes_read ;
    while((bytes_read = read(fd_src,buff,COUNT)) && (bytes_read >0)){
        if(write(fd_dest,buff,bytes_read)<0){
            write(2,"\033[1;31m Couldn't write to the destination file \033[0m \n",strlen("\033[1;31m Couldn't write to the destination file \033[0m \n"));
            return errno;

        }
    }
    if(bytes_read<0){
        write(2,"\033[1;31m Couldn't read the source file \033[0m \n",strlen("\033[1;31m Couldn't read the source file \033[0m \n"));
            return errno;
    }
    close(fd_dest);
    close(fd_src);
    if(unlink(argv[1])!=0){
      write(2,"\033[1;31m Couldn't remove the source file \033[0m \n",strlen("\033[1;31m Couldn't remove the source file \033[0m \n"));
      return errno;
    }
    
}
