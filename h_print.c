#include "main.h"
/**
 * handlePrint - Prints an argument based on its data type
 *
 * @format: A formatted string containing the arguments
 * @index: Index used to track the position in the format string
 * @arg_list: List of arguments to be printed
 * @buffer: Buffer array used for handling the print
 * @flags: Active flags that have been calculated
 * @width: Specification for width
 * @precision: Specification for precision
 * @size: Size specifier
 *
 * Return: The number of characters printed or -1 if an unknown format specifier is encountered
 */
int handlePrint(const char *format, int *index, va_list arg_list,
                char buffer[], int flags, int width, int precision, int size)
{
    int i, unknown_length = 0, printed_chars = -1;

    typedef struct
    {
        char format_char;
        int (*function)(va_list, char[], int, int, int, int);
    } FormatType;

    FormatType format_types[] = {
        {'c', printChar}, {'s', printString},
        {'%', printPercent}, {'i', printInt}, 
        {'d', printInt}, {'b', printBinary}, 
        {'u', printUnsigned}, {'o', printOctal}, 
        {'x', printHexadecimal}, {'X', printHexUpper}, 
        {'p', printPointer}, {'S', printNonPrintable}, 
        {'r', printReverse}, {'R', printRot13string}, {'\0', NULL}};

    for (i = 0; format_types[i].format_char != '\0'; i++)
    {
        if (format[*index] == format_types[i].format_char)
            return format_types[i].function(arg_list, buffer, flags, width, precision, size);
    }

    if (format_types[i].format_char == '\0')
    {
        if (format[*index] == '\0')
            return -1;

        unknown_length += write(1, "%%", 1);

        if (format[*index - 1] == ' ')
            unknown_length += write(1, " ", 1);
        else if (width)
        {
            --(*index);
            while (format[*index] != ' ' && format[*index] != '%')
                --(*index);
            if (format[*index] == ' ')
                --(*index);
            return 1;
        }

        unknown_length += write(1, &format[*index], 1);
        return unknown_length;
    }

    return printed_chars;
}
