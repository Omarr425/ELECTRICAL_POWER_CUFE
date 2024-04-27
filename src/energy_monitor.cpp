#include "energy_monitor.h"
#include <iostream>



// this file is for testing for now
int main(){
  string file_addr;
  dataTable data = dataTable();
  file_IO file;


  cout << "PLEASE CHOOSE A FILE TO IMPORT" << endl;
  cin >> file_addr;

  if(file.data_import(file_addr,&data,csv)){
    cout<<"SUCCESS"<<endl;
  }else
  {
    cout<<"ERR"<<endl;
  }



  signal dummySignal = signal(&data);
  dummySignal.signal_analytics();


  cout << "PLEASE CHOOSE A FILE TO EXPORT" << endl;
  cin >> file_addr;

  if(file.data_export(file_addr,dummySignal.get_sig_data(),csv)){
    cout<<"SUCCESS"<<endl;
  }else
  {
    cout<<"ERR"<<endl;
  }

  cout<< dummySignal.get_analytics().rms << endl;
  cout<< dummySignal.get_analytics().avg << endl;


  cout<<"PROGRAM EXECUTED SUCCESSFULLY TYPE Q to QUIT" << endl;
  while (std::cin.get() != 'Q'){
  };
  std::cout<<"TERMINATE"<< endl;
  return 1;
}
