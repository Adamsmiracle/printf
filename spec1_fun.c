#include "main.h"

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * printOctal - Prints an unsigned number in octal notation.
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
int printOctal(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    int index = BUFFER_SIZE - 2;
    unsigned long int number = va_arg(args, unsigned long int);
    unsigned long int initial_number = number;

    UNUSED(width);

    number = convertToSizeUnsgnd(number, size);

    if (number == 0)
        buffer[index--] = '0';

    buffer[BUFFER_SIZE - 1] = '\0';

    while (number > 0)
    {
        buffer[index--] = (number % 8) + '0';
        number /= 8;
    }

    if (flags & FLAG_HASH && initial_number != 0)
        buffer[index--] = '0';

    index++;

    return (writeUnsgnd(0, index, buffer, flags, width, precision, size));
}

/**
 * printPointer - Prints the value of a pointer variable.
 *
 * @args: A list of arguments.
 * @buf: An array used to handle the printing operation.
 * @flags: Flags that calculate active formatting options.
 * @width: Specification for width.
 * @precision: Specification for precision.
 * @size: Size specifier.
 *
 * Return: The count of characters printed.
 */
int printPointer(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    char extra_character = 0, padding_character = ' ';
    int index = BUFFER_SIZE - 2, length = 2, padding_start = 1; /* length=2, for '0x' */
    unsigned long int num_addresses;
    char hexadecimal_map[] = "0123456789abcdef";
    void *addresses = va_arg(args, void *);

    UNUSED(width);
    UNUSED(size);

    if (addresses == NULL)
        return (write(1, "(nil)", 5));

    buffer[BUFFER_SIZE - 1] = '\0';
    UNUSED(precision);

    num_addresses = (unsigned long int)addresses;

    while (num_addresses > 0)
    {
        buffer[index--] = hexadecimal_map[num_addresses % 16];
        num_addresses /= 16;
        length++;
    }

    if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
        padding_character = '0';
    if (flags & FLAG_PLUS)
        extra_character = '+', length++;
    else if (flags & FLAG_SPACE)
        extra_character = ' ', length++;

    index++;

    return (writePointer(buffer, index, length, width, flags, padding_character, extra_character, padding_start));
}

/************* PRINT UNSIGNED NUMBER *************************/
/**
 * printUnsigned - Prints an unsigned number.
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
int printUnsigned(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    int index = BUFFER_SIZE - 2;
    unsigned long int number = va_arg(args, unsigned long int);

    number = convertToSizeUnsgnd(number, size);

    if (number == 0)
        buffer[index--] = '0';

    buffer[BUFFER_SIZE - 1] = '\0';

    while (number > 0)
    {
        buffer[index--] = (number % 10) + '0';
        number /= 10;
    }

    index++;

    return (writeUnsgnd(0, index, buffer, flags, width, precision, size));
}

int printInt(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    int index = BUFFER_SIZE - 2;
    int is_negative = 0;
    long int num = va_arg(args, long int);
    unsigned long int n;

    num = convertToSizeNumber(num, size);

    if (num == 0)
        buffer[index--] = '0';

    buffer[BUFFER_SIZE - 1] = '\0';
    n = (unsigned long int)num;

    if (num < 0)
    {
        n = (unsigned long int)((-1) * num);
        is_negative = 1;
    }

    while (n > 0)
    {
        buffer[index--] = (n % 10) + '0';
        n /= 10;
    }

    index++;

    return (writeNumber(is_negative, index, buffer, flags, width, precision, size));
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

int printHexUpper(va_list args, char buffer[], int flags, int width_spec, int precision_spec, int size_spec)
{
    return (printHexa(args, "0123456789ABCDEF", buffer, flags, 'X', width_spec, precision_spec, size_spec));
}
