/** @file: tokenizer.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.3.0
	@date 2017-11-23
	@note Compiles under Visual C++ 15.4.4

	@brief Tokenizer class implementation.
	*/

#include "../inc/tokenizer.hpp"
#include "../inc/boolean.hpp"
#include "../inc/function.hpp"
#include "../inc/integer.hpp"
#include "../inc/operator.hpp"
#include "../inc/pseudo_operation.hpp"
#include "../inc/real.hpp"
#include "../inc/variable.hpp"

#include <exception>
#include <limits>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

/** Default constructor loads the keyword dictionary. */
Tokenizer::Tokenizer() {
	keywords_["abs"]     = keywords_["Abs"]		= keywords_["ABS"]		= make<Abs>();
	keywords_["and"]     = keywords_["And"]		= keywords_["AND"]		= make<And>();
	keywords_["arccos"]  = keywords_["Arccos"]	= keywords_["ARCCOS"]	= make<Arccos>();
	keywords_["arcsin"]  = keywords_["Arcsin"]	= keywords_["ARCSIN"]	= make<Arcsin>();
	keywords_["arctan"]  = keywords_["Arctan"]	= keywords_["ARCTAN"]	= make<Arctan>();
	keywords_["arctan2"] = keywords_["Arctan2"]	= keywords_["ARCTAN2"]	= make<Arctan2>();
	keywords_["ceil"]    = keywords_["Ceil"]	= keywords_["CEIL"]		= make<Ceil>();
	keywords_["cos"]     = keywords_["Cos"]		= keywords_["COS"]		= make<Cos>();
	keywords_["e"]       = keywords_["E"]								= make<E>();
	keywords_["exp"]     = keywords_["Exp"]		= keywords_["EXP"]		= make<Exp>();
	keywords_["false"]   = keywords_["False"]	= keywords_["FALSE"]	= make<False>();
	keywords_["floor"]   = keywords_["Floor"]	= keywords_["FLOOR"]	= make<Floor>();
	keywords_["lb"]      = keywords_["Lb"]		= keywords_["LB"]		= make<Lb>();
	keywords_["ln"]      = keywords_["Ln"]		= keywords_["LN"]		= make<Ln>();
	keywords_["log"]     = keywords_["Log"]		= keywords_["LOG"]		= make<Log>();
	keywords_["max"]     = keywords_["Max"]		= keywords_["MAX"]		= make<Max>();
	keywords_["min"]     = keywords_["Min"]		= keywords_["MIN"]		= make<Min>();
	keywords_["mod"]     = keywords_["Mod"]		= keywords_["MOD"]		= make<Modulus>();
	keywords_["nand"]    = keywords_["Nand"]	= keywords_["NAND"]		= make<Nand>();
	keywords_["nor"]     = keywords_["Nor"]		= keywords_["NOR"]		= make<Nor>();
	keywords_["not"]     = keywords_["Not"]		= keywords_["NOT"]		= make<Not>();
	keywords_["or"]      = keywords_["Or"]		= keywords_["OR"]		= make<Or>();
	keywords_["pi"]      = keywords_["Pi"]		= keywords_["PI"]		= make<Pi>();
	keywords_["pow"]     = keywords_["Pow"]		= keywords_["POW"]		= make<Pow>();
	keywords_["result"]  = keywords_["Result"]	= keywords_["RESULT"]	= make<Result>();
	keywords_["sin"]     = keywords_["Sin"]		= keywords_["SIN"]		= make<Sin>();
	keywords_["sqrt"]    = keywords_["Sqrt"]	= keywords_["SQRT"]		= make<Sqrt>();
	keywords_["tan"]     = keywords_["Tan"]		= keywords_["TAN"]		= make<Tan>();
	keywords_["true"]    = keywords_["True"]	= keywords_["TRUE"]		= make<True>();
	keywords_["xnor"]    = keywords_["Xnor"]	= keywords_["XNOR"]		= make<Xnor>();
	keywords_["xor"]     = keywords_["Xor"]		= keywords_["XOR"]		= make<Xor>();
}




/** Get an identifier from the expression.
	Assumes that the currentChar is pointing to a alphabetic.
	*/
Token::pointer_type Tokenizer::_get_identifier(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression) {
	// accumulate identifier
	string_type ident;
	do
		ident += *currentChar++;
	while (currentChar != end(expression) && isalnum(*currentChar));

	// check for predefined identifier
	dictionary_type::iterator iter = keywords_.find(ident);
	if (iter != end(keywords_))
		return iter->second;

	// check for variable
	iter = variables_.find(ident);
	if (iter != variables_.end())
		return iter->second;

	// add a variable
	Token::pointer_type result = make<Variable>();
	variables_[ident] = result;
	return result;
}




/** Get a number token from the expression.
	@return One of BinaryInteger, Integer, or Real.
	@param currentChar [in,out] an iterator to the current character.  Assumes that the currentChar is pointing to a digit.
	@param expression [in] the expression being scanned.
*/
Token::pointer_type Tokenizer::_get_number(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression) {
	assert(isdigit(*currentChar) && "currentChar must pointer to a digit");

	// Either Integer or Real
	string digits(1, *currentChar++);

	while (currentChar != end(expression) && isdigit(*currentChar))
		digits += *currentChar++;

	if (currentChar == end(expression) || (!isdigit(*currentChar) && *currentChar != '.'))
		return make<Integer>(Integer::value_type(digits));

	// a real number
	digits += *currentChar++;
	while (currentChar != end(expression) && isdigit(*currentChar))
		digits += *currentChar++;


	return make<Real>(Real::value_type(digits));
}



/** Tokenize the expression.
	@return a TokenList containing the tokens from 'expression'.
	@param expression [in] The expression to tokenize.
	@note Tokenizer dictionary may be updated if expression contains variables.
	@note Will throws 'BadCharacter' if the expression contains an un-tokenizable character.
	*/
TokenList Tokenizer::tokenize(string_type const& expression) {
	TokenList tokenizedExpression;
	auto currentChar = expression.cbegin();

	for(;;)
	{
		// strip whitespace
		while (currentChar != end(expression) && isspace(*currentChar))
			++currentChar;

		// check of end of expression
		if (currentChar == end(expression)) break;

		// check for a number
		if (isdigit(*currentChar)) {
			tokenizedExpression.push_back(_get_number(currentChar, expression));
			continue;
		}

		// check for 2-character operators
#define CHECK_2OP( symbol1, symbol2, token )\
		if( *currentChar == symbol1 ) {\
			auto nextChar = next(currentChar);\
			if( nextChar != end(expression) && *nextChar == symbol2 ) {\
				currentChar = next(nextChar);\
				tokenizedExpression.push_back( make<token>() );\
				continue;\
			}\
		}
		CHECK_2OP('<', '=', LessEqual)
		CHECK_2OP('>', '=', GreaterEqual)
		CHECK_2OP('=', '=', Equality)
		CHECK_2OP('!', '=', Inequality)
		CHECK_2OP('*', '*', Power)
#undef CHECK_2OP

			// check for 1-character operators
#define CHECK_OP(symbol, token)\
		if( *currentChar == symbol ) {\
			++currentChar;\
			tokenizedExpression.push_back( make<token>() );\
			continue;\
		}
		CHECK_OP('*', Multiplication)
		CHECK_OP('/', Division)
		CHECK_OP('%', Modulus)
		CHECK_OP('(', LeftParenthesis)
		CHECK_OP(')', RightParenthesis)
		CHECK_OP(',', ArgumentSeparator)
		CHECK_OP('<', Less)
		CHECK_OP('>', Greater)
		CHECK_OP('!', Factorial)
		CHECK_OP('=', Assignment)
#undef CHECK_OP


		// check for multi-purpose operators
		if (*currentChar == '+') {
			++currentChar;
			if (!tokenizedExpression.empty() &&
				(is<RightParenthesis>(tokenizedExpression.back()) ||
					is<Operand>(tokenizedExpression.back()) ||
					is<PostfixOperator>(tokenizedExpression.back())))
				tokenizedExpression.push_back(make<Addition>());
			else
				tokenizedExpression.push_back(make<Identity>());
			continue;
		}
		if (*currentChar == '-') {
			++currentChar;
			if (!tokenizedExpression.empty() &&
				(is<RightParenthesis>(tokenizedExpression.back()) ||
					is<Operand>(tokenizedExpression.back()) ||
					is<PostfixOperator>(tokenizedExpression.back())))
				tokenizedExpression.push_back(make<Subtraction>());
			else
				tokenizedExpression.push_back(make<Negation>());
			continue;
		}


		// Identifiers
		if (isalpha(*currentChar)) {
			tokenizedExpression.push_back(_get_identifier(currentChar, expression));
			continue;
		}

		// not a recognized token
		throw XBadCharacter(expression, currentChar - begin(expression));
	}

	return tokenizedExpression;
}

/*=============================================================

Revision History

Version 0.3.0: 2017-11-23
Added Python-style power operator '**'.

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitXOr, BitShiftLeft, BitShiftRight
Simplified CHECK_OP macros

Version 0.1.0: 2012-11-15
Replaced BadCharacter with XTokenizer, XBadCharacter, and XNumericOverflow
Added BinaryInteger, Binary <function>

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
