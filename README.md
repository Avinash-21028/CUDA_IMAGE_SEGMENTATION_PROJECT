# Image Segmentation CUDA Project
This project performs image segmentation and edge detection using CUDA for acceleration. The program processes images by performing edge detection, Sobel filtering, colorization (for grayscale images), and segmentation by color. The processed images are saved to an output directory.

## Features

- **Edge Detection**: Uses Canny edge detection algorithm.
- **Sobel Filtering**: Applies Sobel filter to detect vertical and horizontal edges.
- **Color Segmentation**: Segments images based on color using HSV color space. The colored photos are in aerial folder in initials in data while black and white are in textures in initials in data folder.
- **CUDA Acceleration**: Accelerates processing using CUDA-enabled GPU, falling back to CPU if CUDA is not available.

## Requirements

- CMake 3.10 or higher
- OpenCV 4.2.0 or higher
- CUDA 11.3 or higher (optional for GPU acceleration)
- GCC 9.3.0 or higher
- NVIDIA GPU with CUDA capability

## Installation

See the `INSTALL` file for detailed installation instructions.

## How to Use

1. Place your `black and white` input images in the `data/initial/textures` directory and  `colored` images in `data/initial/aerials`. 
2. Build the project using CMake and make.
3. Run the `segmentation` executable.
4. The results are in `data/processed/textures` and `data/processed/aerials`.

**OR**
instead of 2 and 3 just run the following in the directory `image-segmentation-cuda/`
chmod +x run.sh
./run.sh

### Example

cd /home/coder/project/image-segmentation-cuda
rm -rf build
rm -rf /home/coder/project/image-segmentation-cuda/data/processed
mkdir build
cd build
cmake ..
make
./segmentation