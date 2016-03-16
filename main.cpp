#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <tesseract/baseapi.h>

#include <vector>
#include <fstream>
#include <iostream>

#include <segment.h>
#include <recognition.h>

tesseract::TessBaseAPI ocr;

int main(int argc, char *argv[])
{
    cv::Mat ticket = binarize(cv::imread(argv[1]));
    auto regions = findTextAreas(ticket);

    std::ofstream file;
    file.open("ticket.txt", std::ios::out | std::ios::binary);

    for(auto region : regions)
    {
        auto cropped = deskewAndCrop(ticket, region);
        std::string text = identifyText(cropped, "eng");

        file.write(text.c_str(), std::strlen(text.c_str()));
        file << std::endl;
    }

    file.close();

    return 0;
}

std::string identifyText(cv::Mat input, std::string language)
{
    ocr.Init(NULL, language.c_str(), tesseract::OEM_TESSERACT_ONLY);
    ocr.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    ocr.SetImage(input.data, input.cols, input.rows, 1, input.step);
    std::string text = ocr.GetUTF8Text();

//    std::cout << "Text:" << std::endl;
//    std::cout << text << std::endl;

    return text;
}
