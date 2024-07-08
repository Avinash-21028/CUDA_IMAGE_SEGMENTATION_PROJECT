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

### Photos
original texture 1.4.05
![1 4 05](https://github.com/Avinash-21028/CUDA_IMAGE_SEGMENTATION_PROJECT/assets/100469984/7c18144b-5f88-492e-87df-4cb3042592a1)
colorized
![1 4 05_colorized](https://github.com/Avinash-21028/CUDA_IMAGE_SEGMENTATION_PROJECT/assets/100469984/12e9afac-55a0-445a-8e92-a6caaa6d9004)
edges
![1 4 05_edges](https://github.com/Avinash-21028/CUDA_IMAGE_SEGMENTATION_PROJECT/assets/100469984/3cc80fe7-bf2e-4aff-b304-fdfab625216d)
horizontal edges
![1 4 05_horizontal](https://github.com/Avinash-21028/CUDA_IMAGE_SEGMENTATION_PROJECT/assets/100469984/a115b91c-9e3d-4124-a086-b37761336bec)
vertical edges
![1 4 05_vertical](https://github.com/Avinash-21028/CUDA_IMAGE_SEGMENTATION_PROJECT/assets/100469984/89c52094-1ca9-4e0b-ba96-9999d98a2f87)
segmented
![1 4 05_segmented](https://github.com/Avinash-21028/CUDA_IMAGE_SEGMENTATION_PROJECT/assets/100469984/16c98dfb-d66e-4adf-b142-9feb16ba7d3c)

