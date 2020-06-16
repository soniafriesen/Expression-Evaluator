#pragma once

/*! \file		operand.hpp
	\author		Garth Santor/Trinh Han
	\date		2019-11-05
	\version	1.0.0
	\note		Compiles under Visual C++ v142 (std:c++ 17)

	\brief		Operand class declaration.
	*/


#include "token.hpp"
#include <cassert>
#include <deque>


/*! Operand token base class. */
class Operand : public Token {
public:
	DEF_POINTER_TYPE(Operand)
	using operand_list_type = std::deque<Operand::pointer_type>;
};


/*! Make a new smart-pointer managed Token object with constructor parameter. */
template <typename T, typename U> inline Operand::pointer_type make_operand(U const& param) {
	return Operand::pointer_type(new T(param));
}


/*! Gets the value from an operand. */
template <typename OPERAND_TYPE>
typename OPERAND_TYPE::value_type get_value(Token::pointer_type const& operand) {
	assert(is<OPERAND_TYPE>(operand));
	return dynamic_cast<OPERAND_TYPE*>(operand.get())->get_value();
}


/*!	Type for a list of operands. */
using OperandList = Operand::operand_list_type;



/*=============================================================

Revision History

Version 1.0.0: 2019-11-05
C++ 17 cleanup

Version 0.1.1: 2012-11-13
C++ cleanup.

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

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
