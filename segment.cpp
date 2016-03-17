#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

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
