#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long int original_seconds){
    long int seconds{original_seconds}, minutes, hours;
    string time;
    if(original_seconds > 59){
        minutes = ((seconds - (seconds % 60)) / 60);
        seconds = seconds % 60;
    }
    else{
        minutes = 0;
    }
    if(minutes > 59){
        hours = ((minutes - (minutes % 60)) / 60);
        minutes = minutes % 60;
    }
    else{
        hours = 0;
    }
    if(seconds < 10 && minutes < 10){
        return string(std::to_string(hours) + ":0" + std::to_string(minutes) + ":0" + std::to_string(seconds));
    }
    else if(seconds < 10){
    return string(std::to_string(hours) + ":" + std::to_string(minutes) + ":0" + std::to_string(seconds));
    }
    else if(minutes < 10){
        return string(std::to_string(hours) + ":0" + std::to_string(minutes) + ":" + std::to_string(seconds));
    }
    else{
        return string(std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds));
    }
}