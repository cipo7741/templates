#if 1
#include <iostream>
#include <opencv2/opencv.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "Timer.h"

static boost::mt19937 randomMT;

int generateInt(int maxVal){
    return (randomMT()%(maxVal + 1));
}

template <typename T>
void remove_at(std::vector<T>& v, typename std::vector<T>::size_type n)
{
    std::swap(v[n], v.back());
    v.pop_back();
}

int main() {

    Timer tmr;

    std::cout << "Hello, World!" << std::endl;
    cv::Mat imageMat = cv::imread("../resource/test2.png",CV_LOAD_IMAGE_GRAYSCALE);


    // vector of positions in matrix that have region color
    std::vector<cv::Point2i> theVector;
    for(int x = 0; x < imageMat.rows; ++x){
        for(int y = 0; y < imageMat.cols; ++y){
            int i = *imageMat.ptr(x,y);
            //std::cout << x << "-" << y << std::endl;
            if(i == 0) {
                theVector.push_back(cv::Point2i(y,x));
            }
        }
    }

    double t = tmr.elapsed();
    std::cout << t << " filled vector with " << theVector.size() << " points" << std::endl;

    // shuffle vector
    std::random_shuffle(theVector.begin(), theVector.end(), generateInt);

    t = tmr.elapsed();
    std::cout << t << " shuffled vector" << std::endl;

    // draw n cells at first n positions of shuffled vector
    int numSimCells = 128000;
    cv::Mat color_image = cv::Mat::zeros(imageMat.size(), CV_8UC3);
    for(int i = 0; i < numSimCells; i=i+1){
        //std::cout << theVector.at(i).x << ":" << theVector.at(i).y << std::endl;
        cv::circle(color_image, theVector.at(i), 7, cv::Scalar(0,255,0), -1, 8);
    }

    t = tmr.elapsed();
    std::cout << t << " drawn cells" << std::endl;

    // save result image
    cv::Mat imageToShow = cv::Mat::zeros(imageMat.size(),CV_8UC3);
    cv::Mat blackCellMask = cv::Mat::zeros(color_image.size(),CV_8S);
    cv::cvtColor(color_image, blackCellMask,CV_RGB2GRAY);
    cv::threshold(blackCellMask,blackCellMask,0,255,cv::THRESH_BINARY);
    cv::cvtColor(imageMat, imageToShow, CV_GRAY2BGR);
    color_image.copyTo(imageToShow, blackCellMask);
    cv::imwrite("out.png",imageToShow);
    //cv::imshow("Input Image", imageToShow);
    //cv::waitKey();

    t = tmr.elapsed();
    std::cout << t << " drawn image" << std::endl;

    return 0;
}
#endif