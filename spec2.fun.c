#include "main.h"

/************************* PRINT NON-PRINTABLE *************************/
/**
 * printNonPrintable - Prints ASCII codes in hexadecimal for non-printable characters.
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
int printNonPrintable(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    int index = 0, offset = 0;
    char *string = va_arg(args, char *);

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (string == NULL)
        return (write(1, "(null)", 6));

    while (string[index] != '\0')
    {
        if (isPrintableChar(string[index]))
            buffer[index + offset] = string[index];
        else
            offset += appendHexCode(string[index], buffer, index + offset);

        index++;
    }

    buffer[index + offset] = '\0';

    return (write(1, buffer, index + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * printReverse - Prints a string in reverse order.
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
int printReverse(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    char *inputString;
    int index, charCount = 0;

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(size);

    inputString = va_arg(args, char *);

    if (inputString == NULL)
    {
        UNUSED(precision);
        inputString = ")Null(";
    }

    for (index = 0; inputString[index]; index++)
        ;

    for (index = index - 1; index >= 0; index--)
    {
        char character = inputString[index];
        write(1, &character, 1);
        charCount++;
    }

    return (charCount);
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * printRot13String - Prints a string in ROT13 encoding.
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
int printRot13string(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    char result;
    char *inputString;
    unsigned int i, j;
    int charCount = 0;
    char inputChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char outputChars[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

    inputString = va_arg(args, char *);
    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (inputString == NULL)
        inputString = "(AHYY)";

    for (i = 0; inputString[i]; i++)
    {
        for (j = 0; inputChars[j]; j++)
        {
            if (inputChars[j] == inputString[i])
            {
                result = outputChars[j];
                write(1, &result, 1);
                charCount++;
                break;
            }
        }

        if (!inputChars[j])
        {
            result = inputString[i];
            write(1, &result, 1);
            charCount++;
        }
    }

    return (charCount);
}

/**
 * printHexa - Prints a hexadecimal number in either lowercase or uppercase.
 *
 * @args: A list of arguments containing the number to be printed.
 * @map_to: An array of values used to map the number to either lowercase or uppercase.
 * @buff: An array used for handling the printing operation.
 * @flags: Flags that calculate active formatting options, like F_HASH, F_ZERO, etc.
 * @char_flag: A flag character, such as 'x', 'X', etc.
 * @width_spec: Specification for width in formatting.
 * @precision_spec: Specification for precision in formatting.
 * @size_spec: A size specifier, such as S_LONG, S_SHORT, etc.
 *
 * Return: The count of characters printed.
 */
int printHexa(va_list args, char mapTo[], char buffer[], int flags, char charFlag, int widthSpec, int precisionSpec, int sizeSpec)
{
    int i = BUFFER_SIZE - 2;
    unsigned long int num = va_arg(args, unsigned long int);
    unsigned long int initNum = num;

    UNUSED(widthSpec);

    num = convertToSizeUnsgnd(num, sizeSpec);

    if (num == 0)
        buffer[i--] = '0';

    buffer[BUFFER_SIZE - 1] = '\0';

    while (num > 0)
    {
        buffer[i--] = mapTo[num % 16];
        num /= 16;
    }

    if (flags & FLAG_HASH && initNum != 0)
    {
        buffer[i--] = charFlag;
        buffer[i--] = '0';
    }

    i++;

    return (writeUnsgnd(0, i, buffer, flags, widthSpec, precisionSpec, sizeSpec));
}
