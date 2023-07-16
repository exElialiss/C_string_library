#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "math.h"
#include "stdarg.h"

#define BUFF_SIZE 256
#define MY_NULL ((void *)0)
typedef long unsigned my_size_t;

char *s21_strncpy(char *dest, const char *src, my_size_t n);
int s21_strncmp(const char *str1, const char *str2, my_size_t n);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
char *s21_strerror(int errnum);
my_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
void *s21_memset(void *str, int c, my_size_t n);
char *s21_strncat(char *dest, const char *src, my_size_t n);
void *s21_memchr(const void *str, int c, my_size_t n);
int s21_memcmp(const void *str1, const void *str2, my_size_t n);
void *s21_memcpy(void *dest, const void *src, my_size_t n);
my_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strchr(const char *str, int c);
void *s21_insert(const char *src, const char *str, my_size_t start_index);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
int s21_isdigit(char c);

#if defined(VERBOSE_MODE) && defined(DEBUG)
typedef enum specifier {
  NONE_SPEC,
  CHAR,
  DECIMAL,
  INT,
  SCI_e,
  SCI_E,
  FLOAT,
  SHORT_FLOAT_g,
  SHORT_FLOAT_G,
  UNSIGNED_OCT,
  STR,
  UNSIGNED_DEC_INT,
  UNSIGNED_HEX_x,
  UNSIGNED_HEX_X,
  POINTER_ADDR,
  N_OF_SCANNED_CHARS_UNTIL_N_OCCURS,
  PERCENT_CHAR
} specifier;
#endif

typedef enum TypeWidth {
  WIDTH_NONE,
  WIDTH_NUMBER,
  WIDTH_NOT_ASSIGNED
} TypeWidth;

typedef enum TypeLength {
  LENGTH_NONE,
  LENGTH_SHORT,
  LENGTH_LONG,
  LENGTH_LONG_LONG,
  LENGTH_DOUBLE,
  LENGTH_LONG_DOUBLE
} TypeLength;

typedef struct StringPatterns {
  void *addr;
  TypeWidth width;
  unsigned int widthNumber;

  TypeLength TypeLength;

  char buff[512];
  char spec;
} StringPatterns;

int s21_sscanf(const char *str, const char *format, ...);
long double s21_strtold(const char *buffer);
int s21_atoi(const char *str);
char *s21_strcpy(char *dest, const char *src);

int checkEOF(const char *src);
void writeCharsToBuff(char **str, const char *chars, char *buff, int16_t width,
                      int start_index);
unsigned long long int s21_strntoul(const char *string, char **endptr,
                                    int basis, int n_byte);
int isSpace(char c);
void unsignedTypeConverter(StringPatterns *pattern,
                           unsigned long long int result, int signBeforeNumber);
void intTypeConverter(StringPatterns *pattern, long long int result);
void floatTypeConverter(StringPatterns *pattern, long double result);
int isAlphabet(char c);

StringPatterns parsePatterns(char **fstr, va_list *va);
void fstrParseWidth(char **fstr, StringPatterns *pattern);
void writeStringToMemory(char **str, const int *failFlag, int *res,
                         StringPatterns *pattern);
void writeUnsignedToMemory(char **str, int *failFlag, int *res,
                           StringPatterns *pattern);
void fstrParseLength(char **fstr, StringPatterns *pattern);
void fstrParseSpecifier(char **fstr, StringPatterns *pattern);
int parseNumberFromFstr(char **fstr);
void skipSpacesInStr(char **src);
void skipCharsInBuffer(char **src, int *failFlag, StringPatterns *pattern);
void writeCharToMemory(char **str, int *res, StringPatterns *pattern,
                       int *failFlag);

void writePatternsToMemory(char **src, StringPatterns *tokens, int tok_len,
                           int *res);
void writeIntToMemory(char **str, int *failFlag, int *res,
                      StringPatterns *pattern);
void writeUnspecIntToMemory(char **str, int *failFlag, int *res,
                            StringPatterns *pattern);
void writeFloatToMemory(char **str, int *res, StringPatterns *pattern);
void writeHexOrOctToMemory(char **str, int *failFlag, int *res,
                           StringPatterns *pattern, int base);

typedef struct {
  int minus_flag;
  int plus_flag;
  int octothorpe_flag;
  int space_flag;
  int zero_flag;
  int width_flag;
  int precision_flag;
  int prec_flag;
  int length_flag;
  int specifier_flag;
} flags;

int s21_sprintf(char *str, const char *format, ...);

const char *parsingParameters(const char *str, flags *info);
const char *parsingSpecifier(const char *str, flags *info);
void resetFlags(flags *info);
char *specialFunction(va_list *ptr, flags info, char **str, const char **format,
                      unsigned int *count);
char *forIntegers(char **str, flags a, va_list *ptr, unsigned int *count);
char *forUnsignedIntegers(char **str, flags a, va_list *ptr,
                          unsigned int *count);
char *forDoubles(char **str, flags a, va_list *ptr, unsigned int *count);
char *forChars(char **str, flags a, va_list *ptr, const char **format,
               unsigned int *count);
char *charPointers(char **str, flags a, va_list *ptr, const char **format,
                   unsigned int *count);
char *wCharPointers(char **str, flags info, va_list *ptr, const char **format,
                    unsigned int *count);
char *pointers(char **str, flags a, va_list *ptr, unsigned int *count);
char *integerPointers(char **str, va_list *ptr, unsigned int count);
char *reverse(char s[]);
char *specItoa(long long int value, char *result, int base);
char *specUItoa(long long unsigned value, char *result, int base);
void widthHelper(char *result, flags info, int *i, int strlength);
void negativeSign(char *str, int i);
void positiveSign(flags info, char *str, int i);
void printBase(flags info, unsigned long x, char *result, int *i,
               int *precision);
int numberToStr(long double x, char *nu, long double x1, int *length);
void processingWithG(int *specificator, int *precision, char *nu, int *og,
                     long double x);
void processingWithE(long double x, flags info, int precision, char **nu1,
                     int og);
void doubleToStr(long double x, long double x1, char *nu, int *length);
void roundDouble(int length, int precision, char *nu, flags info);
void cutOffZeros(char *nu, flags info, int og);
void recursiveLongInt(long double d_arg, int symbols, char **str);
void expToStr(long double x, char *nu, char *nunu, flags a, int *i,
              int precision);
void toUpper(char *x);
void *s21_memmove(void *dest, const void *src, my_size_t n);
char *s21_strcat(char *dest, const char *src);

#endif