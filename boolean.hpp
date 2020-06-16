#pragma once

/*! \file		boolean.hpp
	\author		Garth Santor/Trinh Han
	\date		2019-11-05
	\version	1.0.0
	\note		Compiles under Visual C++ v142 (std:c++ 17)

	\brief		Boolean class declaration.
	*/

#include "operand.hpp"
#include "operator.hpp"


/*! Boolean token. */
class Boolean : public Operand {
public:
	using value_type = bool;
	DEF_POINTER_TYPE(Boolean)
private:
	value_type	value_;
public:
	Boolean(value_type const& value) : value_(value) { }

	value_type				get_value() const { return value_; }
	string_type				to_string() const;
};


/*! Boolean True literal. */
class True : public Boolean {
public:
	True() : Boolean(true) { }
};

/*! Boolean False literal. */
class False : public Boolean {
public:
	False() : Boolean(false) { }
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
