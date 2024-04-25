#pragma once



#include <vector>
#include <string>
using namespace std;



class dataTable{
  private:
    int _cols_num;
    int _rows_num;

    vector<vector<string>> _table; 

  public:
    dataTable();
    
    int get_row_num();
    int get_col_num();


    void insertData(string d, int row_num , int _columns_num);
    void clearData(int row_num , int col_num);

    string getData(int row_num , int _columns_num);

    void popRow();
    void popColumn();
    int row_num_Refresh();
    int col_num_Refresh();
    
};

