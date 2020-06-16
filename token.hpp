#pragma once
/*! \file		token.hpp
	\author		Garth Santor/Trinh Han
	\date		2019-11-05
	\version	1.0.0
	\note		Compiles under Visual C++ v142 (std:c++ 17)

	\brief		Token class declaration for Expression Evaluator project.
	*/

#include <memory>
#include <utility>
#include <string>
#include <typeinfo>
#include <vector>
#include <ostream>



/*! Defines the appropriate type of smart pointer used in this system. */
#define DEF_POINTER_TYPE(_TT) using pointer_type = std::shared_ptr<_TT>;


/*! Token base class. */
class Token {
public:
	DEF_POINTER_TYPE(Token)
	using string_type = std::string;
	
	// Block copying
	Token(Token const&) = delete;
	Token& operator = (Token const&) = delete;

	Token() = default;
	virtual ~Token() = default;
	virtual string_type	to_string() const;
};



/*! Make a new smart-pointer managed Token object. */
template <typename T> inline Token::pointer_type make() { return Token::pointer_type(new T); }



/*! Make a new smart-pointer managed Token object with constructor parameter. */
template <typename T, typename U> inline Token::pointer_type make(U const& param) { return Token::pointer_type(new T(param)); }



/*! Compare two tokens for same value. */
inline bool operator == (Token::pointer_type const& lhs, Token::pointer_type const& rhs) {
#if !defined(NDEBUG)
	auto l = lhs->to_string();
	auto r = rhs->to_string();
#endif
	return lhs->to_string() == rhs->to_string();
}



/*! Test for family membership. */
template <typename CAST_TYPE, typename ORIGINAL_TYPE>
inline bool is(ORIGINAL_TYPE const& tkn) {
	return dynamic_cast<CAST_TYPE const*>(tkn.get()) != nullptr;
}



/*! Test for family membership. */
template <typename CAST_TYPE, typename ORIGINAL_TYPE>
inline bool is(ORIGINAL_TYPE const * tknPtr) {
	return dynamic_cast<CAST_TYPE const*>(tknPtr) != nullptr;
}



/*! Convert to subclass type. */
template <typename CONVERTED_TYPE>
inline typename CONVERTED_TYPE::pointer_type convert(Token::pointer_type const& tkn) {
	return std::dynamic_pointer_cast<CONVERTED_TYPE>(tkn);
}



/*! Container of tokens. */
using TokenList = std::vector<Token::pointer_type>;



/*! stream operators */
inline std::ostream& operator << (std::ostream& os, Token const& token) {
	return os << token.to_string();
}

inline std::ostream& operator << (std::ostream& os, Token::pointer_type const& token) {
	return os << token->to_string();
}


/*=============================================================

Revision History

Version 1.0.0: 2019-11-05
C++ 17 cleanup

Version 0.2.1: 2012-11-13
C++ 11 cleanup

Version 0.2.0: 2010-11-20
Changed parameter of is_convertable_from to const&

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
