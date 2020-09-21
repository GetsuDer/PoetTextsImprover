#include <cassert>

#include "../Include/parsing.h"


//! \brief Splits the input buffer into strings by replacing \n on \0
//! \param [in] data Buffer, in which strings are placed
//! \return Returns the number of strings
int
split_on_strings(char * data)
{
    assert(data);

    int string_number = 0;
    data++;
    bool good_string = false;
    while (*data) {
        if (*data == '\n') {
            if (good_string) {
                string_number++;
                *data = '\0';
                good_string = false;
            }
        } else {
            good_string = true;
        }
        data++;
    }

    return string_number;
}

//! \brief Changes all \0 chars on \n chars
//! \param [in] data Char buffer
//! \param [in] data_size Buffer size
void
join_from_strings(char * data, int data_size)
{
    assert(data);
    assert(data_size > 0);

    while (data_size) {
        if (!*data) {
            *data = '\n';
        }
        data++;
        data_size--;
    }
    data--;
    *data = '\0'; //At the end must be \0
}

//! \brief Get two arrays of pointer on strings
//! \param [in] data Strings buffer
//! \param [in] string_number Number of strings
//! \param [in] data_size Size of the strings buffer
//! \param [out] on_beginnings Pointers on beginnings
//! \param [out] on_ends Pointers on ends
//! \return True, if success
bool
make_pointer_tables(char * data, char ** on_beginnings, char ** on_ends, int data_size, int string_number)
{
    assert(data);
    assert(on_beginnings);
    assert(on_ends);
    assert(data_size > 0);
    assert(string_number > 0);

    if (*data) { //There must be \0 in the beginning
        return false;
    }
    
    while (data_size && !*data) { //We suppose, that there is at least one not-\0 char in this fata
        data++; //There could be \0 in beginning. And not only in beginning.
        data_size--;
    }

    if (!data_size) {
        return false;
    }

    *on_beginnings = data;
    bool good_string = false;

    while (data_size && string_number) {
        if (!*data) {
            if (good_string) {
                *on_ends = (data - 1);
                on_beginnings++;
                on_ends++;
                string_number--;
                good_string = false;
            }
        } else {
            if (!good_string) {
                *on_beginnings = data;
                good_string = true;
            }
        }
        data++;
        data_size--;
    }
    
    if (string_number) {
        return false;
    }
    return true;
} 
