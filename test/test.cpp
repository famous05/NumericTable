#include <iostream>
#include <vector>
#include <memory>


#include "numeric_table.h"

int main()
{

	// Read the points data set
	auto table = std::make_unique<NumericTable>(3);
	table->readTSV("points_data.dat");
	//table->print();
	std::cout << "Number of Rows of Data Points = " << table->getNumRows() << std::endl;
	std::cout << "Number of Cols of Data Points = " << table->getNumCols() << std::endl;

	// Re-shape the data to 9 columns. Careful, you may lose data here !
	table->setNumCols(9);
	std::cout << "Number of Rows after Re-shaping = " << table->getNumRows() << std::endl;


	// Write data to CSV format, set column width to 15
	table->writeToCSV("points_data.csv", 15);


	// Create a new table object by copying previous one
	std::unique_ptr<NumericTable> table_2(new NumericTable);
	*table_2 = *table; // do a deep copy

	// Print details about new table
	std::cout << "Number of Columns in table_2 = " << table_2->getNumCols() << std::endl;
	std::cout << "Number of Rows in table_2 = " << table_2->getNumRows() << std::endl;

	// Trim new table by setting a shorter number of row
	table_2->setNumRows(5);
	table_2->print();



	std::cout << "Number of Columns in table_2 = " << table_2->getNumCols() << std::endl;
	std::cout << "Number of Rows in table_2 = " << table_2->getNumRows() << std::endl;

	// Clear new table
	table_2->clear();


	// Re-read data from file
	table_2->readTSV("points_data.dat");

	// Print details about new table
	std::cout << "Number of Columns in table_2 = " << table_2->getNumCols() << std::endl;
	std::cout << "Number of Rows in table_2 = " << table_2->getNumRows() << std::endl;

	// The table seem to have been reshaped to 9 columns from the deep copy


	// Re-shape the data back to 3 columns and write to file
	table_2->setNumCols(3);
	table_2->scale(1000); // convert to mm
	table_2->write("points_data_scaled.pipe", "|");
	
}
