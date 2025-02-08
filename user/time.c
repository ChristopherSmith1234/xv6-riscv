#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int calculate_command_size(int argc, char* argv[]);
int calculate_char_array_size_no_null(char* array_address);

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Usage: time [command]\n");
    } else {
        int command_size = calculate_command_size(argc, argv);

        printf("Size of command: %u\n", command_size);
    }

    exit(0);
}

int calculate_command_size(int argc, char* argv[]) {
    int command_size = 0;

    if (argc > 1) {
        int argument_index = 1;
        int argument_count = argc;

        int null_character_size = sizeof(char);        
        printf("char size: %u\n", null_character_size);
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