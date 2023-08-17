#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat src_img, gray_img, binary_img, copy_img;
    Rect rect;
    Point center;
    int offset = 15;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;//typedef Vec<int, 4> Vec4i;
    vector<Point> approxCurve;
    double epsilon; // epsilon Parameter specifying the approximation accuracy. This is the maximum distance
                    //between the original curve and its approximation.

    src_img = cv::imread("c:/Users/Koteneva/Documents/LevelUp/detect/IMG.jpg");

    if(!src_img.data)
        return -1;

    cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
    threshold(gray_img, binary_img, 60, 255, THRESH_BINARY); // Любому пикселю со значением больше 60
                                                              // будет присвоено значение 255 (белый)
    findContours(binary_img, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
    copy_img = src_img;
    for (size_t i = 0; i < contours.size(); ++i)
    {
        drawContours(copy_img, contours, i, {0,255,0}, 2, LINE_AA, hierarchy);
        rect = boundingRect(contours[i]);
        center = Point(rect.x + rect.width / 2 - 2 * offset, rect.y + rect.height + offset);
        if (contours[i].size())
        {
            epsilon = 0.01 * arcLength(contours[i], true);
            approxPolyDP(contours[i], approxCurve, epsilon, true);
            if (approxCurve.size())
            {
                for (size_t j = 0; j < approxCurve.size(); ++j)
                {
                    drawMarker(copy_img, approxCurve[j], {0,0,255});
                }
                if (approxCurve.size() == 3)
                {
                    putText(copy_img, "Triangle", center, FONT_ITALIC, 0.5, {255,255,255});
                }
                else if(approxCurve.size() == 4)
                {
                    if (rect.width / 100 == rect.height / 100)
                    {
                        putText(copy_img, "Square", center, FONT_ITALIC, 0.5, {255,255,255});
                    }
                    else
                    {
                        putText(copy_img, "Rect", center, FONT_ITALIC, 0.5, {255,255,255});
                    }
                }
                else if(approxCurve.size() > 8)
                {
                    putText(copy_img, "Circle", center, FONT_ITALIC, 0.5, {255,255,255});
                }
             }
        }
    }

    namedWindow("APPROX_NONE", WINDOW_AUTOSIZE);
    imshow("APPROX_NONE", copy_img);
    waitKey(0);
    return 0;
}
