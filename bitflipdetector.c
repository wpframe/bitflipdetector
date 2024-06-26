#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>

volatile int interrupted = 0;

void interrupt_handler(int sig){
    if(sig == SIGINT) interrupted = 1;
}

int main(){
    int tests = 0;
    int size = 1073741824;
    unsigned char *bytes = (unsigned char*)calloc(size, 1);
    mlock(bytes, size);
    memset(bytes, 0, size);
    time_t t = time(NULL);
    pid_t pid = getpid();
    printf("Program (PID %d) started at unix time %ld\n", pid, t);
    printf("Byte array located at %p\n", bytes);
    signal(SIGINT, interrupt_handler);
    while(!interrupted){
        for(int i = 0; i < size; i++){
            if(bytes[i] > 0){
                printf("Bit flip detected!\n");
                printf("Unix time: %ld\n", t);
                printf("Test number: %d\n", tests);
                printf("Position in byte array: %d/1073741824\n", i);
                bytes[i] = 0;
            }
        }
        tests++;
        sleep(1);
    }
    free(bytes);
    return 0;
}
