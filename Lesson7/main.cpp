#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    cv::Mat image = cv::imread("C:/Users/User/Pictures/763627.jpg");

    if(!image.data)
        return -1;

    cv::namedWindow("example", cv::WINDOW_AUTOSIZE);

    cv::imshow("example", image);

    cv::waitKey(0);

//    cv::destroyWindow("example");

    cout << "Hello World!" << endl;
    return 0;
}
