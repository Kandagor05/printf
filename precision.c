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
            int precision = -1; // Initialize precision to -1 (undefined)

            // Check for precision (e.g., %5c, %.10s, etc.)
            if (*format == '.') {
                format++; // Move past the dot ('.')
                // Parse the precision value from the format string
                precision = 0;
                while (*format >= '0' && *format <= '9') {
                    precision = precision * 10 + (*format - '0');
                    format++;
                }
            }

            switch (*format) {
                case 'c':
                    ch = va_arg(args, int);
                    putchar(ch);
                    printed_chars++;
                    break;
                case 's':
                    str = va_arg(args, const char *);
                    if (precision < 0) {
                        // No precision specified, print the entire string
                        while (*str) {
                            putchar(*str);
                            str++;
                            printed_chars++;
                        }
                    } else {
                        // Print the string up to the specified precision
                        int i = 0;
                        while (*str && i < precision) {
                            putchar(*str);
                            str++;
                            i++;
                            printed_chars++;
                        }
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
    int count = _printf("Precision test: %.5s, %8c, %%%.3s\n", "Hello", 'A', "World");
    printf("Number of characters printed: %d\n", count);
    return 0;
}

