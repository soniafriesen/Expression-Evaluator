#pragma once

/*! \file		function.hpp
	\author		Garth Santor/Trinh Han
	\date		2019-11-05
	\version	1.0.0
	\note		Compiles under Visual C++ v142 (std:c++ 17)
	\student	Sonia Friesen 0813682, v.3.0.0
	\brief		function token declarations.
	*/

#include "operation.hpp"
#include "integer.hpp"
#include <vector>

/*! Function token base class. */
class Function : public Operation { };

		/*! One argument function token base class. */
		class OneArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 1; }
		};

				/*! Absolute value function token. */
				class Abs : public OneArgFunction {	};

				/*! arc cosine function token. */
				class Arccos : public OneArgFunction {	};

				/*! arc sine function token. */
				class Arcsin : public OneArgFunction { 
				};

				/*! arc tangent function token.  Argument is the slope. */
				class Arctan : public OneArgFunction { 
				};

				/*! ceil function token. */
				class Ceil : public OneArgFunction { 
				};

				/*! cosine function token. */
				class Cos : public OneArgFunction { 
				};

				/*! exponential function token.  pow(e,x), where 'e' is the euler constant and 'x' is the exponent. */
				class Exp : public OneArgFunction { 
				};

				/*! floor function token. */
				class Floor : public OneArgFunction { 
				};

				/*! logarithm base 2 function token. */
				class Lb : public OneArgFunction {
				};

				/*! natural logarithm function token. */
				class Ln : public OneArgFunction { 
				};

				/*! logarithm base 10 function token. */
				class Log : public OneArgFunction { 
				};

				/*! previous result token. Argument is the 1-base index of the result. */
				class Result : public OneArgFunction {
				};

				/*! sine function token. */
				class Sin : public OneArgFunction {
				};

				/*! Square root token. */
				class Sqrt : public OneArgFunction {
				};

				/*! tangeant function. */
				class Tan : public OneArgFunction { 
				};


		/*!	Two argument function token base class. */
		class TwoArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 2; }
		};

				/*! 2 parameter arc tangent function token.
					First argument is the change in Y, second argument is the change in X. */
				class Arctan2 : public TwoArgFunction { 
				};

				/*! Maximum of 2 elements function token. */
				class Max : public TwoArgFunction {
				};

				/*! Minimum of 2 elements function token. */
				class Min : public TwoArgFunction {
				};

				/*! Pow function token.  First argument is the base, second the exponent. */
				class Pow : public TwoArgFunction { 
				};


/*=============================================================

Revision History

Version 1.0.0: 2019-11-05
C++ 17 cleanup

Version 0.1.0: 2016-11-02
Added 'override' keyword where appropriate.

Version 0.0.2: 2014-10-30
Removed binary function

Version 0.0.1: 2012-11-13
C++ 11 cleanup

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
