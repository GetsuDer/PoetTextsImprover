#ifndef H_SORTING
#define H_SORTING

int cmp(char * string1, char * string2);
int cmp_reversed(char * string1, char * string2);
void quick_sort(char ** input_data, int elements_number, int (*cmp)(char *, char *));

#endif
