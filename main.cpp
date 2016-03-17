#include <opencv2/core/core.hpp>

#include <fstream>
#include <iostream>

#include <imgprocessing.h>
#include <recognition.h>

int main(int argc, char *argv[])
{
    std::string preparedImage = prepareImg(argv[1]);
    cv::Mat processedImage = processImage(preparedImage);

    std::string text = identifyText(processedImage, "rus+eng");
    saveResult(text);

    return 0;
}
