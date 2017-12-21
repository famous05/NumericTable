/*
	DynamicTable: Reads and writes numeric data in column format

    Copyright (C) 2013 - 2018  Osarobo F. Okhuahesogie
	E-Mail: ofokhuahesogie@wabtec.com,	famous.osarobo@gmail.com

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

//C++
#include <cstring>
#include <cctype>


//Developer
#include "dynamic_table.h"


DynamicTable::DynamicTable()
{
	this->numColumns = 0;
	this->numRecords = 0;
	this->has_nan = false;
	this->has_inf = false;
}


DynamicTable::DynamicTable(int numCols)
{
	this->numColumns = numCols;
	this->has_nan = false;
	this->has_inf = false;
}


DynamicTable::DynamicTable(DynamicTable* DT)
{
	this->numRecords = DT->numOfRecords();
	this->numColumns = DT->numOfColumns();
	this->record = DT->record;
	this->has_nan = false;
	this->has_inf = false;
}


DynamicTable::~DynamicTable()
{
	this->record.clear();
}


int DynamicTable::numOfRecords()
{
	return this->numRecords;
}


int DynamicTable::numOfColumns()
{
	return this->numColumns;
}



void DynamicTable::setNumOfColumns(int numCols)
{
	// first update number of records 
	this->numColumns = numCols;
	this->numRecords = (int)(((double)this->numOfRecords() * (double)numOfColumns())/(double)numCols);  
}


void DynamicTable::setNumOfRecords(int numRecs)
{
	// This function is useful only when using dynamic table to write data
	// when you know the number of records already
	this->numRecords = numRecs;
}


bool DynamicTable::hasNaN()
{
	return this->has_nan;
}


bool DynamicTable::hasInf()
{
	return this->has_inf;
}


void DynamicTable::appendData(double data)
{
	this->record.push_back(data);
	this->numRecords = (int)((double)this->record.size()/(double)this->numOfColumns());
}


double DynamicTable::getDataAt(int row, int column)
{	
	int dataIndex = (row * this->numOfColumns()) + column;
	
	if((row > (this->numOfRecords()-1))||(column > (this->numOfColumns()-1)))
	{
		std::cout << "Requested table index is out of range in ";
		std::cout << "DynamicTable::getDataAt(int row, int column)" << std::endl;
		std::cout << "Exiting program....." << std::endl;
		exit(1);
	}
	else
	{
		return record.at(dataIndex);
	}	
}


void DynamicTable::setDataAt(double data, int row_index, int col_index)
{
	int data_index = (row_index * this->numOfColumns()) + col_index;
	this->record.at(data_index) = data;
}


void DynamicTable::scaleData(double scale_factor)
{
	int data_index;
	for(int row = 0; row < this->numOfRecords(); row++)
	{
		for(int col = 0; col < this->numOfColumns(); col++)
		{
			data_index = (row * this->numOfColumns()) + col;
			this->record.at(data_index) = this->record.at(data_index) * scale_factor;
		}
	}
}


void DynamicTable::print()
{
	for(int iRow = 0;iRow<this->numOfRecords();iRow++)
	{
		for(int iCol = 0;iCol<this->numOfColumns();iCol++)
		{			
			if(iCol==this->numOfColumns()-1)
			{
				std::cout << std::setw(15) << std::left << this->getDataAt(iRow,iCol) << "  " << std::endl;
				
			}
			else
			{
				std::cout << std::setw(15) << std::left << this->getDataAt(iRow,iCol) << "  ";
			}			
		}
	}
}


void DynamicTable::clear()
{
	this->record.clear();
}


void DynamicTable::readCurveFile(std::string file_name)
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
		std::cout << " in DynamicTable::readCurveFile(std::string file_name)" << std::endl;
		exit(0);
	}

	while(!reader.eof())
	{
		//read in line				
		getline(reader,line_data);
		
		//ingore lines with command markers anywhere********************
		has_comment  = false;
		has_alpha_num = false;

		for(int i = 0;i<line_data.length();i++)
		{
			if((line_data.at(i) == '#')||(line_data.at(i) == '!'))
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
			for(int i = 0;i<line_data.length();i++)
			{
				if(isalnum(line_data.at(i))|| (line_data.at(i)=='.') || (line_data.at(i)=='-'))
				{
					i_str.push_back(line_data.at(i));	
				}

				if((i_str.size()!=0) && ((line_data.at(i)==' ')||(i==line_data.length()-1)))
				{
					line_str.push_back(i_str);
					i_str.clear();
				}
				
			}	
		}


		if((has_comment == false) && (has_alpha_num == true))
		{
			for(int i=0;i<3;i++) //read data in first 3 pos of string vector
			{
				i_data = atof(line_str.at(i).c_str());
				record.push_back(i_data);
				data_counter+=1;

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

	this->numRecords = (int)((double)data_counter/(double)this->numColumns);

	reader.close();
}


void DynamicTable::readTSVFile(std::string file_name)
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
		std::cout << " in DynamicTable::readFile(string file_name)" << std::endl;
		exit(0);
	}

	while(!reader.eof())
	{
		// read each line			
		getline(reader,line_data);
		
		has_alpha_num = false;

		for(int i = 0;i<line_data.length();i++)
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
			for(int i = 0;i<line_data.length();i++)
			{
				if(isalnum(line_data.at(i))|| (line_data.at(i)=='.') || (line_data.at(i)=='-'))
				{
					i_str.push_back(line_data.at(i));	
				}

				if((i_str.size()!=0) && ((line_data.at(i)==' ')||(i==line_data.length()-1)))
				{
					line_str.push_back(i_str);
					i_str.clear();
				}
				
			}	
		}


		if(has_alpha_num == true)
		{
			for(int i=0;i<line_str.size();i++) 
			{
				i_data = atof(line_str.at(i).c_str());
				record.push_back(i_data);
				data_counter+=1;

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

	this->numRecords = (int)((double)data_counter/(double)this->numColumns);

	reader.close();
}


void DynamicTable::readCSVFile(std::string file_name)
{
	this->readFile(file_name,",");
}
    

void DynamicTable::readFile(std::string file_name, std::string sep)
{
	
	// catch if sep == space                                                                       
    
	
	std::ifstream reader(file_name.c_str());
	  

	if(!reader)
	{
		std::cout << "Error while opening file " << file_name.c_str();
		std::cout << " in DynamicTable::readFile(std::string file_name, std::string sep)" << std::endl;
		exit(0);
	}


	std::vector<double> splitted_line_data;
	std::string line_data;
	
	while(!reader.eof())
	{
		getline(reader,line_data);
		splitted_line_data = DynamicTable::splitStringReturnDouble(line_data, sep);
		for(int i = 0; i < splitted_line_data.size(); i++)
		{

			this->appendData(splitted_line_data.at(i));
		}
		splitted_line_data.clear();
	}
}





void DynamicTable::writeToFile(std::string fileName, std::string sep, double col_width)
{
	std::ofstream myFile(fileName.c_str());
	int k;
	for(int i = 0;i<this->numOfRecords();i++)
	{
		for(int j = 0;j<this->numOfColumns();j++)
		{
			k = (i*this->numOfColumns()) + j;
			if(j < (this->numOfColumns() -1))
			{
				myFile << std::setw(col_width) << std::left << this->record.at(k) << sep;
			}		
			
			if(j == (this->numOfColumns() -1))
			{
				myFile << std::setw(col_width) << std::left << this->record.at(k) << sep << std::endl;	
			}

		}	
	}
    myFile.close();
}

void DynamicTable::writeToTSVFile(std::string fileName, double col_width)
{
	std::ofstream myFile(fileName.c_str());
	int k;
	for(int i = 0;i<this->numOfRecords();i++)
	{
		for(int j = 0;j<this->numOfColumns();j++)
		{
			k = (i*this->numOfColumns()) + j;
			if(j < (this->numOfColumns() -1))
			{
				myFile << std::setw(col_width) << std::left << this->record.at(k);
			}		
			
			if(j == (this->numOfColumns() -1))
			{
				myFile << std::setw(col_width) << std::left << this->record.at(k) << std::endl;	
			}

		}	
	}
    myFile.close();
}

void DynamicTable::writeToCSVFile(std::string fileName, double col_width)
{
	this->writeToFile(fileName, ",", col_width);
}


void DynamicTable::writeToTecplot(std::string file_name)
{
	std::ofstream out_file(file_name.c_str());

	out_file << "title = \"sample mesh\"\n";
    out_file << "variables = \"x\", \"y\", \"z\"\n";
    out_file << "                        " << std::endl;
	out_file << "zone i = " << this->numOfRecords() << ", j=" << this->numOfColumns() << ", f=point" << std::endl;
	out_file << "                        " << std::endl;
	
	for(int i = 0;i <this->numOfRecords();i++)
	{
		out_file << std::setw(20) << std::right << this->getDataAt(i,0) << std::setw(20) << std::right <<
		this->getDataAt(i,1) << std::setw(20) << std::right << this->getDataAt(i,2) << std::endl;
	}
	out_file.close();
}




std::vector<std::string> DynamicTable::splitString(std::string string_to_split, 
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


std::vector<double> DynamicTable::splitStringReturnDouble(std::string string_to_split,
                                                                std::string split_string)
{
   std::vector<std::string> splitted_string = 
   DynamicTable::splitString(string_to_split,split_string);
   
   std::vector<double> splitted_string_double;

   for (int i = 0; i < splitted_string.size(); i++)
   {
        splitted_string_double.push_back(atof(splitted_string.at(i).c_str()));
   } 

   return splitted_string_double;
}
    


