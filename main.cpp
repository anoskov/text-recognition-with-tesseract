#include <opencv2/core/core.hpp>

#include <fstream>
#include <iostream>

#include <imgprocessing.h>
#include <recognition.h>

int main(int argc, char *argv[])
{
    cv::Mat processedImage = processImage(argv[1]);

    std::string text = identifyText(processedImage, "rus+eng");
    saveResult(text);

    return 0;
}
