#pragma once
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
#include <fstream>

  enum{
    signal_defaulSignalImportPath,
    signal_defaulSignalExportPath,
    signal_defaultAccuracyFactor
  };

class _settings{

  YAML::Node config;

  std::string signal_exportPath;
  std::string signal_importPath;
  std::string signal_accuracyFactor;


  public:
  _settings(){
    config = YAML::LoadFile("config.yaml");
    signal_exportPath = config["signal"]["defaultExportPath"].as<std::string>();
    signal_importPath = config["signal"]["defaultImportPath"].as<std::string>();
    signal_accuracyFactor = config["signal"]["defaultAccuracyFactor"].as<std::string>();
  }
  bool save_settings(){
    std::ofstream file;
    file.open("config.yaml");
    if(file.is_open()){
      file << config;
      file.close();
      return true;
    }else{
      return false;
    }
  }


  template <typename t>
  void change_settings(int settingToChange,t data){
    switch (settingToChange)
    {
    case signal_defaulSignalImportPath:
        signal_importPath = data;
        config["signal"]["defualtImportPath"] = signal_importPath;
      break;
    
    case signal_defaulSignalExportPath:
        signal_exportPath = data;
        config["signal"]["defaultExportPath"] = signal_exportPath;
      break;

    case signal_defaultAccuracyFactor:
        signal_accuracyFactor = data;
        config["signal"]["defaulAccuracyFactor"] = signal_defaultAccuracyFactor;
      break;

    default:
      break;
    }
  }

std::string get_settings(int settingToGet){
    switch (settingToGet)
    {
      case signal_defaulSignalImportPath:
        return signal_importPath;
        break;
    
      case signal_defaulSignalExportPath:
        return signal_exportPath;
        break;

      case signal_defaultAccuracyFactor:
        return signal_accuracyFactor;

      default:
        return 0;
        break;
    }
  }



};