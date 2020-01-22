#ifndef Skyscraper_H
#define Skyscraper_H

#include <vector>
#include <string>

#include "Floor.hpp"

class Skyscraper
{
public:
    Skyscraper() = default;

    virtual ~Skyscraper() = default;

    void setName(std::string name);
    std::string getName();

    const Floor* getFloor(unsigned int floorNumber);
    Floor& addFloor();

    void print();
private:
    std::string mName;
    std::vector<Floor> mFloors;
};

#endif // Skyscraper_H