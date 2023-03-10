#include "TestPoly.h"
#include <iostream>
#include "Poly.h"
using namespace std;

int main()
{
	int max_degree = 1000;
	double max_coeff = 100;
	int max_eval_degree = 20;
	double max_eval_coeff = 10;
	int max_run = 50;
	vector<int> max_size_array = { 1, 5, 10 };

    double fullMark = 0;
    double totalMark = 0;

	TestPoly tp(max_degree, max_coeff, max_eval_degree, max_eval_coeff, max_run, max_size_array);
//    vector<int> degFirst = {799, 778, 97};
//    vector<double> coeffFirst = {-85, 53, 39};
//    Poly First(degFirst, coeffFirst);
//
//    vector<int> degSecond = {722, 289};
//    vector<double> coeffSecond = {-17, -27};
//    Poly Second(degSecond, coeffSecond);
//    First.multiplyPoly(Second);
//    string output = First.toString();
//    cout << output << endl;
    //[1521,1500,1088,1067,819,386]
    //[1445,-901,2295,-1431,-663,-1053]
    tp.testConstructorDefault(totalMark, fullMark);
    tp.testConstructorParameters(totalMark, fullMark);
    tp.testAddMono(totalMark, fullMark);
    tp.testAddPoly(totalMark, fullMark);
    tp.testMultiplyMono(totalMark, fullMark);
    tp.testMultiplyPoly(totalMark, fullMark);
    tp.testDuplicate(totalMark, fullMark);
    tp.testEvaluate(totalMark, fullMark);

    cout << "********************************" << endl;
    cout << "*** FINAL TOTAL MARK IS " << totalMark << "/" << fullMark << " ***" << endl;
    cout << "********************************" << endl;
}
