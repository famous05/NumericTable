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

    /**
     * Default constructor
     */
    NumericTable();


    /**
     * Constructor
     *
     *  Parameters:
     *      int n_cols:     number of columns to create in table
     */
    NumericTable(int n_cols);


    /**
     * Copy constructor.to create a new table using an existing table
     * 
     * Parameters:
     *      const NumericTable& nt:     existing table 
     */
    NumericTable(const NumericTable& nt);


    /**
     * Assignment operator
     *
     * Parameters:
            const NumericTable& nt:     table assigned to calling object
     */
    NumericTable& operator = (const NumericTable& nt);


    /**
     * Default destructor
     */
    virtual ~NumericTable();


    /**
     * Returns: int
     *      Number of records in the table
     */
    int getNumRows() const;


    /**
     * Returns: int
     *      Number of columns in the table
     */
    int getNumCols() const;


    /**
     * Sets number of columns
     *
     * Parameters:
     *      int n_cols:     number of columns in table
     *  
     * NOTE: This function will reshape an existing table if set to a different
     *       number of columns from what it was before. There is also a risk of
     *       losing data.
     */  
    void setNumCols(int n_cols);


    /**
     * Sets number of rows
     *
     * Parameters:
     *      int n_rows:     number of rows in table
     *  
     * NOTE: This function will hide data beyond n_rows if any. It does not 
     *       delete the data.
     */     
     void setNumRows(int n_rows);


    /**
     * Returns true if file contains NaN
     */
    bool hasNaN() const;

    /**
     * Returns true if file contains Inf
     */
    bool hasInf() const;


    /** 
     * Appends data to table. Appends by row, then each column
     *
     * Parameters:
     *      double data:    data to append to table
     */
    void appendData(double data);


    /**
     * Returns the data stored at row 'row' and column 'col'
     *
     * Parameters:
     *      int row:    row index of data to return
     *      int col:    column index of data to return
     */
    double getDataAt(int row, int col);


    /**
     * Sets the value at row 'row' and column 'col'
     *
     * Parameters:
     *      double data:    data to set
     *      int row:        row index to store data
     *      int col:        column index to store data
     */
    void setDataAt(double data, int row, int col);


    /**
     * Scales data in table
     *
     * Parameters:
     *      double sf:      scale factor for data in table
     */
    void scale(double sf);


    /**
     * Prints the table to screen, with option to set column width
     * 
     * Parameters:
     *      int col_width:  column width of print to screen (optional)
     */ 
    void print(int col_width = 20);


	/**
     * Clears all data from the table
     */
    void clear();



    // *********************** Reader functions ********************************

	/**
     * Reads tab or space separated files
     *
     * Parameters:
     *      std::string file_name:      name of file to read
     */
    void readTSV(std::string file_name);


	/**
     * Reads comma separated file
     *
     * Parameters:
     *      std::string file_name:      name of file to read
     */
     void readCSV(std::string file_name);


	/**
     * Reads a file separted by user specified separator
     *
     * Parameters:
     *      std::string file_name:      name of file to read
     *      std::string sep:            user specified separator
     */    void read(std::string file_name, std::string sep);

    // ************************ End of reader functions ************************



    // *************************** Writer functions ****************************

    /**
     * Writes the content of the table to file
     *
     * Parameters:
     *      std::string file_name:      name of output file
     *      std::string sep:            file separator string
     *      int col_width:              width of columns in output file
     *
     * NOTE: Does not allow writing space or table separated file. Use the 
     *       writeTSV function for that purpose
     */
    void write(std::string file_name, std::string sep, int col_width = 20);


    
    /**
     * Writes to tab or space separated file
     *
     * Parameters:
     *      std::string file_name:      name of output file
     *      int col_width:              width of columns in output file (optional)
     */
    void writeToTSV(std::string file_name, int col_width = 20);


    /**
     * Writes to comma separated file
     *
     * Parameters:
     *      std::string file_name:      name of output file
     *      int col_width:              width of columns in output file (optional)
     */    
     void writeToCSV(std::string file_name, int col_width = 20);

    // *************************************************************************


	private:

    /**
     * Splits input string
     *
     * Parameters:
     *      std::string string_to_split:      input string to split
     *      std::string split_string:         character to split by
     *
     * Returns: std::vector<std::string>
     *      A vector of strings
     *
     * NOTE: Cannot split using space or tab
     */ 
	static std::vector<std::string> splitString(std::string string_to_split,
												std::string split_string);


    /**
     * Splits input string
     *
     * Parameters:
     *      std::string string_to_split:      input string to split
     *      std::string split_string:         character to split by
     *
     * Returns: std::vector<double>
     *      A vector of doubles
     *
     * NOTE: Cannot split using space or tab
     */ 
	static std::vector<double> splitStringReturnDouble(std::string string_to_split,
												std::string split_string);



    private:
		TableData* table_data = nullptr;
		int num_rows;
		int num_cols;
		bool data_has_inf;
		bool data_has_nan;
};

#endif
