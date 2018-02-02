/*
	NumericTable: Reads and writes numeric data in column format

    Copyright (C) 2017 - 2018  Osarobo Famous Okhuahesogie
	E-Mail: famous.osarobo@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef NUMERICTABLE_H
#define NUMERICTABLE_H

//C++
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cctype>

#include "stdlib.h"
#include "math.h"

typedef std::vector<double>  TableData;

class NumericTable
{

    public:

    // Default constructor
    NumericTable();

    // Constructor
    NumericTable(int n_cols);

    // Copy constructor
    NumericTable(const NumericTable& NT);

    // Assignment operator
    NumericTable& operator = (const NumericTable& nt);


    // Destructor
    virtual ~NumericTable();

    // Returns number of records in the table
    int get_num_rows() const;


    // Returns number of columns in the table
    int get_num_cols() const;


    // Sets number of columns
    void set_num_cols(int n_cols);


    // Sets number of rows. Use with caution
    void set_num_rows(int n_rows);


    // Returns true if file contains NaN
    bool has_nan() const;

    // Returns true if file contains Inf
    bool has_inf() const;


    // Appends data to table
    void append_data(double data);


    // Returns the data stored at row 'row' and column 'col'
    double get_data_at(int row, int col);


    // Sets the value at row 'row' and column 'col'
    void set_data_at(double data, int row, int col);


    // Scales data in table by scale_factor
    void scale(double scale_factor);


    // Prints the table to screen, with option to set column width
    void print(int col_width = 20);


	// Clears data from the table
    void clear();



    // *********************** Reader functions ********************************

	// Reads ANSYS BladeGen profile.curve file format
    void read_ansys_curve(std::string file_name);


	// Reads tab or space separated file
    void read_tsv(std::string file_name);


    // Reads comma separated file
    void read_csv(std::string file_name);

    // Reads file separated by 'sep'
    void read(std::string file_name, std::string sep);

    // ************************ End of reader functions ************************



    // *************************** Writer functions ****************************
    // Writes to 'sep' seperated format, with option to specify column with.
    // Does not allow writing to space or tab separated file.
    // Use the write_tsv function to write to space/tab separated.
    void write(std::string file_name, std::string sep, int col_width = 20);


    // Writes to tab or space separated file, with option to set column width
    void write_tsv(std::string file_name, int col_width = 20);


    // Writes to comma separated file, with option to set column width
    void write_csv(std::string file_name, int col_width = 20);


    // Writes to tecplot (.tec) file format, with option to set column width
    void write_tecplot(std::string file_name, int col_width = 20);
    // *************************************************************************


	private:
	// Splits inout string into vector of string base on 'split_string'.
	// Returns a vector of strings. Cannot split string using space/tab
	static std::vector<std::string> split_string(std::string string_to_split,
												std::string split_string);


	// Splits inout string into vector of string base on 'split_string'.
	// Returns a vector of double. Cannot split string using space/tab
	static std::vector<double> split_string_return_double(std::string string_to_split,
												std::string split_string);



    private:
		TableData* table_data = nullptr;
		int num_rows;
		int num_cols;
		bool data_has_inf;
		bool data_has_nan;
};

#endif
