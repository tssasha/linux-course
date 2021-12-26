#include <rhash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

ssize_t my_getline(char **line) {
#ifdef READLINE
    free(*line);

    *line = readline(NULL);
	if (*line == NULL) {
        return 0;
    }
    add_history(*line);
    return strlen(*line);
#else
    size_t alloc_size = 0;
    return getline(line, &alloc_size, stdin);
#endif
}

int calculate_hash(const char* msg, char* output, unsigned algo_hash, int flags) {
    char digest[64];
    int res;

    if (msg[0] == '"') {
        msg += 1;
        res = rhash_msg(algo_hash, msg, strlen(msg), digest);
    } else {
        res = rhash_file(algo_hash, msg, digest);
    }
    if(res < 0) {
        fprintf(stderr, "Cannot calculate hash\n");
        return res;
    }

    rhash_print_bytes(output, digest, rhash_get_digest_size(algo_hash), flags);
    return 0;
}

int main() {
    rhash_library_init();
    char output[130];
    char *line = NULL;

    while (my_getline(&line) > 0) {
        char* algo = strtok(line, " ");
        int algo_flag, algo_hash;
        if (isupper(algo[0])) {
            algo_flag = RHPR_HEX;
        } else {
            algo_flag = RHPR_BASE64;
        }

        if (!strcasecmp(algo, "sha1")) {
            algo_hash = RHASH_SHA1;
        } else if (!strcasecmp(algo, "md5")) {
            algo_hash = RHASH_MD5;
        } else if (!strcasecmp(algo, "tth")) {
            algo_hash = RHASH_TTH;
        } else {
            fprintf(stderr, "Unsupported hash algorithm\n");
            continue;
        }

        char* msg = strtok(NULL, " ");
        if (msg == NULL || *msg == '\0') {
            fprintf(stderr, "Empty string\n");
            continue;
        }
        msg_len = strlen(msg);
        if (msg_len > 0 && msg[msg_len - 1] == '\n') {
            msg[msg_len - 1] = '\0';
        }
        if (!calculate_hash(msg, output, algo_hash, algo_flag)) {
            printf("%s\n", output);
        }
    }
    free(line);
    return 0;
}