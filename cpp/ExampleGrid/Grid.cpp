#include <opencv2/core/mat.hpp>
#include <iostream>
#include <set>
#include "Grid.hpp"

Grid::Grid(cv::Mat const &imageMat, int biggestRadius) :
        nGridPoints_(),
        offset_(biggestRadius),
        nTiles_(calculateBoxes(imageMat, 4*biggestRadius+1)) {

}

std::vector<Cell> Grid::getCellsNear(Cell const &cell) {
    cv::Point tmpPoint = cell.getPosition();
    for (int i = 0; i < nTiles_.size(); ++i) {
        if (tmpPoint.inside(nTiles_.at(i))) {
            std::vector<Cell> &result = nGridPoints_[i];
            for (std::vector<Cell>::iterator it = result.begin(); it != result.end(); /* blank */ ) {
                if (it->getColor() != cell.getColor()) {
                    result.erase(it++);       // Note the subtlety here
                } else {
                    ++it;
                }
            }
            return result;
        }
    }
    std::cerr << "no matching tile fund at x:" << tmpPoint.x << ", y:" << tmpPoint.y << std::endl;
}

bool Grid::addCell(Cell const &cell) {
    cv::Point tmpPoint = cell.getPosition();
    for (int i = 0; i < nTiles_.size(); ++i) {
        if (tmpPoint.inside(nTiles_.at(i))) {
            nGridPoints_[i].push_back(cell);
        }
    }
    return false;
}

//std::vector<Cell> Grid::getGridPointNear(Cell const &cell) {
////    return
//}

cv::Rect Grid::getBoxById(int i) {
    return nTiles_[i];
}

std::vector<cv::Rect> Grid::calculateBoxes(const cv::Mat &imageMat, int boxSize) const {
    std::vector<cv::Rect> result;
    int nTimesX = imageMat.size().width / boxSize;
    int nTimesY = imageMat.size().height / boxSize;
    //std::cout << nTimesX << " " << nTimesY << std::endl;
    for (int iy = 0; iy < nTimesY + 1; iy++) {
        for (int ix = 0; ix < nTimesX + 1; ix++) {
            cv::Rect tmpBox = createBox(ix * boxSize, iy * boxSize, boxSize, boxSize, imageMat.size().width,
                                        imageMat.size().height);
            //std::cout << tmpBox.width << " " << tmpBox.height << std::endl;
            result.push_back(tmpBox);
        }
    }
    return result;
}

cv::Rect Grid::createBox(int x, int y, int width, int height, int maxX, int maxY) const {
    //std::cout << x << ", " << y << ", " << width << ", " << height << ", " << maxX << ", " << maxY << std::endl;
    if (x + width > maxX) {
        return cv::Rect(x, y, maxX - x, height);
    } else if (y + height > maxY) {
        return cv::Rect(x, y, width, maxY - y);
    } else if (x + width > maxX && y + height > maxY) {
        return cv::Rect(x, y, maxX - x, maxY - y);
    } else {
        return cv::Rect(x, y, width, height);
    }
}