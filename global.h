#include <stdint.h>

inline static void quantizeToIntArray(char* data_ptr, uint32_t size) {
int factor = 1000000;
int* int_data_ptr = (int*) data_ptr;
float* float_data_ptr = (float*) data_ptr;
for (uint32_t i = 0; i < size; i++) 
    int_data_ptr[i] = (int)(float_data_ptr[i] * factor);
}

inline static void dequantizeToFloatArray(char* data_ptr, uint32_t size) {
float factor = 1000000.0;
int* int_data_ptr = (int*) data_ptr;
float* float_data_ptr = (float*) data_ptr;
for (uint32_t i = 0; i < size; i++) 
    float_data_ptr[i] = (float)(int_data_ptr[i] / factor);
}
