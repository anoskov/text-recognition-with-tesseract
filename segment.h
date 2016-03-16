#ifndef SEGMENT_H
#define SEGMENT_H

cv::Mat binarize(cv::Mat);
cv::Mat deskewAndCrop(cv::Mat, const cv::RotatedRect&);
std::vector<cv::RotatedRect> findTextAreas(cv::Mat);

#endif // SEGMENT_H
