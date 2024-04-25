#include "energy_monitor.h"
#include <iostream>


using namespace std;


int main(){
  string file_addr;
  dataTable dataObj = dataTable();
  cout << "PLEASE CHOOSE A FILE" << endl;
  cin >> file_addr;
  cout << "sad" << endl;
  if(data_import(file_addr, &dataObj, csv)){
    cout << "SUCCESSSSS" << endl;
  }
  else{
    cout << "FAIL" << endl;
  }
  
  cout<<"FUCK YOU , I WIN" << endl;
  return 1;
}