#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void get_prime(int cur_nums[]){
    int cur_num;
    read(cur_nums[0], &cur_num, sizeof(cur_num));
    if(cur_num == -1){
        exit(0);
    }
    printf("prime %d\n", cur_num);

    int next_nums[2];
    pipe(next_nums);

    if(fork() == 0){
        close(next_nums[1]);
        close(cur_nums[0]);
        get_prime(next_nums);
    }
    else{
        close(next_nums[0]);

        int buf;
        while(read(cur_nums[0], &buf, sizeof(buf)) && buf != -1){
            if(buf % cur_num != 0){
                write(next_nums[1], &buf, sizeof(buf));
            }
        }

        buf = -1;
        write(next_nums[1], &buf, sizeof(buf));
        wait(0);
        exit(0);
    }
}

int main(int argc, char* argv[]){
    int input_pipe[2];
    pipe(input_pipe);

    if(fork() == 0){
        close(input_pipe[1]);
        get_prime(input_pipe);
        exit(0);
    }
    else{
        close(input_pipe[0]);

        int num;
        for(int num = 2; num <= 35; num++){
            write(input_pipe[1], &num, sizeof(num));
        }

        num = -1;
        write(input_pipe[1], &num, sizeof(num));
    }

    wait(0);
    exit(0);
}