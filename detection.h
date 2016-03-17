#ifndef DETECTION_H
#define DETECTION_H

std::vector<cv::Mat> separateChannels(cv::Mat&);
void detectText(cv::Mat&);

#endif // DETECTION_H
