#pragma once

#include "data_IO/data_IO.h"
#include <stdlib.h>
#include <type_traits>
#include <string>

  using namespace std;

template <typename t>
struct eng_multiplier{

  t to_millis(t v)
  {
    if(is_arithmetic<t>::value){
      return v*10e-3;
    }
    else if(is_same_v<t,string>)
    {
      return v+"10e-3";
    }
  }


  t to_micros(t v)
  {
    if(is_arithmetic<t>::value){
      return v*10e-6;
    }
    else if(is_same_v<t,string>)
    {
      return v+"10e-6";
    }
  }


  t to_nanos(t v)
  {
    if(is_arithmetic<t>::value){
      return v*10e-9;
    }
    else if(is_same_v<t,string>)
    {
      return v+"10e-9";
    }
  }


  t to_kilos(t v)
  {
    if(is_arithmetic<t>::value){
      return v*10e3;
    }
    else if(is_same_v<t,string>)
    {
      return v+"10e3";
    }
  }


  t to_megas(t v)
  {
    if(is_arithmetic<t>::value){
      return v*10e6;
    }
    else if(is_same_v<t,string>)
    {
      return v+"10e6";
    }
  }


  t to_gigas(t v)
  {
    if(is_arithmetic<t>::value){
      return v*10e9;
    }
    else if(is_same_v<t,string>)
    {
      return v+"10e9";
    }
  }
};


