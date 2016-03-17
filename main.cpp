#include <opencv2/text/erfilter.hpp>
#include  "opencv2/highgui.hpp"

#include  <vector>
#include  <iostream>

#include <detection.h>

int main(int argc, const char * argv[])
{
    auto input = cv::imread(argv[1]);
    detectAndExtractText(input);

    return 0;
}

