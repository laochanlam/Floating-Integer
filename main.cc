#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <cmath>

const float Epsilon = 0.000001 * 3;
const unsigned int SampleIdx = 135;

int main () {
    int num_count = 1024000 - 1;
    float* data = (float*)malloc(sizeof(int32_t) * num_count);
    for (int i = 0; i < num_count; i++)
        data[i] = i * 0.000001;

    float naive_preaction_sample = data[SampleIdx];
    // Naive method without any optimization
    std::chrono::high_resolution_clock::time_point naive_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        quantizeNaive((char*)data, num_count);
        dequantizeNaive((char*)data, num_count);
    }
    std::chrono::high_resolution_clock::time_point naive_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> naive_time = std::chrono::duration_cast<std::chrono::duration<double>>(naive_end - naive_start);
    double naive_total_time = naive_time.count();
    float naive_postaction_sample = data[SampleIdx];

    // flush data
    for (int i = 0; i < num_count; i++)
        data[i] = i * 0.000001;

    float avx2_preaction_sample = data[SampleIdx];
    // Boost with AVX2
    std::chrono::high_resolution_clock::time_point avx2_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        quantizeAVX2((char*)data, num_count);
        dequantizeAVX2((char*)data, num_count);
    }
    std::chrono::high_resolution_clock::time_point avx2_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> avx2_time = std::chrono::duration_cast<std::chrono::duration<double>>(avx2_end - avx2_start);
    double avx2_total_time = avx2_time.count();
    float avx2_postaction_sample = data[SampleIdx];

    if (abs(naive_postaction_sample - naive_preaction_sample) < Epsilon ) {
        printf("Naive: %f\n", naive_total_time);
    } else {
        printf("Naive correntness error with epsilon = %f\n", abs(naive_postaction_sample - naive_preaction_sample));
    }

     if (abs(avx2_postaction_sample - avx2_preaction_sample) < Epsilon ) {
        printf("AVX2: %f\n", avx2_total_time);
    } else {
        printf("AVX2 correntness error with epsilon = %f\n", abs(avx2_postaction_sample - avx2_preaction_sample));
    }
}