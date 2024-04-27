#pragma once 

#include <stdlib.h>
#include <vector>
#include "../../core/core.h"
#include <string>

struct _signal_data{
  std::string dataLabels[4] = {"time","val","dv/dt","vdt"};
  dataTable *data;
};



class signal{
  protected:
  //Basic data
  struct _analytics{
    double base_frequency;
    
    double avg_ptp; //avg peak to peak

    double max_ptp;
    double max_ptp_time; //time in seconds;
    double min_ptp;
    double min_ptp_time;

    double avg_max_vals; //avg amplitude
    double avg_min_vals;


    //VALUES MAX/MIN
    double max_val;
    double max_val_time; //time in seconds;
    double min_val;
    double min_val_time;
 
    //SLOPE MAX/MIN
    double max_dvBdt;
    double max_dvBdt_time; //time in seconds;
    double min_dvBdt;
    double min_dvBdt_time;

    double dc_offset;
    double thd;  //total harmonic distortion;
    double rms;
    double avg;
    
    bool is_harmonic;
    bool is_periodic;

  }analytics;

    
    _signal_data signal_data;
//METHODS FOR SETTING AND GETTING VALUES FROM the signal dataset
    inline void putValue(double val, int row, int col){
      signal_data.data->insertData(val,row,col);
    }

    inline double getValue(int row, int col){
      return signal_data.data->getData(row,col);
    }

    inline void refreshData(){
      signal_data.data->col_Refresh();
      signal_data.data->row_Refresh();
    }



    double accuracy_for_min_max = 0.95;

    dataTable val_maximas;
    dataTable val_manimas;
    dataTable dvBdt_maximas;
    dataTable dvBdt_manimas;

    bool timeDomain_analysed;
    
    double _dvBdt(double v1, double v2, double t1, double t2);
    double _dv2Bdt2(double v1, double v2, double v3, double t1, double t2);
    double _vdt(double v1, double v2, double t1, double t2);
    

    //Makes variable data out of the time-value data such as slopes and areas wrt to time
    bool pre_analyze();
    bool soft_analyze();

    double timeStart;
    double timeEnd;
    int samples_num;

  public:

    signal(dataTable *d);
    enum{
      time,
      val,
      first_deriv,
      second_deriv,
      area
    };

    bool signal_analytics();

    const _analytics get_analytics();
    dataTable get_sig_data()const;
};



//Scalar with signal or signal with signal operations
struct _signal_operation{

      //signal with a signal arthimetic
    signal add(signal base_sig1,  signal base_sig2);
    signal subtract(signal base_sig1, signal base_sig2);
    signal multiply(signal base_sig1, signal base_sig2);
    signal divide(signal base_sig1, signal base_sig2);
    double phase_diff(signal base_sig1, signal base_sig2);
    
    double integ_vpower(signal base_sig1, int power);
    

    //Scalar with a signal arthimetic
    signal add(signal base_sig1,  double val);
    signal subtract(signal base_sig1, double val);
    signal multiply(signal base_sig1, double val);
    signal divide(signal base_sig1, double val);
    signal logarithmic(signal base_sig);

  //filtering
    enum filterType{
      cascade
    };
    //first order filters returns filtered signals
      //second order filters yet to come
    signal lowPass_filter(signal base_sig, int order=1, int t = cascade);
    signal highPass_filter(signal base_sig, int order=1, int t = cascade);
    signal bangReject_filter(signal base_sig, int order=1, int t = cascade);
    signal bandPass_filter(signal base_sig, int order=1, int t = cascade);
    signal factor_frequency(signal base_sig, float increase_ratio);



    //extracts a subset of a signal with time boundaries
    signal subsignal_time(signal base_sig, double time_start,  double time_end);
    //extracts a subset of a signal with value boundaries
    signal subsignal_value(signal base_sig, double value1,  double value2);
    //extract a subset of a signal starting from a value for a certain period
    signal subsignal_value_till(signal base_sig, double value1,  double time_after);

    //frequency analytics
    std::vector<double[2]> forrierTransform(signal base_sig);
};