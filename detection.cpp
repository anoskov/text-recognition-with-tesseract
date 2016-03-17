#include <opencv2/text/erfilter.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>
#include <iostream>

#include <segment.h>

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

cv::Mat drawER(const std::vector<cv::Mat> &channels, const std::vector<std::vector<cv::text::ERStat>> &regions,
        const std::vector<cv::Vec2i> &group, const cv::Rect rect)
{
    cv::Mat out = cv::Mat::zeros(channels[0].rows+2, channels[0].cols+2, CV_8UC1);
    int flags = 4 + (255 << 8) + cv::FLOODFILL_FIXED_RANGE + cv::FLOODFILL_MASK_ONLY;

    for (int g = 0; g < (int)group.size(); g++)
    {
        int idx = group[g][0];
        cv::text::ERStat er = regions[idx][group[g][1]];
        if (er.parent == NULL)
            continue;

        int px = er.pixel % channels[idx].cols;
        int py = er.pixel / channels[idx].cols;
        cv::Point p(px, py);

        cv::floodFill(channels[idx], out, p, cv::Scalar(255), nullptr, cv::Scalar(er.level), cv::Scalar(0), flags);
    }

    out = out(rect);
    std::vector<cv::Point> points;
    cv::findNonZero(out, points);

    return deskewAndCrop(out, minAreaRect(points));
}

void detectAndExtractText(cv::Mat &input)
{
    //Convert the input image to grayscale.
    //Just do Mat processed = input; to work with colors.
    cv::Mat processed;
    cv::cvtColor(input, processed, CV_RGB2GRAY);

    auto channels = separateChannels(processed);

    // Create ERFilter objects with the 1st and 2nd stage classifiers
    auto filter1 = cv::text::createERFilterNM1(cv::text::loadClassifierNM1("trained_classifierNM1.xml"),15,0.00015f,0.13f,0.2f,true,0.1f);
    auto filter2 = cv::text::createERFilterNM2(cv::text::loadClassifierNM2("trained_classifierNM2.xml"),0.5);

    std::cout << "Processing " << channels.size() << " channels..." << std::endl;
    std::vector<std::vector<cv::text::ERStat> > regions(channels.size());
    for (int c=0; c < (int)channels.size(); c++)
    {
        std::cout << "    Channel " << (c+1) << std::endl;
        filter1->run(channels[c], regions[c]);
        filter2->run(channels[c], regions[c]);
    }
    filter1.release();
    filter2.release();

    //Separate character groups from regions
    std::vector< std::vector<cv::Vec2i> > groups;
    std::vector<cv::Rect> groupRects;
    cv::text::erGrouping(input, channels, regions, groups, groupRects, cv::text::ERGROUPING_ORIENTATION_HORIZ);

    for (int i = 0; i < (int)groups.size(); i++)
    {
         cv::Mat wordImage = drawER(channels, regions, groups[i], groupRects[i]);

         cv::imshow("Word Image", wordImage);
         cv::waitKey(0);
    }
}
