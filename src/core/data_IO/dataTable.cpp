#include "dataTable.h"

dataTable::dataTable(){
  _rows_num = 0;
  _cols_num = 0; 
}

int dataTable::get_row_num(){
  return _rows_num;
}


int dataTable::get_col_num(){
  return _cols_num;
}


void dataTable::insertData(string d,  int row_num , int col_num){
  if(row_num > _rows_num){
    _rows_num = row_num;
  }
  if(col_num > _cols_num){
    _cols_num = col_num;
  }


  _table[row_num][col_num] = string(d);

}

void dataTable::clearData(int row_num, int col_num){
  _table[row_num][col_num] = "";
}

string dataTable::getData(int row_num, int col_num){
  return _table[row_num][col_num];
}

void dataTable::popRow(){
  _table.pop_back();
  _rows_num--;
} 

void dataTable::popColumn(){
  for(int i = 0; i < _table.size(); i++){
    _table[i].pop_back();
  }
} 

int dataTable::row_num_Refresh(){
  return _table.size();
}


int dataTable::col_num_Refresh(){
   return _table[0].size();
}