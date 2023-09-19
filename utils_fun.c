#include "main.h"
/**
 * appendHexCode - Appends the ASCII code in hexadecimal format to an array of characters.
 *
 * @buffer: An array of characters.
 * @index: The index at which to start appending.
 * @ascii_code: The ASCII code to append.
 *
 * Return: Always 3 (indicating the number of characters appended).
 */
int appendHexCode(char asciiCode, char buffer[], int index)
{
    char hexMap[] = "0123456789ABCDEF";

    /* Ensure that the ASCII code is positive */
    if (asciiCode < 0)
        asciiCode *= -1;

    buffer[index++] = '\\';
    buffer[index++] = 'x';

    buffer[index++] = hexMap[asciiCode / 16];
    buffer[index] = hexMap[asciiCode % 16];

    return 3;
}

/**
 * isDigitChar - Checks if a character is a digit.
 *
 * @ch: The character to be evaluated.
 *
 * Return: 1 if 'ch' is a digit, otherwise 0.
 */

int isDigitChar(char ch)
{
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

/**
 * isPrintableChar - Checks if a character is printable.
 *
 * @ch: The character to be evaluated.
 *
 * Return: 1 if 'ch' is a printable character, otherwise 0.
 */

int isPrintableChar(char ch)
{
    if (ch >= 32 && ch < 127)
        return 1;
    return 0;
}

/**
 * convertToSizeNumber - Casts a number to the specified size.
 *
 * @num: The number to be cast.
 * @size: A number indicating the type to which 'num' should be cast.
 *
 * Return: The casted value of 'num'.
 */
long int convertToSizeNumber(long int num, int sizeSpecifier)
{
    if (sizeSpecifier == SIZE_LONG)
        return num;
    else if (sizeSpecifier == SIZE_SHORT)
        return (short)num;

    return (int)num;
}

/**
 * convertToSizeUnsigned - Casts an unsigned number to the specified size.
 *
 * @num: The number to be cast.
 * @size: A number indicating the type to which 'num' should be cast.
 *
 * Return: The casted value of 'num'.
 */

unsigned int convertToSizeUnsgnd(unsigned long int num, int size)
{
    if (size == SIZE_LONG)
        return num;
    else if (size == SIZE_SHORT)
        return (unsigned short)num;

    return (unsigned int)num;
}