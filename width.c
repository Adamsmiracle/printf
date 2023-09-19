#include "main.h"
/**
 * getWidth - Retrieves the width specifier for printing from the format string.
 *
 * @format_str: A formatted string containing the arguments.
 * @index_ptr: A pointer used to track the position in the format string.
 * @arg_list: A list of arguments to be printed.
 *
 * Return: The width specifier for printing.
 */
int getWidth(const char *formatString, int *indexPtr, va_list argList)
{
    int currentIndex;
    int widthSpecifier = 0;

    for (currentIndex = *indexPtr + 1; formatString[currentIndex] != '\0'; currentIndex++)
    {
        if (isDigitChar(formatString[currentIndex]))
        {
            widthSpecifier *= 10;
            widthSpecifier += formatString[currentIndex] - '0';
        }
        else if (formatString[currentIndex] == '*')
        {
            currentIndex++;
            widthSpecifier = va_arg(argList, int);
            break;
        }
        else
        {
            break;
        }
    }

    *indexPtr = currentIndex - 1;

    return widthSpecifier;
}

/************************* WRITE HANDLE *************************/
/**
 * handleWriteChar - Writes a single character to a buffer.
 *
 * @c: The character to be written.
 * @buffer: The buffer array used for writing.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: The number of characters written.
 */

int handleWriteChar(char c, char buffer[], int flags, int width, int precision, int size)
{
    int i = 0;
    char padd = ' ';

    UNUSED(precision);
    UNUSED(size);

    if (flags & FLAG_ZERO)
        padd = '0';

    buffer[i++] = c;
    buffer[i] = '\0';

    if (width > 1)
    {
        buffer[BUFFER_SIZE - 1] = '\0';
        for (i = 0; i < width - 1; i++)
            buffer[BUFFER_SIZE - i - 2] = padd;

        if (flags & FLAG_MINUS)
            return (write(1, &buffer[0], 1) + write(1, &buffer[BUFFER_SIZE - i - 1], width - 1));
        else
            return (write(1, &buffer[BUFFER_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1));
    }

    return (write(1, &buffer[0], 1));
}