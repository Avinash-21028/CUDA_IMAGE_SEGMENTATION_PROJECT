#include <opencv2/opencv.hpp>
#include <cuda_runtime.h>
#include <opencv2/core/cuda.hpp>

void colorizeImage(const cv::Mat& gray, cv::Mat& colorized) {
    #ifdef HAVE_OPENCV_CUDA
    cv::cuda::GpuMat d_gray(gray);
    cv::cuda::GpuMat d_colorized;
    cv::cuda::applyColorMap(d_gray, d_colorized, cv::COLORMAP_JET);
    d_colorized.download(colorized);
    #else
    cv::applyColorMap(gray, colorized, cv::COLORMAP_JET);
    #endif
}

void edgeDetection(const cv::Mat& gray, cv::Mat& edges) {
    #ifdef HAVE_OPENCV_CUDA
    cv::cuda::GpuMat d_gray(gray);
    cv::cuda::GpuMat d_edges;
    cv::cuda::Canny(d_gray, d_edges, 100, 200);
    d_edges.download(edges);
    #else
    cv::Canny(gray, edges, 100, 200);
    #endif
}

void sobelFilter(const cv::Mat& gray, cv::Mat& vertical, cv::Mat& horizontal) {
    #ifdef HAVE_OPENCV_CUDA
    cv::cuda::GpuMat d_gray(gray);
    cv::cuda::GpuMat d_vertical, d_horizontal;
    cv::cuda::Sobel(d_gray, d_vertical, CV_64F, 1, 0, 5);
    cv::cuda::Sobel(d_gray, d_horizontal, CV_64F, 0, 1, 5);
    d_vertical.download(vertical);
    d_horizontal.download(horizontal);
    #else
    cv::Sobel(gray, vertical, CV_64F, 1, 0, 5);
    cv::Sobel(gray, horizontal, CV_64F, 0, 1, 5);
    #endif
}
