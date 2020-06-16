/*! \file		ee_main.cpp
	\author		Garth Santor/Trinh Han
	\date		2019-11-05
	\version	1.0.0
	\note		Compiles under Visual C++ v142 (std:c++ 17)
	@student	Sonia Friesen 0813682, v.3.0.0
	\brief		Expression Evaluator application.
	*/

#include "../ee_common/inc/expression_evaluator.hpp"
#include "../ee_common/inc/function.hpp"
#include "../ee_common/inc/real.hpp"
#include "../ee_common/inc/variable.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

//NOTE: Using Big IF, The email I sent with the operator polymorph issue was not resolved in time for the due date. For me to get this done in a timely fashion and handed in with the boost tests working, I had to quickly do the Big If (well not exatly quickly more like a few hours with lots of code). 
int main()
{
	cout << "Expression Evaluator, (c) 1998-2019 Garth Santor\n";
	cout << "Expression Evaluator, (c) 2019 Sonia Friesen\n";
	cout << "Enter 'help' for a reference \n";

	ExpressionEvaluator ee;

	for (unsigned count = 0; ; ++count) {

		try
		{
			// Get the input from the user
			cout << "> ";
			string command;
			if (!getline(cin, command) || command.empty())
			{
				cout << "no command was given" << endl;
				break;
			}				

			// Display a help message
			if (command == "help")
			{
				cout << "Expression Evaluator 2019 (v 3.0.0)\n\n"

					"var = assign a variable\n"
					"setp #          sets the precision of floating point output\n\n"

					"arithmetic operations :\n"
					"addition                n + r\n"
					"division                n / r\n"
					"factorial               n!\n"
					"identity                + n, +r\n"
					"modulus                 n % n, n mod n\n"
					"multiplication          n*r\n"
					"negation                - n, -r\n"
					"power                   n**r\n"
					"subtraction             n - r\n\n"

					"relational operations :\n"
					"less              a < b\n"
					"greater           a > b\n"
					"less - equal      a <= b\n"
					"greater - equal   a >= b\n"
					"equal             a == b\n"
					"not- equal        a != b\n\n"

					"boolean operations :\n"
					"not and or xor nand nor xnor\n\n"

					"constants :\n"
					"Pi              pi\n"
					"Euler           e\n"
					"Boolean true    true\n"
					"Boolean false   false\n\n"

					"functions :\n"
					"absolute value                  abs(n), abs(r)\n"
					"arc cosine                      arccos(r)\n"
					"arc sine                        arcsin(r)\n"
					"arc tangent                     arctan(r), arctan2(r, r)\n"
					"ceiling                         ceil(r)\n"
					"cosine                          cos(r)\n"
					"exponential                     exp(r)\n"
					"floor                           floor(r)\n"
					"logarithm(base 2)               lb(r)\n"
					"logarithm(base e)               ln(r)\n"
					"logarithm(base 10)              log(r)\n"
					"maximum                         max(a, b)\n"
					"minimum                         min(a, b)\n"
					"power                           pow(base, exponent)\n"
					"sine                            sin(r)\n"
					"square root                     sqrt(r)\n"
					"tangent                         tan(r)" << endl;
				continue;
			}

			// Convert the evaluated expression to a Token pointer
			auto result = ee.evaluate(command);

			Operand::pointer_type varPtr = dynamic_pointer_cast<Operand>(result);

			// Cast the value to a string to be displayed
			string str = result->to_string();
			string strCheck = "";
			strCheck = str[0];

			// Check whether it is an Integer, Real, Boolean, or Variable. Then
			// remove the characters of Integer, Real, Boolean, or Variable to display
			// just the value.
			if (strCheck == "I")
			{
				str = str.substr(9);
			}
			else if (strCheck == "R")
			{
				str = str.substr(5);
			}
			else if (strCheck == "V")
			{
				Token::pointer_type variableValue = get_value<Variable>(varPtr);
				str = variableValue->to_string();
				str = str.substr(9);
			}
			else if (strCheck == "B")
			{
				str = str.substr(9);

				if (str == "1")
				{
					str = "true";
				}
				else
				{
					str = "false";
				}
			}

			cout << "[" << count << "] = " << str << endl;
		}
		catch (exception e)
		{
			cerr << e.what() << endl;
			continue;
		}
		catch (...)
		{
			cerr << "Unknown exception" << endl;
			continue;
		}
	}
}

/*=============================================================

Revision History

Version 3.0.0 2019-11-05
By Sonia Friesen, Using the Big If

Version 1.0.0: 2019-11-05
C++ 17 cleanup

Version 0.3.0: 2017-11-23
Added Python-style power operator '**'

Version 0.2.0: 2016-10-29
Added help command.

Version 0.1.0: 2014-11-27
Added: setp to set the real number precision.

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2010-11-23
Alpha release.

=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han of Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/
