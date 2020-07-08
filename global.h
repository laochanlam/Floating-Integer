#include <stdint.h>

#include <immintrin.h>

// scale up float then translate it to int
// without any further optimization
inline static void quantizeNaive(char* data_ptr, uint32_t size) {
    int factor = 1000000;
    int* int_data_ptr = (int*) data_ptr;
    float* float_data_ptr = (float*) data_ptr;
    for (uint32_t i = 0; i < size; i++) {
        int_data_ptr[i] = (int)(float_data_ptr[i] * factor);
    }
}

// functioned the same as quantizeNaive
// boost with avx 256 instructions
inline static void quantizeAVX2(char* data_ptr, uint32_t size) {
    float factor = 1000000.0;
    const float *factor_ptr;
    factor_ptr = &factor;
    int* int_data_ptr = (int*) data_ptr;
    float* float_data_ptr = (float*) data_ptr;

    __m256* input_avx = (__m256*) data_ptr;
    // 0xF4240 is 1000000 in hex
    __m256 factor_in_avx = _mm256_broadcast_ss(factor_ptr);
    // __m256 factor_in_avx = _mm256_set1_ps(1000000.0);

    for (uint32_t i = 0; i < size / sizeof(__m256i); i++) {
        __m256 scaled_input_avx = _mm256_mul_ps(input_avx[i], factor_in_avx);
        __m256i output_avx = _mm256_cvtps_epi32(scaled_input_avx);
        _mm256_packs_epi32(output_avx, _mm256_setzero_si256());

       int *output = (int *)&output_avx;
       int_data_ptr[i*8] = output[0];
       int_data_ptr[i*8+1] = output[1];
       int_data_ptr[i*8+2] = output[2];
       int_data_ptr[i*8+3] = output[3];
       int_data_ptr[i*8+4] = output[4];
       int_data_ptr[i*8+5] = output[5];
       int_data_ptr[i*8+6] = output[6];
       int_data_ptr[i*8+7] = output[7];
    }
}

// translate back to float and scale down
// without any further optimization
inline static void dequantizeNaive(char* data_ptr, uint32_t size) {
    float factor = 1000000.0;
    int* int_data_ptr = (int*) data_ptr;
    float* float_data_ptr = (float*) data_ptr;
    for (uint32_t i = 0; i < size; i++) {
        float_data_ptr[i] = (float)(int_data_ptr[i] / factor);
    }
}

// functioned the same as dequantizeNaive
// boost with avx 256 instructions
inline static void dequantizeAVX2(char* data_ptr, uint32_t size) {
    float factor = 1000000.0;
    int* int_data_ptr = (int*) data_ptr;
    float* float_data_ptr = (float*) data_ptr;
    for (uint32_t i = 0; i < size; i++) {
        float_data_ptr[i] = (float)(int_data_ptr[i] / factor);
    }
}
