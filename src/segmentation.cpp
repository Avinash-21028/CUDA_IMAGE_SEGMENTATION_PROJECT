#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <dirent.h>

// Function declarations
void colorizeImage(const cv::Mat &gray, cv::Mat &colorized);
void edgeDetection(const cv::Mat &gray, cv::Mat &edges);
void sobelFilter(const cv::Mat &gray, cv::Mat &vertical, cv::Mat &horizontal);

void segmentByColor(const cv::Mat &image, std::vector<cv::Mat> &segments)
{
    if (image.channels() != 3)
    {
        std::cerr << "Image is not a color image. Skipping segmentation." << std::endl;
        return;
    }

    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    int bins = 12;
    cv::Mat hist;
    int channels[] = {0, 1};
    int histSize[] = {bins, bins};
    float hranges[] = {0, 180};
    float sranges[] = {0, 256};
    const float *ranges[] = {hranges, sranges};

    cv::calcHist(&hsv, 1, channels, cv::Mat(), hist, 2, histSize, ranges, true, false);
    cv::normalize(hist, hist, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());

    cv::Mat backproj;
    cv::calcBackProject(&hsv, 1, channels, hist, backproj, ranges);

    cv::threshold(backproj, backproj, 50, 255, cv::THRESH_BINARY);
    cv::findContours(backproj, segments, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
}

void processImage(const std::string &imagePath, const std::string &outputDir, bool isTexture)
{
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_UNCHANGED);
    if (image.empty())
    {
        std::cerr << "Error opening image: " << imagePath << std::endl;
        return;
    }

    if (image.channels() == 1 && !isTexture)
    {
        std::cerr << "Image is grayscale but expected color: " << imagePath << std::endl;
        return;
    }

    // Extract filename without extension
    size_t dotPos = imagePath.find_last_of('.');
    size_t slashPos = imagePath.find_last_of('/');
    std::string filename = imagePath.substr(slashPos + 1, dotPos - slashPos - 1);

    std::string edgesPath = outputDir + "/" + filename + "_edges.png";
    std::string verticalPath = outputDir + "/" + filename + "_vertical.png";
    std::string horizontalPath = outputDir + "/" + filename + "_horizontal.png";
    std::string colorizedPath = outputDir + "/" + filename + "_colorized.png";
    std::string segmentedPath = outputDir + "/" + filename + "_segmented.png";

    // Edge detection
    cv::Mat edges, vertical, horizontal;
    edgeDetection(image, edges);
    sobelFilter(image, vertical, horizontal);

    // Save edge detection results
    cv::imwrite(edgesPath, edges);
    cv::imwrite(verticalPath, vertical);
    cv::imwrite(horizontalPath, horizontal);

    cv::Mat colorized;
    if (isTexture)
    {
        // Colorize the grayscale image if it's grayscale
        if (image.channels() == 1)
        {
            colorizeImage(image, colorized);
            cv::imwrite(colorizedPath, colorized);
        }
        else
        {
            colorized = image;
        }
    }
    else
    {
        colorized = image;
    }

    // Segment the colorized image by color
    std::vector<cv::Mat> segments;
    segmentByColor(colorized, segments);
    cv::Mat segmented = cv::Mat::zeros(colorized.size(), colorized.type());
    cv::drawContours(segmented, segments, -1, cv::Scalar(255, 255, 255), -1);
    cv::imwrite(segmentedPath, segmented);

    std::cout << "Processed " << imagePath << " successfully!" << std::endl;
}

void processDirectory(const std::string &dataDir, const std::string &outputDir, bool isTexture)
{
    // Create output directory if it doesn't exist
    DIR *dir = opendir(outputDir.c_str());
    if (dir)
    {
        closedir(dir);
    }
    else
    {
        std::string command = "mkdir -p " + outputDir;
        system(command.c_str());
    }

    // Open the data directory
    DIR *dp;
    struct dirent *ep;
    dp = opendir(dataDir.c_str());
    if (dp != nullptr)
    {
        while ((ep = readdir(dp)))
        {
            std::string fileName = ep->d_name;
            if (fileName.find(".tiff") != std::string::npos)
            {
                std::string filePath = dataDir + "/" + fileName;
                processImage(filePath, outputDir, isTexture);
            }
        }
        closedir(dp);
    }
    else
    {
        perror("Couldn't open the directory");
    }
}

int main()
{
    std::string texturesDir = "/home/coder/project/image-segmentation-cuda/data/initial/textures";
    std::string aerialsDir = "/home/coder/project/image-segmentation-cuda/data/initial/aerials";
    std::string processedTexturesDir = "/home/coder/project/image-segmentation-cuda/data/processed/textures";
    std::string processedAerialsDir = "/home/coder/project/image-segmentation-cuda/data/processed/aerials";

    // Process textures (grayscale images)
    processDirectory(texturesDir, processedTexturesDir, true);

    // Process aerials (color images)
    processDirectory(aerialsDir, processedAerialsDir, false);

    std::cout << "All images processed successfully!" << std::endl;
    return 0;
}
