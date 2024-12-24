#include <fcntl.h>   
#include <unistd.h>  
#include <ctype.h>   
#include <stdlib.h>  
#include <stdio.h>   

#define BUFFER_SIZE 1024  

int main(int argc, char *argv[]) {
    if (argc != 4) {
        write(2, "Usage: ./solution <input_file> <digits_file> <other_file>\n", 58);
        exit(1);
    }

    
    int fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0) {
        
        write(2, "Error: Cannot open input file\n", 30);
        exit(1);
    }

    
    int fd_digits = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_digits < 0) {
        write(2, "Error: Cannot create digits file\n", 33);
        close(fd_in);
        exit(2);
    }

    int fd_other = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_other < 0) {
        write(2, "Error: Cannot create other file\n", 32);
        close(fd_in);
        close(fd_digits);
        exit(2);
    }

    
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd_in, buffer, BUFFER_SIZE)) > 0) {
        
        char digits[BUFFER_SIZE];
        char others[BUFFER_SIZE];
        ssize_t digits_index = 0, others_index = 0;

        
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (isdigit(buffer[i])) {
                digits[digits_index++] = buffer[i];
            } else {
                others[others_index++] = buffer[i];
            }
        }

        if (write(fd_digits, digits, digits_index) != digits_index) {
            write(2, "Error: Write to digits file failed\n", 35);
            close(fd_in);
            close(fd_digits);
            close(fd_other);
            exit(3);
        }

        
        if (write(fd_other, others, others_index) != others_index) {
            write(2, "Error: Write to other file failed\n", 34);
            close(fd_in);
            close(fd_digits);
            close(fd_other);
            exit(3);
        }
    }

    
    if (bytes_read < 0) {
        write(2, "Error: Read from input file failed\n", 35);
        close(fd_in);
        close(fd_digits);
        close(fd_other);
        exit(3);
    }

    // Close all file descriptors
    close(fd_in);
    close(fd_digits);
    close(fd_other);

    return 0;
}
