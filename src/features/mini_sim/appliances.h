#pragma once
#include <json.hpp>
#include "../signals/signal.h"
#include "../signals/signal_operation.h"
#include "../signals/electric.h"
#include <fstream>

class appliance {
  using json = nlohmann::ordered_json;
  private:
    double maximum_tripVoltage = 0;
    double tripVoltage_startTime = 0;
    double maximum_tripVoltage_duration = 0;
    double maximum_tripCurrent = 0;
     double tripCurrent_startTime = 0;
    double maximum_tripCurrent_duration = 0;
    double R = 0;
    double L = 0;
    double C = 0;
    double real = 0;
    double complex = 0;
    std::string name;
    unsigned int inputSignal_idx = 0;



    bool voltageTripped = false;
    bool currentTripped = false;
    double tripTime;

    signal* impedanceTable = NULL;
    _voltage* volt_input = NULL;
    _current* result_current = NULL; 
    _power* powerResult = NULL;


  public:
    appliance(_voltage* _volt_input,  _current* _result_current = NULL, std::string _name = "appliance"){
      name = _name;
      //READ APPLIANCE PROPERTIES FROM JSON FILE FIRST IF EXISTS IF IT DOESN'T CREATE ONE 
      ifstream file;
      json in;
      file.open("appliance/"+_name+".json");
      if(file.is_open()){
        in = json::parse(file);
        maximum_tripVoltage = in[_name]["_maximum_tripVoltage"];
        maximum_tripVoltage_duration = in[_name]["_maximum_tripVoltage_duration"];
        maximum_tripCurrent = in[_name]["_maximum_tripCurrent"];
        maximum_tripCurrent_duration = in[_name]["_maximum_tripCurrent_duration"];
        R = in[_name]["_R"];
        L = in[_name]["_L"];
        C = in[_name]["_C"];
        real = in[_name]["_real"];
        complex = in[_name]["_complex"];
        file.close();
        
      }else{
        init(_name);
      }
    //LINK THE VOLT TO THE APPLIANCE AND THE RESULT CURRENT TOO
    //IF RESULT CURRENT WAS PROVIDED PROVIDE POWER STATISTICS INSTANTLY
      volt_input = _volt_input;
      result_current = _result_current;

      if(!volt_input->isTimeAnalysed())volt_input->analyse();
      if(!result_current->isTimeAnalysed())result_current->analyse();

      if(_result_current != NULL){
        *powerResult = _power(volt_input,result_current);
        powerResult->analyse();
      }
    }  

    double trip();
    void readStep(){
      if( (inputSignal_idx < volt_input->get_analytics().samples_num ) || (inputSignal_idx < result_current->get_analytics().samples_num ) ){
        double thisInstantVoltage = 0;
        double thisInstantTime = 0;
        double thisInstantCurrent = 0;
        
        if(inputSignal_idx < volt_input->get_analytics().samples_num){
          double thisInstantVoltage = volt_input->get_sig_data().getData(inputSignal_idx,_val);
          double thisInstantTime = volt_input->get_sig_data().getData(inputSignal_idx,_time);
        }

        if(inputSignal_idx < result_current->get_analytics().samples_num){
          double thisInstantCurrent = result_current->get_sig_data().getData(inputSignal_idx,_val);
        }

        if(thisInstantVoltage > maximum_tripVoltage){
          tripVoltage_startTime = thisInstantTime;
        }

        if(thisInstantCurrent > maximum_tripCurrent){
          tripCurrent_startTime = thisInstantTime;
        }
        inputSignal_idx++;
      }
    }


    static void init(std::string _name,
              double _maximum_tripVoltage = 0,
              double _maximum_tripVoltage_duration = 0,
              double _maximum_tripCurrent = 0,
              double _maximum_tripCurrent_duration = 0,
              double _R = 0,
              double _L = 0,
              double _C = 0,
              double _real = 0,
              double _complex = 0
    ){
      json out;
      ofstream file;
      out[_name]["_maximum_tripVoltage"] = std::to_string(_maximum_tripVoltage);
      out[_name]["_maximum_tripVoltage_duration"] = std::to_string(_maximum_tripVoltage_duration);
      out[_name]["_maximum_tripCurrent"] = std::to_string(_maximum_tripCurrent);
      out[_name]["_maximum_tripCurrent_duration"] = std::to_string(_maximum_tripCurrent_duration);
      out[_name]["_R"] = std::to_string(_R);
      out[_name]["_L"] = std::to_string(_L);
      out[_name]["_C"] = std::to_string(_C);
      out[_name]["_real"] = std::to_string(_real);
      out[_name]["_complex"] = std::to_string(_complex);

      file.open("appliance/"+_name+".json");
      if(file.is_open()){
        file << out;
      }
      file.close();
    }



    void refresh(){
      ifstream file;
      json in;
      file.open("appliance/"+name+".json");
      if(file.is_open()){
        in = json::parse(file);
        maximum_tripVoltage = in[name]["_maximum_tripVoltage"];
        maximum_tripVoltage_duration = in[name]["_maximum_tripVoltage_duration"];
        maximum_tripCurrent = in[name]["_maximum_tripCurrent"];
        maximum_tripCurrent_duration = in[name]["_maximum_tripCurrent_duration"];
        R = in[name]["_R"];
        L = in[name]["_L"];
        C = in[name]["_C"];
        real = in[name]["_real"];
        complex = in[name]["_complex"];
      }
      file.close();
    }
};