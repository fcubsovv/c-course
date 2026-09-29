#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

size_t user_strlen(const char * s) {
    size_t i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

int n_fputs(const unsigned char *str, FILE *stream) {
    while (*str != '\n' && *str != '\0') {
        if (fputc(*str, stream) == EOF) {
            return EOF;
        }
        str++;
    }
    if (*str == '\n') {
        if (fputc('\n', stream) == EOF) {
            return EOF;
        }
    }
    return 0;
}
size_t user_strnlen(const char *s, size_t maxlen) {
    for (size_t i = 0; i <= maxlen; i++) {
        if (s[i] == '\0') {
            return i + 1;
        }
    }
    return maxlen;
}

char * user_strchr(const char * s, int c) {
    while( *s != '\0' ) {
        if(*s == c) {
            return (char *)s;
        }
        s++;
    }
    if (c == '\0') {
        return (char *)s;
    }
    return NULL;
}

int user_strcmp(const char * s1, const char * s2) {
    while (*s1 == *s2) {
        if (*s1 == '\0') {
            return 0;
        }
        s1++;
        s2++;
    }
    return *s1-*s2;
}
int user_strncmp(const char * s1, const char * s2, size_t n) {
    int i = 0;
    while (s1[i] == s2[i] && i < n) {
        if (s1[i] == '\0') {
            return 0;
        }
    }
    return s1[i] - s2[i];
}

char * user_strcpy(char * dest, const char * src) {
    for (int i = 0; (dest[i] = src[i]) != '\0'; i++);
    return dest;
}

char * user_strncpy(char *dest, const char *src, size_t n) {
    int i = 0;
    for (;(i < n) && (dest[i] = src[i]) != '\0';i++);
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

char * user_strcat(char *dest, const char *src) {
    char * first_pointer = dest;
    while (*dest != '\0') {
        dest++;
    }
    while ((*dest = *src) != '\0') {
        dest++;
        src++;
    }
    return first_pointer;
}

char * user_strncat(char *dest, const char *src, size_t n) {
    char * first_pointer = dest;
    while (*dest != '\0')
        dest++;
    for (size_t i = 0; i < n && src[i] != '\0'; i++) {
        *dest = src[i];
        dest++;
    }
    *dest = '\0';
    return first_pointer;
}

char * user_strdup(const char * s) {
    size_t size = user_strlen(s) + 1;
    char * new_string = (char *)malloc(size * sizeof(char));
    if (new_string == NULL) {
        return NULL;
    }
    char * new_start = new_string;
    for (;(*new_string = *s) != '\0';) {
        new_string++;
        s++;
    }
    return new_start;
}

char * user_strndup(const char *s, size_t n) {
    const size_t realsize = user_strlen(s);
    const size_t size = realsize > n ? n : realsize;
    char * new_string = (char *)calloc(size + 1, sizeof(char));
    if (new_string == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        new_string[i] = s[i];
    }
    return new_string;
}

char * user_strrvs(char * s) {
    int size = user_strlen(s);
    for (int i = 0; i < size/2; i++) {
        char temporary = s[i];
        s[i] = s[size - i - 1];
        s[size - i - 1] = temporary;
    }
    return s;
}

int user_puts(const char * string) {
    for (;*string!='\0'; string++) {
        putchar(*string);
    }
    putchar('\n');
    return 0;
}

char * user_strstr(const char *haystack, const char *needle) {
    char * runner = (char*) haystack;
    char * finder = (char*) needle;
    while(*runner!='\0') {
        if(*runner == *needle) {
            char * started = runner;
            finder = (char*) needle;
            while(*runner == *finder) {
                runner++;
                finder++;
                if (*finder == '\0') {
                    return started;
                }
            }
            runner = started;
        }
        runner++;
    }
    return NULL;
}

char * user_strnstr(const char *haystack, const char *needle, size_t len) {
    char * runner = (char*) haystack;
    char * finder = (char*) needle;
    for (size_t i = 0; i < len && *runner!='\0'; i++) {
        if(*runner == *needle) {
            char * started = runner;
            finder = (char*) needle;
            while(*runner == *finder) {
                runner++;
                finder++;
                if (*finder == '\0') {
                    return started;
                }

            }
            runner = started;
        }
    runner ++;
    }
    return NULL;
}



char * user_fgets(char * s, int size, FILE * stream) {
    int c = 0;
    int i = 0;
    for (; i < size - 1 && (c = fgetc(stream)) != EOF; i++) {
        if (c == '\n') {
            s[i] = c;
            i++;
            break;
        }
        s[i] = c;
    }
    if (i == 0) {
        return NULL;
    }
    s[i] = '\0';
    return s;
}

int user_fputs(const char *s, FILE *stream) {
    while(*s!='\0') {
        if(fputc(*s, stream) == EOF) {
            return EOF;
        }
        s++;
    }
    return 0;
}

ssize_t user_getline(char * * lineptr, size_t * n, FILE * stream) {
    int c = 0;
    size_t i = 0;
    if (* lineptr == NULL && * n == 0) {
        * n = 16;
        *lineptr = (char *)calloc(*n, sizeof(char));
        if(* lineptr == NULL) {
            return -1;
        }
    }
    if (lineptr == NULL || n == 0 || stream == NULL) {
        return -1;
    }
    for (i = 0; (c = fgetc(stream)) != EOF && c != '\n'; i++) {
        if (i+2 > *n) {
            size_t new_size = *n * 2;
            char * new_ptr = (char*)realloc(*lineptr, new_size);
            *lineptr = new_ptr;
            *n = new_size;
            if(new_ptr == NULL) {
                return -1;
            }
        }
        (*lineptr)[i] = c;
    }
    if (c == '\n') {
        (*lineptr)[i] = c;
        i++;
    }
    (*lineptr)[i] = '\0';
    return i;
}

char * user_itoa (int num, char * buffer) {
    int i = 0, sign = 0;
    if ((sign = num) < 0) {
        num = -num;
    }
    do {
        buffer[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);
    if (sign < 0) {
        buffer[i++] = '-';
    }
    buffer[i] = '\0';
    user_strrvs(buffer);
    return buffer;
}
int user_atoi (char * str) {
    int number = 0;
    while (*str!= '\0'){
        number*=10;
        number+=*str-'0';
        str++;
    }
    return number;
}

float user_atof (char * str) {//TODO minus
    float number = 0;
    while (*str != '.') {
        number*=10;
        number+=*str-'0';
        str++;
    }
    float bottom = 1;
    while (*str != '\0') {
        bottom/=10;
        number+=bottom*(*str-'0');
    }
    return number;
}

char * user_strsep(char * * stringp, const char *delim) {
    if(stringp == NULL && *stringp == NULL) {
        return NULL;
    }
    char * start = * stringp;
    char * element = strpbrk(start, delim);
    if (element != NULL) {
        *element = '\0';
        element ++;
        *stringp = element;
    } else {
        *stringp = NULL;
    }
    return start;
}


void * user_memmove(void *dst, const void *src, size_t len) {
    const char * new_src = (const char *) src;
    char * new_dst = (char *)dst;

    if (new_dst < new_src) {
        while (len--) {
            *(new_dst++) = *(new_src++);
        }
    } else {
        const char * last_s = new_src + (len - 1);
        char * last_d = new_dst + (len - 1);
        while (len--) {
            *(last_d--) = *(last_s--);
        }
    }
    return dst;
}


void * user_memcpy(void *dest, const void *src, size_t n) {
    unsigned char * new_dest = (unsigned char *)dest;
    const unsigned char *new_src = (const unsigned char *)src;

    size_t steps = n / sizeof(uint64_t);
    size_t remaining = n % sizeof(uint64_t);
    for (size_t i = 0; i < steps; i++) {
        *(uint64_t*)new_dest = *(uint64_t*)new_src;
        new_dest += sizeof(uint64_t);
        new_src += sizeof(uint64_t);
    }
    if (remaining == 0) {
        return dest;
    }

    size_t steps_4 = remaining / sizeof(uint32_t);
    size_t remaining_after_steps_4 = remaining % sizeof(uint32_t);
    for (size_t i = 0; i < steps_4; i++) {
        *(uint32_t*)new_dest = *(uint32_t*)new_src;
        new_dest += sizeof(uint32_t);
        new_src += sizeof(uint32_t);
    }
    if (remaining_after_steps_4 == 0) {
        return dest;
    }

    size_t steps_2 = remaining / sizeof(uint16_t);
    size_t remaining_after_steps_2 = remaining % sizeof(uint16_t);
    for (size_t i = 0; i < steps_2; i++) {
        *(uint16_t*)new_dest = *(uint16_t*)new_src;
        new_dest += sizeof(uint16_t);
        new_src += sizeof(uint16_t);
    }
    if (remaining_after_steps_2 == 0) {
        return dest;
    }

    for (size_t i = 0; i < remaining_after_steps_2; i++) {
        *new_dest = *new_src;
        new_dest++;
        new_src++;
    }
    return dest;
}

void strclean (char* src) {
    char *dst = src;
    while (*src) {
        if (islower(*src)) *dst++ = *src;
        src++;
    }
    *dst = '\0';
}
