#ifndef EXAMPLEPARALELL_TIMER_HPP
#define EXAMPLEPARALELL_TIMER_HPP

#include <iostream>
#include <ctime>

class Timer
{
public:
    Timer() { clock_gettime(CLOCK_REALTIME, &beg_); }

    double start() {
        return beg_.tv_sec + beg_.tv_nsec / 1000000000.;
    }

    double elapsed() {
        clock_gettime(CLOCK_REALTIME, &end_);
        return end_.tv_sec - beg_.tv_sec +
               (end_.tv_nsec - beg_.tv_nsec) / 1000000000.;
    }

    void reset() { clock_gettime(CLOCK_REALTIME, &beg_); }

private:
    timespec beg_, end_;
};

#endif //EXAMPLEPARALELL_TIMER_HPP
