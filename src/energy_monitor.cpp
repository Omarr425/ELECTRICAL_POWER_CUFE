#include "energy_monitor.h"
#include <iostream>



// this file is for testing for now
int main(){
  string file_name;
  dataTable data = dataTable();
  file_IO file;


  cout << "PLEASE CHOOSE A FILE TO IMPORT" << endl;
  cin >> file_name;
  signal dummySignal = signal();

  if(dummySignal.loadData(file_name)){
    cout<<"SUCCESS"<<endl;  
    
    dummySignal.signal_analytics();



  cout << "PLEASE CHOOSE A FILE TO EXPORT" << endl;
  cin >> file_name;
  if(dummySignal.exportSignal(file_name)){
    cout<<"SUCCESS"<<endl;
  }else
  {
    cout<<"ERR"<<endl;
  }

  cout<< dummySignal.get_analytics().min_val << endl;
  cout<< dummySignal.get_analytics().max_val << endl;
  cout<< dummySignal.get_analytics().max_ptp << endl;
  cout<< dummySignal.get_analytics().min_ptp << endl;

  }else
  {
    cout<<"ERR"<<endl;
  }





  cout<<"PROGRAM EXECUTED SUCCESSFULLY TYPE Q to QUIT" << endl;
  while (std::cin.get() != 'Q'){
  };
  std::cout<<"TERMINATE"<< endl;
  return 1;
}
