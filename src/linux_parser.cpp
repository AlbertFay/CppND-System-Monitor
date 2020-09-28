#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <cmath>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization(){
  float mem_total, mem_free;
  string line, name, number;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  std::vector<float> memory{};

  //Parse through file and move memory data to vector
  if(stream.is_open()){
    for(int i = 0; i < 4; i++){
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> name;
      linestream >> number;
      memory.push_back(std::stof(number));
    }
  }
  //assign vector data to corresponding variables
  mem_total = memory[0];
  mem_free = memory[1];

  return ((mem_total-mem_free)/mem_total);

}

// TODO: Read and return the system uptime
long LinuxParser::UpTime(){
  long uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open()){
    getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime;
}

/*
I felt that it was easier to Parse the file and do the calculations within
the Processor class.

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }
*/

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses(){
  string name, line;
  int processes;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    while(line.std::string::find("processes") == std::string::npos){
      getline(stream, line);
    }
    std::istringstream linestream(line);
    linestream >> name >> processes;
  }
    return processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses(){
  string name, line;
  int procs_running;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    while(line.std::string::find("procs_running") == std::string::npos){
      getline(stream, line);
    }
    std::istringstream linestream(line);
    linestream >> name >> procs_running;
  }
    return procs_running;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid){
  string line;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);
  if(stream.is_open()){
    stream >> line;
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::Ram(int pid){
  string name, line;
  float kilobytes;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if(stream.is_open()){
    while(line.std::string::find("VmSize") == std::string::npos){
      getline(stream, line);
    }
    std::istringstream linestream(line);
    linestream >> name >> kilobytes;
  }
    return kilobytes;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid){
  string name, line, uid;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if(stream.is_open()){
    while(line.std::string::find("Uid:") == std::string::npos){
      getline(stream, line);
    }
    std::istringstream linestream(line);
    linestream >> name >> uid;
  }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid){
  string name, line, uid;
  std::ifstream stream(kPasswordPath);
  uid = Uid(pid);
  if(stream.is_open()){
    while(line.std::string::find(uid) == std::string::npos){
      replace(line.begin(), line.end(), ':', ' ');
      getline(stream, line);
    }
    replace(line.begin(), line.end(), ':', ' ');
    std::istringstream linestream(line);
    linestream >> name;
  }
  return name;
  }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid){
  string value;
  long starttime;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if(stream.is_open()){
    for(int i = 0; i < 21; i++){
      stream >> value;
    }
    stream >> starttime;
  }
  return starttime;
}

float LinuxParser::CpuUtilization(int pid){
  string value;
  long utime, stime, cutime, cstime, starttime;
  starttime = LinuxParser::UpTime(pid);
  float total_time, seconds, cpu_usage;

  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if(stream.is_open()){
    for(int i = 0; i < 13; i++){
      stream >> value;
    }
    stream >> utime >> stime >> cutime >> cstime;
  }
  total_time = utime + stime + cutime + cstime;
  seconds = UpTime() - (starttime / sysconf(_SC_CLK_TCK));
  cpu_usage = (total_time / sysconf(_SC_CLK_TCK)) / seconds;
  return cpu_usage;
}