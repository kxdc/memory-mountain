#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef double data_t; // define datatype to generate results
static char* size_units[] = { "B", "kB", "MB", "GB" };
static char* time_units[] = { "ns", "us", "ms", "s" };

char* transfer_size(size_t origin_size)
{
    char* transferred_size = (char*)malloc(10); // result to return
    int unit_index = 0;
    float size = origin_size;
        
    while(size >= 1000)
    {
        size /= 1000;
        unit_index++;
    }

    sprintf(transferred_size, "%.1f%s", size, size_units[unit_index]);

    return transferred_size;
}

char* transfer_time(double origin_time, int unit_index)
{
    if(unit_index < 0)
    {
        return NULL;
    }
    int time = origin_time;
    char* transferred_time = (char*)malloc(10);

    while(time > 1000)
    {
        time /= 1000;
        unit_index++;
    }

    sprintf(transferred_time, "%.2f%s", (double)time, time_units[unit_index]);

    return transferred_time;
}

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
        printf("%d repeats -> %s\n", target_loop, transfer_time(duration, 1));

        if(target_loop > 1000)
        {
            break;
        }

        target_loop *= 10;
    }

    double duration_last_loop = duration / target_loop;
    size_t quantity = (count/stride) * sizeof(data_t);

    printf("Read %s bytes data in %s ms, speed is %.1f MB/s \n",
           transfer_size(quantity),
           transfer_time(duration_last_loop, 1),
           ((float)quantity/duration_last_loop));
    
    return 0;
}
