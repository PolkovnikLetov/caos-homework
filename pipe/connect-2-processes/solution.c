#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void print_error(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

#define ERROR(msg) print_error(msg)

int main(int argc, char const* argv[]) {
    if (argc < 3) {
        ERROR("Invalid argument count: ./solution [CMD1] [CMD2]");
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        ERROR("Failed to open input pipe");
    }

    pid_t pid = fork();
    if (pid == -1) {
        ERROR("Failed to fork process");
    }

    if (pid == 0) {  
        close(pipefd[0]);  
        dup2(pipefd[1], STDOUT_FILENO);  
        close(pipefd[1]);  
        execlp(argv[1], argv[1], (char*)NULL);  
        ERROR("Failed to run 1st command");
    } else {  
        close(pipefd[1]);  
        dup2(pipefd[0], STDIN_FILENO);  
        close(pipefd[0]);  

        execlp(argv[2], argv[2], (char*)NULL);  
        ERROR("Failed to run 2nd command");
    }

    return 0;
}
