#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Magick++/Image.h>

cv::Mat binarize(cv::Mat input)
{
    cv::Mat binaryImage;
    cv::cvtColor(input, input, CV_BGR2GRAY);
    cv::threshold(input, binaryImage, 0, 255, cv::THRESH_OTSU);

    int white = cv::countNonZero(binaryImage);
    int black = binaryImage.size().area() - white;

    return white < black ? binaryImage : ~binaryImage;
}



Magick::Image prepareImg(const std::string file)
{
    Magick::Image image;
    image.read(file);
    image.density(Magick::Geometry(300,300));
    image.quantizeColorSpace(Magick::GRAYColorspace);
    image.quantizeColors( 256 );
    image.quantize();

    return image;
}

cv::Mat processImage(const std::string file)
{
    Magick::Image preparedImage = prepareImg(file);
    cv::Mat mat(preparedImage.rows(), preparedImage.columns(), CV_8UC3);
    preparedImage.write(0, 0, preparedImage.columns(), preparedImage.rows(), "BGR", Magick::CharPixel, mat.data);
    cv::Mat processedImage = binarize(mat);

    return processedImage;
}
