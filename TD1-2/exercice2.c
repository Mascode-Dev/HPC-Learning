#include <stdio.h>
#include <string.h>


size_t string_length_with_strlen(const char *str) {
    return strlen(str);
}

size_t string_length_manually(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main() {
    const char *str = "Hello World";

    size_t len1 = string_length_with_strlen(str);
    size_t len2 = string_length_manually(str);

    printf("Length using strlen: %zu\n", len1);
    printf("Length using manual iteration: %zu\n", len2);

    return 0;
}