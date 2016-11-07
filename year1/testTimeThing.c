#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int parse_date(char* date, struct tm* tm)
{
    char* format;
    char* formats[] = {
        "%F %I", /* "2011-03-12 06:38:05 AM" */
        "%F %T", /* "2011-03-12 18:38:05" */
        "%F %R", /* "2011-03-12 18:38" */
        NULL,
    };

    for (format = formats[0]; format; ++ format) {
        if (strptime(date, format, &tm)) {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char** argv)
{
    float diff;

    char* date1;
    char* date2;

    struct tm tm1;
    struct tm tm2;

    time_t time1;
    time_t time2;

    if (argc != 3) {
        fprintf(stderr, "usage: compare-date date1 date2\n");
        exit(1);
    }

    date1 = argv[1];
    date2 = argv[2];

    if (!parse_date(date1, &tm1)) {
        fprintf(stderr, "unsupported date: %s\n", date1);
        exit(1);
    }

    if (!parse_date(date2, &tm1)) {
        fprintf(stderr, "unsupported date: %s\n", date2);
        exit(1);
    }

    time1 = mktime(&tm1);
    time2 = mktime(&tm2);
    diff = difftime(time1, time2);

    printf("%s %c %s\n",
        date1,
        (diff < 0 ? '<' : (diff > 0 ? '>' : '==')),
        date2);

    return 0;
}
