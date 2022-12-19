
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <random>
#include <iomanip>

#include "matrix.h"

using namespace std;
double predict(vector<double> coefficients, double intercept, vector<double> values, int n);

int main(){

  vector<vector<string>> string_data;

  string filename = "./IRIS.csv";

  fstream file(filename, ios::in);
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      vector<string> row;
      string word;
      stringstream str(line);
      while (getline(str, word, ',')) {
        row.push_back(word);
      }
      string_data.push_back(row);
    }
    file.close();
  } else {
    cout << "Error: Could not read file." << endl;
  }

  // Remove Header:
  vector<string> header = string_data[0];
  string_data.erase(string_data.begin());

  vector<vector<double>> dataset;
  vector<double> row;

  map<string, double> class_label_map = {
    {"Iris-setosa", 0.0},
    {"Iris-versicolor", 1.0},
    {"Iris-virginica", 2.0}
  };

  // Convert content to matrix:
  for (int i = 0; i < string_data.size(); i++){
    row.clear();
    // Convert string nums to doubles
    for (int j = 0; j < string_data[i].size() - 1; j++){
      try {
        row.push_back(stod(string_data[i][j]));
      } catch (const std::invalid_argument&) {
        cout << "Could not convert to double" << endl;
      }
    }

    // Convert classes to doubles
    row.push_back(class_label_map[string_data[i][4]]);

    // Add row to matrix
    dataset.push_back(row);
  }

  vector<double> test_values = {3.4,1.4,0.3,0};
  vector<vector<double>> train, test;
  double test_size = 0.2;

  mt19937 rng(random_device{}());
  uniform_real_distribution<double> dist(0, 1);

  for (vector<double> x : dataset) {
      if (dist(rng) < test_size) {
          test.push_back(x);
      } else {
          train.push_back(x);
      }
  }

  Matrix df(train, header);
  df.print_matrix(10);
  df.set_statistics();
  df.set_regression_model(0);
  df.print_summary_stats();

  double res = df.predict(test_values);
  cout << "Predicted: " << res << "\tActual: 4.6" << endl;

  Matrix outliers = df.drop_outliers();

  cout << "\n\n===========================================================================================================================================\n\n";
  cout << "Outliers: " << endl;
  outliers.print_matrix(10);
  cout << "\n\n===========================================================================================================================================\n\n";

  df.print_matrix(10);
  df.set_statistics();
  df.set_regression_model(0);
  df.print_summary_stats();

  double mean_square_error = 0;
  double mean_abs_per_error = 0;

  for (int i = 0; i < test.size(); i++) {
      test_values[0] = test[i][1];
      test_values[1] = test[i][2];
      test_values[2] = test[i][3];
      test_values[3] = test[i][4];
      res = df.predict(test_values);
      mean_abs_per_error += abs(test[i][0] - res) / test[i][0];
      mean_square_error += (res - test[i][0]) * (res - test[i][0]);
      cout << "Predicted: " << res << "\tActual: " << test[i][0] << endl;
  }
  mean_square_error /= test.size();
  mean_abs_per_error /= test.size();

  cout << "Mean Square Error: " << mean_square_error << endl;
  cout << "Mean Absolute Percentage Error: " << mean_abs_per_error << endl;

  return 0;
}


