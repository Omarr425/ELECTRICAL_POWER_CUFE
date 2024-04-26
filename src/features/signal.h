#pragma once 

#include <stdlib.h>
#include <vector>
#include "../core/core.h"
#include <string>

struct signal_data{
  signal_data(string *labels);const
  std::vector<string> labels;
  dataTable data;
};


class signal{
  private:
  //Basic data
    double frequency;

    double avg_ptp; //avg peak to peak

    double max_ptp;
    double max_ptp_time; //time in seconds;
    double min_ptp;
    double min_ptp_time;

    double avg_amp; //avg amplitude
    
    double max_amp;
    double max_amp_time; //time in seconds;
    double min_amp;
    double min_amp_time;
    dataTable amp_maximas;
    dataTable amp_manimas;


    double max_dvBdt;
    double max_dvBdt_time; //time in seconds;
    double min_dvBdt;
    double min_dvBdt_time;
    dataTable dvBdt_maximas;
    dataTable dvBdt_manimas;


    double direct_offset;
    
    double thd;  //total harmonic distortion;
    double rms;
    double avg;
    bool magnitude_analysed;

    std::string dataLabels[4] = {"Time","Value","dV/dT","V.dT"};
    signal_data data = signal_data(dataLabels); 

    signal(dataTable *data);
    void signal_magnitude_analytics();


    //basic time-value data
    
    //frequency analytics
    std::vector<signal> forrierTransform(signal base_sig);


    //Signal arthimetic

    //extracts a subset of a signal with time boundaries
    signal subsignal_time(signal base_sig, double time_start,  double time_end);
    //extracts a subset of a signal with value boundaries
    signal subsignal_value(signal base_sig, double value1,  double value2);


    //signal with a signal arthimetic
    signal add(signal base_sig1,  signal base_sig2);
    signal subtract(signal base_sig1, signal base_sig2);
    signal multiply(signal base_sig1, signal base_sig2);
    signal divide(signal base_sig1, signal base_sig2);

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



};