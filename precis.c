#include "main.h"
/**
 * getPrecision - Retrieves the precision value for printing from the format string.
 *
 * @format_string: A formatted string containing the arguments.
 * @index_ptr: A pointer used to keep track of the position in the format string.
 * @arg_list: A list of arguments to be printed.
 *
 * Return: The precision value.
 */
int getPrecision(const char *format_string, int *index_pointer, va_list arg_list)
{
    int current_index = *index_pointer + 1;
    int precision_value = -1;

    if (format_string[current_index] != '.')
        return precision_value;

    precision_value = 0;

    for (current_index += 1; format_string[current_index] != '\0'; current_index++)
    {
        if (isDigitChar(format_string[current_index]))
        {
            precision_value *= 10;
            precision_value += format_string[current_index] - '0';
        }
        else if (format_string[current_index] == '*')
        {
            current_index++;
            precision_value = va_arg(arg_list, int);
            break;
        }
        else
            break;
    }

    *index_pointer = current_index - 1;

    return precision_value;
}
