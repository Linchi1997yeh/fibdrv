#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"
#define LENGTH 100
#define BUFFSIZE 8 * sizeof(int) * LENGTH / 3 + 2
#define LOGPHI 0.20898764025
#define LOGSQRT5 0.34948500216
int main()
{
    int offset = 5000; /* TODO: try test something bigger than the limit */
    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }
    for (int i = 4000; i <= offset; i++) {
        // calculate how many digits are needed for fib(i)
        // digits needed for fib(n) = n*LOG(Phi) - (LOG √5)
        float digits = i * LOGPHI - LOGSQRT5;
        float buf_size = floor(digits / 9);
        int size = (int) buf_size;
        if (size < 0) {
            size = 0;
        }
        char *buf = malloc(sizeof(char) * (BUFFSIZE * size));
        lseek(fd, i, SEEK_SET);
        long long time1 = read(fd, buf, size);
        // long long time2 = read(fd, buf, 1);

        // output time and result
        printf("%d %lld %d %s\n", i, time1, size, buf);
        // printf("%d %lld %lld %s\n", i, time1);

        // printf("%d %lld %lld %s\n", i, time1, time2, buf);
        free(buf);

        // printf("%d %s \n", i, buf); // output fibonacci number
    }

    close(fd);
    return 0;
}
