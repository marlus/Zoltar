#ifndef RIDDLE
#define RIDDLE

#include <vector>

typedef struct riddle
{
    std::string question;
    std::string answer;
    std::vector<struct riddle> stRiddles;
} riddle;

#endif // DATA

