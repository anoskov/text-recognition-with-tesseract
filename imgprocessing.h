#ifndef SEGMENT_H
#define SEGMENT_H

#include <Magick++/Image.h>

cv::Mat binarize(cv::Mat);
Magick::Image prepareImg(const std::string);
cv::Mat processImage(const std::string);

#endif // SEGMENT_H
