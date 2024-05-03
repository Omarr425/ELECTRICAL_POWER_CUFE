#pragma once
#include "signal.h"
#include "signal_operation.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class _current: public signal{
};

class _voltage: public signal{
};

class _power: public signal{
  private:
    float active;
    float reactive;
    float powerFactor;

  public:
  //
    _signal_operation operation;
    _power(_voltage* volt, _current* current):  signal(signal_operation_global.multiply(current, volt)){
    }

    double get_energy(double time_start,double time_end){
      if(!this->isTimeAnalysed())this->analyse();
      if(time_start < this->get_analytics().timeStart)return 0;
      if(time_start > this->get_analytics().timeEnd)return 0;
      unsigned int idx = 0;
      double energy_0 = 0;
      double energy_1 = 0;
      //Search for the time corresponding index in the data and iterate index 
      while(this->getValue(idx, _time) < time_start)idx++;
      //capture energy_0
      energy_0 = getValue(idx,  _area);
      //Find time end and energy at it
      while( (this->getValue(idx,_time) < time_end) && (idx < analytics.samples_num) )idx++;
      //capture energy_1
      energy_1 = getValue(idx, _area);
      
      return energy_1 - energy_0;
    }
};

