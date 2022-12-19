
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
  Matrix df(dataset, header);
  df.set_statistics();
  df.set_regression_model(0);
  df.print_summary_stats();

  double res = df.predict(test_values);
  cout << "Predicted: " << res << "\tActual: 4.6" << endl;

  Matrix outliers = df.drop_outliers();

  cout << "\n\n================================================================\n\n";
  outliers.set_statistics();
  outliers.set_regression_model(0);
  outliers.print_summary_stats();
  cout << "\n\n================================================================\n\n";

  df.set_statistics();
  df.set_regression_model(0);
  df.print_summary_stats();

  res = df.predict(test_values);
  cout << "Predicted: " << res << "\tActual: 4.6" << endl;

  #if 0
  // Split into train and test:
  matrix train;
  matrix test;

  random_shuffle(dataset.begin(), dataset.end());

  for (int i = 0; i < dataset.size(); i++){
    if ((float) rand()/RAND_MAX > 0.67)
      test.push_back(dataset[i]);
    else 
      train.push_back(dataset[i]);
  }

  #endif

  return 0;
}

