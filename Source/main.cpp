#include <limits.h>
#include <cstdio>
#include <sys/stat.h>
#include <cstdlib>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include "../Include/input.h"
#include "../Include/sorting.h"
#include "../Include/parsing.h"
#include "../Include/main.h"

int
main(int argc, char **argv)
{
    if (argc < ARGNUM) {
        fprintf(stderr, "No input or output file\n");
        return 1;
    }

// Read data from file   
     
    int file_descriptor = open_file(argv[INPUT], O_RDONLY, 0);
    if (file_descriptor < 0) {
        fprintf(stderr, "main: File error\n");
        return 1;
    }

    char * data = NULL;
    int data_size = read_data_from_file(file_descriptor, &data);
    close(file_descriptor);

    if (!data || data_size < 0) {
        fprintf(stderr, "main: Can`t read data\n");
        return 1;
    }
    
// Parse data and make pointer tables    
    int strings_number = split_on_strings(data);

    char ** on_beginnings = (char **) calloc(strings_number, sizeof(*on_beginnings));
    if (!on_beginnings) {
        free(data);
        fprintf(stderr, "main: Sorry, can`t allocate memory\n");
        return 1;
    }

    char ** on_ends = (char **) calloc(strings_number, sizeof(*on_ends));
    if (!on_ends) {
        free(data);
        free(on_beginnings);
        fprintf(stderr, "main: Sorry, can`t allocate memory\n");
        return 1;
    }

    bool status = make_pointer_tables(data, on_beginnings, on_ends, data_size, strings_number);
    if (!status) {
        fprintf(stderr, "main: Can`t make pointer tables\n");
        free(data);
        free(on_beginnings);
        free(on_ends);
        return 1;
    }

    quick_sort(on_beginnings, strings_number, cmp);
    
    quick_sort(on_ends, strings_number, cmp_reversed);

//All work done, now write the answers
    file_descriptor = open_file(argv[OUTPUT], OUT_FLAGS, OUT_MODE);

    if (file_descriptor < 0) {
        fprintf(stderr, FILE_ERROR);
        close(file_descriptor);
        free(data);
        free(on_beginnings);
        free(on_ends);
        return 1;
    }

    write_data_to_file(file_descriptor, on_beginnings, strings_number, false);
    write_data_to_file(file_descriptor, on_ends, strings_number, true);
    
    join_from_strings(data, data_size);
    if (write(file_descriptor, data, data_size) < 0) {
        fprintf(stderr, FILE_ERROR);
        return 1;
    }

    close(file_descriptor);
    free(data);
    free(on_beginnings);
    free(on_ends);
    return 0;
}
