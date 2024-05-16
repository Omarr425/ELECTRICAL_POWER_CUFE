#include "energy_monitor_cli.h"
#include <iostream>
#include "features/signals/signal.h"

/*
  SUBSIGNAL IMPLEMENTATION TEST FOR SIGNAL ANALYSIS FOR DIFFERENT STATES FOR A SIGNAL
  DIVIDE AND CONQUER LIKISH APPROACH WHERE EACH TIME A PERIOD WITH DIFFERENT PERIODIC TIME BREAKS A SET
  THE SET THAT WAS BROKEN BECOMES A UNIQUE SIGNAL THAT DESERVES AN ANALYSIS FOR IT ONLY 


*/


/*!
  @file energy_monitor_cli.cpp
  @brief the main file where the main() function exists and the program starts executing
*/

using v_container = dataTable<double>;


void analyticBlock(signal *dummySignal, bool show_peaks_troughs = false);

int main(){
  std::string user_input;
  v_container dataContainer;
  file_IO file_manipulation;

  pdf_wrap PDF_LOVE;


  PDF_LOVE.init("SADPDF.PDF");
  PDF_LOVE.textPiece_start();
  PDF_LOVE.setFontStyle(5,50,50,50,1);
  PDF_LOVE.setCursor(LEFT(30), TOP(50));
  PDF_LOVE.addText("SAD");
  PDF_LOVE.newLine();
  PDF_LOVE.addText("SAD BUT TWICE");
  PDF_LOVE.newLine();
  PDF_LOVE.addText("SAD BUT THRICE");
  PDF_LOVE.newLine();
  PDF_LOVE.textPiece_end();
  PDF_LOVE.end();



  cout << "EXTRACTING DATA FROM THE FILE.........." << endl;
  file_manipulation.data_import("Load1.csv",dataContainer,csv);
  

  cout << "COLUMNS NUMBER OF CURRENT TABLE IS :::" << dataContainer.get_col_num() << endl;
  cout << "ROWS NUMBER OF CURRENT TABLE IS :::" << dataContainer.get_row_num() << endl;

  /*I HAD TO EXTRACT COLUMNS AND MANIPULATE THEM SINCE THE EXPECTED FORMAT WAS NOT PROVIDED*/


  cout << "REARRANGING DATA.........." << endl;
  std::vector<double> time;
  dataContainer.extractColumn(0,time);
  std::vector<double> current;
  dataContainer.extractColumn(2,current);
  std::vector<double> voltage;
  dataContainer.extractColumn(1,voltage);



  v_container currentTable;
  currentTable.insertColumn(_time,time);
  currentTable.insertColumn(_val,current);
  currentTable.sub_table(currentTable,  0,  500000,  0,  1);
  

  v_container voltageTable;  
  voltageTable.insertColumn(_time,time);
  voltageTable.insertColumn(_val,voltage);
  voltageTable.sub_table(voltageTable,  0,  500000,  0,  1);
  /*NOW I HAVE THE EXPECTED FORMAT*/

  _voltage voltage_input;
  _current current_input;
  voltage_input.set_hysteresis(0, -100);
  current_input.set_hysteresis(0, -3);
  voltage_input.loadData(voltageTable);
  current_input.loadData(currentTable);


  _power result_power = _power(voltage_input,current_input);

 

  cout << "ANALYSING UNFILTERED SIGNALS .....\n\n" << endl;
  cout << "\n***********VOLTAGE ANALYSIS******\n" << endl;
  analyticBlock(&voltage_input);
  for(int i = 0; i < voltage_input.subSignal_periodBased()->subSignals.size(); i++){
    cout << "----------------------------------" << endl;
    cout << "SUBSIGNAL : " << i << endl;
    cout << "----------------------------------" << endl;
      analyticBlock( &(voltage_input.subSignal_periodBased()->subSignals.at(i)) );
  }
  cout << "\n***********CURRENT ANALYSIS******\n" << endl;
  analyticBlock(&current_input);
  for(int i = 0; i < current_input.subSignal_periodBased()->subSignals.size(); i++){
    cout << "----------------------------------" << endl;
    cout << "SUBSIGNAL : " << i << endl;
    cout << "----------------------------------" << endl;
      analyticBlock( &(current_input.subSignal_periodBased()->subSignals.at(i)) );
  }
  cout << "\n***********POWER ANALYSIS******\n" << endl;
  analyticBlock(&result_power);
  for(int i = 0; i < result_power.subSignal_periodBased()->subSignals.size(); i++){
    cout << "----------------------------------" << endl;
    cout << "SUBSIGNAL : " << i << endl;
    cout << "----------------------------------" << endl;
      analyticBlock( &(result_power.subSignal_periodBased()->subSignals.at(i)) );
  }


  cout << "POWER FACTOR :::" << result_power.get_PF() << endl;
  cout << "active :::" << result_power.get_active() << endl;
  cout << "apparent :::" << result_power.get_apparent() << endl;


  cout << "TYPE \"EXPORT\" TO EXPORT UNFILTERED else to pass" << endl;
  cin >> user_input;

  if (user_input == "EXPORT") {
      cout << "EXPORTING UNFILTERED .....\n\n" << endl;

      voltage_input.exportSignal("voltage_output.csv",true ,  sig_exp::csv);
      current_input.exportSignal("current_output.csv",false, sig_exp::csv);
      result_power.exportSignal("power_output.csv",false , sig_exp::csv);
  }

  
  cout << "Filtering .....\n\n" << endl;
  
  
  signal_operation_global.firstO_lowPass_filter(voltage_input,voltage_input,500,2);
  signal_operation_global.firstO_lowPass_filter(current_input,current_input,500,2);
  result_power = _power(voltage_input,current_input);

  cout << "\n***********FILTERED VOLTAGE ANALYSIS******\n" << endl;
  analyticBlock(&voltage_input);
  for(int i = 0; i < voltage_input.subSignal_periodBased()->subSignals.size(); i++){
    cout << "----------------------------------" << endl;
    cout << "SUBSIGNAL : " << i << endl;
    cout << "----------------------------------" << endl;
      analyticBlock( &(voltage_input.subSignal_periodBased()->subSignals.at(i)) );
  }
  cout << "\n***********FILTERED CURRENT ANALYSIS******\n" << endl;
  analyticBlock(&current_input);
  for(int i = 0; i < current_input.subSignal_periodBased()->subSignals.size(); i++){
    cout << "----------------------------------" << endl;
    cout << "SUBSIGNAL : " << i << endl;
    cout << "----------------------------------" << endl;
      analyticBlock( &(current_input.subSignal_periodBased()->subSignals.at(i)) );
  }
  cout << "\n***********FILTERED POWER ANALYSIS******\n" << endl;
  analyticBlock(&result_power);
  for(int i = 0; i < result_power.subSignal_periodBased()->subSignals.size(); i++){
    cout << "----------------------------------" << endl;
    cout << "SUBSIGNAL : " << i << endl;
    cout << "----------------------------------" << endl;
      analyticBlock( &(result_power.subSignal_periodBased()->subSignals.at(i)) );
  }

  cout << "POWER FACTOR :::" << result_power.get_PF() << endl;
  cout << "active :::" << result_power.get_active() << endl;
  cout << "apparent :::" << result_power.get_apparent() << endl;

  cout << "TYPE \"EXPORT\" TO EXPORT FILTERED else to pass" << endl;
  cin >> user_input;
  if (user_input == "EXPORT") {
      cout << "EXPORTING FILTERED .....\n\n" << endl;
      voltage_input.exportSignal("voltage_output_filtered.csv");
      current_input.exportSignal("current_output_filtered.csv");
      result_power.exportSignal("power_output_filtered.csv");
  }
  cout << "NOW SIMULATING THE APPLIANCE MODEL USING FILTERED CURRENT AND VOLTAGE.........." << endl;


  cout << "SIMULATING APPLIANCE WITH FILTERED CURRENT&VOLTAGE .....\n\n" << endl;
  appliance modelAppliance = appliance(voltage_input,current_input,"refrigerator");
  unsigned int steps_number = modelAppliance.get_power()->get_analytics()->samples_num;
  for(unsigned int step = 0;  step < steps_number ; step++)modelAppliance.readStep();

  cout << "SIMULATION RESULTS\n\n" << endl;
  cout << "VOLTAGE TRIPPED : " << bool_to_string(modelAppliance.voltage_tripped()) << endl;
  if(modelAppliance.voltage_tripped()){
    cout << "AT :::" << modelAppliance.voltage_tripTime() << endl;
  }
  cout << "CURRENT TRIPPED : " << bool_to_string(modelAppliance.current_tripped()) << endl;
  if(modelAppliance.current_tripped()){
    cout << "AT :::" << modelAppliance.current_tripTime() << endl;
  }
  
  //GET ENERGY CONSUMED FROM TIME OF START TILL A VERY LONG TIMEE
  double energy = modelAppliance.get_power()->get_energy(0,100000);
  //NOW WE HAVE ENERY IN WATT.SECOND
  energy = ((energy/1000)/ (3600) );

  cout << "ENERGY COST :::" << tarrif_calc(energy) << " EGP" <<endl; 

  cout << "TYPE QUIT TO EXIT" << endl;
  while (1) {
     cin >> user_input;
      if (user_input == "QUIT")break;
  }


  return 1;
}



void analyticBlock(signal *dummySignal, bool show_peaks_troughs){
  if(!dummySignal->isTimeAnalysed())dummySignal->analyse();
  std::cout << "TIME_START :: " << dummySignal->get_analytics()->timeStart << endl;
  std::cout << "TIME_END :: " << dummySignal->get_analytics()->timeEnd << endl;
  std::cout << "MAX::"<<dummySignal->get_analytics()->max_val << " at "  <<  dummySignal->get_analytics()->max_val_time << endl;
  std::cout << "MIN::"<<dummySignal->get_analytics()->min_val << " at "  <<  dummySignal->get_analytics()->min_val_time << endl;
  std::cout << "AVG::"<<dummySignal->get_analytics()->avg << endl;
  std::cout << "RMS::"<<dummySignal->get_analytics()->rms << endl;
  std::cout << "SAMPLING_RATE::"<<dummySignal->get_analytics()->avg_sample_time << endl;
  std::cout << "NUM_OF_SAMPLES::"<<dummySignal->get_analytics()->samples_num << endl;
  std::cout << "DATA VIABLE ::" << dummySignal->dataViable() << endl;
  std::cout << "FREQUENCY ::" << dummySignal->get_analytics()->base_frequency << endl;
}


