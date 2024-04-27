#include "signal.h"
#include <iostream>


// EXPECTED DATA FORMAT FIRST COLUMN TIME SECOND COLUMN VALUES
signal::signal(dataTable *d){
  //CONSTRUCTOR
  
  signal_data.data = d;
}

double signal::_dvBdt(double v1, double v3, double t1, double t2){
  return (v1 - v3)/((t1 - t2)*2); //function for first derivative of discrete data
}


double signal::_dv2Bdt2(double v1, double v2, double v3,double t1, double t2){
  return (v1 - 2*v2 + v3) / ((t1-t2)*(t1-t2));    //function for second derivative of discrete data 
}

double signal::_vdt(double v1, double v2, double t1, double t2){
  return (v1 + v2) * (t1 - t2) * 0.5; //RETURNS AREA OF TRAPEZOID
}


/**
 * @brief does pre analytic operation like getting slopes and areas wrt and adds them to the datatable data 
 * 
*/
bool signal::pre_analyze()
{
//CHECK IF THE ONCE PASSED TABLE HAS AT LEAST 2 COLUMNS for TIME and Values respectively
  if(signal_data.data->get_col_num() < 2)
  {
    std::cerr << "THE CHOSEN DATA TABLE HAS AT LEAST A ROW MISSING" << endl;
    return false;
  }else
  //START DOING BASIC ANALYTICS
  {   

    int row_index = 0;

    double current_val = getValue(row_index,val);
    double next_val = getValue(row_index + 1,val);
    double current_time = getValue(row_index,time);
    timeStart = current_time;
    double max_amp = current_val;
    double min_amp = current_val;

    
    int amp_maximas_idx = 0;
    int amp_minimas_idx = 0;
    int dvBdt_maximas_idx = 0;
    int dvBdt_manimas_idx = 0;
    
    double vdt = 0;

    double last_val = current_val;
    double last_time = current_time;


    //START FILLING COLUMNS FOR integration with respect to time , first derivative , second derivative;
    for(row_index = 1; row_index < (signal_data.data->get_row_num() - 1); row_index++){

      current_val = getValue(row_index,val);
      next_val = getValue(row_index + 1,val);
      current_time = getValue(row_index,time);

      if(last_time >= current_time){
        std::cerr << "CORRUPTED DATA" << endl;
        return false;
      }
      
      double current_dvBdt = _dvBdt(last_val,  next_val, last_time, current_time);
      double current_dv2Bdt2 = _dv2Bdt2(last_val,current_val,next_val, current_time, last_time);
      
      vdt += _vdt(last_val,  current_val, current_time, last_time);

      putValue(current_dvBdt,row_index,first_deriv);
      putValue(current_dv2Bdt2,row_index,second_deriv);
      putValue(vdt,row_index,area);


      last_val = current_val;
      last_time = current_time;
    }

    current_val = getValue(row_index,val);
    current_time = getValue(row_index,time);
    samples_num = row_index + 1;

    vdt += _vdt(last_val,  current_val, current_time, last_time);
    putValue(vdt,row_index,area);
    
    timeEnd = current_time;

    refreshData();
    return true;
  }
}



bool signal::soft_analyze(){
  dataTable *sigDat = (signal_data.data);
  bool last_firstDerivSign = sigDat;
  bool current_first_deriv_sign;


  for(int i = 0;  i < samples_num; i++){
    getValue(i,first_deriv);


    




  }
  return true;
}




bool signal::signal_analytics(){
  if(pre_analyze()){
    //FUTURE WORK THAT INCLUDES TRANSFORM NON EQUALY TIME-SPACED discrete signal into equally time-spaced discrete signal using approximation techniques
  
  
  
  
  } 
  else{
    return false;
  } 
}




const signal::_analytics signal::get_analytics()
{
  return analytics;
}

dataTable signal::get_sig_data() const
{ 
  return *(signal_data.data);
}
