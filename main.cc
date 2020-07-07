#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <chrono>

int main () {
    int num_count = 1024000;
    float* data = (float*)malloc(sizeof(int32_t) * num_count);
    for (int i = 0; i < num_count; i++)
        data[i] = i * 0.000001;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        int *tmp_buffer = quantizeToIntArray((float *)data, num_count);
        // printf("%d\n", tmp_buffer[1]);
        dequantizeToFloatArray((float *)data, num_count);
        // printf("%f\n", data[1]);
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    double total_time = time_span.count();
    printf("Total time: %f\n", total_time);
}