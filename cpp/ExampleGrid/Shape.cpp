
#include "Shape.hpp"

Shape::Shape(int radius) :
        mask_(),
        contour_(),
        center_(){
    mask_ = cv::Mat::zeros(2 * radius + 1, 2 * radius + 1, CV_8UC1);
    cv::circle(mask_,cv::Point(radius,radius),radius,255,-1);
    contour_ = findBiggestContour(mask_);
    center_ = computeCenter(contour_);
}

const cv::Mat &Shape::getMask() const {
    return mask_;
}

const std::vector<cv::Point> &Shape::getContour() const {
    return contour_;
}

const cv::Point &Shape::getCenter() const {
    return center_;
}

const std::vector<cv::Point> Shape::calculatePixel() const {
    std::vector<cv::Point> result;
    // accept only char type matrices
    cv::Mat mat = mask_.clone();
    CV_Assert(mat.depth() == CV_8U);
    int channels = mat.channels();
    int nRows = mat.rows;
    int nCols = mat.cols * channels;
    if (!mat.empty()) {
        int i, j;
        uchar *p;
        for (i = 0; i < nRows; ++i) {
            p = mat.ptr<uchar>(i);
            for (j = 0; j < nCols; ++j) {
                if ((int) p[j] > 0) {
                    result.push_back(cv::Point(i, j));
                }
            }
        }
    } else {
        std::cerr << "cv::Mat is empty." << std::endl;
        throw std::invalid_argument("Argument cv::Mat is empty.");
    }
    return result;
}


std::vector<cv::Point> Shape::findBiggestContour(cv::Mat mask) {

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    /// Find contours
    findContours(mask, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    if (contours.empty()) {
        throw std::out_of_range("No contour found in given cell shape image.");
    } else if (contours.size() == 1) {
        return contours.back();
    } else {
        unsigned long biggest_contour_index = 0;
        for (size_t i = 0; i < contours.size(); i++) {
            if (contours.at(biggest_contour_index).size() <= contours.at(i).size()) {
//            std::cout << contours.at(i).size() << std::endl;
                biggest_contour_index = (int) i;
            }
        }
        return contours.at(biggest_contour_index);
    }
}

bool Shape::operator==(const Shape &rhs) const {
    return contour_ == rhs.getContour();
}

bool Shape::operator!=(const Shape &rhs) const {
    return !(rhs == *this);
}

cv::Point Shape::computeCenter(std::vector<cv::Point> contour) {
    cv::Moments mo = cv::moments(contour);
    return cv::Point((int) (mo.m10 / mo.m00), (int) (mo.m01 / mo.m00));
}





