#pragma once
#include <json.hpp>
#include <iostream>
#include <string>
#include <fstream>

using json = nlohmann::json;


class _settings{

  json configs;
  void loadDefaultConfigs(){
    configs["signal"]["export_path"] = R"(signals/)" ;
    configs["signal"]["import_path"] = R"(signals/)" ;
    configs["signal"]["min_max_accuracy"] = to_string(0.05);
    configs["signal"]["freq_diff"] = to_string(0.05);
    configs["signal"]["samplingRate_diff"] = to_string(0.05);
  }



  public:
  _settings(){ 

    std::ifstream configFileRead("configFile.json");
    if(!configFileRead.is_open()){

      std::ofstream configFileWrite;
      configFileWrite.open("configFile.json");
      loadDefaultConfigs();
      configFileWrite << std::setw(4) << configs;
      configFileWrite.close();
    }else{
      configs = json::parse(configFileRead);
    }
  }



  bool save_settings(){
    std::ofstream configFileWrite("configFile.json");
    configFileWrite << setw(4) << configs << endl;
    return true;
  }



  template <typename t>
  void change_setting(string class_name, string setting,t val){
    configs[class_name][setting] = to_string(val);
  }



  string get_setting(string class_name,string setting){
    cout << configs[class_name][setting] << endl; 
    return configs[class_name][setting];
  }

};