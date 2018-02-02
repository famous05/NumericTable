#include <iostream>
//#include <vector>
#include <memory>
#include "numeric_table.h"

int main()
{

	NumericTable T(3);
	T.read_csv("test_csv.csv");
	T.print();
	T.write_csv("tt.tsv");
	T.print();


	NumericTable T2(3);
	T2.clear();
	T2.read_csv("tt.tsv");
	T2.write("file.dat","|");
	T2.write_tecplot("file.tec");


	T2.clear();
	T2.read_ansys_curve("Profile.curve");
	T2.write_tecplot("Profile.tec");


	//auto table = std::make_unique<NumericTable>(3);
	//*table = T2;
	//table->scale(2000);
	//table->writeToTSVFile("Scaled_Profile.dat");


	//auto b_curve =
    //std::make_unique<GeometricEntity::Curves::BezierCurve>(cpts,num_points);
	//std::unique_ptr<GeomEnt::BezierControlPoint> cp(new GeomEnt::BezierControlPoint(0,0,0,1));

	//std::unique_ptr<NumericTable> table(new NumericTable(3));
	//*table = T2;
	//table->readCurveFile("Profile.curve");
	//table->scale(2000);
	//table->writeToTSVFile("Scaled_Profile.dat");

	//auto t = std::make_shared<NumericTable>(T2);
	auto t = std::make_shared<NumericTable>(3);
	*t = T2;
	//t->readCurveFile("Profile.curve");
	t->scale(-0.0001);
	t->write_tsv("Scaled_Profile.dat");


	//NumericTable * nt = new NumericTable(T2);
	//nt->scale(-20);
	//nt->writeToCSVFile("Neg_Profile.csv");




/*
	typedef std::vector<double> vdouble;

	vdouble v1;
	vdouble* v2 = new vdouble;
	for(int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2->push_back(i);
	}

	std::cout << sizeof(v1) << std::endl;
	std::cout << sizeof(v2) << std::endl;
	std::cout << sizeof(*v2) << std::endl;

	for (const auto& val : v1)
	{
		std::cout << val << std::endl;
	}
*/

	//delete nt;
	//nt = nullptr;
}
