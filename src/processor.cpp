#include <string>
#include <fstream>
#include <unistd.h>
#include <iostream>

#include "processor.h"
#include "linux_parser.h"

using namespace std;


void Processor::getTimes(int time){
    sleep(time);
    string line, cpu;
    double user, nice ,system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if(stream.is_open()){
        getline(stream, line);
        istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    }
    Processor::idle_time_ = idle;
    Processor::total_time_ = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization(){
    float total_time, idle_time;
    float total_time_one, idle_time_one;
    float total_time_delta, idle_time_delta;
    getTimes(0);
    total_time = Processor::total_time_;
    idle_time = Processor::idle_time_;
    getTimes(1);
    total_time_one = Processor::total_time_;
    idle_time_one = Processor::idle_time_;

    total_time_delta = total_time_one - total_time;
    idle_time_delta = idle_time_one - idle_time;

    float test = (1 - (idle_time_delta / total_time_delta));
    return test;
}