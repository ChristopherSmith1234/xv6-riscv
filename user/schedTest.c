#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

const int MAX_PROCESS = 8;

int main() {
    updateScheduler();

    int index = 0;
    int pid;

    char* runArguments[2]; 

    runArguments[0] = "twip";
    runArguments[1] = 0;

    while (index < MAX_PROCESS) {
        pid = fork();

        if (pid == 0) {
            exec(runArguments[0], runArguments);

            exit(0);
        }

        ++index;
    }
    
    index = 0;
    int exitStatus = 0;

    while (index < MAX_PROCESS) {
        if (pid != 0) {
            wait(&exitStatus);
        }

        ++index;
    }

    updateScheduler();

    exit(0);
}