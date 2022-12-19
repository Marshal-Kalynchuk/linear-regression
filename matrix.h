
#ifndef matrix
#define matrix
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <math.h>
#include <string.h>
#include <algorithm>

using namespace std;

class Matrix
{
public:
  Matrix(vector<vector<double>> dataset, vector<string> header);

  //~Matrix();
  // PROMISES: Delete the matrix

  int get_rows() const { return rowsM; }
  int get_cols() const { return colsM; }

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

  vector<double> drop_row(int row_id);
  // REQUIRES: Row index.
  // PROMISES: Drops a row in matrix and returns the dropped row.

  vector<double> drop_column(int column_id);
  // REQUIRES: Column index.
  // PROMISES: Drops a column in matrix and returns the dropped column.

  Matrix drop_outliers();
  // REQUIRES: set_statistics
  // PROMISES: Returns a matrix of the dropped rows.

  void set_sum_column();
  void set_mean_column();
  void set_mean_squared_column();
  void set_quartiles();
  void set_std_column();
  void set_sum_squared_column();
  void set_sum_product_column();
  void set_variance_column();

  void set_regression_model(int dependent_column);
  void set_statistics();

  void print_summary_stats();

  void print_matrix(int rows);

private:
  vector<vector<double>> matrixM;
  int rowsM;
  int colsM;

  const int nameWidth     = 25;
  const int numWidth      = 25;

  vector<string> headerM;
  vector<double> sumM;
  vector<double> meanM;

  vector<double> medianM;
  vector<double> first_quartileM;
  vector<double> third_quartileM;

  vector<double> stddevM;
  vector<double> sum_squaredM;
  vector<double> mean_squaredM;
  vector<double> sum_productM;
  vector<double> varianceM;

  int dependent_columnM;
  vector<double> regression_coefficientsM;
  double regression_interceptM;
};

#endif