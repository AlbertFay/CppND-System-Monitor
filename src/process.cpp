#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization(){
    //cpu_utilization_ = LinuxParser::CpuUtilization(pid_);
    //return cpu_utilization_;
    return LinuxParser::CpuUtilization(pid_);
}

// TODO: Return the command that generated this process
string Process::Command(){
    return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram() const {
    int ram_ = (int)(LinuxParser::Ram(pid_) / 1000);
    return std::to_string(ram_);
}

// TODO: Return the user (name) that generated this process
string Process::User(){
    return LinuxParser::User(pid_);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime(){
    long starttime = LinuxParser::UpTime(pid_) / sysconf(_SC_CLK_TCK);
    return LinuxParser::UpTime() - starttime;    
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    return Ram() > a.Ram();
}