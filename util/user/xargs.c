#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void run(char* program, char** args) {
	if(fork() == 0) { 
		exec(program, args);
		exit(0);
	}
	return;
}

int main(int argc, char *argv[]){
	char buf[2048];
	char* p = buf;
    char* last_p = buf;
	char* args_buf[128];
	char** args = args_buf;

	for(int a = 1; a < argc; ++a) {
		*args = argv[a];
		++args;
	}

	char** pa = args;
	while(read(0, p, 1) != 0) {
		if(*p == ' ' || *p == '\n') {
			*p = '\0';
            *pa = last_p;
            ++pa;
			last_p = p + 1;

			if(*p == '\n') {
				*pa = 0;
				run(argv[1], args_buf);
				pa = args;
			}
		}
		++p;
	}
	if(pa != args) {
		*p = '\0';
        *pa = last_p;
        ++pa;
		*pa = 0;
		run(argv[1], args_buf);
	}

	while(wait(0) != -1) {

    };

	exit(0);
}