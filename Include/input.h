#ifndef H_INPUT
#define H_INPUT

//! This value is returned if there is an error during work with files (opening, writing etc)
constexpr int OPEN_FILE_ERROR = -1;

int open_file(char * file_name, int flags, int mode);
int read_data_from_file(int file_descriptor, char ** data);
void write_data_to_file(int file_descriptor, char ** order, int strings_number, bool reversed);

#define HELLO "Enter path to the file where input text is and to the file where the result must be\n"
#define FILE_ERROR "Error in writing or reading from file\n"
#endif
