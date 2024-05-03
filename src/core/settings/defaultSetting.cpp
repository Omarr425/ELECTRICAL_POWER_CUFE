#include "defaultSetting.h"
#include <string>
#include <sstream>
#include <json.hpp>


using json = nlohmann::ordered_json;
void default_settings_init(json *def){
  signal_defaults(def);
}


void signal_defaults(json *def){
    (*def)["signal"]["export_path"] = R"(signals/)" ;
    (*def)["signal"]["import_path"] = R"(signals/)" ;
    (*def)["signal"]["min_max_accuracy"] = std::to_string(0.05);
    (*def)["signal"]["freq_diff"] = std::to_string(0.05);
    (*def)["signal"]["samplingRate_diff"] = std::to_string(0.05);
    (*def)["signal"]["maxima_rounding"] = std::to_string(0.001);
    (*def)["signal"]["minima_rounding"] = std::to_string(0.1);
}



