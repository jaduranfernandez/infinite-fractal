
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <cstdlib>
#include "Color.h"
#include "Fractal.h"
#include <thrust/complex.h>

#define THREADS_PER_BLOCK 32

__device__ float linearInterpolationCuda(float value, float a, float b, float c, float d) {
    return c + (((d - c) / (b - a)) * (value - a));
}

__device__ thrust::complex<double> fromPixelToComplex(int x, int y, int width, int height, Fractal fractal) {
    float realValue = linearInterpolationCuda(x, 0, width, fractal.left, fractal.right);
    float imaValue = linearInterpolationCuda(y, 0, height, fractal.up, fractal.down);
    return thrust::complex<double>(realValue, imaValue);
}


__global__ void calculatePixelColor(Fractal fractal, Color* colors, int width, int height) {
    
    int x = threadIdx.x + (blockDim.x * blockIdx.x);
    int y = threadIdx.y + (blockDim.y * blockIdx.y);
    if (y > height - 1 || x > width - 1) return;


    int currentIteration = 0;
    thrust::complex<double> point = fromPixelToComplex(x, y, width, height, fractal);
    thrust::complex<double> previousCoordinate = point;
    thrust::complex<double> nextCoordinate = point*point + point;
    float magDifference = fractal.tolerance + 1;
    while (currentIteration < fractal.maxIterations && magDifference > fractal.tolerance) {
        previousCoordinate = nextCoordinate;
        nextCoordinate = nextCoordinate * nextCoordinate + point;
        nextCoordinate = nextCoordinate * nextCoordinate + point;
        magDifference = abs(nextCoordinate - previousCoordinate);
        currentIteration++;
    }
    float intensity = (currentIteration - 1) / (float)fractal.maxIterations;
    //  Color lerping
    colors[y * width + x].r = fractal.color.r + (fractal.altColor.r - fractal.color.r) * intensity;
    colors[y * width + x].g = fractal.color.g + (fractal.altColor.g - fractal.color.g) * intensity;
    colors[y * width + x].b = fractal.color.b + (fractal.altColor.b - fractal.color.b) * intensity;


    /*colors[y * width + x].r = fractal.color.r * intensity;
    colors[y * width + x].g = fractal.color.g * intensity;
    colors[y * width + x].b = fractal.color.b * intensity;*/
}

void parallelFractal(Fractal fractal, Color* h_Colors, int width, int height) {
    size_t numbytes = width * height * sizeof(Color);
    
    Color* d_Colors;


    cudaMalloc((void**)&d_Colors, numbytes);

    cudaMemset(d_Colors, 0, numbytes);

    cudaMemcpy(d_Colors, h_Colors, numbytes, cudaMemcpyHostToDevice);

    const dim3 blockSize(THREADS_PER_BLOCK, THREADS_PER_BLOCK);
    const dim3 gridSize(ceil(width / blockSize.x + 1), ceil(height / blockSize.y + 1));

    calculatePixelColor << < gridSize, blockSize >> > (fractal, d_Colors, width, height);
    cudaMemcpy(h_Colors, d_Colors, numbytes, cudaMemcpyDeviceToHost);
    

    //Free memory
    cudaFree(d_Colors);
}



