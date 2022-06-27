#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"
#define LENGTH 100
#define BUFFSIZE 8 * sizeof(int) * LENGTH / 3 + 2

int main()
{
    long long sz;

    char buf[BUFFSIZE];
    char write_buf[] = "testing writing";
    int offset = 5000; /* TODO: try test something bigger than the limit */

    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    // for (int i = 0; i <= offset; i++) {
    //     sz = write(fd, write_buf, strlen(write_buf));
    //     printf("Writing to " FIB_DEV ", returned the sequence %lld\n", sz);
    // }

    // for (int i = 0; i <= offset; i++) {
    //     lseek(fd, i, SEEK_SET);
    //     sz = read(fd, buf, 1);
    //     printf("Reading from " FIB_DEV
    //            " at offset %d, returned the sequence "
    //            "%lld.\n",
    //            i, sz);
    // }

    // for (int i = offset; i >= 0; i--) {
    //     lseek(fd, i, SEEK_SET);
    //     sz = read(fd, buf, 1);
    //     printf("Reading from " FIB_DEV
    //            " at offset %d, returned the sequence "
    //            "%lld.\n",
    //            i, sz);
    // }

    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        long long time1 = read(fd, buf, 0);
        long long time2 = read(fd, buf, 1);
        printf("%d %lld %lld\n", i, time1, time2);  // output time
        // printf("%d %s \n", i, buf); // output fibonacci number
    }

    close(fd);
    return 0;
}
