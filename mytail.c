#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#define BUFSIZE 2048

int main(int argc, char *argv[]) {

        char buffer [BUFSIZE];
        char buffer2 [BUFSIZE];
        int fd;
        int length;
        int i;
        int z;
        int k;
        int m, n, r;
        int nl_count, nl_count2;       // newline count


        if (argc < 2) {
                perror("Not enough arguments\n");  
                return(1);
        }

        for(i = 1; i <= argc-1; i++) {  //iterate through all the arguments

                write(1, "filename: ", 10);             
                write(1, argv[i], strlen(argv[i]));     // print file name
                write(1, "\n", 1);                      // print newline
        
                nl_count = 0;       // newline count
                if((fd=open(argv[i], O_RDONLY)) <= 0) {  // if file does not exist, return error
                        perror("Cannot open file\n");  
                        return 1;
                }

                length = read(fd, buffer, BUFSIZE);     // read file and get its length
                if (length <= 0) {     
                        close(fd);                      
                        perror("Empty file\n");         // if file is empty, return error
                        return 1;
                }
                close(fd);                              // close file

                if(length > BUFSIZE) {                  // if filesize > BUFSIZE, return error
                        perror("File too big\n");  
                        return 1;
                }

                nl_count = 0; 
                for (z = 0; z < length; z++) {
                        if (buffer[z] == EOF)           // break if buffer reaches EOF
                                break;
                        if (buffer[z] == '\n') {        // add 1 to counter for every newline
                                nl_count++;
                        }
                }
                // if file has <= 10 newlines
                if (nl_count <= 10) {                   // if file has <= 10 newlines
                        write(1, buffer, length);       // print contents of file
                        continue;                       // continue to next argument
                }        
                
                // if file has > 10 newlines
                m = nl_count - 10;          // set m as new line count - 10
                nl_count2 =0;
                r = 0;         
                for (k = 0; k < length; k++) {  // iterate through buffer again until new line count = m
                        if(buffer[k] == '\n' || buffer[k] == EOF) {             // check for newlines or EOF
                                nl_count2++;    // increment new line count by 1 
                                if (nl_count2 == m) {
                                        for(n = k+1; n <= length; n++) {        
                                                buffer2[r++] = buffer[n];       // copy chars for output to console             
                                        }
                                         write(1, buffer2, length-k);           // write to console                   
                                }   
                        }                                     
                }
                continue;
        }
        return(0);
}