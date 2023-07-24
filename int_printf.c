#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int printed_chars = 0;
    char ch;
    const char *str;

    while (*format) {
        if (*format == '%') {
            format++; // Move to the next character after '%'
            switch (*format) {
                case 'c':
                    ch = va_arg(args, int);
                    putchar(ch);
                    printed_chars++;
                    break;
                case 's':
                    str = va_arg(args, const char *);
                    while (*str) {
                        putchar(*str);
                        str++;
                        printed_chars++;
                    }
                    break;
                case '%':
                    putchar('%');
                    printed_chars++;
                    break;
                default:
                    putchar('%');
                    putchar(*format);
                    printed_chars += 2;
                    break;
            }
        } else {
            putchar(*format);
            printed_chars++;
        }
        format++;
    }

    va_end(args);
    return printed_chars;
}

int main() {
    int count = _printf("This is a test: %c %s %%\n", 'A', "Hello");
    printf("Number of characters printed: %d\n", count);
    return 0;
}

