#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
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

std::string prepareImg(const std::string file)
{
    Magick::Image image;
    image.read(file);
    //image.quality(1000);
    image.density(Magick::Geometry(300,300));
    //image.scale("10000");
    image.quantizeColorSpace(Magick::GRAYColorspace);
    image.quantizeColors( 256 );
    image.quantize();

    std::string pathToFile = "./preparedImage.png";
    image.write(pathToFile);

    return pathToFile;
}

cv::Mat processImage(const std::string file)
{
    cv::Mat preparedImage = cv::imread(file);
    cv::Mat processedImage = binarize(preparedImage);

    return processedImage;
}
