#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define FIB_DEV "/dev/fibonacci"

int main()
{
    // char buf[1];
    char write_buf[] = "testing writing";
    int offset = 100; /* TODO: try test something bigger than the limit */
    int iterations = 10000;
    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }
    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        double time_1[iterations];
        double time_2[iterations];
        double mean_t1 = 0.0, sd_k = 0.0, sd_u = 0.0, mean_t2 = 0.0,
               res_t1 = 0.0, res_t2 = 0.0, time_dif = 0.0;
        int count_t1 = 0, count_t2 = 0;
        // Choose 2 metrics (t1, t2) to be calculated
        for (int j = 0; j < iterations; j++) {
            long long t1, t2;
            t2 = write(fd, write_buf, 0);
            t1 = write(fd, write_buf, 1);
            time_1[j] = t1;
            time_2[j] = t2;
            mean_t1 += t1;
            mean_t2 += t2;
        }
        // get mean
        mean_t1 /= iterations;
        mean_t2 /= iterations;

        // get standar deviation
        for (int j = 0; j < iterations; j++) {
            sd_k += (time_1[j] - mean_t1) * (time_1[j] - mean_t1);
            sd_u += (time_2[j] - mean_t2) * (time_2[j] - mean_t2);
        }
        sd_k = sqrt(sd_k / (iterations - 1));
        sd_u = sqrt(sd_u / (iterations - 1));


        // remove outliers
        for (int j = 0; j < iterations; j++) {
            if (time_1[j] <= (mean_t1 + 2 * sd_k) &&
                time_1[j] >= (mean_t1 - 2 * sd_k)) {
                res_t1 += time_1[j];
                count_t1 += 1;
            }
            if (time_2[j] <= (mean_t2 + 2 * sd_u) &&
                time_2[j] >= (mean_t2 - 2 * sd_u)) {
                res_t2 += time_2[j];
                count_t2 += 1;
            }
        }
        res_t1 /= count_t1;
        res_t2 /= count_t2;
        time_dif = res_t2 - res_t1;
        printf("%d %f %f %f \n", i, res_t1, res_t2, time_dif);
    }

    close(fd);
    return 0;
}
