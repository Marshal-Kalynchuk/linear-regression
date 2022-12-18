#include <matrix.h>

Matrix::Matrix(vector<vector<double>> dataset){
  // Set rowsM and columnsM
  rowsM = dataset.size();
  columnsM = dataset[0].size();
  // initialize the matrix off a 2d vector of doubles
  vector<double> row;
  for (int i = 0; i < rowsM; i++){
    row.clear();
    for (int j = 0; j < columnsM; j++){
      row.push_back(dataset[i][j]);
    }
    matrixM.push_back(row);
  }
}

double Matrix::get_sum_column(int column_id) const{
  assert(column_id >= 0 && column_id < columnsM);
  return sum_columnsM[column_id];
}

double Matrix::get_mean_column(int column_id) const{
  assert(column_id >= 0 && column_id < columnsM);
  return mean_columnsM[column_id];
}

double Matrix::get_mean_squared_column(int column_id) const{
  assert(column_id >= 0 && column_id < columnsM);
  return mean_squared_columnsM[column_id];
}

double Matrix::get_median_column(int column_id) const{
  assert(column_id >= 0 && column_id < columnsM);
  return median_columnsM[column_id];
}

double Matrix::get_std_column(int column_id) const{
  assert(column_id >= 0 && column_id < columnsM);
  return std_columnsM[column_id];
}

double Matrix::get_sum_squared_column(int column_id) const{
  assert(column_id >= 0 && column_id < columnsM);
  return sum_squared_columnsM[column_id];
}

double Matrix::get_sum_product_column(int column_id) const{
  assert(column_id >= 0 && column_id < columnsM);
  return sum_product_columnsM[column_id];
}

Matrix Matrix::drop_row(int row_id) const{

}

Matrix Matrix::drop_column(int column_id) const{

}
