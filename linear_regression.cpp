
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

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
        cout << "|" << word << "|" << endl;
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

  vector<vector<double>> matrix;
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
    matrix.push_back(row);
  }

  // Print data
  for(int i = 0; i < header.size(); i++)
    cout << header[i] << '\t';
  cout << '\n';
  for(int i = 0; i < matrix.size(); i++){
    for(int j = 0; j < matrix[i].size(); j++){
      cout<<matrix[i][j]<<"\t\t";
    }
    cout<<"\n";
  }
  
  return 0;
}