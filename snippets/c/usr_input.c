// https://stackoverflow.com/questions/54055462/what-is-the-vulnerability-in-this-c-code

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int
main(int argc, char **argv)
{
    (void) foo(argv[1]);
    exit(0);
}

int
foo(char *arg)
{
    return bar(arg);
}

int
bar(char *arg)
{
    char lbuf[1024];
    if (strlen(&arg) >= 1024)
        return -1;

    memset(lbuf, 0, sizeof(lbuf));
    sprintf(lbuf, "%s", "Welcome: ");
    read(0, lbuf + strlen(lbuf), sizeof(lbuf) - strlen(lbuf) - 1);
    printf(lbuf);
    fflush(stdout);

    return 0;
}
