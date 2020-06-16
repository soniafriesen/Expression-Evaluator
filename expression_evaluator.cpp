/** @file: expression_evaluator.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visual C++ v110
	@student	Sonia Friesen 0813682, v.3.0.0
	@brief ExpressionEvaluator class implementation.
	*/

#include "../inc/expression_evaluator.hpp"
#include "../inc/tokenizer.hpp"
#include "../inc/parser.hpp"
#include "../inc/RPNEvaluator.hpp"
#include "../inc/function.hpp"

#if defined(SHOW_STEPS)
#include <iostream>
#endif

ExpressionEvaluator::result_type	ExpressionEvaluator::evaluate(expression_type const& expr) {
	TokenList infixTokens = tokenizer_.tokenize(expr);
	TokenList postfixTokens = parser_.parse(infixTokens);
	Operand::pointer_type result = rpn_.evaluate(postfixTokens);
	return result;
}


/*=============================================================

Revision History

Version 3.0.0 2019-11-05
By Sonia Friesen, Using the Big If

Version 0.0.0: 2010-10-31
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
