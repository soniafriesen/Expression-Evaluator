/*! \file		operator.cpp
	\author		Garth Santor/Trinh Han
	\date		2019-11-05
	\version	1.0.0
	\note		Compiles under Visual C++ v142 (std:c++ 17)

	\brief		Operator class implementations.
	*/

#include "../inc/operator.hpp"
#include "../inc/operand.hpp"
#include "../inc/integer.hpp"
#include "../inc/real.hpp"
#include "../inc/variable.hpp"
#include <cassert>
#include "../inc/boolean.hpp"


/*=============================================================

Revision History

Version 1.0.0: 2019-11-05
C++ 17 cleanup

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-08
Added exception for assignment to a non-variable.

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
