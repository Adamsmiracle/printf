#include "main.h"
/**
 * printChar - Prints a single character.
 *
 * @args: A list of arguments containing the character to be printed.
 * @buf: An array used to handle the printing operation.
 * @fl: Flags that determine the active formatting options.
 * @w: Specification for width in the formatted output.
 * @prec: Specification for precision in the formatted output.
 * @sz: A specifier indicating the size for the formatted output.
 *
 * Return: The count of characters printed.
 */

int printChar(va_list args, char buf[], int flag, int wid, int precis, int siz)
{
    char ch = va_arg(args, int);

    return (handleWriteChar(ch, buf, flag, wid, precis, siz));
}
/**
 * printString - Prints a string.
 *
 * @args: A list of arguments containing the string to be printed.
 * @buf: An array used to handle the printing operation.
 * @fl: Flags that determine the active formatting options.
 * @w: Specification for width in the formatted output.
 * @prec: Specification for precision in the formatted output.
 * @sz: A specifier indicating the size for the formatted output.
 *
 * Return: The count of characters printed.
 */
int printString(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    int length = 0, i;
    char *str = va_arg(args, char *);

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
    {
        str = "(null)";
        if (precision >= 6)
            str = "      ";
    }

    while (str[length] != '\0')
        length++;

    if (precision >= 0 && precision < length)
        length = precision;

    if (width > length)
    {
        if (flags & FLAG_MINUS)
        {
            write(1, &str[0], length);
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            return (width);
        }
        else
        {
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], length);
            return (width);
        }
    }

    return (write(1, str, length));
}

/**
 * printPercent - Prints a percent sign.
 *
 * @args: A list of arguments (not used in this function).
 * @buf: An array used to handle the printing operation.
 * @fl: Flags that determine the active formatting options (not used in this function).
 * @w: Specification for width in the formatted output (not used in this function).
 * @prec: Specification for precision in the formatted output (not used in this function).
 * @sz: A specifier indicating the size for the formatted output (not used in this function).
 *
 * Return: The count of characters printed (always 1 for the percent sign).
 */
int printPercent(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    UNUSED(args);
    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    return (write(1, "%%", 1));
}

/**
 * printInt - Prints an integer.
 *
 * @args: A list of arguments containing the integer to be printed.
 * @buf: An array used to handle the printing operation.
 * @fl: Flags that determine the active formatting options.
 * @w: Specification for width in the formatted output.
 * @prec: Specification for precision in the formatted output.
 * @sz: A specifier indicating the size for the formatted output.
 *
 * Return: The count of characters printed.
 */

/**
 * printBinary - Prints an unsigned integer in binary format.
 *
 * @args: A list of arguments containing the integer to be printed in binary format.
 * @buf: An array used to handle the printing operation.
 * @fl: Flags that determine the active formatting options (not used in this function).
 * @w: Specification for width in the formatted output (not used in this function).
 * @prec: Specification for precision in the formatted output (not used in this function).
 * @sz: A specifier indicating the size for the formatted output (not used in this function).
 *
 * Return: The count of characters printed.
 */
int printBinary(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    unsigned int number, mask, i, sum;
    unsigned int binaryBits[32];
    int count;

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    number = va_arg(args, unsigned int);
    mask = 2147483648; /* (2 ^ 31) */
    binaryBits[0] = number / mask;
    for (i = 1; i < 32; i++)
    {
        mask /= 2;
        binaryBits[i] = (number / mask) % 2;
    }
    for (i = 0, sum = 0, count = 0; i < 32; i++)
    {
        sum += binaryBits[i];
        if (sum || i == 31)
        {
            char digit = '0' + binaryBits[i];
            write(1, &digit, 1);
            count++;
        }
    }
    return (count);
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * printHexadecimal - Prints an unsigned number in hexadecimal notation.
 *
 * @args: A list of arguments.
 * @buffer: An array used to handle the printing operation.
 * @flags: Flags that calculate active formatting options.
 * @width_spec: Specification for width.
 * @precision_spec: Specification for precision.
 * @size_spec: Size specifier.
 *
 * Return: The count of characters printed.
 */
int printHexadecimal(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    return (printHexa(args, "0123456789abcdef", buffer, flags, 'x', width, precision, size));
}
