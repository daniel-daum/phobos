#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

void read_csv(std::string file_path, int num_rows,
              std::vector<std::string> column_names) {
  std::ifstream file(file_path);
  std::string line;
  std::map<std::string, int> header_map;

  // Read header line first
  if (getline(file, line)) {

    std::stringstream ss(line);
    std::string header;
    int index = 0;

    while (getline(ss, header, ',')) {
      // Remove quotes if they exist
      if (header.front() == '"' && header.back() == '"') {
        header = header.substr(1, header.length() - 2);
      }
      header_map[header] = index++;
    }

    // Read data rows
    int rows_read = 0;
    while (file.good() && rows_read < num_rows) {
      getline(file, line);

      // Split line into cells
      std::stringstream ss(line);
      std::string cell;
      std::vector<std::string> row;

      while (getline(ss, cell, ',')) {
        // Remove quotes if they exist
        //
        // 
        if (cell.front() == '"' && cell.back() == '"') {

          cell = cell.substr(1, cell.length() - 2);
        }
        row.push_back(cell);
      }

      // Display only selected columns
      // 
      for (const std::string &col_name : column_names) {
          
        if (header_map.find(col_name) != header_map.end()) {
            
          int col_index = header_map[col_name];
          
          if (col_index < row.size()) {
            std::cout << row[col_index] << " | ";
          }
        }
      }

      std::cout << std::endl;

      rows_read++;
    }

    file.close();
  }
}

int main() {
  // Provide a list of columns to displayed
  std::vector<std::string> columns = {"city", "state_name", "population", "income_household_median", "income_household_six_figure"};
  
  // provide filepath, number of rows to be displayed, and the columns to be displayed by their name
  read_csv("./uscities.csv", 10, columns);

  return 0;
}
