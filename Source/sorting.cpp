#include <cassert>
#include <ctype.h>
#include <cstdio>

#include "../Include/sorting.h"

//! \brief Moves pointer to the next alpha
//! \param [in] str - String, pointer to which must be moved
static char *
next_alpha(char *str)
{
    assert(str);
    while (*str && !isalpha(*str)) {
        str++;
    }
    return str;
}


//!\brief Moves pointer to the previous alpha
//! \param [in] str - String, pointer to which must be moved
static char *
previous_alpha(char *str)
{
    assert(str);
    while (*str && !isalpha(*str)) {
       str--;
    }
    return str;
} 

//! \brief Comparator for two strings from the beginning.
//! \param [in] string1, string2 Strings which must be compared.
//! \return Returns -1 if string1 < string2, 0 if string1 == string2, 1 if string1 > string2
int
cmp(char * string1, char * string2)
{
    assert(string1);
    assert(string2);

    string1 = next_alpha(string1);
    string2 = next_alpha(string2);

    while (*string1 && *string2 && tolower(*string1) == tolower(*string2)) {
        string1++;
        string1 = next_alpha(string1);

        string2++;
        string2 = next_alpha(string2);
    }

    string1 = next_alpha(string1);
    string2 = next_alpha(string2);

    if (!*string1 && !*string2) {
        return 0;
    }

    if (!*string1) {
        return -1;
    }
    if (!*string2) {
        return 1;
    }
    assert(isalpha(*string1) && isalpha(*string2));
    return (tolower(*string1) < tolower(*string2)) ? -1 : 1;
}

//! \brief Comparator for two strings from the end
//! \param [in] string1, string2 String which must be compared
//! \return Returns -1 if string1 < string2, 0 if string1 == string2, 1 if string1 > string2
int
cmp_reversed(char *string1, char *string2)
{
    assert(string1);
    assert(string2);

    string1 = previous_alpha(string1);
    string2 = previous_alpha(string2);

    while (*string1 && string2 && tolower(*string1) == tolower(*string2)) {
        string1--;
        string1 = previous_alpha(string1);

        string2--;
        string2 = previous_alpha(string2);
    }
    string1 = previous_alpha(string1);
    string2 = previous_alpha(string2);

    if (!*string1 && !*string2) {
        return 0;
    }
    if (!*string1) {
        return -1;
    }
    if (!*string2) {
        return 1;
    }
    return (tolower(*string1) < tolower(*string2)) ? -1 : 1;
}

//! \brief Sorts [first_elem, second_elem) interval of the input array
//! \param [in] input_data Values to sort
//! \param [in] first_elem, second_elem Bounding elements
//! \param [in] cmp Comparator
static void
quick_sort_part(char **input_data, int first_elem, int second_elem, int (*cmp)(char *, char *))
{
    int bound_left = first_elem, bound_right = second_elem;
    if (second_elem - first_elem <= 1) {
        return;
    }
    
    char * medium_elem = input_data[(first_elem + second_elem) / 2];
    
    second_elem--;

    while (first_elem < second_elem) {
        
        while (cmp(input_data[first_elem], medium_elem) == -1) {
            first_elem++;
        }
        
        while (cmp(input_data[second_elem], medium_elem) == 1) {
            second_elem--;
        }
        
        if (first_elem <= second_elem) {
            char * tmp = input_data[first_elem];
            input_data[first_elem] = input_data[second_elem];
            input_data[second_elem] = tmp;
            first_elem++;
            second_elem--;
        }
    }
    if (second_elem > bound_left) {
        quick_sort_part(input_data, bound_left, second_elem + 1, cmp);
    }
    if (bound_right > first_elem + 1) {
        quick_sort_part(input_data, first_elem, bound_right, cmp);
    }
    return;
}

//! \brief This function sorts input_data array
//! \param [in] input_data Values to sort
//! \param [in] elemets_number Values number
//! \param [in] cmp Comparator
void
quick_sort(char ** input_data, int elements_number, int (*cmp)(char *, char *))
{
    quick_sort_part(input_data, 0, elements_number, cmp);
    return;
}

