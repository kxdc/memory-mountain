#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <SIZE> <STRIDE>\n",argv[0]);
        printf("Wallk an allcated memory buffer, generating read throughput results.\n");
        printf("  <SIZE> is the byte size of buffer.\n");
        printf("  <STRIDE> is the distance of two successive reads (in 64bit items).\n");
        exit(1);
    }

    size = atoll(argv[1]);
    stride = atoll(argv[2]);
}
