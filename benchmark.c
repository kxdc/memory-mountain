#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define datatype to generate results
typedef double data_t;

data_t mount(data_t* data, size_t count, int stride)
{
    data_t result = 0;
    for(size_t i = 0; i < count; i += stride)
    {
        result += data[i];
    }

    return result;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <SIZE> <STRIDE>\n",argv[0]);
        printf("Wallk an allcated memory buffer, generating read throughput results.\n");
        printf("  <SIZE> is the byte size of buffer.\n");
        printf("  <STRIDE> is the distance of two successive reads (in 64bit items).\n");
        return 1;
    }

    int stride = atoll(argv[2]);                // size of each step
    size_t size = atoll(argv[1]);               // size of data_array
    size_t count = size / sizeof(data_t);       // elements number of data_array
    data_t* data_array = (data_t*)malloc(size); // the data array
    printf("size = %ju, stride=%d\n", size, stride);

    double duration = 0; // in ms-level
    int target_loop = 1;

    while(1)
    {
        volatile data_t dummy=0;
        dummy += mount(data_array, count, stride); // cache warm up

        clock_t start_time = clock();
        for(int i = 1; i < target_loop; i++)
        {
            dummy += mount(data_array, count, stride);
        }
        clock_t stop_time = clock();

        duration = (uintmax_t)stop_time - (uintmax_t)start_time;
        printf("%d repeats -> %f\n", target_loop, duration);

        if(target_loop > 1000)
        {
            break;
        }

        target_loop *= 10;
    }

    double duration_last_loop = duration / target_loop;
    size_t quantity - (count/stride)*sizeof(data_t);

    printf("Read %s bytes data in %f ms, speed is %.1f MB/s \n",
           quantity, duration_last_loop, ((float)quantity/duration_last_loop);
    
    return 0;
}
