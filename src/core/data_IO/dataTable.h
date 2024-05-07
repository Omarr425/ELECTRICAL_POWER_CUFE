#pragma once



#include <vector>
#include <string>
using namespace std;



/*
  DYNAMIC DATA HOLDER THAT KEEPS DATA IN RECTANGULAR 2D arrays for now
*/


class dataTable{
  private:
    unsigned int _cols_num = 0;
    unsigned int _rows_num = 0;
    vector<vector<double>> _table; 
  public:

    dataTable(); 
    unsigned int get_row_num();
    unsigned int get_col_num();

    void insertData(double d, unsigned int row , unsigned int col);
    double getData(int row , int col)const;

    void eraseRow(int start_row, int rows_num = 1);
    void eraseColumn(int start_col, int cols_num = 1);
    void refresh();
    bool extractRow(unsigned int rowNumber, std::vector<double>* returnArray);
    bool extractColumn(unsigned int columnNumber, std::vector<double>* returnArray);
    bool insertRow(unsigned int rowNumber, std::vector<double> *putArray);
    bool insertColumn(unsigned int columnNumber, std::vector<double>* putArray);
};
