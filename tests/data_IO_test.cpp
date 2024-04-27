
#include "data_IO_test.h"
#include <iostream>
#include <iomanip>

using namespace std;

// this file is for testing for now
int main(){
  string file_addr;
  dataTable dataObj = dataTable();
  file_IO fileio;

  //IMPORT DATA AS CSV
  cout << "PLEASE CHOOSE IMPORT FILE" << endl;
  cin >> file_addr;
  if(fileio.data_import(file_addr, &dataObj, csv)){
    cout << "DATA IMPORT SUCCESS" << endl;
  }
  else{
    cout << "DATA IMPORT FAIL" << endl;
  }



  //EXPORT READ DATA AS CSV
  cout << "PLEASE CHOOSE EXPORT FILE" << endl;
  cin >> file_addr;
  if(fileio.data_export(file_addr,dataObj,csv)){
    cout << "DATA EXPORT SUCCESS" << endl;
  }
  else{
    cout << "DATA EXPORT FAIL" << endl;
  }


  cout<<"PROGRAM EXECUTED SUCCESSFULLY TYPE Q to QUIT" << endl;
  while (cin.get() != 'Q'){
  };
  cout<<"TERMINATE"<< endl;
  return 1;
}
