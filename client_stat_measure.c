#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"

int main()
{
    char buf[1];
    // char write_buf[] = "testing writing";
    int offset = 100; /* TODO: try test something bigger than the limit */
    int iterations = 5;
    long long mean_k[offset + 1][iterations];
    long long mean_u[offset + 1][iterations];
    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    // test C kernel mode vs user model
    for (int j = 0; j < iterations; j++) {
        for (int i = 0; i <= offset; i++) {
            long long sz;
            struct timespec t_start, t_end;
            clock_gettime(CLOCK_REALTIME, &t_start);
            sz = write(fd, buf, 0);
            clock_gettime(CLOCK_REALTIME, &t_end);
            long long dif = t_end.tv_nsec - t_start.tv_nsec;
            // printf("%d %lld %lld\n", i, dif, sz);
            mean_k[i][j] = sz;
            mean_u[i][j] = dif;
            printf("%d %lld %lld \n", i, mean_k[i][j], mean_u[i][j]);
        }
    }


    close(fd);
    return 0;
}
