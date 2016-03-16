#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <tesseract/baseapi.h>

#include <vector>
#include <fstream>
#include <iostream>

#include <segment.h>

cv::Mat binarize(cv::Mat input)
{
    cv::Mat binaryImage;
    cv::cvtColor(input, input, CV_BGR2GRAY);
    cv::threshold(input, binaryImage, 0, 255, cv::THRESH_OTSU);

    int white = cv::countNonZero(binaryImage);
    int black = binaryImage.size().area() - white;

    return white < black ? binaryImage : ~binaryImage;
}

std::vector<cv::RotatedRect> findTextAreas(cv::Mat input)
{
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3));
    cv::Mat dilated;
    cv::dilate(input, dilated, kernel, cv::Point(-1, -1), 5);
    cv::imshow("Dilated", dilated);

    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(dilated, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<cv::RotatedRect> areas;
    for (auto contour : contours)
    {
        auto box = cv::minAreaRect(contour);
        if (box.size.width < 20 || box.size.height < 20)
            continue;

        double proportion;
        if (box.angle < -45.0)
            proportion = box.size.height / box.size.width;
        else
            proportion = box.size.width / box.size.height;

        areas.push_back(box);
    }
    return areas;
}

cv::Mat deskewAndCrop(cv::Mat input, const cv::RotatedRect& box)
{
    double angle = box.angle;
    cv::Size2f size = box.size;

    if (angle < -45.0)
    {
        angle += 90.0;
        std::swap(size.width, size.height);
    }

    cv::Mat transform = cv::getRotationMatrix2D(box.center, angle, 1.0);
    cv::Mat rotated;
    cv::warpAffine(input, rotated, transform, input.size(), cv::INTER_CUBIC);

    cv::Mat cropped;
    cv::getRectSubPix(rotated, size, box.center, cropped);
    cv::copyMakeBorder(cropped,cropped, 10, 10, 10, 10, cv::BORDER_CONSTANT, cv::Scalar(0));

    return cropped;
}
