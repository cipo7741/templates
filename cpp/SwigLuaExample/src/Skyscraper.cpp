#include "Skyscraper.hpp"

#include <iostream>
#include <utility>

void Skyscraper::setName(std::string name)
{
    mName = std::move(name);
}

std::string Skyscraper::getName()
{
    return mName;
}

const Floor* Skyscraper::getFloor(unsigned int floorNumber)
{
    if (floorNumber < mFloors.size())
        return &mFloors[floorNumber];
    else
        return nullptr;
}

Floor& Skyscraper::addFloor()
{
    mFloors.emplace_back();
    return mFloors[mFloors.size()-1];
}

void Skyscraper::print()
{
    for (unsigned int i=0; i<mFloors.size(); i++)
    {
        Floor floor = mFloors[i];
        std::cout << "Storey: " << i << " Fibre: " << (floor.getHasFibre() ? "y" : "n") << " Carpet Colour: " << floor.getCarpetColour() << std::endl;
    }
}
