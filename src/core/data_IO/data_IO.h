#pragma once

#include "dataTable.h"
#include <fstream>
#include <string>


enum dataType{
  csv,
  pdf,
  // and any file file formats you can think of that have function assosiated and can handle
};


/**
  @brief a function that imports files with supported file formats
  @param file_address as a string containing the path to the file and the file name
  @param data modifies the dataTable instance to hold the data from the file
  @param type file extension
  @return true if operation is successfull false if anything else happens
*/
bool data_import(string file_address,  dataTable *data,  int type);
bool data_export(string file_address, dataTable data, int type);

/**
  @brief csv File I/O functions 
*/
bool csv_import(string file_address, dataTable *table);
bool csv_export(string file_address, dataTable table);

/**
  @brief pdf File I/O functions 
*/
bool pdf_import(string file_address, dataTable *table);
bool pdf_export(string file_address, dataTable table);