#include <stdint.h>

static int sending_buff[4096000];

inline static int *quantizeToIntArray(float *data_ptr, uint32_t size)
{
    int factor = 1000000;
    for (uint32_t i = 0; i < size; i++)
        sending_buff[i] = (int)(data_ptr[i] * factor);
    return (int *)sending_buff;
}

inline static char *dequantizeToFloatArray(float *data_ptr, uint32_t size)
{
    float factor = 1000000.0;
    for (uint32_t i = 0; i < size; i++)
        data_ptr[i] = (float)(sending_buff[i] / factor);
    return (char *)data_ptr;
}
