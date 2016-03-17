#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <detection.h>

int main(int argc, char *argv[])
{
    cv::Mat input = cv::imread(argv[1]);

    detectText(input);
    cv::resize(input, input, cv::Size(input.cols/2, input.rows/2));
    cv::imshow("Grouping", input);
    cv::waitKey(0);

    return 0;
}

