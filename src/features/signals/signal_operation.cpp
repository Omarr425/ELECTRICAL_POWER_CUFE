#include "signal_operation.h"
#include "iostream"

#define _USE_MATH_DEFINES
#include "cmath"
#include "math.h"
#include <stdlib.h>
#include "../../core/core.h"

//--------------INITIALIZED STATIC MEMBER SETTINGS-------------//

float _signal_operation::samplingRate_diff = stof(settings.get_setting("signal","samplingRate_diff"));
float _signal_operation::freq_diff_accuracy = stof(settings.get_setting("signal","freq_diff"));
_signal_operation signal_operation_global;


void _signal_operation::refreshSettings(){
  samplingRate_diff = stof(settings.get_setting("signal","samplingRate_diff"));
  freq_diff_accuracy = stof(settings.get_setting("signal","freq_diff"));  
}


/**
 * @brief we check the summing boundaries for the two signals and keep summing intersecting values until we reach the end of domain
 * the domain is defined by the mode of both time sets
 * @param base_sig1 the first signal to add
 * @param base_sig2 the second signal to add
 * @param mode the mode of operation (UNION for UNION summation INTERSECT for intersect summation)
 * @return result signal
*/
signal _signal_operation::add(signal* base_sig1,  signal* base_sig2, int mode)
{ signal resultant;
  //TIME DOMAIN ANALYTICS ARE CRITICAL FOR THE SIGNAL BEFORE OPERATION so we check if they have been analysed before 
  //and if not we analyse them
  if(!base_sig1->isTimeAnalysed())base_sig1->analyse();
  if(!base_sig2->isTimeAnalysed())base_sig2->analyse();


  //check for their their sampling times if they are valid
  if(!isNear(base_sig1->get_analytics().avg_sample_time , base_sig2->get_analytics().avg_sample_time, samplingRate_diff)  ){
    std::cerr << "CANT WORK WITH THESE TWO SIGNALS  __FAR_SAMPLING_RATES";
    lastOperationSuccess = false;
    return resultant;
  }

  //CHECK DOMAIN BOUNDARIES FOR THE RESULTANT
  double time_end = base_sig1->analytics.timeEnd;
  double time_start = base_sig1->analytics.timeStart;
  unsigned int base_sig1_idx = 0;
  unsigned int base_sig2_idx = 0;
  unsigned int resultant_sig_idx = 0;


  switch (mode)
  {
  case UNION:
  //UNION OPERATION FOR BOTH TIME DOMAINS
    if(base_sig2->analytics.timeEnd > time_end){
      time_end = base_sig2->analytics.timeEnd;
    }
    if(base_sig2->analytics.timeEnd < time_start){
      time_start = base_sig2->analytics.timeStart;
    }
    break;
  
  case INTERSECT:
  //INTERSECT OPERATION FOR BOTH TIME DOMAINS and ITERATE each data set to reach its begining
    if(base_sig2->analytics.timeEnd < time_end){
      time_end = base_sig2->analytics.timeEnd;
    }
    if(base_sig1->analytics.timeEnd > time_start){
      time_start = base_sig2->analytics.timeStart;
    }
    //BOTH NOW POINT AT THE START OF THE INTERSECTION DOMAIN
    for(base_sig1_idx;  base_sig1->getValue(base_sig1_idx, _time)  <= time_start;  base_sig1_idx++);
    for(base_sig2_idx;  base_sig1->getValue(base_sig2_idx, _time)  <= time_start;  base_sig2_idx++);
    break;

  default:
    break;
  }

  //now we know summing boundaries
  //

  double avg_samplingTime = (base_sig1->get_analytics().avg_sample_time + base_sig2->get_analytics().avg_sample_time)/2;



  for(resultant_sig_idx;  ;resultant_sig_idx++){
    double sum = 0;
    double resultant_time = time_start + resultant_sig_idx*avg_samplingTime;

    bool base_sig1_inDomain = false;
    bool base_sig2_inDomain = false; 
    if(base_sig1_idx < base_sig1->analytics.samples_num){
      base_sig1_inDomain = isInDomain(time_start, time_end, base_sig1->getValue(base_sig1_idx, _time));
    }
    if((base_sig2_idx < base_sig2->analytics.samples_num)){
      base_sig2_inDomain = isInDomain(time_start, time_end, base_sig2->getValue(base_sig2_idx, _time));
    }

//CHECK IF VALUES ARE IN DOMAIN AND IF IT IS TRUE ADD THEM TO THE RESULTANT
    if(base_sig1_inDomain){
      sum +=  base_sig1->getValue(base_sig1_idx,_val); 
      base_sig1_idx++;
    }
    if(base_sig2_inDomain){
      sum +=  base_sig2->getValue(base_sig2_idx,_val);
      base_sig2_idx++;
    }

    resultant.putValue(sum, resultant_sig_idx ,  _val);
    resultant.putValue(resultant_time, resultant_sig_idx, _time);

    //WE WENT OUT OF DOMAIN SUMMATION ENDED
    if(!base_sig1_inDomain && !base_sig2_inDomain){
      break;
    }
  }

  

  lastOperationSuccess = true;
  return  resultant;
}
/* -------------------------END OF SIGNAL ADD--------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------*/

signal _signal_operation::multiply(signal* base_sig1, signal* base_sig2, int mode)
{
  signal resultant;
  if(!base_sig1->isTimeAnalysed())base_sig1->analyse();
  if(!base_sig2->isTimeAnalysed())base_sig2->analyse();

  //check for their their sampling times if they are valid
  if(!isNear(base_sig1->get_analytics().avg_sample_time , base_sig2->get_analytics().avg_sample_time, samplingRate_diff)  ){
    std::cerr << "CANT WORK WITH THESE TWO SIGNALS  __FAR_SAMPLING_RATES";
    lastOperationSuccess = false;
    return resultant;
  }

  //CHECK DOMAIN BOUNDARIES FOR THE RESULTANT
  double time_end = base_sig1->analytics.timeEnd;
  double time_start = base_sig1->analytics.timeStart;
  unsigned int base_sig1_idx = 0;
  unsigned int base_sig2_idx = 0;
  unsigned int resultant_sig_idx = 0;


  switch (mode)
  {
  case UNION:
  //UNION OPERATION FOR BOTH TIME DOMAINS
    if(base_sig2->analytics.timeEnd > time_end){
      time_end = base_sig2->analytics.timeEnd;
    }
    if(base_sig1->analytics.timeEnd < time_start){
      time_start = base_sig2->analytics.timeStart;
    }
    break;
  
  case INTERSECT:
  //INTERSECT OPERATION FOR BOTH TIME DOMAINS and ITERATE each data set to reach its begining
    if(base_sig2->analytics.timeEnd < time_end){
      time_end = base_sig2->analytics.timeEnd;
    }
    if(base_sig1->analytics.timeEnd > time_start){
      time_start = base_sig2->analytics.timeStart;
    }
    //BOTH NOW POINT AT THE START OF THE INTERSECTION DOMAIN
    for(base_sig1_idx;  base_sig1->getValue(base_sig1_idx, _time)  <= time_start;  base_sig1_idx++);
    for(base_sig2_idx;  base_sig1->getValue(base_sig2_idx, _time)  <= time_start;  base_sig2_idx++);
    break;

  default:
    break;
  }

  //now we know multiplication boundaries
  //

  double avg_samplingTime = (base_sig1->get_analytics().avg_sample_time + base_sig2->get_analytics().avg_sample_time)/2;


  for(resultant_sig_idx;  ;resultant_sig_idx++){
    double result = 1;
    double resultant_time = time_start + resultant_sig_idx*avg_samplingTime;
    bool base_sig1_inDomain = false;
    bool base_sig2_inDomain = false; 

    
    if(base_sig1_idx < base_sig1->analytics.samples_num){
      base_sig1_inDomain = isInDomain(time_start, time_end, base_sig1->getValue(base_sig1_idx, _time));
    }
    if((base_sig2_idx < base_sig2->analytics.samples_num)){
      base_sig2_inDomain = isInDomain(time_start, time_end, base_sig2->getValue(base_sig2_idx, _time));
    }

    if(base_sig1_inDomain){
      result *=  base_sig1->getValue(base_sig1_idx,_val); 
      base_sig1_idx++;
    }
    if(base_sig2_inDomain){
      result *=  base_sig2->getValue(base_sig2_idx,_val);
      base_sig2_idx++;
    }

    resultant.putValue(result, resultant_sig_idx ,  _val);
    resultant.putValue(resultant_time, resultant_sig_idx, _time);
  
    //WE WENT OUT OF DOMAIN SUMMATION ENDED
    if(!base_sig1_inDomain && !base_sig2_inDomain){

      break;
    }

//CHECK IF VALUES ARE IN DOMAIN AND IF IT IS TRUE ADD THEM TO THE RESULTANT

  }

  lastOperationSuccess = true;
  return  resultant;
}

/* -------------------------END OF SIGNAL MULTIPLY--------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------*/
/*BASE SIGNAL ONE IS THE REFRENCE*/
/**
 * @brief calculates phase difference based on maximas and minimas times
 * @param base_sig1 the reference signal
 * @param base_sig2 the signal to compare with
 * @return the phase difference
*/
double _signal_operation::phase_diff(signal *base_sig1, signal *base_sig2)
{ 
  double avgPhaseDiff = 0;


  if(!base_sig1->isTimeAnalysed())base_sig1->analyse();
  if(!base_sig2->isTimeAnalysed())base_sig2->analyse();
  //check for their their sampling times if they are valid

  if(!isNear(base_sig1->get_analytics().avg_sample_time , base_sig2->get_analytics().avg_sample_time, samplingRate_diff)  ){
    std::cerr << "CANT WORK WITH THESE TWO SIGNALS __FAR_SAMPLING_RATES" << endl;
    lastOperationSuccess = false;
    return 0;
  }
  if(!isNear(base_sig1->get_analytics().base_frequency,  base_sig2->get_analytics().base_frequency, freq_diff_accuracy)  ){
    std::cerr << "CANT WORK WITH THESE TWO SIGNALS __FAR_FREQUENCIES_" << endl;
    lastOperationSuccess = false;
    return 0;
  }

  double reference_time = base_sig1->get_valMaximas().time.at(0);
  //WE KEEP COMPARING THE MAXIMAS OF THE SECOND SIGNAL TO INTEGER ORDERS OF THE FIRST SIGNAL and see the time difference between them  
  // timeDiff = peak(n)_time - sig2_nearest_maxima;
  double time_start = base_sig2->analytics.timeStart;
  double time_end = base_sig2->analytics.timeEnd;
  while(reference_time <= time_start){
    reference_time += base_sig1->analytics.periodic_time;
  }

  double sum_phaseDiff = 0;
  //NOW WE HAVE THE the FIRST PEAK of BASE_SIG1 TIME THAT IS IN THE TIME DOMAIN OF BASE_SIG2

  size_t idx = 0;
  for(idx; idx < base_sig2->get_valMaximas().time.size(); idx++){
    double time_diff = base_sig2->get_valMaximas().time.at(idx) - reference_time;
    sum_phaseDiff += time_diff/(base_sig1->get_analytics().periodic_time) * 2 * M_PI;  
    reference_time += base_sig1->analytics.periodic_time;
  }
   avgPhaseDiff = sum_phaseDiff/idx;
  //AVG PHASE DIFFERENCE IN RADS
  return -constrain(avgPhaseDiff);
}


/* -------------------------PHASE ANGLE END--------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------*/

signal _signal_operation::multiply(signal *base_sig1, double val)
{
  if(!base_sig1->isTimeAnalysed())base_sig1->analyse();
  signal resultant;

  for(unsigned int idx = 0; idx < base_sig1->analytics.samples_num;  idx++){
    double multiple = base_sig1->getValue(idx, _val) * val;
    double result_time = base_sig1->getValue(idx, _time);
    resultant.putValue(multiple,  idx,  _val);
    resultant.putValue(result_time,  idx,  _time);
  }
  return resultant;
}


signal _signal_operation::add(signal* base_sig1, double val)
{

  if(!base_sig1->isTimeAnalysed())base_sig1->analyse();
  signal resultant;
  for(unsigned int idx = 0; idx < base_sig1->analytics.samples_num;  idx++){
    double sum = base_sig1->getValue(idx, _val) + val;
    double result_time = base_sig1->getValue(idx, _time);
    resultant.putValue(sum, idx,  _val);
    resultant.putValue(result_time, idx,  _time);
  }
  return resultant;
}


