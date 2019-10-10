#include "Cell.hpp"

Cell::Cell(int radius_, const cv::Point &position_) :
        shape_(radius_),
        position_(position_) {
}

const cv::Scalar &Cell::getColor() const {
    return color_;
}

const cv::Point &Cell::getPosition() const {
    return position_;
}

void Cell::setShape(int radius) {
    Cell::shape_ = Shape(radius);
}

void Cell::setPosition(const cv::Point &position_) {
    Cell::position_ = position_;
}

bool Cell::operator==(const Cell &rhs) const {
    return color_ == rhs.color_ &&
           shape_ == rhs.shape_ &&
           position_ == rhs.position_;
}

bool Cell::operator!=(const Cell &rhs) const {
    return !(rhs == *this);
}

const std::vector<cv::Point> Cell::getContour() const {
    std::vector<cv::Point> result;
    //result.reserve((unsigned long) (_simCellType.getHeights() * _simCellType.getWidths()));
    std::vector<cv::Point> contour = shape_.getContour();
    if(contour.empty()){
        std::cerr << "Your Shape has 0 pixels ..." << std::endl;
    }
    cv::Point centerPoint = shape_.getCenter();
    for (auto shapePoint : contour) {
        shapePoint += (position_ - centerPoint);
        result.push_back(shapePoint);
    }
    return result;
}

const cv::Point Cell::getCenter() const {
    return shape_.getCenter();
}


