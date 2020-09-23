#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void getTimes(int time);

  // TODO: Declare any necessary private members
  float total_time_;
  float idle_time_;
};

#endif