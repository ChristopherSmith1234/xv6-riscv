#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//  Exit codes:
//  0: Success
//  1: Usage error
//  2: Child process creation error
//  3: Command execution error
//  4: Child process return error

const int TICKS_PER_SECOND = 100;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Usage: time [command]\n");

        return 1;
    } else {
        int start_time = uptime();
        int process_id = fork();

        if (process_id < 0) {
            printf("Failed to create child process. Exiting...\n");
            
            return 2;
        } else if (process_id == 0) {
            //  *************
            //  Child process
            //  *************

            int argument_count = argc - 1;

            char* arguments[argument_count];
            int argument_index = 0;

            while (argument_index < argument_count) {
                //  argv[0] is program name, so begin at argv[1]
                arguments[argument_index] = argv[argument_index + 1];

                ++argument_index;
            }
            
            int command_exit_status = exec(arguments[0], arguments);

            if (command_exit_status != 0) {
                printf("Could not execute command. Exiting...\n");

                return 3;
            }
        }

        int child_process_return_status = 0;
        wait(&child_process_return_status);

        if (child_process_return_status != 0) {
            printf("Error occured while returning from process. Exiting...\n");

            return 4;
        }

        int end_time = uptime();
        int ticks_elapsed = end_time - start_time;
        int execution_time = ticks_elapsed * TICKS_PER_SECOND;

        printf("Real-time: %u\n", execution_time);
    }

    return 0;
}