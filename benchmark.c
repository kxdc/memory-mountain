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

    size_t size = atoll(argv[1]);
    int stride = atoll(argv[2]);

    size_t count = size / sizeof(data_t);
}
