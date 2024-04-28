#pragma once



#include <vector>
#include <string>
using namespace std;



/*
  DYNAMIC DATA HOLDER THAT KEEPS DATA IN RECTANGULAR 2D arrays for now
*/


class dataTable{
  private:
    int _cols_num;
    int _rows_num;
    vector<vector<double>> _table; 





  public:

    dataTable(); 
    int get_row_num();
    int get_col_num();

    void insertData(double d, int row , int col);
    double getData(int row , int col);

    void eraseRow(int start_row, int rows_num = 1);
    void eraseColumn(int start_col, int cols_num = 1);

    void refresh();
};

