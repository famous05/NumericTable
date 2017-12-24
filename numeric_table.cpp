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


//Developer
#include "numeric_table.h"


NumericTable::NumericTable()
{
	this->num_cols = 0;
	this->num_rows = 0;
	this->has_nan = false;
	this->has_inf = false;
}


NumericTable::NumericTable(int n_cols)
{
	this->num_cols = n_cols;
	this->has_nan = false;
	this->has_inf = false;
}

/*
NumericTable::NumericTable(const NumericTable& NT)
{
	this->num_rows = NT.getNumRows();
	this->num_cols = NT.getNumCols();
	this->table_data = NT.table_data;
	this->has_nan = false;
	this->has_inf = false;
}
*/

NumericTable::~NumericTable()
{
	this->table_data.clear();
}


int NumericTable::getNumRows()
{
	return this->num_rows;
}


int NumericTable::getNumCols()
{
	return this->num_cols;
}



void NumericTable::setNumCols(int num_cols)
{
	// first update number of records
	this->num_cols = num_cols;
	this->num_rows =
	(int)(((double)this->getNumRows() * (double)this->getNumCols())/(double)num_cols);
}


void NumericTable::setNumRows(int num_rows)
{
	// This function is useful only when using dynamic table to write data
	// when you know the number of records already
	this->num_rows = num_rows;
}


bool NumericTable::hasNaN()
{
	return this->has_nan;
}


bool NumericTable::hasInf()
{
	return this->has_inf;
}


void NumericTable::appendData(double data)
{
	this->table_data.push_back(data);
	this->num_rows = (int)((double)this->table_data.size()/(double)this->getNumCols());
}


double NumericTable::getDataAt(int row, int column)
{
	int data_index = (row * this->getNumCols()) + column;

	if((row > (this->getNumRows() - 1)) || (column > (this->getNumCols() - 1)))
	{
		std::cout << "Requested table index is out of range in ";
		std::cout << "NumericTable::getDataAt(int row, int column)" << std::endl;
		std::cout << "Exiting program....." << std::endl;
		exit(1);
	}
	else
	{
		return this->table_data.at(data_index);
	}
}


void NumericTable::setDataAt(double data, int row_index, int col_index)
{
	int data_index = (row_index * this->getNumCols()) + col_index;
	this->table_data.at(data_index) = data;
}


void NumericTable::scale(double scale_factor)
{
	int data_index;
	for(int row = 0; row < this->getNumRows(); row++)
	{
		for(int col = 0; col < this->getNumCols(); col++)
		{
			data_index = (row * this->getNumCols()) + col;
			this->table_data.at(data_index) = this->table_data.at(data_index) * scale_factor;
		}
	}
}


void NumericTable::print()
{
	for(int row = 0; row < this->getNumRows(); row++)
	{
		for(int col = 0; col < this->getNumCols(); col++)
		{
			if(col == this->getNumCols() - 1)
			{
				std::cout << std::setw(15) << std::left << this->getDataAt(row, col) << "  " << std::endl;

			}
			else
			{
				std::cout << std::setw(15) << std::left << this->getDataAt(row, col) << "  ";
			}
		}
	}
}


void NumericTable::clear()
{
	this->table_data.clear();
}


void NumericTable::readCurveFile(std::string file_name)
{

	int data_counter = 0;
	std::string line_data, i_str;
	bool has_comment, has_alpha_num;
	double i_data;
	std::vector<std::string> line_str;


	std::ifstream reader(file_name.c_str());

	if(!reader)
	{
		std::cout << "Error while opening file " << file_name.c_str();
		std::cout << " in NumericTable::readCurveFile(std::string file_name)" << std::endl;
		exit(0);
	}

	while(!reader.eof())
	{
		//read in line
		getline(reader,line_data);

		//ingore lines with command markers anywhere********************
		has_comment  = false;
		has_alpha_num = false;

		for(int i = 0; i < line_data.length(); i++)
		{
			if((line_data.at(i) == '#') || (line_data.at(i) == '!'))
			{
				has_comment = true;
			}

			//check if line has number or character
			//i.e. not empty
			if(isalnum(line_data.at(i)))
			{
				has_alpha_num = true;
			}
		}
		//**************************************************************


		if((has_comment == false) && (has_alpha_num == true))
		{
			for(int i = 0; i < line_data.length(); i++)
			{
				if(isalnum(line_data.at(i)) || (line_data.at(i) == '.') || (line_data.at(i) == '-'))
				{
					i_str.push_back(line_data.at(i));
				}

				if((i_str.size() != 0) && ((line_data.at(i) == ' ') || (i == line_data.length()-1)))
				{
					line_str.push_back(i_str);
					i_str.clear();
				}

			}
		}


		if((has_comment == false) && (has_alpha_num == true))
		{
			for(int i = 0; i < 3; i++) //read data in first 3 pos of string vector
			{
				i_data = atof(line_str.at(i).c_str());
				this->table_data.push_back(i_data);
				data_counter += 1;

				if(isnan(i_data))
				{
					this->has_nan = true;
				}

				if(isinf(i_data))
				{
					this->has_inf = true;
				}
			}
		}

		line_str.clear();
	}

	this->num_rows = (int)((double)data_counter/(double)this->num_cols);

	reader.close();
}


void NumericTable::readTSVFile(std::string file_name)
{
	int data_counter = 0;
	std::string line_data, i_str;
	bool has_comment, has_alpha_num;
	double i_data;
	std::vector<std::string> line_str;

	std::ifstream reader(file_name.c_str());

	if(!reader)
	{
		std::cout << "Error while opening file " << file_name.c_str();
		std::cout << " in NumericTable::readTSVFile(string file_name)" << std::endl;
		exit(0);
	}

	while(!reader.eof())
	{
		// read each line
		getline(reader,line_data);

		has_alpha_num = false;

		for(int i = 0; i< line_data.length(); i++)
		{
			// check if line has number or character
			// i.e. not empty
			if(isalnum(line_data.at(i)))
			{
				has_alpha_num = true;
			}
		}


		if(has_alpha_num == true)
		{
			for(int i = 0; i < line_data.length(); i++)
			{
				if(isalnum(line_data.at(i)) || (line_data.at(i) == '.') || (line_data.at(i) == '-'))
				{
					i_str.push_back(line_data.at(i));
				}

				if((i_str.size() != 0) && ((line_data.at(i) == ' ') || (i == line_data.length()-1)))
				{
					line_str.push_back(i_str);
					i_str.clear();
				}
			}
		}


		if(has_alpha_num == true)
		{
			for(int i = 0; i < line_str.size(); i++)
			{
				i_data = atof(line_str.at(i).c_str());
				this->table_data.push_back(i_data);
				data_counter += 1;

				if(isnan(i_data))
				{
					this->has_nan = true;
				}

				if(isinf(i_data))
				{
					this->has_inf = true;
				}
			}
		}

		line_str.clear();
	}

	this->num_rows = (int)((double)data_counter/(double)this->num_cols);

	reader.close();
}


void NumericTable::readCSVFile(std::string file_name)
{
	this->readFile(file_name,",");
}


void NumericTable::readFile(std::string file_name, std::string sep)
{

	std::ifstream reader(file_name.c_str());

	if(!reader)
	{
		std::cout << "Error while opening file " << file_name.c_str();
		std::cout << " in NumericTable::readFile(std::string file_name, std::string sep)";
		std::cout << " " << std::endl;
		exit(0);
	}

	std::vector<double> splitted_line_data;
	std::string line_data;

	while(!reader.eof())
	{
		getline(reader,line_data);
		splitted_line_data = NumericTable::splitStringReturnDouble(line_data, sep);
		for(int i = 0; i < splitted_line_data.size(); i++)
		{

			this->appendData(splitted_line_data.at(i));
		}
		splitted_line_data.clear();
	}
}



void NumericTable::writeToFile(std::string file_name, std::string sep, int col_width)
{
	std::ofstream my_file(file_name.c_str());
	int k = 0;
	for(int i = 0; i < this->getNumRows(); i++)
	{
		for(int j = 0; j< this->getNumCols(); j++)
		{
			k = (i * this->getNumCols()) + j;
			if(j < (this->getNumCols() - 1))
			{
				my_file << std::setw(col_width) << std::left << this->table_data.at(k) << sep;
			}

			if(j == (this->getNumCols() - 1))
			{
				my_file << std::setw(col_width) << std::left << this->table_data.at(k) << sep << std::endl;
			}

		}
	}
    my_file.close();
}

void NumericTable::writeToTSVFile(std::string file_name, int col_width)
{
	std::ofstream my_file(file_name.c_str());
	int k = 0;
	for(int i = 0; i < this->getNumRows(); i++)
	{
		for(int j = 0; j < this->getNumCols(); j++)
		{
			k = (i * this->getNumCols()) + j;
			if(j < (this->getNumCols() - 1))
			{
				my_file << std::setw(col_width) << std::left << this->table_data.at(k);
			}

			if(j == (this->getNumCols() -1))
			{
				my_file << std::setw(col_width) << std::left << this->table_data.at(k) << std::endl;
			}

		}
	}
    my_file.close();
}

void NumericTable::writeToCSVFile(std::string file_name, int col_width)
{
	this->writeToFile(file_name, ",", col_width);
}


void NumericTable::writeToTecplot(std::string file_name)
{
	std::ofstream out_file(file_name.c_str());

	out_file << "title = \"sample mesh\"\n";
    out_file << "variables = \"x\", \"y\", \"z\"\n";
    out_file << "                        " << std::endl;
	out_file << "zone i = " << this->getNumRows() << ", j=" << this->getNumCols() << ", f=point" << std::endl;
	out_file << "                        " << std::endl;

	for(int i = 0;i <this->getNumRows();i++)
	{
		out_file << std::setw(20) << std::right << this->getDataAt(i,0) << std::setw(20) << std::right <<
		this->getDataAt(i,1) << std::setw(20) << std::right << this->getDataAt(i,2) << std::endl;
	}
	out_file.close();
}




std::vector<std::string> NumericTable::splitString(std::string string_to_split,
																std::string split_string)
{
    /*
        This function cannot separate string using space.
    */

    std::string data_s;
    std::vector<std::string> splitted_string;


    // remove space manually
    std::string sts = string_to_split;
    string_to_split.clear();

    for(int i = 0; i < sts.length(); i++)
    {
    	if (sts.at(i) != ' ')
    	{
    		string_to_split.push_back(sts.at(i));
    	}
    }


    std::string s1, s2;

    for(int i = 0; i < string_to_split.length(); i++)
    {
        s1 = string_to_split.at(i);
        s2 = split_string;
        if(s1 == s2)
        {
            splitted_string.push_back(data_s);
            data_s.clear();
        }
        else if(i == string_to_split.length()-1)
        {
            data_s = data_s + string_to_split.at(i);
            splitted_string.push_back(data_s);
            data_s.clear();
        }
        else
        {
            data_s = data_s + string_to_split.at(i);
        }
    }
    return splitted_string;
}


std::vector<double> NumericTable::splitStringReturnDouble(std::string string_to_split,
                                                                std::string split_string)
{
   std::vector<std::string> splitted_string =
   NumericTable::splitString(string_to_split,split_string);

   std::vector<double> splitted_string_double;

   for (int i = 0; i < splitted_string.size(); i++)
   {
        splitted_string_double.push_back(atof(splitted_string.at(i).c_str()));
   }

   return splitted_string_double;
}
