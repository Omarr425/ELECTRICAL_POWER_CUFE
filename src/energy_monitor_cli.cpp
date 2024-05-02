#include "energy_monitor_cli.h"
#include <iostream>







void analyticBlock(signal*);
// this file is for testing for now




int main(){
  string file_name;
  dataTable data = dataTable();
  file_IO file;


  cout << "PLEASE CHOOSE A FILE TO IMPORT" << endl;
  cin >> file_name;
  signal dummySig1 = signal();
  
  if(dummySig1.loadData(file_name)){
    cout<<"SUCCESS"<<endl;  
    cout << "PLEASE CHOOSE A FILE TO IMPORT" << endl;
    cin >> file_name;
    signal dummySig2 = signal();
    dummySig2.loadData(file_name);
    _signal_operation operation;

    cout << "PHASE ANGLE    :::  " << operation.phase_diff(&dummySig1, &dummySig2)/M_PI << "PI" << endl;

    signal dummySig3 = operation.multiply(&dummySig1,  &dummySig2, INTERSECT);

    //analyticBlock(&dummySig1); 
    //analyticBlock(&dummySig2);
    //analyticBlock(&dummySig3);
 


    cout << "PLEASE CHOOSE A FILE TO EXPORT" << endl;
    cin >> file_name;
    if(dummySig3.exportSignal(file_name)){
      cout<<"SUCCESS"<<endl;
    }else{
      cout<<"ERR"<<endl;
    }
  }else{
    cout<<"ERR"<<endl;
  }

  cout<<"PROGRAM EXECUTED SUCCESSFULLY TYPE Q to QUIT" << endl;
  while (std::cin.get() != 'Q'){
  };
  std::cout<<"TERMINATE"<< endl;
  return 1;
}






void analyticBlock(signal *dummySignal){
  dummySignal->analyse();
  cout << "NUM_P::"<<dummySignal->get_analytics().periods_num << endl;
  cout << "MAX::"<<dummySignal->get_analytics().max_val << " at "  <<  dummySignal->get_analytics().max_val_time << endl;
  cout << "MIN::"<<dummySignal->get_analytics().min_val << " at "  <<  dummySignal->get_analytics().min_val_time << endl;
  cout << "PTP::"<<dummySignal->get_analytics().max_ptp << endl;
  cout << "NUM_MAXES::"<<dummySignal->get_valMaximas().value.size() << endl;
  cout << "---------MAXIMAS----------------" << endl;
  for(int i = 0; i < dummySignal->get_valMaximas().value.size(); i++){
    cout << dummySignal->get_valMaximas().value.at(i) << " at " << dummySignal->get_valMaximas().time.at(i) << endl;
  }
  cout << "----------------------------------" << endl;
  cout << "NUM_MINS::"<<dummySignal->get_valMinimas().value.size() << endl;
  for(int i = 0; i < dummySignal->get_valMinimas().value.size(); i++){
    cout << dummySignal->get_valMinimas().value.at(i) << " at " << dummySignal->get_valMinimas().time.at(i) << endl;
  }
    cout << "----------------------------------" << endl;
  cout << "DC_OFF::"<<dummySignal->get_analytics().dc_offset << endl;
  cout << "AVG::"<<dummySignal->get_analytics().avg << endl;
  cout << "RMS::"<<dummySignal->get_analytics().rms << endl;
  cout << "DUTY::"<<dummySignal->get_analytics().duty_cycle << endl;
  cout << "FREQ::"<<dummySignal->get_analytics().base_frequency << endl;
  cout << "ANG_FREQ::"<<dummySignal->get_analytics().base_angular_frequency << endl;
  cout << "SAMPLING_RATE::"<<dummySignal->get_analytics().avg_sample_time << endl;
  cout << "HAS DATA ::" << dummySignal->hasData() << endl;
  cout << "DATA VIABLE ::" << dummySignal->dataViable() << endl;
}