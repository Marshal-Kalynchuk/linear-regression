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