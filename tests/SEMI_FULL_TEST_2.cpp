#include "energy_monitor_cli.h"
#include <iostream>




void analyticBlock(signal *dummySignal, bool show_peaks_troughs=false);





int main(){
  _voltage volt1;
  _current current1;
  std::string user_input;


  cout << "ENTER VOLT INPUT" << endl;
  cin >> user_input;
  volt1.loadData(user_input);
  
  cout << "ENTER CURRENT INPUT" << endl;
  cin >> user_input;
  current1.loadData(user_input);


  cout << "ENTER EXPORT FILTERED VOLT" << endl;
  cin >> user_input;
  _voltage volt2 = volt1;
  signal_operation_global.firstO_lowPass_filter(&volt2,&volt2,1000,1);
  volt2.exportSignal(user_input);

  cout << "ENTER EXPORT FILTERED CURRENT" << endl;
  cin >> user_input;
  _current current2 = current1;
  signal_operation_global.firstO_lowPass_filter(&current2,&current2,1000,1);
  current2.exportSignal(user_input);

  cout << "ENTER EXPORT UNFILTERED POWER" << endl;
  cin >> user_input;
  _power power1 = _power(&volt1,&current1);
  power1.exportSignal(user_input);

  cout << "ENTER EXPORT FILTERED POWER" << endl;
  cin >> user_input;
  _power power2 = _power(&volt2,&current2);
  power2.exportSignal(user_input);


  appliance refrigerator = appliance(&volt1,&current1,"refrigerator");
  cout << refrigerator.get_power()->get_energy(0,5) << endl;
  for(int i = 0; i < 60000; i++)refrigerator.readStep();
  cout << "CURRENT TRIP DETECTED ::: " << refrigerator.current_tripped() << endl;
  cout << "VOLTAGE TRIP DETECTED ::: " << refrigerator.current_tripped() << endl;


  cout << "TYPE DEEP_ANALYTICS FOR IN DETAIL ANALYSIS RESULTS OR PRESS ENTER TO QUIT" << endl;
  cin >> user_input; 

  if(user_input == "DEEP_ANALYTICS"){
    cout << "----------------------INPUT CURRENT-----------------------" << endl;
    analyticBlock(&current1);
    cout << "----------------------INPUT VOLTAGE-----------------------" << endl;
    analyticBlock(&volt1);
    cout << "----------------------FILTERED CURRENT-----------------------" << endl;    
    analyticBlock(&current2);
    cout << "----------------------FILTERED VOLTAGE-----------------------" << endl;    
    analyticBlock(&volt2);
    cout << "----------------------UNFILTERED COMPONENTS POWER-----------------------" << endl;    
    analyticBlock(&power1);
    cout << "--------------------------------------------------" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "PHASE ANGLE    :::  " << signal_operation_global.phase_diff(&volt1, &current1)/M_PI << "PI" << endl;
    cout << "ENERGY CONSUMPTION :::  " << power1.get_energy(0,5) << endl;
    cout << "APPARENT:::  " << power1.get_apparent() << endl;
    cout << "ACTIVE:::  " << power1.get_active() << endl;
    cout << "REACTIVE:::  " << power1.get_reactive() << endl;
    cout << "POWER_FACTOR:::  " << power1.get_PF() << endl;
    cout << "LOAD TYPE:::  " << power1.get_loadType() << endl;
    cout << "POWER_FACTOR_TYPE ::: " << power1.pf_type() << endl;
    cout << "----------------------FILTERED COMPONENTS POWER-----------------------" << endl;
    analyticBlock(&power2);
    cout << "--------------------------------------------------" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "PHASE ANGLE    :::  " << signal_operation_global.phase_diff(&volt1, &current1)/M_PI << "PI" << endl;
    cout << "ENERGY CONSUMPTION :::  " << power2.get_energy(0,5) << endl;
    cout << "APPARENT:::  " << power2.get_apparent() << endl;
    cout << "ACTIVE:::  " << power2.get_active() << endl;
    cout << "REACTIVE:::  " << power2.get_reactive() << endl;
    cout << "POWER_FACTOR:::  " << power2.get_PF() << endl;
    cout << "LOAD TYPE:::  " << power2.get_loadType() << endl;
    cout << "POWER_FACTOR_TYPE ::: " << power2.pf_type() << endl;
  }
}



void analyticBlock(signal *dummySignal, bool show_peaks_troughs){
  dummySignal->analyse();
  cout << "NUM_P::"<<dummySignal->get_analytics()->periods_num << endl;
  cout << "MAX::"<<dummySignal->get_analytics()->max_val << " at "  <<  dummySignal->get_analytics()->max_val_time << endl;
  cout << "MIN::"<<dummySignal->get_analytics()->min_val << " at "  <<  dummySignal->get_analytics()->min_val_time << endl;
  cout << "PTP::"<<dummySignal->get_analytics()->avg_ptp << endl;
  


  if(show_peaks_troughs){
    cout << "NUM_MAXES::"<<dummySignal->get_valMaximas()->value.size() << endl;
    cout << "---------MAXIMAS----------------" << endl;
    for(int i = 0; i < dummySignal->get_valMaximas()->value.size(); i++){
    cout << dummySignal->get_valMaximas()->value.at(i) << " at " << dummySignal->get_valMaximas()->time.at(i) << endl;
    }
    cout << "----------------------------------" << endl;
    cout << "NUM_MINS::"<<dummySignal->get_valMinimas()->value.size() << endl;
    cout << "---------MINIMAS----------------" << endl;
    for(int i = 0; i < dummySignal->get_valMinimas()->value.size(); i++){
    cout << dummySignal->get_valMinimas()->value.at(i) << " at " << dummySignal->get_valMinimas()->time.at(i) << endl;
  }
    cout << "----------------------------------" << endl;
  }

  cout << "DC_OFF::"<<dummySignal->get_analytics()->dc_offset << endl;
  cout << "AVG::"<<dummySignal->get_analytics()->avg << endl;
  cout << "RMS::"<<dummySignal->get_analytics()->rms << endl;
  cout << "DUTY::"<<dummySignal->get_analytics()->duty_cycle << endl;
  cout << "FREQ::"<<dummySignal->get_analytics()->base_frequency << endl;
  cout << "ANG_FREQ::"<<dummySignal->get_analytics()->base_angular_frequency << endl;
  cout << "SAMPLING_RATE::"<<dummySignal->get_analytics()->avg_sample_time << endl;
  cout << "NUM_OF_SAMPLES::"<<dummySignal->get_analytics()->samples_num << endl;
  cout << "DATA VIABLE ::" << dummySignal->dataViable() << endl;
}
