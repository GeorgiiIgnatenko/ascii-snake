#include <sys/time.h>

#include <chrono>
#include <ctime>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

time_t getMils()
{
    time_t millisec_since_epoch =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch())
            .count();

    return millisec_since_epoch;
}

// class Time
// {
// public:
//     static time_t milliseconds()
//     {
//         struct timeval time_now{};
//         gettimeofday(&time_now, nullptr);
//         time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
//         return msecs_time;
//     }
// };
