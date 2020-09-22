#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cassert>
#include <unistd.h>

#include "../Include/input.h"

//! \brief Opens the file specified by file_name
//! \param [in] file_name - the name of the file to open
//! \return Returns the file descriptor of the opened file
int
open_file(char * file_name, int flags, int mode)
{
    assert(file_name);

    int file_descriptor = open(file_name, flags, mode);
    if (file_descriptor < 0) {
        fprintf(stderr, "Error in opening file\n");
        return OPEN_FILE_ERROR;
    }
    return file_descriptor;
}


//! \brief Reads all data from the file specified by file_descriptor
//! \param [in] file_descriptor - file_descriptor for reading data
//! \return Returns the data size    
int
read_data_from_file(int file_descriptor, char **data)
{
    assert(file_descriptor >= 0);
    struct stat info_buffer;
    if (fstat(file_descriptor, &info_buffer)) { // read the file info. return 0, if success
        fprintf(stderr, "read_data_from_file: Can`t get data about file. Stopping.\n");
        return -1;
    }
    int data_size = info_buffer.st_size + 1 + 1;
    char * data_buffer = (char *) calloc(1, data_size); // +1 for \0 at the end and at the beginning
    if (!data_buffer) {
        fprintf(stderr, "read_data_from_file: Can`t allocate memory. Stopping;\n");
        return -1;
    }
    if (read(file_descriptor, data_buffer + 1, data_size) < 0) {
        fprintf(stderr, "read_data_from_file: Can`t read data\n");
        return -1;
    }
    *data_buffer = '\0';
    *data = data_buffer;
    return data_size;
}

//! \brief Write text into file in right order
//! \param [in] file_descriptor File descriptor for output
//! \param [in] order Pointer to sorted pointers to strings
//! \param [in] strings_number Len of the order array
//! \param [in] reversed Is true, if pointers in order point on the endings of the strings
void
write_data_to_file(int file_descriptor, char ** order, int strings_number, bool reversed)
{
    assert(file_descriptor > 0);
    assert(order);   

    char *tmp = NULL;
    for (int i = 0; i < strings_number; i++) {
        tmp = order[i];
        while (*tmp) {
            if (reversed) {
                tmp--;
            } else {
                tmp++;
            }
        }    
        if (reversed) {
            if (write(file_descriptor, tmp + 1, order[i] - tmp) < 0) {
                fprintf(stderr, FILE_ERROR);
            }
        } else {
            if (write(file_descriptor, order[i], tmp - order[i]) < 0) {
                fprintf(stderr, FILE_ERROR);
                return;
            }
        }
        if (write(file_descriptor, "\n", 1) < 0) {
            fprintf(stderr, FILE_ERROR);
            return;
        }
    }
    if (write(file_descriptor, "\n", 1) < 0) {
        fprintf(stderr, FILE_ERROR);
        return;
    }
    return;
}
