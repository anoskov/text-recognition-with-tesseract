#ifndef DETECTION_H
#define DETECTION_H

std::vector<cv::Mat> separateChannels(cv::Mat&);
cv::Mat drawER(const std::vector<cv::Mat>&,
               const std::vector<std::vector<cv::text::ERStat>>&,
               const std::vector<cv::Vec2i>&,
               const cv::Rect);
void detectAndExtractText(cv::Mat&);

#endif // DETECTION_H
