#pragma once
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
#include <fstream>

  enum{
    defaulSignalImportPath,
    defaulSignalExportPath,
  };

class _settings{

  YAML::Node config;

  std::string signal_exportPath;
  std::string signal_importPath;


  public:
  _settings(){
    config = YAML::LoadFile("config.yaml");
    signal_exportPath = config["defaultExportPath"].as<std::string>();
    signal_importPath = config["defaultImportPath"].as<std::string>();
  }
  void save_settings(){
    std::ofstream file;
    file << config;
  }


  template <typename t>
  void change_settings(int settingToChange,t data){
    switch (settingToChange)
    {
    case defaulSignalImportPath:
        signal_importPath = data;
        config["signal"]["defualtImportPath"] = signal_importPath;
      break;
    
    case defaulSignalExportPath:
        signal_exportPath = data;
        config["signal"]["defaultExportPath"] = signal_exportPath;
      break;

    default:
      break;
    }
  }

template <typename t>
t get_settings(int settingToGet){
    switch (settingToGet)
    {
      case defaulSignalImportPath:
        return signal_importPath;
        break;
    
      case defaulSignalExportPath:
        return signal_exportPath;
        break;

      default:
        return 0;
        break;
    }
  }



};