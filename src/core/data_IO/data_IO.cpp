#include "data_IO.h"
#include <sstream>




bool csv_import(string file_address, dataTable *table){
  ifstream file;
  string cell;
  char c;
  int row_index = 0;
  int col_index = 0;

  file.open(file_address);
  if(file.is_open()){

    //operations to fill the dataTable object from the file

      while(file.get(c)){
        switch (c)
        {
        case '\n':
          table->insertData(cell,  row_index, col_index);
          row_index++;
          cell = "";
          break;
        case ',':
          table->insertData(cell,  row_index, col_index);
          col_index++;
          cell = "";
          break;        
        default:
          cell.push_back(c);
          break;
        }
        
      }

    file.close();
    return true;
  }
  else{
    return false;
  }
}


bool pdf_import(string file_address, dataTable *table){
  return false;
};



bool csv_export(string file_address, dataTable table){
  return false;
};


bool pdf_export(string file_address, dataTable table){
  return false; 
}





bool data_import(string file_address,  dataTable *data,  int type){
  switch (type)
  {
  case csv:
    return csv_import(file_address, data);
    break;
  case pdf:
    return pdf_import(file_address, data);
    break;
  default:
    return false;
    break;
  }
}

bool data_export(string file_address, dataTable data, int type){
  switch (type)
  {
  case csv:
    return csv_export(file_address, data);
    break;
  case pdf:
    return pdf_export(file_address, data);
  default:
    return false;
    break;
  }
}