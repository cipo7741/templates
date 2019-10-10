#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <chrono>
#include <boost/random/mersenne_twister.hpp>
#include <omp.h>
#include "Timer.hpp"

unsigned int seed = 0;
boost::mt19937 randomMT(seed);

unsigned int generateInt(unsigned int maxVal) {
    return (randomMT() % (maxVal + 1));
}

void runSimulation(cv::Mat image, int id) {
    cv::Mat result = image.clone();
    int x = generateInt(600);
    int y = generateInt(400);
    cv::circle(result, cv::Point(x, y), 30, cv::Scalar(0, 0, 255), -1);

    std::vector<int> compression_params;
    compression_params.push_back((int &&) cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    Timer t;

    try {
        cv::imwrite("../out/" + std::to_string(t.start()) + std::to_string(id) + "test" + std::to_string(x) + ".png",
                    result, compression_params);
    }
    catch (cv::Exception &ex) {
        std::cout << "Exception converting image to PNG format:";
        std::cout << "    " << ex.what();
    }
    //std::cout << "Saved PNG file " << id << std::endl;
}

void runNTimes(cv::Mat image, int n, int id) {
    for (int i = 0; i < n; ++i) {
        runSimulation(image, id);
    }
}

void runNTimesOnMultipleImages(std::vector<cv::Mat> imageVector, int n, int id) {
    for (auto image : imageVector) {
        runNTimes(image, n, id);
    }
}

int main() {

    int noThreads(7);
    int noSimulations(21);

    std::cout << "Hello, World!" << std::endl;

    std::vector<cv::Mat> images;

    images.push_back(cv::imread("../img/1.png"));
    images.push_back(cv::imread("../img/2.png"));
    images.push_back(cv::imread("../img/3.png"));

    Timer t;

#ifdef _OPENMP
    omp_set_dynamic(0);     // Explicitly disable dynamic teams
    omp_set_num_threads(noThreads); // Use 4 threads for all consecutive parallel regions
#pragma omp parallel for
    for (int i = 0; i < noSimulations / images.size(); i++) {
        //runPerSimulation(nMicroscopeImages, nSimCellTypes, nSimulationParameters);
        runNTimesOnMultipleImages(images, 3, i);
    }
#else
    for (int i = 0; i < noSimulations / images.size(); i++) {
        //runPerSimulation(nMicroscopeImages, nSimCellTypes, nSimulationParameters);
        runNTimesOnMultipleImages(images, 3, i);
    }
#endif

    std::cout << t.elapsed() << std::endl;

    return 0;
}