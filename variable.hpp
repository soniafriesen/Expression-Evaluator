#pragma once

/*! \file: variable.hpp
	\author Garth Santor/Trinh Han
	\date 2019-11-05
	\version 1.0.0
	\note Compiles under Visual C++ v142 (std:c++ 17)

	\brief Variable class declaration.
	*/

#include "operand.hpp"



/*! Variable operand token. */
class Variable : public Operand {
public:
	DEF_POINTER_TYPE(Variable)
	using value_type = Operand::pointer_type;
private:
	value_type	value_;
public:
	Variable() = default;
	value_type				get_value() const { return value_; }
	void					set_value(Operand::pointer_type const& value) { value_ = value; }
	string_type				to_string() const override;
};


/*=============================================================

Revision History

Version 1.0.0: 2019-11-05
C++ 17 cleanup

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

Version 0.0.0: 2009-11-26
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
