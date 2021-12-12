#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <unistd.h>


#define _(STRING) gettext(STRING)


int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("this", ".");
    textdomain("this");

    int min = 1, max = 100, mid;

    printf(_("Please select number between %d and %d, and make it secret\n"), min, max);
    printf(_("Do Androids Dream of Electric Sheep? I'll try to guess it\n"));

    while (min != max) {
        mid = (max + min) / 2;
        printf(_("Is your number greater than %d? (y - yes, n - no)\n"), mid);
        char buffer[16] = {"\0"};
        scanf("%s", buffer);
        buffer[2] = '\0';

        if (!strcmp(_("y"), buffer))
            min = mid + 1;
        else if (!strcmp(_("n"), buffer))
            max = mid;
        else
            printf(_("I don't understand\n"));
    }
    printf(_("Your selected number is %d\n"), max);
    return 0;
}