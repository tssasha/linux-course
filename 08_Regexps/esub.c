#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>

#define MAX_MATCHES 10

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Invalid number of arguments\n");
        return -1;
    }
    const char* regexp = argv[1];
    const char* substitution = argv[2];
    const char* string = argv[3];

    regex_t regex_comp;
    char msgbuf[100];

    int reti = regcomp(&regex_comp, regexp, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return -1;
    }

    regmatch_t matches[MAX_MATCHES];
    reti = regexec(&regex_comp, string, MAX_MATCHES, matches, 0);
    if (reti && reti != REG_NOMATCH) {
        regerror(reti, &regex_comp, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex_comp);
        return -1;
    }

    const char *ptr = string;
    for (int pos = 0; *ptr != '\0'; ptr++, pos++) {
        if (reti == REG_NOMATCH || pos != matches->rm_so) {
            putchar(*ptr);
            continue;
        }
        ptr += matches->rm_eo - matches->rm_so - 1;
        for (const char *sptr = substitution; *sptr != '\0'; sptr++) {
            if (*sptr != '\\') {
                putchar(*sptr);
                continue;
            }
            sptr++;
            if (*sptr == '\\') {
                putchar(*sptr);
            }
            else if (isdigit(*sptr)) {
                int digit = *sptr - '0';
                if (digit == 0) {
                    putchar('0');
                }
                else {
                    for (regoff_t pos = (matches + digit)->rm_so; pos < (matches + digit)->rm_eo; pos++) {
                        putchar(string[pos]);
                    }
                }
            }
            else {
                fprintf(stderr, "Incorrect substitution\n");
                regfree(&regex_comp);
                return -1;
            }
        }
    }
    putchar('\n');
    regfree(&regex_comp);
}