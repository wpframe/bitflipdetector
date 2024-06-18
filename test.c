#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

// This was mostly GPTed

int main() {
    int pid;
    unsigned long address;
    unsigned char data = 1;
    printf("Enter the PID of the program: ");
    if(scanf("%d", &pid) != 1){
        fprintf(stderr, "Invalid PID input.\n");
        return 1;
    }
    printf("Enter the memory address (in hexadecimal): ");
    if(scanf("%lx", &address) != 1){
        fprintf(stderr, "Invalid memory address input.\n");
        return 1;
    }
    if(ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1){
        perror("attach");
        return 1;
    }
    waitpid(pid, NULL, 0);
    long original_data = ptrace(PTRACE_PEEKDATA, pid, (void *)address, NULL);
    if(original_data == -1 && errno != 0){
        perror("peekdata");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return 1;
    }
    unsigned long modified_data = (original_data & ~0xFF) | data;
    if(ptrace(PTRACE_POKEDATA, pid, (void *)address, (void *)modified_data) == -1){
        perror("pokedata");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return 1;
    }
    if(ptrace(PTRACE_DETACH, pid, NULL, NULL) == -1){
        perror("detach");
        return 1;
    }
    return 0;
}