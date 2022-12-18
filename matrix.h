
#ifndef matrix
#define matrix
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <math.h>
#include <string.h>

using namespace std;

class Matrix{
public:
  Matrix(vector<vector<double>> dataset, vector<string> header);

  //~Matrix();
  // PROMISES: Delete the matrix

  int get_rows() const { return rowsM; }
  int get_cols() const { return columnsM; }

  double get_sum_column(int column_id) const;
  // REQUIRES: Column index.
  // PROMISES: Returns the sum of a column.

  double get_mean_column(int column_id) const;
  // REQUIRES: Column index.
  // PROMISES: Returns the mean of a column.

  double get_mean_squared_column(int column_id) const;
  // REQUIRES: Column index.
  // PROMISES: Returns the mean squared of a column.

  double get_median_column(int column_id) const;
  // REQUIRES: Column index
  // PROMISES: Returns the median of a column.

  double get_std_column(int column_id) const;
  // REQUIRES: Column index.
  // PROMISES: Returns the standared deviations of a column.

  double get_sum_squared_column(int column_id) const;
  // REQUIRES: Column index.
  // PROMISES: Returns the sum of squares of a column.

  double get_sum_product_column(int column_id) const;
  // REQUIRES: Index of columns.
  // PROMISES: Returns the sum product of column and dependent column.

  double predict(vector<double> parameters) const;
  // REQUIRES: Parameters size == coefficients size, parameters order == coefficients order.
  // PROMISES: Returns the predicted value of the regression model.

  Matrix drop_row(int row_id) const;
  // REQUIRES: Row index.
  // PROMISES: Drops a row in matrix and returns the dropped row.

  Matrix drop_column(int column_id) const;
  // REQUIRES: Column index.
  // PROMISES: Drops a column in matrix and returns the dropped column.

  void set_sum_column();
  void set_mean_column();
  void set_mean_squared_column();
  void set_median_column();
  void set_std_column();
  void set_sum_squared_column();
  void set_sum_product_column();
  void set_variance_column();

  void set_regression_model(int dependent_column);
  void set_statistics();

  void print_summary_stats();

  void quicksort(double array[], int first, int last);
  int partition(double array[], int first, int last);

private:
  vector<vector<double>> matrixM;
  int rowsM;
  int columnsM;

  vector<string> headerM;
  vector<double> sum_columnsM;
  vector<double> mean_columnsM;
  vector<double> median_columnsM;
  vector<double> std_columnsM;
  vector<double> sum_squared_columnsM;
  vector<double> mean_squared_columnsM;
  vector<double> sum_product_columnsM;
  vector<double> variance_columnsM;

  int dependent_columnM;
  vector<double> regression_coefficientsM;
  double regression_interceptM;
};

#endif