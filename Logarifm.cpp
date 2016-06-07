// Exponent.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <omp.h>

using namespace std;

double ln(double x, int precision=100){
	double result = 0;
	if(x >= 0 && x<=2)
	{
		x-=1;
		for (int i=1; i<precision; i+=2)
		{
			result+=(pow(x,i)/(double)i - pow(x, i+1)/(double)(i+1));
		}
	}
	else if (x>2)
	{
		x=(x/(x-1));
		for(int i=1; i<precision;i++)
		{
			result+=1.0/(i*pow(x,i));
		}	
	}
	return result;
}

double parallel_ln(double x, int precision=100){
	double result = 0;
	if(x >= 0 && x<=2)
	{
		x-=1;
#pragma omp parallel for
		for (int i=1; i<precision; i+=2)
		{
			result+=(pow(x,i)/(double)i - pow(x, i+1)/(double)(i+1));
		}
	}
	else if (x>2)
	{
		x=(x/(x-1));
#pragma omp parallel for
		for(int i=1; i<precision;i++)
		{
			result+=1.0/(i*pow(x,i));
		}	
	}
	return result;
}

int _tmain(int argc, char* argv[])
{
	string mode = "p";
	if(argc>1){
		mode = argv[1];
	}
	double parameter = 1;
	if(argc<3){
		cout << "Enter x: ";
		cin >> parameter;
	}
	else{
		parameter = stod(argv[3]); 
	}
	int count = 10000;
	if(mode == "n"){
		int t1 = GetTickCount();
		double result;
		for(int i = 0; i<count; i++)
			result = ln(parameter);
		int t2 = GetTickCount();
		cout << "Result: " << result << endl;		
		cout << "Time spent: " << t2 - t1;
	}
	else if(mode =="p"){
		omp_set_num_threads(2);
		int t1 = GetTickCount();
	double result;

		for(int i = 0; i<count; i++)
			result = parallel_ln(parameter);
		int t2 = GetTickCount();
		cout << "Result: " << result << endl;		
		cout << "Time spent: " << t2 - t1;
		
	}
	return 0;
}


