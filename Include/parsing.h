#ifndef H_PARSING
#define H_PARSING
int split_on_strings(char * data);
bool make_pointer_tables(char * data, char ** on_beginnings, char ** on_ends, int data_size, int string_number);
void join_from_strings(char * data, int data_size);
#endif
