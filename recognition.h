#ifndef RECOGNITION_H
#define RECOGNITION_H

std::string identifyText(cv::Mat, std::string);
void saveResult(std::string, const std::string = "./result.txt");

#endif // RECOGNITION_H
