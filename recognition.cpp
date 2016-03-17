#include <opencv2/core/core.hpp>
#include <tesseract/baseapi.h>
#include <iostream>
#include <fstream>

tesseract::TessBaseAPI ocr;

std::string identifyText(cv::Mat input, std::string language)
{
    ocr.Init(NULL, language.c_str(), tesseract::OEM_TESSERACT_ONLY);
    //std::string whitelist = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.:";
    //ocr.SetVariable("tessedit_char_whitelist", whitelist.c_str());
    ocr.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    ocr.SetImage(input.data, input.cols, input.rows, 1, input.step);
    std::string text = ocr.GetUTF8Text();

    return text;
}

void saveResult(std::string text, const std::string pathToFile = "./result.txt")
{
    // Remove blank lines
    text.erase(std::unique(text.begin(), text.end(), [] (char a, char b) {return a == '\n' && b == '\n';}), text.end());
    std::ofstream file;
    file.open(pathToFile, std::ios::out | std::ios::binary);
    file.write(text.c_str(), std::strlen(text.c_str()));
    file << std::endl;
    file.close();
}
