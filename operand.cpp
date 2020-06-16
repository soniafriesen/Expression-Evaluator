/*! \file: operand.cpp
	\author		Garth Santor/Trinh Han
	\date		2019-11-05
	\version	1.0.0
	\note		Compiles under Visual C++ v142 (std:c++ 17)

	@brief Operand class and utilities implemenation.
	*/

#include "../inc/operand.hpp"
#include "../inc/boolean.hpp"
#include "../inc/integer.hpp"
#include "../inc/real.hpp"
#include "../inc/variable.hpp"
#include <algorithm>
#include <cassert>
#include <sstream>



/*=============================================================

Revision History

Version 1.0.0: 2019-11-05
C++ 17 cleanup

Version 0.0.2: 2017-12-12
Added an exception to dereference when there is no value stored in the variable.

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-14
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
