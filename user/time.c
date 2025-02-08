#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int calculate_command_size(int argc, char* argv[]);
int calculate_char_array_size_no_null(char* array_address);
void assemble_command(int argc, char* argv[], char* command);
void write_characters(char command[], int write_index, char* argument);

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Usage: time [command]\n");
    } else {
        int command_size = calculate_command_size(argc, argv);

        printf("Size of command: %u\n", command_size);
        char command[command_size];

        assemble_command(argc, argv, command);

        printf("Command is: %s\n", command);
    }

    exit(0);
}

void assemble_command(int argc, char* argv[], char* command) {
    if (argc > 1) {
        int write_index = 0;

        int argument_index = 1;
        int argument_count = argc;

        while (argument_index < argument_count) {
            char* argument = argv[argument_index];
            int argument_size_no_null = calculate_char_array_size_no_null(argument);

            if (argument_index != 1) {
                command[write_index] = ' ';
                ++write_index;
            }

            write_characters(command, write_index, argument);

            write_index += argument_size_no_null;

            ++argument_index;
        }

        command[write_index] = '\0';
    }
}

void write_characters(char command[], int write_index, char* argument) {
    while ((int)*argument != 0) {
        command[write_index] = *argument;

        ++write_index;
        ++argument;
    }
}

int calculate_command_size(int argc, char* argv[]) {
    int command_size = 0;

    if (argc > 1) {
        int argument_index = 1;
        int argument_count = argc;

        int null_character_size = sizeof(char);        
        int space_size = 0;

        while (argument_index < argument_count) {
            char* argument_address = argv[argument_index];
            int argument_size_no_null 
                = calculate_char_array_size_no_null(argument_address);            
            int argument_size = argument_size_no_null + space_size;

            command_size += argument_size;

            space_size = null_character_size;

            ++argument_index;
        }

        command_size += null_character_size;
    }

    return command_size;
}

int calculate_char_array_size_no_null(char* array_address) {
    int char_array_size = 0;

    while ((int)*array_address != 0) {
        ++char_array_size;
        ++array_address;
    }

    return char_array_size;
}