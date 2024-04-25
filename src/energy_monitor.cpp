#include "energy_monitor.h"
#include <iostream>
#include "core/core.h"
using namespace std;


int main(){
  string file_addr;
  dataTable dataObj = dataTable();
  cout << "PLEASE CHOOSE A FILE" << endl;
  cin >> file_addr;

  if(data_import(file_addr, &dataObj, csv)){
    cout << "SUCCESSSSS";
  }
  else{
    cout << "FAIL";
  }


  cout<<"FUCK YOU , I WIN";
  return 1;
}