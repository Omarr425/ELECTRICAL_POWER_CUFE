#pragma once
#include <json.hpp>


using json = nlohmann::ordered_json;
//DEFAULT SETTING FUNCTION FOR ALL
void default_settings_init(json *def);
void signal_defaults(json *def);