#include "main.h"
/**
 * writeNumber - Prints a signed number.
 *
 * @is_negative: Indicates if the number is negative.
 * @ind: The index at which the number starts in the buffer.
 * @buffer: The buffer array used for printing.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: The number of characters printed.
 */
int writeNumber(int isNegative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    int length = BUFFER_SIZE - ind - 1;
    char paddingChar = ' ', extraChar = 0;

    UNUSED(size);

    if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
        paddingChar = '0';
    if (isNegative)
        extraChar = '-';
    else if (flags & FLAG_PLUS)
        extraChar = '+';
    else if (flags & FLAG_SPACE)
        extraChar = ' ';

    return (writeNum(ind, buffer, flags, width, precision, length, paddingChar, extraChar));
}

/**
 * writeNum - Writes a number using a buffer.
 *
 * @ind: The index at which the number starts in the buffer.
 * @buffer: The buffer array used for writing.
 * @flags: Active flags.
 * @width: Width specifier.
 * @prec: Precision specifier.
 * @length: Number length.
 * @padd: Padding character.
 * @extra_c: Extra character.
 *
 * Return: The number of characters written.
 */
int writeNum(int ind, char buffer[], int flags, int width, int precision, int length, char paddingChar, char extraChar)
{
    int i, paddingStart = 1;

    if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0' && width == 0)
        return (0); /* printf(".0d", 0)  no char is printed */
    if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
        buffer[ind] = paddingChar = ' '; /* width is displayed with padding ' ' */
    if (precision > 0 && precision < length)
        paddingChar = ' ';

    while (precision > length)
        buffer[--ind] = '0', length++;

    if (extraChar != 0)
        length++;

    if (width > length)
    {
        for (i = 1; i < width - length + 1; i++)
            buffer[i] = paddingChar;
        buffer[i] = '\0';
        if (flags & FLAG_MINUS && paddingChar == ' ') /* Assign extraChar to the left of buffer */
        {
            if (extraChar)
                buffer[--ind] = extraChar;
            return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
        }
        else if (!(flags & FLAG_MINUS) && paddingChar == ' ') /* Assign extraChar to the left of buffer */
        {
            if (extraChar)
                buffer[--ind] = extraChar;
            return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
        }
        else if (!(flags & FLAG_MINUS) && paddingChar == '0') /* Assign extraChar to the left of padding */
        {
            if (extraChar)
                buffer[--paddingStart] = extraChar;
            return (write(1, &buffer[paddingStart], i - paddingStart) +
                    write(1, &buffer[ind], length - (1 - paddingStart)));
        }
    }
    if (extraChar)
        buffer[--ind] = extraChar;
    return (write(1, &buffer[ind], length));
}

/**
 * writeUnsigned - Writes an unsigned number.
 *
 * @is_negative: A flag indicating if the number is negative.
 * @ind: The index at which the number starts in the buffer.
 * @buffer: The buffer array used for writing.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: The number of characters written.
 */
int writeUnsgnd(int isNegative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    int length = BUFFER_SIZE - ind - 1, i = 0;
    char paddingChar = ' ';

    UNUSED(isNegative);
    UNUSED(size);

    if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
        return (0); /* printf(".0d, 0)  no char is printed */

    if (precision > 0 && precision < length)
        paddingChar = ' ';

    while (precision > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
        paddingChar = '0';

    if (width > length)
    {
        for (i = 0; i < width - length; i++)
            buffer[i] = paddingChar;

        buffer[i] = '\0';

        if (flags & FLAG_MINUS) /* Assign extra char to the left of buffer [buffer > paddingChar] */
        {
            return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
        }
        else /* Assign extra char to the left of paddingChar [paddingChar > buffer] */
        {
            return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
        }
    }

    return (write(1, &buffer[ind], length));
}

/**
 * writePointer - Writes a memory address.
 *
 * @buffer: An array of characters.
 * @ind: The index at which the number starts in the buffer.
 * @length: The length of the number.
 * @width: Width specifier.
 * @flags: Active flags.
 * @padd: The character used for padding.
 * @extra_c: The extra character.
 * @padd_start: The index at which padding should start.
 *
 * Return: The number of characters written.
 */
int writePointer(char buffer[], int ind, int length, int width, int flags, char paddingChar, char extraChar, int paddingStart)
{
    int i;

    if (width > length)
    {
        for (i = 3; i < width - length + 3; i++)
            buffer[i] = paddingChar;
        buffer[i] = '\0';
        if (flags & FLAG_MINUS && paddingChar == ' ') /* Assign extra char to the left of buffer [buffer > paddingChar] */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extraChar)
                buffer[--ind] = extraChar;
            return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
        }
        else if (!(flags & FLAG_MINUS) && paddingChar == ' ') /* Assign extra char to the left of buffer [buffer > paddingChar] */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extraChar)
                buffer[--ind] = extraChar;
            return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
        }
        else if (!(flags & FLAG_MINUS) && paddingChar == '0') /* Assign extra char to the left of paddingChar [paddingChar > buffer] */
        {
            if (extraChar)
                buffer[--paddingStart] = extraChar;
            buffer[1] = '0';
            buffer[2] = 'x';
            return (write(1, &buffer[paddingStart], i - paddingStart) + write(1, &buffer[ind], length - (1 - paddingStart) - 2));
        }
    }

    buffer[--ind] = 'x';
    buffer[--ind] = '0';
    if (extraChar)
        buffer[--ind] = extraChar;
    return (write(1, &buffer[ind], BUFFER_SIZE - ind - 1));
}
