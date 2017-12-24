#include <iostream>

#include "numeric_table.h"

int main()
{
	NumericTable T(3);
	T.readCSVFile("test_csv.csv");
	T.print();
}
