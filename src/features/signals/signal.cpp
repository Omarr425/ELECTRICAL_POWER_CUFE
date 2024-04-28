#include "signal.h"
#include <iostream>


// EXPECTED DATA FORMAT FIRST COLUMN TIME SECOND COLUMN VALUES

bool signal::loadData(string name, string fileLocation){
    //CONSTRUCTOR
  file_IO importFile;

  if(importFile.data_import(fileLocation+name,  &signal_data.data, csv)){
    _has_data = true;
    data_viable = true;
    refreshData();
    return true;
  }else{
    _has_data = false;
    data_viable = false;
    return false;
  }
}

bool signal::hasData(){
  return _has_data;
}

bool signal::dataViable(){
  return data_viable;
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
  if(signal_data.data.get_col_num() < 2)
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

    double vdt = 0;

    double last_val = current_val;
    double last_time = current_time;


    //START FILLING COLUMNS FOR integration with respect to time , first derivative , second derivative;
    for(row_index = 1; row_index < (signal_data.data.get_row_num() - 1); row_index++){

      current_val = getValue(row_index,val);
      next_val = getValue(row_index + 1,val);
      current_time = getValue(row_index,time);

      if(last_time >= current_time){
        std::cerr << "CORRUPTED DATA" << endl;
        data_viable = false;
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

#define positive 1
#define zero 0
#define negative -1
#define sign(c)((c>0) ? positive : ((c<0) ? negative : zero))
/// @brief VALUES ANALYTICS THAT EVALUATE MAXIMAS_MINIMAS using SLOPE DATA
bool signal::update_maximas_minimas()
{
    int index = 1;

  double last_firstDeriv;
  double current_firstDeriv = getValue(index,first_deriv);
  last_firstDeriv = current_firstDeriv;


  for(int index = 2;  index < (samples_num - 1); index++){
    current_firstDeriv = getValue(index,first_deriv);
    //DETECT WHEN THE SLOPE CHANGES DIRECTION TO DETECT MINIMAS AND MAXIMAS
    if((sign(current_firstDeriv) == positive) && (sign(last_firstDeriv) == zero))
    {//MINIMA DETECTED
    //WILL SEARCH THE FOLLOWING AND THE PAST ELEMENT FOR THE ABOLUTE SMALLEST
    
    double localMinima = getValue(index - 1,val);
    double temp;
    int ridx = 0;
    for(int i = 0; i < 2; i++ ){
      if(temp < localMinima){
        localMinima = temp;
        ridx = i;   
      }
    }

      double _time = getValue(index + ridx,time);
      val_minimas.value.push_back(localMinima);
      val_minimas.time.push_back(_time);
    }

     if((sign(current_firstDeriv) == negative) && (sign(last_firstDeriv) == zero))
    {//MAXIMA DETECTED
    //WILL SEARCH THE FOLLOWING AND THE PAST ELEMENTS FOR THE ABOLUTE BIGGEST
    double localMaxima = getValue(index - 1,val);
    double temp;
    int ridx = 0;

    for(int i = 0; i < 2; i++ ){
      if(temp > localMaxima){
        localMaxima = temp;
        ridx = i;
      }
    }

      double _time = getValue(index + ridx,time);
      val_maximas.value.push_back(localMaxima);
      val_maximas.time.push_back(_time);
    }

      last_firstDeriv = current_firstDeriv;
  }
  return true;
}

bool signal::post_maximas_minimas()
{
  //NOW WE SHOULD HAVE two dataSets of local (maximum and minimum) values and their times respectively
  //+add some analytics data top min/max vals and their times
  /// **BLOCK FOR UPDATING
  // (analytics.min_val -- analytics.max_val)and their times -- analytics.avg_max -- analytics.avg_min
  // ++ updating the local maximas and manimas to hold only the biggest maximas and minimas

  analytics.min_val = val_minimas.value.at(0);
  for(int i = 1; i < val_minimas.value.size(); i++){
    if(val_minimas.value[i] < analytics.min_val){
      analytics.min_val = val_minimas.value[i];
      analytics.min_val_time = val_minimas.time[i];
    }
  }  


  analytics.max_val = val_maximas.value.at(0);
  for(int i = 1; i < val_maximas.value.size(); i++){
    if(val_maximas.value[i] < analytics.max_val){
      analytics.max_val = val_maximas.value[i];
      analytics.max_val_time = val_maximas.time[i];
    }
  }

  //filter the maximas and minimas for top maximas and minimas only and other local one are ignored for now

  for(int i = 0; i < val_minimas.value.size(); i++){
    if( (val_minimas.value.at(i) >=  (analytics.min_val*(1-accuracy_for_min_max)) ) ){
      //erase minimas or maximas that are far than the smallest local minima by a certain factor
      val_minimas.value.erase(val_minimas.value.begin() + i);
      val_minimas.time.erase(val_minimas.value.begin() + i);
    }
  }
  

  for(int i = 0; i < val_maximas.value.size(); i++){
    if( (val_maximas.value.at(i) <=  (analytics.max_val*(1-accuracy_for_min_max)) ) ){
      //erase maval_maximas or maximas that are far than the biggest local maxima by a certain factor
      val_maximas.value.erase(val_maximas.value.begin() + i);
      val_maximas.time.erase(val_maximas.value.begin() + i);
    }
  }


  double sum_maxes;
  for(int i = 0; i < val_maximas.value.size(); i++){
    sum_maxes+=val_maximas.value[i];
  }
  analytics.avg_max_val = sum_maxes/val_maximas.value.size();

  double sum_mins;
  for(int i = 0; i < val_minimas.value.size(); i++){
    sum_mins+=val_minimas.value[i];
  }
  analytics.avg_min_val = sum_mins/val_minimas.value.size();


  //get peak to peak data
  int ptp_num = val_minimas.value.size();
  if(val_maximas.value.size() < val_minimas.value.size()) ptp_num = val_maximas.value.size();
  double max_ptp = 0;
  double min_ptp = 0;
  double sum_ptp = max_ptp;
  if(ptp_num > 0){
    max_ptp = val_maximas.value.at(0) - val_minimas.value.at(0);
    min_ptp = val_maximas.value.at(0) - val_minimas.value.at(0);

      for(int i = 1; i < ptp_num; i++){
        double ptp = val_maximas.value[i] - val_minimas.value[i];
        sum_ptp+=ptp;

         if(ptp < min_ptp){
           min_ptp = ptp;
         }else if(ptp > max_ptp){
           max_ptp = ptp;
         }
       }

       analytics.max_ptp = max_ptp;
       analytics.min_ptp = min_ptp;
       analytics.avg_ptp = sum_ptp/ptp_num;

  }
  else{
    std::cerr << "NOT ENOUGH PEAKS " << endl;
  }
  return true;
}

bool signal::soft_analyze(){

//CHECK FOR LOCAL AND MINIMUM MAXIMAS
  update_maximas_minimas();
  post_maximas_minimas();
  return true;
}




bool signal::signal_analytics(){
  if(pre_analyze()){
    //FUTURE WORK THAT INCLUDES TRANSFORM NON EQUALY TIME-SPACED discrete signal into equally time-spaced discrete signal using approximation techniques
    
    soft_analyze();
    return true;
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
  return (signal_data.data);
}


bool signal::exportSignal(string name, string fileLocation){
  file_IO file;
  //CHECKS IF The data does exist and viable
  refreshData();
  if(hasData()&&dataViable()){
    if(file.data_export((fileLocation+name), signal_data.data, csv)){
      return true;
    }
  }
  //if something bad happens when exporting
  return false;
}
