#include "main.h"

/**
 * getFlags - Computes the flags indicating active formatting options
 *
 * @format: The formatted string in which arguments are to be printed
 * @index: An index used to keep track of the position in the format string
 *
 * Return: Flags representing the active formatting options
 */
int getFlags(const char *format, int *index)
{
    /* - + 0 # ' ' */
    /* 1 2 4 8  16 */
    int i, current_index;
    int flags = 0;
    const char FLAGS_CHARACTERS[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_ARRAY[] = {FLAG_MINUS, FLAG_PLUS, FLAG_ZERO, FLAG_HASH, FLAG_SPACE, 0};

    for (current_index = *index + 1; format[current_index] != '\0'; current_index++)
    {
        for (i = 0; FLAGS_CHARACTERS[i] != '\0'; i++)
        {
            if (format[current_index] == FLAGS_CHARACTERS[i])
            {
                flags |= FLAGS_ARRAY[i];
                break;
            }
        }

        if (FLAGS_CHARACTERS[i] == 0)
            break;
    }

    *index = current_index - 1;

    return (flags);
}
