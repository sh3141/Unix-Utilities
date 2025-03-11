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
        fprintf(stderr,"\033[1;31m Couldn't open the source file due to %d \033[0m\n", errno);
        return errno;
    }

    int fd_dest = open(argv[2],O_CREAT|O_WRONLY|O_TRUNC,0644);
    if(fd_dest <0)
    {   if(errno == EISDIR){
                char* src_path =strdup(argv[1]);
                if(src_path ==NULL) {
                        fprintf(stderr,"\033[1;31m Memory allocation to copy source file path failed \033[0m \n ");
                        free(src_path);
                        return errno;
                }

      char* token = strtok(src_path,"/");
      char* final_token = NULL;
      while(token!=NULL){
                final_token = token;
                token = strtok(NULL, "/");
        }
        printf("output string %s \n",final_token);
        size_t dest_path_len = strlen(argv[2]) + strlen(final_token) + 10;
        char* dest_path = malloc(dest_path_len);
        if(dest_path == NULL) {
                fprintf(stderr,"\033[1;31m Memory allocation to destination file path failed \033[0m \n ");
                        free(dest_path);
                        return errno;
                }
                sprintf(dest_path + strlen(dest_path),"%s", argv[2]);
                if(argv[2][strlen(argv[2]) -1] != '/' ) sprintf(dest_path + strlen(dest_path), "%s", "/");
                sprintf(dest_path + strlen(dest_path), "%s", final_token);
                printf("output dest file %s \n",dest_path);
                fd_dest = open(dest_path,O_CREAT|O_WRONLY|O_TRUNC,0644);
                if(fd_dest <0){
                        printf("%d \n", ENOENT);
                        free(src_path);
                        free(dest_path);
                        fprintf(stderr,"\033[1;31m Couldn't creat the destination file due to %d\033[0m\n", errno);
                        return errno;
                }
                free(src_path);
                free(dest_path);
        }
        else{
                fprintf(stderr,"\033[1;31m Couldn't open the destination file\033[0m\n");
                return errno;
        }
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
    if(close(fd_src) <0){
        fprintf(stderr,"Couldn't close the source file due to %d \n" , errno);
        return errno;
    }
    if(unlink(argv[1])!=0){
        printf("source file in trouble %s \n", argv[1]);
      fprintf(stderr, "\033[1;31m Couldn't remove the source file due to %d \033[0m \n",errno);
      return errno;
    }

    
}
