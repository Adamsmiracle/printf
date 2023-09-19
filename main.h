#ifndef PRINTF_MAIN_H
#define PRINTF_MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFFER_SIZE 1024

/* FLAGS */
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

/* SIZES */
#define SIZE_LONG 2
#define SIZE_SHORT 1

/**
 * struct format_specifier - Struct to define a format specifier and its function.
 * @specifier: The format specifier character.
 * @function: The function pointer associated with the format specifier.
 */
struct format_specifier
{
    char specifier;
    int (*function)(va_list, char[], int, int, int, int);
};

typedef struct format_specifier format_specifier_t;

/**
 * _printf - Custom implementation of printf function.
 * @format: The formatted string containing the arguments to be printed.
 * @...: The variable number of arguments to be printed based on the format.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...);

/* Width handler */
int handleWriteChar(char c, char buffer[], int flags, int width, int precision, int size);
void printToBuffer(char buffer[], int *buffer_index);
int writePointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start);
int writeNum(int ind, char buffer[], int flags, int width, int precision, int length, char padd, char extra_c);
int writeNumber(int is_positive, int ind, char buffer[], int flags, int width, int precision, int size);

int writeUnsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size);

/* Functions to handle other specifiers */
int getWidth(const char *format_str, int *index_ptr, va_list arg_list);
int getSize(const char *format_str, int *index_ptr);
int getPrecision(const char *format_str, int *index_ptr, va_list arg_list);
int getFlags(const char *format_str, int *index_ptr);

/* Function to print string in reverse */
int printReverse(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Function to print a string in rot13 */
int printRot13string(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Function to print non-printable characters */
int printNonPrintable(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Function to print memory address */
int printPointer(va_list args, char buffer[], int flags, int width, int precision, int size);

void printToBuffer(char buffer[], int *buffer_index);

int handlePrint(const char *format, int *index, va_list arg_list,
                 char buffer[], int flags, int width, int precision, int size);
/* Functions to print numbers */
int printUnsigned(va_list args, char buffer[], int flags, int width, int precision, int size);
int printBinary(va_list args, char buffer[], int flags, int width, int precision, int size);
int printHexadecimal(va_list args, char buffer[], int flags, int width, int precision, int size);
int printInt(va_list args, char buffer[], int flags, int width, int precision, int size);
int printOctal(va_list args, char buffer[], int flags, int width, int precision, int size);
int printHexUpper(va_list args, char buffer[], int flags, int width, int precision, int size);
int printHexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Funtions to print characters and strings */
int printChar(va_list args, char buffer[], int flags, int width, int precision, int size);
int printString(va_list args, char buffer[], int flags, int width, int precision, int size);
int printPercent(va_list args, char buffer[], int flags, int width, int precision, int size);

/* HELPER FUNCTIONS */
int isPrintableChar(char c);
int appendHexCode(char c, char buffer[], int index);
int isDigitChar(char);

unsigned int convertToSizeUnsgnd(unsigned long int num, int size);
long int convertToSizeNumber(long int num, int size);

#endif /* PRINTF_MAIN_H */
