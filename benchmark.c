#include <stdio.h>
#include <stdlib.h>

// define datatype to generate results
typedef double data_t;

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

    double duration = 0; // in microsecond-level
    int repeats = 1;

    while(1)
    {
        volatile data_t dummy=0;
    }
}
