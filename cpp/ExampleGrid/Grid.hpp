#ifndef EXAMPLECELLOVERLAP_GRID_HPP
#define EXAMPLECELLOVERLAP_GRID_HPP


#include <map>
#include <opencv2/core/types.hpp>
#include "Cell.hpp"

class Grid {

public:

    Grid(cv::Mat const & imageMat, int biggestRadius);

    std::vector<Cell> getCellsNear(Cell const & cell);

    bool addCell(Cell const & cell);

    cv::Rect getBoxById(int i);


private:

    std::vector<Cell> getGridPointNear(Cell const & cell);

    std::map<int, std::vector<Cell>> nGridPoints_;

    int offset_;

    std::vector<cv::Rect> nTiles_;

    std::vector<cv::Rect> calculateBoxes(const cv::Mat &mat, int i) const;

    cv::Rect createBox(int x, int y, int width, int height, int maxX, int maxY) const;
};


#endif //EXAMPLECELLOVERLAP_GRID_HPP
