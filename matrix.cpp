#include "matrix.h"

Matrix::Matrix(vector<vector<double>> dataset, vector<string> header){
  headerM = header;
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
  // Init helper attrubute vectors:
  sum_columnsM = vector<double>(columnsM, 0);
  mean_columnsM = vector<double>(columnsM, 0);
  median_columnsM = vector<double>(columnsM, 0);
  std_columnsM = vector<double>(columnsM, 0);
  sum_squared_columnsM = vector<double>(columnsM, 0);
  mean_squared_columnsM = vector<double>(columnsM, 0);
  sum_product_columnsM = vector<double>(columnsM, 0);
  variance_columnsM = vector<double>(columnsM, 0);

  set_sum_column();
  set_sum_squared_column();
  set_mean_column();
  set_mean_squared_column();
  set_median_column();
  set_variance_column();
  set_std_column();
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

void Matrix::set_sum_column(){
  for(int i = 0; i < columnsM; i++){
    sum_columnsM[i] = 0;
    for (int j = 0; j < rowsM; j++)
      sum_columnsM[i] += matrixM[j][i];
  }
}

void Matrix::set_mean_column(){
  for(int i = 0; i < columnsM; i++)
    mean_columnsM[i] = sum_columnsM[i] / rowsM;
}

void Matrix::set_mean_squared_column(){
  for(int i = 0; i < columnsM; i++)
    mean_squared_columnsM[i] = mean_columnsM[i] * mean_columnsM[i];
}

void Matrix::set_median_column(){
  double column[rowsM];
  for(int i = 0; i < columnsM; i++){
    for (int j = 0; j < rowsM; j++){
      column[j] = matrixM[j][i];
    }
    quicksort(column, 0, rowsM-1);
    median_columnsM[i] = 0;
    if (rowsM % 2 == 0)
      median_columnsM[i] = (column[rowsM / 2] + column[(rowsM / 2) + 1]) / 2;
    else
      median_columnsM[i] = column[rowsM / 2];
  }
}

void Matrix::set_variance_column(){
  for (int i = 0; i < columnsM; i++){
    variance_columnsM[i] = (sum_squared_columnsM[i] - rowsM * mean_squared_columnsM[i]) / (rowsM - 1);
  }
}

void Matrix::set_std_column(){
  for (int i = 0; i < columnsM; i++){
    std_columnsM[i] = sqrt(variance_columnsM[i]);
  }
}

void Matrix::set_sum_squared_column(){
  for(int i = 0; i < columnsM; i++){
  sum_squared_columnsM[i] = 0;
  for (int j = 0; j < rowsM; j++)
    sum_squared_columnsM[i] += matrixM[j][i] * matrixM[j][i];
  }
}

void Matrix::set_sum_product_column(){

}

template<typename T> void printElement(T t, const int& width){
  cout << left << setw(width) << setfill(' ') << t;
}
void Matrix::print_summary_stats(){
  std::cout << std::fixed;
  std::cout << std::setprecision(3);

  const int nameWidth     = 25;
  const int numWidth      = 25;

  cout << "Sample statistics:" << endl;
  printElement("Header:", nameWidth);
  for(int i = 0; i < headerM.size(); i++)
    printElement(headerM[i], nameWidth);

  printElement("\nSum:", nameWidth);
  for (double num: sum_columnsM)
    printElement(num, numWidth);

  printElement("\nSum of Squares:", nameWidth);
  for (double num: sum_squared_columnsM)
    printElement(num, numWidth);

  printElement("\nMean:", nameWidth);
  for (double num: mean_columnsM)
    printElement(num, numWidth);
  
  printElement("\nMean Squared:", nameWidth);
  for (double num: mean_squared_columnsM)
    printElement(num, numWidth);

  printElement("\nMedian:", nameWidth);
  for (double num: median_columnsM)
    printElement(num, numWidth);

  printElement("\nVarience:", nameWidth);
  for (double num: variance_columnsM)
    printElement(num, numWidth);

  printElement("\nStandard Deviation:", nameWidth);
  for (double num: std_columnsM)
    printElement(num, numWidth);
  cout << '\n' << endl;
}

void Matrix::quicksort(double array[], int first, int last){
    if (first < last){
        int splitpoint = partition(array, first, last);

        quicksort(array, first, splitpoint-1);
        quicksort(array, splitpoint+1, last);
    }
};

int Matrix::partition(double array[], int first, int last){
    const double pivotvalue = array[first];
    int left = first + 1;
    int right = last;
    while(true){
        while (left <= right && array[left] <= pivotvalue){
            left++;
        }
        while (right >= left && array[right] >= pivotvalue){
            right--;
        }
        if (right < left){
            break;
        }
        else{
            const double temp = array[left];
            array[left] = array[right];
            array[right] = temp;
        }
    }
    const double temp = array[first];
    array[first] = array[right];
    array[right] = temp;
    return right;
};