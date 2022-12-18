
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;
typedef vector<vector<double>> matrix;

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

  matrix dataset;
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

  // Split into train and test:
  matrix train;
  matrix test;

  for (int i = 0; i < dataset.size(); i++){
    if ((float) rand()/RAND_MAX > 0.66)
      test.push_back(dataset[i]);
    else 
      train.push_back(dataset[i]);
  }

  // Dependent variable sepal_length (first column)
  // Train regression model:
  int rows = train.size();
  int columns = train[0].size();

  double sum_xy[columns] = {0};
  double sum_x_squared[columns] = {0};
  double averages[columns] = {0};

  for (int i = 0; i < rows; i++){
    for (int j = 0; j < columns; j++){
      sum_xy[j] += train[i][0] * train[i][j];
      sum_x_squared[j] += train[i][j] * train[i][j];
      averages[j] += train[i][j];
    }
  }
  for (int i = 0; i < columns; i++){
    averages[i] = averages[i] / rows;
  }

  // Print data:
  cout << "Training dataset: " << endl;
  cout << "Rows: " << train.size() << endl;
  
  cout << "Stats:\n\t\t";
  for(int i = 0; i < header.size(); i++)
    cout << header[i] << '\t';
  cout << '\n';

  cout << "\nSum xy:\t\t";
  for (int i = 0; i < columns; i++)
    cout << sum_xy[i] << "\t\t";
    
  cout << "\nSum x squared:\t";
  for (int i = 0; i < columns; i++)
    cout << sum_x_squared[i] << "\t\t";

  cout << "\nAverage:\t";
  for (int i = 0; i < columns; i++)
    cout << averages[i] << "\t\t";

  cout << "\n\nTop 5: " << endl;
  for(int i = 0; i < header.size(); i++)
    cout << header[i] << '\t';
  cout << '\n';
  for(int i = 0; i < rows && i < 5; i++){
    for(int j = 0; j < columns; j++){

      cout<<train[i][j]<<"\t\t";
    }
    cout<<"\n";
  }

  cout << "\nTest dataset: " << endl;
  cout << "Rows: " << test.size() << endl;
  for(int i = 0; i < header.size(); i++)
    cout << header[i] << '\t';
  cout << '\n';
  for(int i = 0; i < test.size() && i < 5; i++){
    for(int j = 0; j < test[i].size(); j++){
      cout<<test[i][j]<<"\t\t";
    }
    cout<<"\n";
  }
  
  return 0;
}