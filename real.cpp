/*! \file		real.cpp
	\author		Garth Santor/Trinh Han
	\date		2019-11-05
	\version	1.0.0
	\note		Compiles under Visual C++ v142 (std:c++ 17)

	\brief		Real class implementation.
	*/

#include "../inc/real.hpp"
#include "../inc/boolean.hpp"
#include "../inc/function.hpp"
#include "../inc/operator.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;


Real::string_type Real::to_string() const {
	ostringstream oss;
	oss << /*"Real: " << */fixed << setprecision(numeric_limits<value_type>::digits10) << value_;
	return oss.str();
}





/*=============================================================

Revision History

Version 1.0.0: 2019-11-05
C++ 17 cleanup

Version 0.1.0: 2014-10-29
C++ 11 refactor.
Switched value_type to boost::multiprecision::cpp_dec_float_100

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-11-25
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
