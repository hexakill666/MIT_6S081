#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    int p2c[2];
    int c2p[2];

    pipe(p2c);
    pipe(c2p);

    if(fork() != 0){
        write(p2c[1], "!", 1);
        char buf;
        read(c2p[0], &buf, 1);
        printf("%d: received pong\n", getpid());
        wait(0);
    }
    else{
        char buf;
        read(p2c[0], &buf, 1);
        printf("%d: received ping\n", getpid());
        write(c2p[1], &buf, 1);
    }

    exit(0);
}