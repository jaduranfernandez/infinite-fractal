
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <cstdlib>
#include "Color.h"
#include "Fractal.h"
#include <thrust/complex.h>

#define THREADS_PER_BLOCK 8


__global__ void colorTest(Fractal fractal, Color* colors, int width, int height) {
    
    int col = threadIdx.x + (blockDim.x * blockIdx.x);
    int row = threadIdx.y + (blockDim.y * blockIdx.y);
    if (row > height - 1 || col > width - 1) return;


    //printf("(%i,%i) \n", row, col);
    //colors[row * width + col] = Color(0, 0, 255);

    int currentIteration = 0;
    //  (y, 0, windowHeight, up, down)
    float real  = fractal.left + (((fractal.right - fractal.left) / (width)) * (col));
    float image = fractal.up + (((fractal.down - fractal.up) / (height)) * (row));
    thrust::complex<double> point(real,image);
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
    float intensity = currentIteration / (float)fractal.maxIterations;

    colors[row * width + col].r = fractal.color.r * intensity;
    colors[row * width + col].g = fractal.color.g * intensity;
    colors[row * width + col].b = fractal.color.b * intensity;
}

void parallelFractal(Fractal fractal, Color* h_Colors, int width, int height) {
    size_t numbytes = width * height * sizeof(Color);

    
    Color* d_Colors;


    cudaMalloc((void**)&d_Colors, numbytes);

    cudaMemset(d_Colors, 0, numbytes);

    cudaMemcpy(d_Colors, h_Colors, numbytes, cudaMemcpyHostToDevice);

    //Call kernel function

    const dim3 blockSize(THREADS_PER_BLOCK, THREADS_PER_BLOCK);
    const dim3 gridSize(ceil(width / blockSize.x + 1), ceil(height / blockSize.y + 1));

    colorTest << < gridSize, blockSize >> > (fractal, d_Colors, width, height);
    cudaMemcpy(h_Colors, d_Colors, numbytes, cudaMemcpyDeviceToHost);
    //Print result
    


    //Free memory
    cudaFree(d_Colors);
}


void parallelFractalTest(Color* colors, int width, int height) {

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            colors[y * width + x].r = 255;
        }
    }


}

