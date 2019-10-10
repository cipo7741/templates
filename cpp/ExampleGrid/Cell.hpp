#ifndef EXAMPLECELLOVERLAP_CELL_HPP
#define EXAMPLECELLOVERLAP_CELL_HPP


#include <opencv2/core/types.hpp>
#include "Shape.hpp"

class Cell {

public:

    Cell(int radius_, const cv::Point &position_);

    const cv::Point &getPosition() const;

    const cv::Scalar &getColor() const;

    const std::vector<cv::Point> getContour() const;

    const cv::Point getCenter() const;

    void setShape(int radius);

    void setPosition(const cv::Point &position_);

    bool operator==(const Cell &rhs) const;

    bool operator!=(const Cell &rhs) const;

private:

    cv::Scalar color_;

    Shape shape_;

    cv::Point position_;

};


#endif //EXAMPLECELLOVERLAP_CELL_HPP
