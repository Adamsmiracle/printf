#include "main.h"

/**
 * getSize - Retrieves the size specifier for argument casting from the format string.
 *
 * @format_string: A formatted string containing the arguments.
 * @index_ptr: A pointer used to keep track of the position in the format string.
 *
 * Return: The size specifier for argument casting.
 */
int getSize(const char *format_string, int *index_pointer)
{
    int current_index = *index_pointer + 1;
    int size_specifier = 0;

    if (format_string[current_index] == 'l')
        size_specifier = SIZE_LONG;
    else if (format_string[current_index] == 'h')
        size_specifier = SIZE_SHORT;

    if (size_specifier == 0)
        *index_pointer = current_index - 1;
    else
        *index_pointer = current_index;

    return size_specifier;
}
