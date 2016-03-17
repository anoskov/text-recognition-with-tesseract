#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/text.hpp>

#include <vector>
#include <iostream>

#include <segment.h>
#include <detection.h>

std::vector<cv::Mat> separateChannels(cv::Mat& src)
{
    std::vector<cv::Mat> channels;
    // Grayscale images
    if (src.type() == CV_8U || src.type() == CV_8UC1) {
        channels.push_back(src);
        channels.push_back(255-src);
        return channels;
    }

    // Colored images
    if (src.type() == CV_8UC3) {
        cv::text::computeNMChannels(src, channels);
        int size = static_cast<int>(channels.size())-1;
        for (int c = 0; c < size; c++)
            channels.push_back(255-channels[c]);
        return channels;
    }

    // Other types
    std::cout << "Invalid image format!" << std::endl;
    exit(-1);
}

void detectText(cv::Mat& input)
{
    cv::Mat processed;
    cv::cvtColor(input, processed, CV_RGB2GRAY);

    auto channels = separateChannels(processed);

    auto filter1 = cv::text::createERFilterNM1(
                cv::text::loadClassifierNM1("trained_classifierNM1.xml"), 15, 0.00015f, 0.13f, 0.2f, true, 0.1f);
    auto filter2 = cv::text::createERFilterNM2(
                cv::text::loadClassifierNM2("trained_classifierNM2.xml"), 0.5);

    std::cout << "Processing: " << channels.size() << " channels..." << std::endl;

    std::vector<std::vector<cv::text::ERStat> > regions(channels.size());
    for (int c = 0; c < channels.size(); c++)
    {
        std::cout << "      Channel " << (c+1) << std::endl;
        filter1->run(channels[c], regions[c]);
        filter2->run(channels[c], regions[c]);
    }
    filter1.release();
    filter2.release();

    std::vector<std::vector<cv::Vec2i> > groups;
    std::vector<cv::Rect> groupRects;
    cv::text::erGrouping(input, channels, regions, groups, groupRects, cv::text::ERGROUPING_ORIENTATION_HORIZ);

    for (auto rect : groupRects)
        cv::rectangle(input, rect, cv::Scalar(0, 255, 0), 3);
}
