#define STDOUT 1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define SYS_WRITE 1
#define SYS_EXIT 60

long syscall(long number, ...);

const char message[] = "Hello, World!\n";

void _start() {
  if (syscall(SYS_WRITE, STDOUT, message, sizeof(message) - 1) == -1) {
    syscall(SYS_EXIT, EXIT_FAILURE);
  } else {
    syscall(SYS_EXIT, EXIT_SUCCESS);
  }
}
