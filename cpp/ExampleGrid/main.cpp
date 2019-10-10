#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>
#include "Cell.hpp"
#include "Grid.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

//    cv::Mat numbers = cv::imread("../numbers.png",CV_LOAD_IMAGE_COLOR);
//    Grid grid(numbers,100);
//    cv::Rect aRect = grid.getBoxById(7);
//    cv::imshow("",numbers(aRect));
//    cv::waitKey();



    cv::Mat a = cv::Mat::zeros(400, 600, CV_8UC3);
    Grid grid(a, 10);
    cv::Scalar color(0,0,255);



    //for (int i = 0; i < 50; ++i) {
        int x = rand() % 600;
        int y = rand() % 400;
        int r = rand() % 255;
        Cell c(10,cv::Point(x,y));
        color += cv::Scalar(r,0,0);
        std::vector<Cell> sameCellsNearby = grid.getCellsNear(c);
        if(sameCellsNearby.empty()){
            std::cout << c.getPosition() << std::endl;
            //cv::circle(a, c.getPosition(), 10, color, -1);
            std::vector<cv::Point> contour = c.getContour();

            for(auto pixel : contour){
                std::cout << pixel;
            }
            std::cout << std::endl;
            std::cout << c.getCenter() << std::endl;

            //cv::polylines(a,contour,true,color,1);
            //cv::fillPoly(a,contour,color);
            //cv::fillPoly(a, contour, color);
            cv::drawContours(a,{c.getContour()},0,color);

        }
        grid.addCell(c);
    //}

    for(int i = 0; i < 150; i++){
        cv::rectangle(a,grid.getBoxById(i),cv::Scalar(0,0,255));
    }

    cv::imshow("first tile",a(grid.getBoxById(44)));
    cv::waitKey();




//
//    std::vector<Cell> nSimCells = grid.getCellsNear(cell, cellType);
//
//    for(auto nearSimCell : nSimCells) {
//        if(!cell.overlap(nearSimCell)){
//            // accept cell
//        }
//    }



//
    cv::imshow("",a);
    cv::waitKey();



    return 0;
}