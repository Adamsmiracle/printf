#include "main.h"



/**
 * _printf - Custom printf function
 * @format: Format string passed as arg
 * Return: The nNumber of characters printed.
 */
int _printf(const char *format, ...)
{
	int j, prnt_chars = 0;
	int flgs, width, prcs, size, buffer_index = 0;
	va_list args;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (j = 0; format && format[j] != '\0'; j++)
	{
		if (format[j] != '%')
		{
			buffer[buffer_index++] = format[j];
			if (buffer_index == BUFFER_SIZE)
				printToBuffer(buffer, &buffer_index);
			prnt_chars++;
		}
		else
		{
			printToBuffer(buffer, &buffer_index);
			flgs = getFlags(format, &j);
			width = getWidth(format, &j, args);
			prcs = getPrecision(format, &j, args);
			size = getSize(format, &j);
			++j;
			prnt_chars += handlePrint(format, &j, args, buffer,
				flgs, width, prcs, size);
			if (prnt_chars == -1)
			{
				va_end(args);
				return (-1);
			}
		}
	}

	printToBuffer(buffer, &buffer_index);

	va_end(args);

	return (prnt_chars);
}

/**
 * printToBuffer - Prints the contents of the buffer if it exists
 * @buffer: Array containing characters
 * @buffer_index: Index at which to add the next char
 */

void printToBuffer(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);

	*buffer_index = 0;
}
