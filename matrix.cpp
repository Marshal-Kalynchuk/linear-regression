#include "matrix.h"

Matrix::Matrix(vector<vector<double>> dataset, vector<string> header){
  headerM = header;
  // Set rowsM and columnsM
  rowsM = dataset.size();
  colsM = dataset[0].size();
  // initialize the matrix off a 2d vector of doubles
  vector<double> row;
  for (int i = 0; i < rowsM; i++){
    row.clear();
    for (int j = 0; j < colsM; j++){
      row.push_back(dataset[i][j]);
    }
    matrixM.push_back(row);
  }
  // Init helper attrubute vectors:
  sumM = vector<double>(colsM, 0);
  meanM = vector<double>(colsM, 0);
  medianM = vector<double>(colsM, 0);
  first_quartileM = vector<double>(colsM, 0);
  third_quartileM = vector<double>(colsM, 0);
  stddevM = vector<double>(colsM, 0);
  sum_squaredM = vector<double>(colsM, 0);
  mean_squaredM = vector<double>(colsM, 0);
  sum_productM = vector<double>(colsM, 0);
  varianceM = vector<double>(colsM, 0);
}

double Matrix::get_sum_column(int col) const{
  assert(col >= 0 && col < colsM);
  return sumM[col];
}

double Matrix::get_mean_column(int col) const{
  assert(col >= 0 && col < colsM);
  return meanM[col];
}

double Matrix::get_mean_squared_column(int col) const{
  assert(col >= 0 && col < colsM);
  return mean_squaredM[col];
}

double Matrix::get_median_column(int col) const{
  assert(col >= 0 && col < colsM);
  return medianM[col];
}

double Matrix::get_std_column(int col) const{
  assert(col >= 0 && col < colsM);
  return stddevM[col];
}

double Matrix::get_sum_squared_column(int col) const{
  assert(col >= 0 && col < colsM);
  return sum_squaredM[col];
}

double Matrix::get_sum_product_column(int col) const{
  assert(col >= 0 && col < colsM);
  return sum_productM[col];
}

vector<double> Matrix::drop_row(int row_id){
  vector<double> row = matrixM[row_id];
  matrixM.erase(matrixM.begin() + row_id);
  return row;
}

vector<double> Matrix::drop_column(int col){

}

Matrix Matrix::drop_outliers(){
  
}

void Matrix::set_regression_model(int dependent_column){
  dependent_columnM = dependent_column;
  set_sum_product_column();
  regression_coefficientsM = vector<double>(colsM-1, 0);
  regression_interceptM = meanM[dependent_column];
  for (int i = 0, j = 0; i < colsM; i++){
    if (i == dependent_columnM) continue;
    else {
      regression_coefficientsM[j] = (
        (sum_productM[i] - rowsM * meanM[i] * meanM[dependent_columnM]) 
        / 
        (sum_squaredM[i] - rowsM * meanM[i]));
        regression_interceptM -= regression_coefficientsM[j] * meanM[i];
      j++;
    }
  }
}

void Matrix::set_sum_column(){
  for(int i = 0; i < colsM; i++){
    sumM[i] = 0;
    for (int j = 0; j < rowsM; j++)
      sumM[i] += matrixM[j][i];
  }
}

void Matrix::set_mean_column(){
  for(int i = 0; i < colsM; i++)
    meanM[i] = sumM[i] / rowsM;
}

void Matrix::set_mean_squared_column(){
  for(int i = 0; i < colsM; i++)
    mean_squaredM[i] = meanM[i] * meanM[i];
}

void Matrix::set_quartiles(){
  double column[rowsM];
  for(int i = 0; i < colsM; i++){
    for (int j = 0; j < rowsM; j++){
      column[j] = matrixM[j][i];
    }
    sort(column, column + rowsM);
    medianM[i] = 0;
    if (rowsM % 2 == 1)
      medianM[i] = column[rowsM / 2];
    else
      medianM[i] = (column[rowsM / 2] + column[(rowsM / 2) - 1]) / 2.0;
    first_quartileM[i] = column[rowsM / 4];
    third_quartileM[i] = column[3 * rowsM / 4];
  }
}

void Matrix::set_variance_column(){
  for (int i = 0; i < colsM; i++){
    varianceM[i] = (sum_squaredM[i] - rowsM * mean_squaredM[i]) / (rowsM - 1);
  }
}

void Matrix::set_std_column(){
  for (int i = 0; i < colsM; i++){
    stddevM[i] = sqrt(varianceM[i]);
  }
}

void Matrix::set_sum_squared_column(){
  for(int i = 0; i < colsM; i++){
  sum_squaredM[i] = 0;
  for (int j = 0; j < rowsM; j++)
    sum_squaredM[i] += matrixM[j][i] * matrixM[j][i];
  }
}

void Matrix::set_sum_product_column(){
  for (int i = 0; i < colsM; i++){
    sum_productM[i] = 0;
    for (int j = 0; j < rowsM; j++)
    sum_productM[i] += matrixM[j][dependent_columnM] * matrixM[j][i];
  }
}

void Matrix::set_statistics(){
  set_sum_column();
  set_sum_squared_column();
  set_mean_column();
  set_mean_squared_column();
  set_quartiles();
  set_variance_column();
  set_std_column();
}

double Matrix::predict(vector<double> parameters)const{
  double result = regression_interceptM;
  for (int i = 0; i < regression_coefficientsM.size(); i++)
    result += regression_coefficientsM[i] * parameters[i];
  return result;
}

template<typename T> void printElement(T t, const int& width){
  cout << left << setw(width) << setfill(' ') << t;
}
void Matrix::print_summary_stats(){
  std::cout << std::fixed;
  std::cout << std::setprecision(3);

  const int nameWidth     = 25;
  const int numWidth      = 25;

  std::cout << "Sample statistics:" << endl;
  printElement("Header:", nameWidth);
  for(int i = 0; i < headerM.size(); i++)
    printElement(headerM[i], nameWidth);

  printElement("\nSum:", nameWidth);
  for (double num: sumM)
    printElement(num, numWidth);

  printElement("\nSum of Squares:", nameWidth);
  for (double num: sum_squaredM)
    printElement(num, numWidth);

  printElement("\nMean:", nameWidth);
  for (double num: meanM)
    printElement(num, numWidth);
  
  printElement("\nMean Squared:", nameWidth);
  for (double num: mean_squaredM)
    printElement(num, numWidth);

  printElement("\nMedian:", nameWidth);
  for (double num: medianM)
    printElement(num, numWidth);

  printElement("\nVarience:", nameWidth);
  for (double num: varianceM)
    printElement(num, numWidth);

  printElement("\nStandard Deviation:", nameWidth);
  for (double num: stddevM)
    printElement(num, numWidth);
  
  std::cout << "\n\nRegression model:" << endl;
  printElement("Parameters:", nameWidth);
  for (int i = 0; i < colsM; i++){
    if (i == dependent_columnM) continue;
    else printElement(headerM[i], numWidth);
  }
  printElement("\nCoefficients:", nameWidth);
  for (double num: regression_coefficientsM)
    printElement(num, numWidth);
  printElement("\nIntercept:", nameWidth);
  printElement(regression_interceptM, numWidth);
  std::cout << endl;
}

