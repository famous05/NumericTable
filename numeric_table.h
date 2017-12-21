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
#include "math.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include "stdlib.h"

typedef std::vector<double>  TableData;

class NumericTable
{

    public:

    // Default constructor
    NumericTable();

    // Constructor
    NumericTable(int numOfColumns);

    // Copy constructor
    NumericTable(const NumericTable& NT);


    // Destructor
    ~NumericTable();

    // Returns number of records in the table
    int getNumRows();


    // Returns number of columns in the table
    int getNumCols();


    // Sets number of columns
    void setNumCols(int n_cols);


    // Sets number of rows. Use with caution
    void setNumRows(int n_rows);


    // Returns true if file contains NaN
    bool hasNaN();

    // Returns true if file contains Inf
    bool hasInf();


    // Appends data to table
    void appendData(double data);


    // Returns the data stored at row 'row' and column 'col'
    double getDataAt(int row, int col);


    // Sets the value at row 'row_index' and column 'col_index'
    void setDataAt(double data, int row_index, int col_index);


    // Scales data in table by scale_factor
    void scale(double scale_factor);


    // Prints the table to screen
    void print();


	// Clears data from the table
    void clear();



    // *********************** Reader functions ****************************************************

	// Reads ANSYS BladeGen profile.curve file format
    void readCurveFile(std::string file_name);


	// Reads tab or space separated file
    void readTSVFile(std::string file_name);


    // Reads comma separated file
    void readCSVFile(std::string file_name);

    // Reads file separated by 'sep'
    void readFile(std::string file_name, std::string sep);

    // ************************ End of reader functions ********************************************



    // *************************** Writer functions ************************************************
    // Writes to 'sep' seperated format, with option to specify column with.
    // Does not allow writing to space or tab separated file. Use the writeToTSVFile function
    // to write to space/tab separated.
    void writeToFile(std::string file_name, std::string sep, double col_width = 20);


    // Writes to tab or space separated file, with option to set column width
    void writeToTSVFile(std::string file_name, double col_width = 20);


    // Writes to comma separated file, with option to set column width
    void writeToCSVFile(std::string file_name, double col_width = 20);


    // Writes to tecplot (.tec) file format
    void writeToTecplot(std::string file_name);
    // *********************************************************************************************


	private:
    	// Splits inout string into vector of string base on 'split_string'.
    	// Returns a vector of strings. Cannot split string using space/tab
		static std::vector<std::string> splitString(std::string string_to_split,
													std::string split_string);


		// Splits inout string into vector of string base on 'split_string'.
		// Returns a vector of double. Cannot split string using space/tab
		static std::vector<double> splitStringReturnDouble(std::string string_to_split,
													std::string split_string);



    private:
		TABLEDATA table_data;
		int num_rows;
		int num_cols;
		bool has_inf;
		bool has_nan;
};

#endif
