#ifndef EXAMPLECELLOVERLAP_SHAPE_HPP
#define EXAMPLECELLOVERLAP_SHAPE_HPP



#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>
#include <iostream>

class Shape {

public:

    Shape(int radius);

    const cv::Mat &getMask() const;

    const std::vector<cv::Point> &getContour() const;

    const cv::Point &getCenter() const;

    const std::vector<cv::Point> calculatePixel() const;

    bool operator==(const Shape &rhs) const;

    bool operator!=(const Shape &rhs) const;

private:

    cv::Mat mask_;

    std::vector<cv::Point> contour_;

    cv::Point center_;

    std::vector<cv::Point> findBiggestContour(cv::Mat mask);

    cv::Point computeCenter(std::vector<cv::Point> contour);

};


#endif //EXAMPLECELLOVERLAP_SHAPE_HPP
