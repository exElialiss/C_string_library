#include "s21_string.h"

static int ncludesExponent(const char *buffer);
static long double s21_atof(const char *buffer);
static long double applyExponent(long double res, const char *buffer);
static int caseInsensSearch(const char *buff, const char *pat);
static int includesInfNan(const char *buffer);
static long double returnNanInf(const char *buffer);

#if defined(__APPLE__)
#define MAX_ERR 107
#define MIN_ERR -1

static const char *const myerror[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_ERR 134
#define MIN_ERR -1

static const char *myerror[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error",
    MY_NULL};
#endif

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *res = NULL;
  if (src && str && s21_strlen(src) >= start_index) {
    my_size_t src_len = s21_strlen(src);
    my_size_t str_len = s21_strlen(str);
    my_size_t res_len = src_len + str_len + 1;
    res = malloc(res_len * sizeof(char));
    if (res) {
      s21_strncpy(res, src, start_index);
      res[start_index] = '\0';
      my_size_t i = start_index;
      my_size_t j = 0;
      while (str[j] != '\0') {
        res[i] = str[j];
        i++;
        j++;
      }
      res[i] = '\0';
      while (src[start_index] != '\0') {
        res[i] = src[start_index];
        i++;
        start_index++;
      }
      res[i] = '\0';
    }
  }
  return res;
}

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str
void *s21_memchr(const void *str, int c, my_size_t n) {
  void *result = MY_NULL;
  const unsigned char *ptr_str = (const unsigned char *)str;

  for (; n--; ++ptr_str) {
    if ((unsigned char)c == *ptr_str) {
      result = (void *)ptr_str;
      break;
    }
  }

  return result;
}

// Сравнивает первые n байтов str1 и str2
int s21_memcmp(const void *str1, const void *str2, my_size_t n) {
  int result = 0;
  const unsigned char *ptr_str1 = (const unsigned char *)str1;
  const unsigned char *ptr_str2 = (const unsigned char *)str2;

  for (; n-- && (result = (*ptr_str1 - *ptr_str2)) == 0; ++ptr_str1, ++ptr_str2)
    ;

  return result;
}

// Копирует n символов из src в dest
void *s21_memcpy(void *dest, const void *src, my_size_t n) {
  unsigned char *ptr_dest = (unsigned char *)dest;
  const unsigned char *ptr_src = (const unsigned char *)src;

  while (n--) *ptr_dest++ = *ptr_src++;

  return dest;
}

void *s21_memset(void *str, int c, my_size_t n) {
  char *answer = (char *)str;
  for (int i = 0; (i < (int)n) && (*answer != '\0'); i++) {
    answer[i] = (char)c;
  }

  return answer;
}

char *s21_strchr(const char *str, int c) {
  char *answer = MY_NULL;
  while ((!answer) && (*str != '\0')) {
    if ((int)(*str) == c) {
      answer = (char *)str;
    }
    str++;
  }

  return answer;
}

char *s21_strerror(int errnum) {
  static char res[256];
  if (errnum < 0 || errnum > 134 || myerror[errnum] == MY_NULL) {
    sprintf(res, "Unknown error %d", errnum);

  } else {
    s21_strncpy(res, myerror[errnum], BUFF_SIZE - 1);
    res[BUFF_SIZE - 1] = '\0';
  }
  return res;
}

my_size_t s21_strlen(const char *str) {
  for (const char *str1 = str;; str1++)
    if (!(*str1)) return str1 - str;
}

char *s21_strncat(char *dest, const char *src, my_size_t n) {
  char *answer = dest;
  while (*answer != '\0') {
    answer++;
  }

  while (*src != '\0' && n > 0) {
    *answer = *src;
    answer++;
    src++;
    n--;
  }
  *answer = '\0';

  return dest;
}

int s21_strncmp(const char *str1, const char *str2, my_size_t n) {
  int val = 0;
  for (my_size_t i = 0; i < n; i++) {
    if (*str1 != *str2) {
      val = *str1 - *str2;
    } else {
      str1++;
      str2++;
    }
  }
  return val;
}

char *s21_strncpy(char *dest, const char *src, my_size_t n) {
  my_size_t i;
  for (i = 0; i < n; i++) {
    dest[i] = src[i];
  }
  return dest;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *scanp;
  int c, sc;

  while ((c = *str1++) != 0) {
    for (scanp = str2; (sc = *scanp++) != '\0';)
      if (sc == c) return ((char *)(str1 - 1));
  }
  return (MY_NULL);
}

char *s21_strrchr(const char *str, int c) {
  char *lastOccurrence = MY_NULL;

  if (c == '\0') {
    return "";
  }

  while (*str != '\0') {
    if (*str == c) {
      lastOccurrence = (char *)str;
    }
    str++;
  }

  return lastOccurrence;
}

my_size_t s21_strcspn(const char *str1, const char *str2) {
  my_size_t i;
  const char *s;
  for (i = 0; *str1; str1++, i++) {
    for (s = str2; *s && *s != *str1; s++)
      ;
    if (!*s) break;
  }
  return i;
}

char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') {
    return (char *)haystack;
  }

  int needleCount = 0;
  char *firstInput = MY_NULL;
  int firstInputFlag = 0;

  while (*haystack != '\0') {
    if (*haystack == needle[needleCount]) {
      needleCount++;

      if (!firstInputFlag) {
        firstInputFlag = 1;
        firstInput = (char *)haystack;
      }

      if (needle[needleCount] == '\0') {
        return firstInput;
      }

    } else {
      needleCount = 0;
      firstInputFlag = 0;
    }
    haystack++;
  }

  return MY_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *nextToken = MY_NULL;

  if (str == MY_NULL) {
    return MY_NULL;
  }

  nextToken = str;

  char *startToken = nextToken;

  // Пропустить начальные разделители
  while (*nextToken != '\0' && s21_strchr(delim, *nextToken) != MY_NULL) {
    nextToken++;
  }

  // Если достигнут конец строки, вернуть MY_NULL
  if (*nextToken == '\0') {
    startToken = MY_NULL;
  } else {
    startToken = nextToken;  // Начало следующего токена

    // Найти конец токена
    while (*nextToken != '\0' && s21_strchr(delim, *nextToken) == MY_NULL) {
      nextToken++;
    }

    // Если достигнут конец строки, установить nextToken в MY_NULL
    if (*nextToken == '\0') {
      nextToken = MY_NULL;
    } else {
      *nextToken = '\0';  // Разделить токен, заменив разделитель на '\0'
      nextToken++;
    }
  }
  return startToken;
}

void *s21_to_lower(const char *str) {
  char *st = MY_NULL;
  if (str) {
    st = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (st) {
      for (my_size_t i = 0; i < s21_strlen(str); i++) {
        st[i] = str[i];
      }
      for (my_size_t i = 0; i < s21_strlen(str); i++) {
        if (st[i] >= 'A' && st[i] <= 'Z') st[i] += 32;
      }
    }
    st[s21_strlen(str)] = '\0';
  }
  return st;
}

void *s21_to_upper(const char *str) {
  char *st = MY_NULL;
  if (str) {
    st = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (st) {
      for (my_size_t i = 0; i < s21_strlen(str); i++) {
        st[i] = str[i];
      }
      for (my_size_t i = 0; i < s21_strlen(str); i++) {
        if (st[i] >= 'a' && st[i] <= 'z') st[i] -= 32;
      }
    }
    st[s21_strlen(str)] = '\0';
  }
  return (st);
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = NULL;
  if (src && trim_chars) {
    const char *start = src;
    const char *end = src + s21_strlen(src) - 1;
    for (; *start && s21_strchr(trim_chars, *start); start++)
      ;
    for (; end > start && s21_strchr(trim_chars, *end); end--)
      ;
    size_t trimmed_len = end - start + 1;
    res = (char *)malloc((trimmed_len + 1) * sizeof(char));
    if (res) {
      s21_strncpy(res, start, trimmed_len);
      res[trimmed_len] = '\0';
    }
  }
  return res;
}

#include "s21_string.h"

int s21_sscanf(const char *str, const char *formatStr, ...) {
  int isEndOfFile = checkEOF(str), res = 0;

  if (!isEndOfFile) {
    va_list args;
    va_start(args, formatStr);
    int patterns_len = 0;

    char *formStr = (char *)formatStr;
    char *src = (char *)str;

    StringPatterns patterns[BUFF_SIZE];

    while (*formStr && patterns_len < BUFF_SIZE) {
      patterns[patterns_len] = parsePatterns(&formStr, &args);
      patterns_len++;
    }

    writePatternsToMemory(&src, patterns, patterns_len, &res);
    va_end(args);
  }

  return (isEndOfFile) ? isEndOfFile : res;
}

int isSpace(char symbol) {
  return (symbol == ' ' || symbol == '\n' || symbol == '\t');
}

int isAlphabet(char symbol) {
  return (symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z');
}

/// @brief Проверяем не пустой ли файл
/// @param src
/// @return
int checkEOF(const char *src) {
  int result = -1;

  for (int i = 0; src[i]; i++) {
    if (!isSpace(src[i]) && src[i] != '\0') {
      result = 0;
      break;
    }
  }

  return result;
}

/// @brief Считываем все имеющиеся спецификаторы, take values of width,length
/// @param formatStr Считанная строка на входе
/// @param args
/// @return Набор из ширины, спецификаторов, длины
StringPatterns parsePatterns(char **formatStr, va_list *args) {
  StringPatterns pattern = {.addr = MY_NULL,
                            .TypeLength = LENGTH_NONE,
                            .spec = 0,
                            .width = WIDTH_NONE,
                            .widthNumber = 0};

  if (isSpace(**formatStr)) {
    pattern.spec = 'z';
    skipSpacesInStr(formatStr);
  }

  if (**formatStr == '%' && !pattern.spec) {
    (*formatStr)++;

    if (**formatStr == '%') {
      s21_memset(pattern.buff, '\0', BUFF_SIZE - 1);
      pattern.buff[0] = '%';
      (*formatStr)++;
      pattern.spec = 'b';
    } else {
      fstrParseWidth(formatStr, &pattern);
      fstrParseLength(formatStr, &pattern);
      fstrParseSpecifier(formatStr, &pattern);

      if (pattern.width != WIDTH_NOT_ASSIGNED)
        pattern.addr = va_arg(*args, void *);
    }

    if (pattern.spec == 'p') pattern.TypeLength = LENGTH_NONE;
  }

  if (isAlphabet(**formatStr) && !pattern.spec) {
    s21_memset(pattern.buff, '\0', BUFF_SIZE - 1);
    int i = 0;
    while (**formatStr && !isSpace(**formatStr) && **formatStr != '%') {
      pattern.buff[i++] = **formatStr;
      (*formatStr)++;
    }
    pattern.spec = 'b';
  }

  return pattern;
}

/// @brief If alphabet char in buffer, skip it
/// @param src
/// @param failFlag
/// @param pattern
void skipCharsInBuffer(char **src, int *failFlag, StringPatterns *pattern) {
  int checkValud = s21_strcspn(*src, pattern->buff);
  int len = s21_strlen(pattern->buff);

  if (len == 1 && **src == pattern->buff[0]) {
    (*src) = (*src) + len;
    return;
  }

  if (checkValud != len)
    *failFlag = 1;
  else
    (*src) = (*src) + len;
}

/// @brief Парсим ширину
/// @param formatStr Считанная строка на входе
/// @param pattern
void fstrParseWidth(char **formatStr, StringPatterns *pattern) {
  if (**formatStr == '*') {
    (*formatStr)++;
    pattern->width = WIDTH_NOT_ASSIGNED;
  } else {
    int gottenNumber = parseNumberFromFstr(formatStr);

    if (gottenNumber) {
      pattern->width = WIDTH_NUMBER;
      pattern->widthNumber = gottenNumber;
    }
  }
}

/// @brief Получаем минимальное количество печатаемых символов
/// @param formatStr Считанная строка на входе
/// @return кол-во печатаемых символов
int parseNumberFromFstr(char **formatStr) {
  char tempal[BUFF_SIZE] = {'\0'};

  int result = 0, i = 0;

  while (**formatStr >= '0' && **formatStr <= '9') {
    tempal[i] = **formatStr;
    (*formatStr)++;
    i++;
  }

  result = s21_atoi(tempal);

  return result;
}

/// @brief Узнаем нужную длину значения
/// @param formatStr Считанная строка на входе
/// @param pattern
void fstrParseLength(char **formatStr, StringPatterns *pattern) {
  switch (**formatStr) {
    case 'L':
      pattern->TypeLength = LENGTH_LONG_DOUBLE;
      (*formatStr)++;
      break;
    case 'h':
      pattern->TypeLength = LENGTH_SHORT;
      (*formatStr)++;
      break;
    case 'l':
      pattern->TypeLength = LENGTH_LONG;
      (*formatStr)++;
      if (**formatStr == 'l') {
        pattern->TypeLength = LENGTH_LONG_LONG;
        (*formatStr)++;
      }
      break;
  }
}

/// @brief Считываем спецификатор
/// @param formatStr
/// @param pattern
void fstrParseSpecifier(char **formatStr, StringPatterns *pattern) {
  pattern->spec = (**formatStr);
  (*formatStr)++;
}

/// @brief Определяем используемые паттерны и производим запись
/// @param src
/// @param patterns
/// @param pattern_len
/// @param res
void writePatternsToMemory(char **src, StringPatterns *patterns,
                           int pattern_len, int *res) {
  char *startStr = *src;

  for (int i = 0, failFlag = 0; i < pattern_len && !failFlag; i++) {
    char spec = patterns[i].spec;

    if (spec == 'c') {
      writeCharToMemory(src, res, (patterns + i), &failFlag);
    }

    if (spec == 'd') {
      writeIntToMemory(src, &failFlag, res, (patterns + i));
    }

    if (spec == 'i' || spec == 'p') {
      writeUnspecIntToMemory(src, &failFlag, res, (patterns + i));
    }

    if (spec == 'g' || spec == 'G' || spec == 'f' || spec == 'e' ||
        spec == 'E') {
      writeFloatToMemory(src, res, (patterns + i));
    }

    if (spec == 'x' || spec == 'X') {
      writeHexOrOctToMemory(src, &failFlag, res, (patterns + i), 16);
    }

    if (spec == 'o') {
      writeHexOrOctToMemory(src, &failFlag, res, (patterns + i), 8);
    }

    if (spec == 's') {
      writeStringToMemory(src, &failFlag, res, (patterns + i));
    }

    if (spec == 'u') {
      writeUnsignedToMemory(src, &failFlag, res, (patterns + i));
    }

    if (spec == 'z') {
      skipSpacesInStr(src);
    }

    if (spec == 'n') {
      *((int *)patterns[i].addr) = (*src) - startStr;
    }

    if (spec == 'b') {
      skipCharsInBuffer(src, &failFlag, (patterns + i));
    }
  }
}

/// @brief Пропускаем пробелы, переносы строк, табуляцию
/// @param str Считанная строка
void skipSpacesInStr(char **str) {
  while (**str && isSpace(**str)) {
    (*str)++;
  }
}

/// @brief Записываем символ
/// @param str
/// @param result
/// @param pattern
/// @param failFlag
void writeCharToMemory(char **str, int *result, StringPatterns *pattern,
                       int *failFlag) {
  *failFlag = 1;
  while (**str) {
    *failFlag = 0;

    if (pattern->width == WIDTH_NOT_ASSIGNED) {
      (*str)++;
      break;

    } else {
      *(char *)pattern->addr = **str;
      (*str)++;
      (*result)++;
      break;
    }
  }
}

/// @brief Записываем переменные типа int %d
/// @param str
/// @param failFlag
/// @param res
/// @param pattern
void writeIntToMemory(char **str, int *failFlag, int *res,
                      StringPatterns *pattern) {
  long long int result = 0;
  char buffer[BUFF_SIZE] = {'\0'};

  *failFlag = 1;

  if (s21_strcspn(*str, "+-0123456789")) {
    int signBeforeNumber = s21_strcspn(*str, "+-");

    if (!(signBeforeNumber > 1 ||
          (signBeforeNumber &&
           (pattern->widthNumber <= 1 && pattern->width)))) {
      buffer[0] = **str;
      (*str)++;
      writeCharsToBuff(str, "0123456789", buffer, pattern->widthNumber, 1);

      if (pattern->width != WIDTH_NOT_ASSIGNED) {
        (*res)++;
      }
      *failFlag = 0;
    }
  }
  result = s21_atoi(buffer);

  if (pattern->spec == 'p' && pattern->width != WIDTH_NOT_ASSIGNED &&
      !*failFlag) {
    unsigned long long int ress =
        s21_strntoul(buffer, NULL, 16, s21_strlen(buffer));
    *(int *)pattern->addr = (int)ress;

  } else {
    if (pattern->width != WIDTH_NOT_ASSIGNED && !*failFlag)
      intTypeConverter(pattern, result);
  }

  if (pattern->width != WIDTH_NUMBER)
    writeCharsToBuff(str, "0123456789", MY_NULL, 0, 0);
}

/// @brief Обработка спецификатора %i определяем размерность числа
/// @param str
/// @param failFlag
/// @param res
/// @param pattern
void writeUnspecIntToMemory(char **str, int *failFlag, int *res,
                            StringPatterns *pattern) {
  *failFlag = 1;

  skipSpacesInStr(str);

  if (s21_strcspn(*str, "0x") == 2) {
    *failFlag = 0;
    writeHexOrOctToMemory(str, failFlag, res, pattern, 16);
  } else if (s21_strcspn(*str, "0") == 1) {
    *failFlag = 0;
    writeHexOrOctToMemory(str, failFlag, res, pattern, 8);
  } else if (s21_strcspn(*str, "+-0123456789")) {
    *failFlag = 0;
    writeIntToMemory(str, failFlag, res, pattern);
  }
}

/// @brief Записываем в буффер подходящие значения из str
/// @param str
/// @param chars
/// @param buff
/// @param width
/// @param startIndex
void writeCharsToBuff(char **str, const char *chars, char *buff, int16_t width,
                      int startIndex) {
  while (**str && s21_strcspn(*str, chars) != 0) {
    if ((width && startIndex >= width) || (isSpace(**str))) {
      break;
    }

    if (buff) {
      buff[startIndex] = **str;
    }

    (*str)++;
    startIndex++;
  }
}

/// @brief Записываем число типа float
/// @param str
/// @param res
/// @param pattern
void writeFloatToMemory(char **str, int *res, StringPatterns *pattern) {
  int checkValud = 0;

  if (pattern->spec == 'f')
    checkValud = s21_strcspn(*str, "0123456789+-");
  else
    checkValud = s21_strcspn(*str, "0123456789eE+-NnaAifIF");

  if (checkValud) {
    int signBeforeNumber = s21_strcspn(*str, "+-");
    if (!(signBeforeNumber > 1 ||
          (signBeforeNumber &&
           (pattern->widthNumber <= 1 && pattern->width)))) {
      char buff[BUFF_SIZE] = {'\0'};
      int start_ind = 0;
      if (signBeforeNumber) {
        buff[0] = **str;
        start_ind = 1;
        (*str)++;
      }

      if (pattern->spec == 'f')
        writeCharsToBuff(str, ".0123456789+-", buff, pattern->widthNumber,
                         start_ind);
      else
        writeCharsToBuff(str, "NnaAifIF.0123456789eE+-", buff,
                         pattern->widthNumber, start_ind);

      if (pattern->width != WIDTH_NOT_ASSIGNED) {
        long double result = s21_strtold(buff);
        (*res)++;
        floatTypeConverter(pattern, result);
      }
    }
  }

  if (pattern->width != WIDTH_NUMBER) {
    if (pattern->spec == 'f')
      writeCharsToBuff(str, ".0123456789", MY_NULL, 0, 0);
    else
      writeCharsToBuff(str, "NaAifIFn.0123456789eE+-", MY_NULL, 0, 0);
  }
}

/// @brief Записываем беззнаковое десятичное целое число %u
/// @param str
/// @param failFlag
/// @param res
/// @param pattern
void writeUnsignedToMemory(char **str, int *failFlag, int *res,
                           StringPatterns *pattern) {
  *failFlag = 1;
  skipSpacesInStr(str);
  char buff[BUFF_SIZE] = {'\0'};

  if (s21_strcspn(*str, "+-0123456789")) {
    int signBeforeNumber = s21_strcspn(*str, "+-");
    if (!((signBeforeNumber > 1 ||
           (signBeforeNumber &&
            (pattern->widthNumber <= 1 && pattern->width))))) {
      *failFlag = 0;
      buff[0] = **str;
      (*str)++;

      writeCharsToBuff(str, "0123456789", buff, pattern->widthNumber, 1);

      if (pattern->width != WIDTH_NOT_ASSIGNED) (*res)++;
    }
  }

  unsigned long long int result = s21_atoi(buff);

  if (pattern->width != WIDTH_NOT_ASSIGNED && !*failFlag)
    unsignedTypeConverter(pattern, result, 1);

  if (pattern->width != WIDTH_NUMBER)
    writeCharsToBuff(str, "0123456789", MY_NULL, 0, 0);
}

/// @brief Записываем число типа oct или hex
/// @param str
/// @param failFlag
/// @param res
/// @param pattern
/// @param base основание 8 или 16
void writeHexOrOctToMemory(char **str, int *failFlag, int *res,
                           StringPatterns *pattern, int base) {
  int signBeforeNumber = 1;
  char *ptr = MY_NULL;

  if (pattern->spec == 'p') {
    base = 16;
  }

  skipSpacesInStr(str);
  if (**str == '-') {
    pattern->widthNumber--;
    signBeforeNumber = -1;
    (*str)++;
  }

  if (base == 16 && **str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X'))
    pattern->widthNumber -= 2;

  if (s21_strcspn(*str, "abcdefABCDEF0123456789") > 0 ||
      s21_strcspn(*str, "abcdefABCDEFxX0123456789") >= 2) {
    unsigned long long int result =
        s21_strntoul(*str, &ptr, base,
                     pattern->width ? pattern->widthNumber : s21_strlen(*str));

    if (pattern->width != WIDTH_NOT_ASSIGNED) {
      *res += 1;

      if (pattern->spec == 'p') {
        *(int *)pattern->addr = (int)result;
      } else {
        unsignedTypeConverter(pattern, result, signBeforeNumber);
      }
    }
  } else {
    *failFlag = 1;
  }
  unsigned int max = (unsigned int)s21_strcspn(*str, "0123456789abcdefABCDEFxX");

  if (pattern->width != WIDTH_NUMBER) {
    *str += max;
  }

  else {
    *str += max < pattern->widthNumber ? max : pattern->widthNumber;
  }
}

/// @brief Записываем строку
/// @param str
/// @param failFlag
/// @param res
/// @param pattern
void writeStringToMemory(char **str, const int *failFlag, int *res,
                         StringPatterns *pattern) {
  int success = 0;
  char buff[BUFF_SIZE] = {'\0'};
  unsigned int i = 0;

  while (**str != '\0' && !success && !(*failFlag)) {
    if (!isSpace(**str)) {
      success = 1;
      while (**str != '\0' && !(*failFlag)) {
        buff[i] = **str;
        i++;

        if (pattern->width == WIDTH_NUMBER && i >= pattern->widthNumber) {
          break;
        }
        (*str)++;

        if (isSpace(**str)) {
          (*str)--;
          break;
        }
      }
    }

    (*str)++;
  }

  if (pattern->width != WIDTH_NOT_ASSIGNED && success) {
    s21_strcpy((char *)pattern->addr, buff);
    (*res)++;
  }
}

/// @brief Конвертирует под нужный тип игнорируя знак
/// @param pattern
/// @param result
/// @param signBeforeNumber
void unsignedTypeConverter(StringPatterns *pattern,
                           unsigned long long int result,
                           int signBeforeNumber) {
  if (pattern->TypeLength == LENGTH_NONE) {
    *(unsigned int *)pattern->addr = signBeforeNumber * (unsigned int)result;

  } else if (pattern->TypeLength == LENGTH_SHORT) {
    *(unsigned short int *)pattern->addr =
        signBeforeNumber * (unsigned short int)result;

  } else if (pattern->TypeLength == LENGTH_LONG) {
    *(unsigned long int *)pattern->addr =
        signBeforeNumber * (unsigned long int)result;

  } else if (pattern->TypeLength == LENGTH_LONG_LONG) {
    *(unsigned long long int *)pattern->addr =
        signBeforeNumber * (unsigned long long int)result;
  }
}

/// @brief Конвертирует под нужный тип int
/// @param pattern
/// @param result
void intTypeConverter(StringPatterns *pattern, long long int result) {
  if (pattern->spec != 'p') {
    if (pattern->TypeLength == LENGTH_NONE) {
      *(int *)pattern->addr = (int)result;
    } else if (pattern->TypeLength == LENGTH_SHORT) {
      *(short int *)pattern->addr = (short int)result;
    } else if (pattern->TypeLength == LENGTH_LONG) {
      *(long int *)pattern->addr = (long int)result;
    } else if (pattern->TypeLength == LENGTH_LONG_LONG) {
      *(long long int *)pattern->addr = (long long int)result;
    }
  }
}

/// @brief Конвертирует под нужный тип float
/// @param pattern
/// @param result
void floatTypeConverter(StringPatterns *pattern, long double result) {
  if (pattern->TypeLength == LENGTH_NONE)
    *(float *)pattern->addr = (float)result;
  if (pattern->TypeLength == LENGTH_LONG)
    *(double *)pattern->addr = (double)result;
  if (pattern->TypeLength == LENGTH_LONG_DOUBLE)
    *(long double *)pattern->addr = (long double)result;
}

char *s21_strcpy(char *dest, const char *src) {
  for (int i = 0; src[i]; i++) {
    dest[i] = src[i];
  }

  dest[s21_strlen(src)] = '\0';

  return dest;
}

int s21_atoi(const char *str) {
  int res = 0;
  int sign = 1;
  int overflow = 0;

  while (*str == ' ') str++;

  if (*str == '-') {
    str++;
    sign = -1;
  }

  if (*str == '+') {
    str++;
  }

  while (*str && *str >= '0' && *str <= '9') {
    res = res * 10 + (*str - '0');
    if (res < 0) {
      overflow = 1;
      break;
    }
    str++;
  }
  if (overflow) {
    res = 0;
  } else {
    res *= sign;
  }

  return res;
}

long double s21_strtold(const char *buffer) {
  long double res = 0.0;
  int includesNan = includesInfNan(buffer);

  if (!includesNan) {
    res = s21_atof(buffer);

    if (ncludesExponent(buffer)) {
      res = applyExponent(res, buffer);
    }
  }

  return (includesNan) ? returnNanInf(buffer) : res;
}

static int caseInsensSearch(const char *buff, const char *pat) {
  int found = 0;
  int len = (int)s21_strlen(pat);

  for (int i = 0; buff[i] && !found; i++) {
    int counter = 0;
    for (int j = 0; j < len; j++) {
      if ((buff[i] == (pat[j] - 'A') + 'a') ||
          (buff[i] == (pat[j] - 'a') + 'A') || pat[j] == buff[i]) {
        counter++;
        i++;
      }

      if (len == counter) {
        found = 1;
        break;
      }
    }
  }

  return found;
}

static int includesInfNan(const char *buffer) {
  int res = 0;

  int test1 = caseInsensSearch(buffer, "inf");
  int test2 = caseInsensSearch(buffer, "nan");

  if (test1 || test2) {
    res = 1;
  }

  return res;
}

static long double returnNanInf(const char *buffer) {
  int res = 0;

  for (int i = 0; buffer[i]; i++) {
    if (buffer[i] == 'i' || buffer[i] == 'I') {
      res = 1;
      break;
    }

    if (buffer[i] == 'n' || buffer[i] == 'N') {
      res = 2;
      break;
    }
  }

  return (res == 1) ? INFINITY : NAN;
}

static long double applyExponent(long double res, const char *buffer) {
  char sign = '+';
  int expon = 0;

  for (char *p = (char *)buffer; *p; p++) {
    if (*p == 'e' || *p == 'E') {
      sign = *(p + 1);
      expon = s21_atoi(p + 2);
    }
  }

  while (expon) {
    if (sign == '-') {
      res /= 10.0;
    } else {
      res *= 10.0;
    }
    expon--;
  }

  return res;
}

static int ncludesExponent(const char *buffer) {
  int res = 0;

  for (char *p = (char *)buffer; *p; p++) {
    if (s21_strcspn(p, "eE")) {
      res = 1;
      break;
    }
  }

  return res;
}

static long double s21_atof(const char *buffer) {
  long double frac = 0.0;
  char *p = (char *)buffer;
  int minus_flag = (*p == '-');
  if (*p == '-' || *p == '+') p++;

  long double res = s21_atoi(p);

  while ((*p) >= '0' && (*p) <= '9') {
    p++;
  }

  if (*p == '.') {
    p++;
    int trailing_zeros = s21_strcspn(p, "0");
    frac = s21_atoi(p);
    int tmp = (int)frac;
    while (tmp) {
      frac /= 10.0;
      tmp /= 10;
    }
    while (trailing_zeros) {
      frac /= 10.0;
      trailing_zeros--;
    }
  }

  res += frac;

  return minus_flag ? -res : res;
}

unsigned long long int s21_strntoul(const char *str, char **endptr, int base,
                                    int n_byte) {
  unsigned long long result = 0;
  short sign = 1;
  if (endptr) *endptr = MY_NULL;
  char dictionary[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if (*str == '-') {
    sign = -1;
    str++;
  }
  if (base == 16 && (!s21_strncmp(str, "0x", 2) || !s21_strncmp(str, "0X", 2)))
    str += 2;
  long long val;
  short ex = 0;
  while (*str && n_byte && !ex) {
    char *tmp2;
    char current_sim = (*str >= 'a' && *str <= 'z') ? *str - 'a' + 'A' : *str;
    tmp2 = s21_strchr(dictionary, (int)current_sim);
    if (!tmp2) {
      ex = 1;
    } else {
      val = (tmp2 - dictionary) / sizeof(char);

      if (val >= base) {
        ex = 1;
      } else {
        result = result * base + val;
        str++;
        n_byte--;
      }
    }
    if (ex) *endptr = (char *)str;
  }
  return result * sign;
}

int s21_sprintf(char *str, const char *format, ...) {
  flags info = {0};  // инифиализация флагов нулями
  unsigned int count = 0;  // подсчет кол-ва напечатанных символов
  va_list ptr;  // позволяет обрабатывать нефиксированный набор параметров
  va_start(ptr, format);  // Требуется последний известный аргумент (чтобы
                          // получить адрес первого неизвестного)
  while (*format) {  // пока форматированная строка не закончилась
    if (*format != '%') {
      *str++ = *format++;
      ++count;
    } else {
      *str = '\0';  // зануляем текущий символ новой строки
      ++format;
      format = parsingParameters(
          format, &info);  // определим параметры без спецификатора
      format = parsingSpecifier(format, &info);  // определим спецификатор
      if (format) {  // проверяем, что форматированная строка существует
        if (info.specifier_flag == '%') {
          *str++ = '%';
          ++count;
        } else {  // достаём аргумент и правильно записываем его в строку
          str = specialFunction(&ptr, info, &str, &format, &count);
        }
      }
      resetFlags(&info);  // сброс флагов перед следующим аргументом
    }
  }
  *str = '\0';  // зануляем строку
  if (!format)
    count = -1;  // если строка была занулена, ставим значение для ошибки
  va_end(ptr);  // окончание работы с вариативной функцией
  return count;
}

const char *parsingParameters(const char *str, flags *info) {
  while (*str == '-' || *str == '+' || *str == '0' || *str == '#' ||
         *str == ' ') {  // пока флаг есть
    switch (*str) {
      case '-':
        info->minus_flag = 1;
        break;
      case '+':
        info->plus_flag = 1;
        break;
      case '#':
        info->octothorpe_flag = 1;
        break;
      case '0':
        info->zero_flag = 1;
        break;
      default:
        info->space_flag = 1;
        break;
    }
    ++str;
  }

  if (*str == '*') {  // если ширина равна звёздочке
    str++;  // отмечаем это на будущее и двигаемся дальше
    info->width_flag = -2;
  } else {
    while (*str >= '0' && *str <= '9') {  // если ширина есть и задана числом
      info->width_flag *=
          10;  // цикл, так как ширина может быть многосимвольным числом
      info->width_flag += *str - '0';
      ++str;
    }
  }

  if (*str == '.') {  // есть точка, следовательно, задана точность
    str++;
    info->prec_flag = 1;  // запоминаем это
    if (*str == '*') {  // если точность задана звёздочкой
      info->precision_flag = -2;  // запомнили это
      str++;
    } else {
      while (*str >= '0' && *str <= '9') {  // парсим аналогично ширине
        info->precision_flag *= 10;
        info->precision_flag += *str - '0';
        str++;
      }
    }
  }
  if (*str == 'h' || *str == 'l' || *str == 'L') {  // если задана длина
    info->length_flag = *str;                       // записываем её
    str++;
  }
  return str;  // возвращаем элемент форматированной строки, который стоит после
               // флагов
}

const char *parsingSpecifier(const char *str, flags *info) {
  int find = 1;  // по умолчанию - найден

  if (!(*str >= 48 || *str <= 57)) {
    switch (*str) {
      case 'd':
      case 'i':
      case 'o':
      case 'u':
      case 'x':
      case 'X':
      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
      case 'c':
      case 's':
      case 'p':
      case 'n':
        break;
      default:
        find = 0;
        break;
    }
  }

  info->specifier_flag = *str;
  str++;
  if (!find) {
    str = MY_NULL;  // если нет подходящего спецификатора, зануляем строку
  }
  return str;
}

char *specialFunction(va_list *ptr, flags info, char **str, const char **format,
                      unsigned int *count) {
  if (info.width_flag == -2) {  // если ширина задана звездой
    int width =
        va_arg(*ptr, my_size_t);  // достаём аргумент, в котором записана ширина
    info.width_flag = width;  // приравнивание ширины к значению аргумента
  }
  if (info.precision_flag == -2) {  // точность
    int ac = va_arg(*ptr, my_size_t);
    info.precision_flag = ac;
  }
  switch (info.specifier_flag)  // тип спецификатора
  {
    case 'd':
    case 'i':
      *str = forIntegers(str, info, ptr, count);
      break;
    case 'o':
    case 'u':
    case 'x':
    case 'X':
      *str = forUnsignedIntegers(str, info, ptr, count);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      *str = forDoubles(str, info, ptr, count);
      break;
    case 'c':
      *str = forChars(str, info, ptr, format, count);
      break;
    case 's':
      *str = charPointers(str, info, ptr, format, count);
      break;
    case 'p':
      *str = pointers(str, info, ptr, count);
      break;
    case 'n':
      *str = integerPointers(str, ptr, *count);
      break;
    default:
      break;
  }
  return *str;  // возвращаем элемент строки, с которого надо продолжить печать
}

char *forIntegers(char **str, flags info, va_list *ptr, unsigned int *count) {
  long int x = va_arg(
      *ptr, long int);  // достаём аргумент, который надо будет напечатать
  int i = 0;
  int size;
  char *array = calloc(21, sizeof(char));
  char *tmp = array;
  if (info.length_flag == 'h') {
    x = (short)x;
  } else if (info.length_flag == 0) {
    x = (int)x;  // изменение типа данных в зависимотси от длины
  }
  specItoa(x, array, 10);  // конвертируем число в строку
  if (x == 0 && info.prec_flag && !info.precision_flag) {
    array[0] = 0;  // особенность работы с нулём
  }
  if (array[0] == '-') array++;

  if (21 > (info.precision_flag > info.width_flag ? info.precision_flag
                                                  : info.width_flag)) {
    size = 21 + 2;
  } else if (info.precision_flag > info.width_flag) {
    size = info.precision_flag + 2;
  } else {
    size = info.width_flag + 2;
  }
  char *result = calloc(
      size,
      sizeof(
          char));  // выделим память для записи числа с нужным форматированием
  widthHelper(result, info, &i, s21_strlen(array));  // обработка ширины
  if (x < 0) {
    negativeSign(result, i);  // пишем знак, если он нужен
  } else {
    positiveSign(info, result, i);
  }
  for (; (info.precision_flag - (int)s21_strlen(array)) > 0;
       i++, info.precision_flag--) {
    s21_strcat(result, "0");  // дополняем до нужной точности нулями
  }

  s21_strcat(
      result,
      array);  // записываем число в массив, где произвели нужное форматирование
  if (info.minus_flag) {
    while ((int)s21_strlen(result) < info.width_flag) s21_strcat(result, " ");
  }  // то пробелы для ширины надо вставлять уже после числа
  s21_strcat(*str, result);
  unsigned int check =
      s21_strlen(result);  // считаем, сколько символов добавится
  *count += check;  // учтем их в напечатанных символах
  free(result);
  free(tmp);
  return *str + check;
}

char *forUnsignedIntegers(char **str, flags info, va_list *ptr,
                          unsigned int *count) {
  unsigned long int x = va_arg(*ptr, unsigned long int);
  int size;
  char num[24] = {0};  // массив для числа
  if (info.length_flag == 'h')
    x = (unsigned short)x;  // в зависимости от длины
  else if (info.length_flag == 0)
    x = (unsigned int)x;  // приводим к нужному типу данных
  if (info.specifier_flag == 'o')
    specUItoa(x, num, 8);  // 8-чный
  else if (info.specifier_flag == 'u')
    specUItoa(x, num, 10);  // 10-чный
  else
    specUItoa(x, num, 16);  // 16-чный
  if (info.specifier_flag == 'X')
    toUpper(num);  // в этом флаге x в базе печатается в верхнем регистре
  if (x == 0 && info.prec_flag && !info.precision_flag) num[0] = 0;
  int i = 0;
  if (24 > (info.precision_flag > info.width_flag ? info.precision_flag
                                                  : info.width_flag)) {
    size = 24 + 2;
  } else if (info.precision_flag > info.width_flag) {
    size = info.precision_flag + 2;
  } else {
    size = info.width_flag + 2;
  }
  char *result =
      calloc(size, sizeof(char));  // массив для форматированного числа
  widthHelper(result, info, &i, s21_strlen(num));  // печать ширины
  printBase(info, x, result, &i, &(info.precision_flag));  // печатаем базу

  for (; info.precision_flag - (int)s21_strlen(num) > 0;
       i++, info.precision_flag--) {
    result[i] = '0';  // если нужна точность - печатаем её
  }
  result[i] = '\0';
  s21_strcat(result, num);  // добавляем число в форматированную строку
  if (info.minus_flag) {  // если ширину надо печатать после числа
    while ((int)s21_strlen(result) < info.width_flag) {
      s21_strcat(result, " ");
    }
  }
  s21_strcat(*str,
             result);  // добавляем форматированное число в финальную строку
  unsigned int add = s21_strlen(result);  // считывание новых символов
  *count += s21_strlen(result);  // увеличиваем счётчик напечатанных символов
  free(result);
  return *str + add;
}

char *forDoubles(char **str, flags info, va_list *ptr, unsigned int *count) {
  long double x, x1;
  int og = 0, i = 0, length = 0, nan_or_inf = 0;
  if (info.length_flag == 'L')
    x1 = x = va_arg(
        *ptr,
        long double);  // выбираем нужный тип данных в зависимости от  длины
  else
    x1 = x = va_arg(*ptr, double);
  char num[500] = {0};   // массив для числа
  char *nu = &(num[1]);  // оставляем первую ячейку на случай удлиннения числа
  int precision = info.prec_flag ? info.precision_flag : 6;
  nan_or_inf = numberToStr(x, nu, x1, &length);  //  запишем число в строку
  if (!nan_or_inf) {  // если нормальное число
    processingWithG(&(info.specifier_flag), &precision, nu, &og,
                    x);  // предобработка для g/G
    if (info.specifier_flag == 'e' || info.specifier_flag == 'E') {  // если e/E
      processingWithE(x, info, precision, &nu,
                      og);  // обработаем и округлим как e/E
    } else {
      roundDouble(length, precision, nu, info);  // как f
      cutOffZeros(nu, info,
                  og);  // убираем нули после десятичной точки, если нужно
    }
    if ((nu[s21_strlen(nu) - 1] == '.') &&
        !(info.specifier_flag == 'f' && info.octothorpe_flag))
      nu[s21_strlen(nu) - 1] = 0;
    // если точка - последний символ + и оставлять её не нужно, то убираем
  }
  if (nu[-1]) nu = num;
  int size = ((unsigned int)(info.width_flag + 2) > (s21_strlen(nu) + 2)
                  ? (unsigned int)(info.width_flag + 2)
                  : (s21_strlen(nu) + 2));
  char *result =
      calloc(size + 1, sizeof(char));  // массив для отформатированного числа
  for (; !info.minus_flag && (info.width_flag - (int)s21_strlen(nu) > 0);
       i++, info.width_flag--) {
    if (info.zero_flag)
      result[i] = '0';  // заполняем ширину нулями или пробелами
    else
      result[i] = ' ';
  }
  if (!nan_or_inf)
    if (x < 0.) {
      negativeSign(result, i);
    } else {
      positiveSign(info, result, i);
    }
  else if (isinf(x) > 0 || isnan(x)) {
    positiveSign(info, result, i);
  }
  if (info.specifier_flag == 'E' || info.specifier_flag == 'G')
    toUpper(nu);  // если нужен верхний регистр
  if (num[0] != 0)
    s21_strcat(result,
               num);  // копируем в финальную строку вместе с нулевой ячейкой
  else
    s21_strcat(result,
               nu);  // или без; смотря, появилась ли там цифра после округления
  if (info.minus_flag)
    for (; (int)s21_strlen(result) < info.width_flag;) s21_strcat(result, " ");
  int add = s21_strlen(result);
  s21_strcat(*str, result);
  *count += add;
  free(result);
  return *str + add;
}

char *forChars(char **str, flags info, va_list *ptr, const char **format,
               unsigned int *count) {
  wchar_t symbol = va_arg(*ptr, wchar_t);

  // берем аргумент с правильным типом данных в зависимости от длины
  if (info.length_flag != 'l') {
    symbol = (char)symbol;
  }

  // если символ - широкий , то зануляем формат-строку
  if (info.length_flag == 'l' && symbol > 127) {
    (**str) = '\0';
    *format = 0;
  } else {
    // допечатываем ширину пробелами
    for (; !info.minus_flag && (info.width_flag - 1 > 0);
         (*str)++, info.width_flag--, (*count)++) {
      (**str) = ' ';
    }
    // записываем в строку нужный символ
    (**str) = symbol;
    (*str)++,
        (*count)++;  // сдвигаемся по строчке и учитываем напечатанный символ
    // минус- значит ширина после символа
    if (info.minus_flag) {
      for (; (info.width_flag - 1 > 0);
           (*str)++, info.width_flag--, (*count)++) {
        (**str) = ' ';
      }
    }
    **str = '\0';
  }

  return *str;
}

char *charPointers(char **str, flags info, va_list *ptr, const char **format,
                   unsigned int *count) {
  if (info.length_flag == 'l') {  // обработка строки широких символов
    wCharPointers(str, info, ptr, format, count);
  } else {  // обработка обычной строки
    char *x = va_arg(*ptr, char *);  // указатель на символ
    int length = (x == NULL ? 6 : s21_strlen(x));  //  длина строки
    if (info.prec_flag && info.precision_flag < length)
      length = info.precision_flag;  // если есть точность - применяем её
    if (info.prec_flag && x == NULL && info.precision_flag < 6)
      length = 0;  // обработка случая, когда указатель пустой и точность
    int size = (length > info.width_flag ? length : info.width_flag) +
               2;  // вычисляем размер результирующей строки
    char *result = calloc(
        size, sizeof(char));  // аллоцируем память для результирующей строки
    int i = 0;
    // заполняем ширину пробелами, если необходимо
    for (; !info.minus_flag && (info.width_flag - length > 0);
         i++, info.width_flag--) {
      if (info.zero_flag)
        result[i] = '0';
      else
        result[i] = ' ';
    }

    // копирование строки в результирующую
    if (x != NULL) {
      for (int q = 0; q < length; q++, i++) {
        result[i] = x[q];
      }
    } else if (length != 0) {
      char *string = "(null)";
      for (int rt = 0; rt < 7; rt++, i++) result[i] = string[rt];
    }
    result[i] = '\0';
    // заполняем ширину пробелами, если необходимо (для флага minus)
    if (info.minus_flag) {
      for (; s21_strlen(result) < (my_size_t)info.width_flag; i++) {
        result[i] = ' ';
      }
    }
    s21_strcat(*str, result);  // к выходной строке добавляем результирующую
    *str += s21_strlen(result);  // обновляем указатель на выходную строку
    *count += s21_strlen(result);  // обновляем количество символов
    free(result);
  }
  return *str;
}

// для не ascii символов
char *wCharPointers(char **str, flags info, va_list *ptr, const char **format,
                    unsigned int *count) {
  // почти то же самое, что для строки обычных символов
  int count_ascii_symbols = 0;
  wchar_t *symbols = va_arg(*ptr, wchar_t *);
  if (symbols != 0) {  // но если строка ненулевая
    for (; count_ascii_symbols >= 0 && symbols[count_ascii_symbols];
         count_ascii_symbols++)
      if (symbols[count_ascii_symbols] > 127) count_ascii_symbols = -2;
  }

  if (count_ascii_symbols < 0) {
    // то функция ставит 0 в финальную строку
    **str = 0;
    *format = 0;  // помечаем ошибку
  } else {        // для обычной строки
    int i = 0;
    int length = symbols == 0 ? 6 : count_ascii_symbols;
    if (info.prec_flag && info.precision_flag < length)
      length = info.precision_flag;
    if (info.prec_flag && symbols == 0 && info.precision_flag < 6) length = 0;
    int size = (length > info.width_flag ? length : info.width_flag) + 2;
    char *result = calloc(size, sizeof(char));

    for (; !info.minus_flag && (info.width_flag - length > 0);
         i++, info.width_flag--) {
      result[i] = ' ';
    }
    if (symbols != 0) {
      for (int q = 0; q < length; q++, i++) {
        result[i] = symbols[q];
      }
    } else if (length != 0) {
      char *string = "(null)";
      for (int rt = 0; rt < 7; rt++, i++) result[i] = string[rt];
    }
    result[i] = '\0';
    if (info.minus_flag) {
      for (; (int)s21_strlen(result) < info.width_flag;)
        s21_strcat(result, " ");
    }
    s21_strcat(*str, result);
    *str += s21_strlen(result);
    *count += s21_strlen(result);
    free(result);
  }
  return *str;
}

char *pointers(char **str, flags info, va_list *ptr, unsigned int *count) {
  long long int A = va_arg(*ptr, long long int);
  char adress[20] = {0};  // здесь хранится значение поинтера без форматирования

  if (A == 0) {
    s21_strcat(adress, "(null)");
  } else {
    specUItoa(A, adress, 16);  // записываем значение поинтера
  }

  int size = 0;

  if ((20 + 4) > (info.precision_flag + 4 > info.width_flag + 2
                      ? info.precision_flag + 4
                      : info.width_flag + 2)) {
    size = 20 + 4;
  } else if ((info.precision_flag + 4) > (info.width_flag + 2)) {
    size = info.precision_flag + 4;
  } else {
    size = info.width_flag + 2;
  }
  // массив для записи с форматированием
  // 0x в начале числа учитывается в ширине, но не в точности, поэтому в
  // одном месте +2, в другом +4
  char *result = calloc(size, sizeof(char));
  int i = 0;
  for (; !info.minus_flag &&
         (info.width_flag -
              ((info.precision_flag * (A != 0)) > (int)s21_strlen(adress)
                   ? (info.precision_flag * (A != 0))
                   : (int)s21_strlen(adress)) -
              2 * (A != 0) >
          0);
       i++, info.width_flag--) {
    result[i] = ' ';  // если нужно печатать ширину - печатаем
  }
  if (A != 0) {  // если ненулевой указатель
    if (info.plus_flag == 1 || info.space_flag == 1) {  // печатаем + или пробел
      if (i != 0)
        result[i - 1] = info.plus_flag ? '+' : ' ';  // печатаем за счёт ширины
      else {  // если в начале ширины не было
        result[i] = info.plus_flag ? '+' : ' ';  // печатаем первым символом
        i++;  // и сдвиг по строке
      }
    }
    result[i] = '0';  // печатаем базу 16-ричного числа
    result[i + 1] = 'x';
    i += 2;  // сдвиг на 2 символа для последующей печати
  }
  for (; A != 0 && info.precision_flag - (int)s21_strlen(adress) > 0;
       i++, info.precision_flag--) {
    result[i] = '0';  // если нужно дополнить нулями для точности - делаем это
  }
  result[i] = '\0';
  // в формат-строку заносим значение поинтера
  s21_strcat(result, adress);
  if (info.minus_flag) {  // если после поинтера нужно дополнить шириной
    for (; (int)s21_strlen(result) < info.width_flag;) s21_strcat(result, " ");
  }
  unsigned int add = s21_strlen(result);
  // копируем формат-строку в финальную
  s21_strcat(*str, result);
  *count += add;
  free(result);
  return *str + add;  // сдвигаемся по финальной строке для дальнейшей печати
}

char *integerPointers(char **str, va_list *ptr, unsigned int count) {
  int *x = va_arg(*ptr, int *);  // этот флаг ничего не дописывает в строку
  *x = count;   // место, в которое записываем int
  return *str;  // записываем количество напечатанных символов
}

void resetFlags(flags *info) {
  info->length_flag = 0;
  info->minus_flag = 0;
  info->plus_flag = 0;
  info->precision_flag = 0;
  info->octothorpe_flag = 0;
  info->space_flag = 0;
  info->specifier_flag = 0;
  info->prec_flag = 0;
  info->width_flag = 0;
  info->zero_flag = 0;
}

char *reverse(char s[]) {
  char tmp;
  int i, j;
  for (i = 0, j = s21_strlen(s) - 1; i < j; ++i, --j) {
    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }

  return s;
}

char *specItoa(long long int value, char *result, int base) {
  int n = llabs(value), i = 0;

  while (n) {
    int r = n % base;
    if (r >= 10) {
      result[i++] = 97 + (r - 10);
    } else {
      result[i++] = 48 + r;
    }
    n /= base;
  }
  if (i == 0) {
    result[i++] = '0';
  }
  if (value < 0) {
    result[i++] = '-';
  }
  result[i] = '\0';

  return reverse(result);
}

char *specUItoa(long long unsigned value, char *result, int base) {
  long long unsigned n = value;
  int i = 0;

  while (n) {
    int r = n % base;
    if (r >= 10) {
      result[i++] = 97 + (r - 10);
    } else {
      result[i++] = 48 + r;
    }
    n /= base;
  }
  if (i == 0) {
    result[i++] = '0';
  }
  result[i] = '\0';

  return reverse(result);
}

void widthHelper(char *result, flags info, int *i, int str_length) {
  // если в этом месте нужно печатать ширину
  while (
      !info.minus_flag &&
      (info.width_flag - (info.precision_flag > str_length ? info.precision_flag
                                                           : str_length) >
       0)) {
    if (!info.prec_flag && info.zero_flag)
      result[(*i)] = '0';  // печатаем нулями
    else
      result[(*i)] = ' ';  // или пробелами, в зависимости от флагов
    (*i)++;
    info.width_flag--;
  }
}

void negativeSign(char *str, int i) {
  int n = 0;
  if (!(str[0] == '0' || i == 0)) n = i - 1;  // куда надо поставить знак
  str[n] = '-';
}

void positiveSign(flags info, char *str, int i) {
  int n = 0;
  if (!(str[0] == '0' || i == 0)) n = i - 1;  // куда надо поставить знак
  if (info.plus_flag)
    str[n] = '+';
  else if (info.space_flag)
    str[n] = ' ';  // или пробел
}

void printBase(flags info, unsigned long x, char *result, int *i,
               int *precision) {
  if (info.octothorpe_flag && x != 0) {  // если надо написать базу числа
    int base = 0;  // здесь отмечаем позицию для записи базы
    if (info.specifier_flag == 'o') {  // если 8-ричное число
      if ((*i) > 0 && result[(*i) - 1] == 32)
        base = (*i) - 1;  // если базу надо писать не в начало
      if (base == 0) {
        (*i)++;  // сдвигаемся по строке, потому что сюда уже будем писать базу
      }
      result[base] = '0';
      (*precision)--;  // у восьмеричного числа база учитывается в точности
    } else if (info.specifier_flag == 'x' ||
               info.specifier_flag == 'X') {  // если 16-ричное число
      if ((*i) > 1 && result[(*i) - 1] == 32) {
        base = (*i) - 2;  // если мы можем взять оба символа из ширины то
                          // запишем базу в счёт ширины
      } else if ((*i) == 1 &&
                 result[(*i) - 1] == 32) {  // заберём из ширины один символ
        (*i)++;  // поэтому сдвиг для дальнейшей записи будет в один символ
      } else {  // тут не сможем взять из ширины, оба символа базы запишутся с
                // текущей позиции
        (*i) += 2;  // поэтому для дальнейшей записи сдвигаемся на 2
      }
      result[base] = '0';  // первый символ 16-ричной базы - 0
      result[base + 1] = info.specifier_flag;  // второй - x или X
    }
  }
}

int numberToStr(long double x, char *nu, long double x1, int *length) {
  int inf_or_nan = 0;
  if (isnan(x)) {
    s21_strcat(nu, "nan");  // если аргумент NAN - записываем его в строку
    inf_or_nan = 1;       // отметили это
  } else if (isinf(x)) {  // тоже с INF, но тут уже есть знак
    if (isinf(x) > 0)
      s21_strcat(nu, "inf");
    else
      s21_strcat(nu, "-inf");
    inf_or_nan = 1;  // отметили это
  } else {  // записываем число в строку, если всё корректно
    doubleToStr(x, x1, nu, length);
  }

  return inf_or_nan;
}

void doubleToStr(long double x, long double x1, char *nu, int *length) {
  if (x < 0) x = -1 * x;
  x1 = (x - fmodl(x, 1));
  char *kind_of_int = nu;
  if (x1 == 0)
    nu[0] = '0';
  else {
    recursiveLongInt(x, 1, &kind_of_int);
  }
  s21_strcat(nu, ".");  // точка после целой части числа
  *length = s21_strlen(nu);  // фиксируем длину числа
  x1 = x =
      fabsl(fmodl(x, 1));  // берём дробную часть исходного числа (по модулю)
  char digit[2] = {'0', 0};
  for (int z = 0; z < 50; z++) {  // максимально печатаемая точность около 49
    x1 = x = x * 10;  // первое число после точки ставим перед точкой
    x1 -= fmodl(x1, 1);  // убираем дробную часть числа, так что останется
                         // только цифра перед точкой
    digit[0] = x1 + '0';
    s21_strcat(
        nu,
        digit);  // добавляем её в строку, в которую записываем исходное число
    x1 = x = fmodl(x, 1);  // записываем сюда десятичную часть исходного числа
                           // после того, как забрали из неё ещё один символ
  }
}

void processingWithG(int *specificator, int *precision, char *nu, int *og,
                     long double x) {
  if (*specificator == 'e' || *specificator == 'E' || *specificator == 'g' ||
      *specificator == 'G') {
    if (*specificator == 'g' || *specificator == 'G') *og = 1;
    int exp = 0, exp_help = 1;
    if ((x < 10 && x > -10) && fmodl(x, 1) == 0)
      exp_help = 0;  // если экспонента 0
    if (exp_help) {  // если модуль экспоненты больше 0
      if (nu[0] > '0') {  // положительная экспонента
        for (; nu[exp] != '.'; exp++)
          ;  // будет равна номеру позиции десятичной точки -1
      } else {
        for (; nu[exp] == '0' || nu[exp] == '.'; exp++)
          ;
        // будет равна позиции первого ненулевого символа -1
      }
      --exp;
      if (nu[0] == '0')
        exp = -1 * exp;  // если экспонента должна быть отрицательной
    }
    if (*specificator == 'g' || *specificator == 'G') {
      if (*precision == 0) *precision = 1;
      if ((-4 <= exp && exp < *precision) ||
          !exp) {  // здесь g отрабатывает как f
        *precision = *precision - exp - 1;  // но меняет точность вот так
      } else {            // здесь отрабатывает как g/G
        *precision -= 1;  // но меняет точность вот так
        *specificator -= 2;  //  поменяем спецификатор с g/G на e/E
        *og = 1;  // но отметим, что изначально это был g/G
      }
    }
    if (*precision < 0) *precision = 0;
  }
}

void processingWithE(long double x, flags info, int precision, char **nu1,
                     int og) {
  char *nu = *nu1;
  int i = 0;
  char *nunu = calloc(s21_strlen(nu), sizeof(char));
  expToStr(x, nu, nunu, info, &i,
           precision);  // записываем мантиссу в строку корректно

  if (og && !info.octothorpe_flag) {  // если g и нужно отрезать нули
    for (int s = s21_strlen(nu) - 1; s > 0 && nu[s] == '0'; s--) nu[s] = 0;
  }  // то отрезаем нули
  if (x != 0) {  // в строку записываем значение экспоненты
    if (i - 1 < 10) {  // если экспонента < 10
      s21_strcat(nunu, "0");  // первой цифрой экспоненты надо записать 0
      specItoa(i - 1, &(nunu[3]),
               10);  // вставляем значение экспоненты после "e+0" или "e-0"
    } else {  // если экспонента больше 10 по модулю, 0 в начале не нужен
      specItoa(i - 1, &(nunu[2]), 10);  // поэтому тут после "e+" или "e-"
    }
  }
  if (nu[s21_strlen(nu) - 1] == '.' && !info.octothorpe_flag)
    nu[s21_strlen(nu) - 1] = 0;  // убираем точку, если она не нужна
  s21_strcat(nu, nunu);  // к строчке с мантиссой добавляем строчку, в которой
                         // записали экспоненту
  free(nunu);
}

// округляем десятичную дробь в соотвествии с нужной точностью
void roundDouble(int length, int precision, char *nu, flags info) {
  unsigned int str_length = s21_strlen(nu);
  if ((unsigned int)(length + precision) <
      s21_strlen(nu)) {  // если строка должна быть короче
    int s = 1;
    int dot = 0;
    if (nu[length + precision] >= '5') {  // если предыдущую цифру нужно менять
      while (nu[length + precision - s] == '9' ||
             nu[length + precision - s] == '.') {
        // пока встречаем 9-ки или точку
        if (nu[length + precision - s] == '.')
          dot = 1;  // отмечаем точку
        else
          nu[length + precision - s] = '0';  // зануляем число
        ++s;                                 // двигаемся  влево
      }
      if (nu[length + precision - s] ==
          0)  // если мы оказались в позиции, где числа раньше не было
        nu[length + precision - s] = '1';  // заносим туда единицу
      else
        nu[length + precision - s] += 1;  // иначе число увеличится на 1
    }
    if (precision == 0)  // если нужна нулевая точность, тоже отметим точку
      dot = 1;
    if (!dot)  // если точки не было, то после числа 0
      nu[length + precision] = 0;
    else {  // если точка есть, то цифры числа после точки при округлении
            // отрезаются
      int dot_location = 0;
      for (; nu[dot_location] != '.'; dot_location++)  // находим точку
        ;
      if (!info.octothorpe_flag && precision == 0)
        nu[dot_location] = 0;  // если её надо оставить - оставляем
      else
        nu[dot_location + precision + 1] =
            0;  // если нет - отрезаем вместе с остатком числа
    }
    for (unsigned int sl = s21_strlen(nu); sl < str_length; sl++)
      nu[sl] = 0;  // чистим остаток строки
  }
}

// после точки обрезает нули
void cutOffZeros(char *nu, flags info, int og) {
  if (og && !info.octothorpe_flag) {  // если изначально  g/G
    int there_is_dot = 0;
    for (unsigned int s = 0; s < s21_strlen(nu); s++)
      if (nu[s] == '.') there_is_dot = 1;
    for (int s = s21_strlen(nu) - 1; there_is_dot && s > 0 && nu[s] == '0'; s--)
      nu[s] = 0;  // ищем точку и отрезаем нули в конце
  }
}

void recursiveLongInt(long double d_arg, int symbols, char **str) {
  long double divider = powl(10, symbols);
  int temp =
      (int)(fmodl(d_arg, divider) / (divider / 10.));  // берём нужную цифру
  if (d_arg / divider >= 1) {  // если число можно делить дальше
    symbols++;
    recursiveLongInt(d_arg, symbols, str);  // то делим дальше
  } else if ((int)d_arg == 0) {
    temp = 0;  // там, где необходимо записать 0 - записываем 0
  }
  **str = temp + '0';  // записываем в строчку нужный чар
  (*str)++;            // сдвигаемся
  **str = '\0';
}

void expToStr(long double x, char *nu, char *nunu, flags a, int *i,
              int precision) {
  if (nu[0] > '0') {  // в этом случае экспонента будет положительной
    for (; nu[(*i)] != '.'; (*i)++)
      ;  // и мы ищем её значение по положению точки
    for (int j = *i; j > 1; j--) nu[j] = nu[j - 1];  // сдвигаем число так
    nu[1] = '.';  // чтобы была одна цифра до десятичной точки, остальные после
    s21_strcat(nunu,
               "e+");  // строчка, в которую будем писать значение экспоненты
    roundDouble(2, precision, nu,
                a);  // округляем мантиссу до нужной точности
    if (nu[-1] != 0) {  // если после округления число стало длинее
      nu[0] = '.';  // смещаем точку на один символ влево
      s21_memmove(
          &nu[1], &nu[2],
          precision + 1);  // смещаем оставшееся число к новому положению точки
      for (int y = precision + 1; y < 80; y++)
        nu[y] = 0;  // чистим ненужную часть строки
      (*i)++;  // инкрементируем значение экспоненты, потому что сдвинули точку
    }
  } else if (x == 0) {  // если исходное число равно нулю
    s21_strcat(nunu, "e+00");  // вид экспоненты такой
    roundDouble(2, precision, nu, a);  // округляем число до нужной точности
  } else {  // иначе экспонента будет отрицательной
    for (; nu[(*i)] == '0' || nu[(*i)] == '.'; (*i)++)
      ;  // и равной положению первой ненулевой цифры
    nu[0] = nu[(*i)];  // первым символом станет первый ненулевой символ
    s21_memmove(&nu[2], &nu[(*i) + 1],
                precision + 1);  // смещаем к точке нужное количество символов
    roundDouble(2, precision, nu, a);  // округляем до нужной точности
    if (nu[-1] == '1') {  // если после округления число стало длиннее
      nu[0] = '.';  // смещаем точку влево
      s21_memmove(&nu[1], &nu[2],
                  precision + 1);  // смещаем оставшуюся часть числа к точке
      (*i)--;  // увеличиваем отрицательную экспоненту из-за смещения точки
    }
    // при увеличении отрицательная экспонента могла стать равной нулю
    if ((*i) - 1 == 0)
      s21_strcat(nunu, "e+");  // а с нулевой экспонентой надо писать "e+"
    else
      s21_strcat(nunu, "e-");  // иначе пишем "e-"
  }
}

void toUpper(char *x) {
  for (int i = 0; x[i]; ++i) {
    if (x[i] >= 'a' && x[i] <= 'z') x[i] -= 32;
  }
}

void *s21_memmove(void *dest, const void *src, my_size_t n) {
  unsigned char *ptr_dest = (unsigned char *)dest;
  const unsigned char *ptr_src = (const unsigned char *)src;

  if (ptr_src < ptr_dest)
    for (ptr_dest += n, ptr_src += n; n--;) *--ptr_dest = *--ptr_src;
  else
    while (n--) *ptr_dest++ = *ptr_src++;

  return dest;
}

char *s21_strcat(char *dest, const char *src) {
  while (*dest) ++dest;
  while (*src) *dest++ = *src++;

  return dest;
}
