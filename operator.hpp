#pragma once

/*! \file		operator.hpp
	\author		Garth Santor/Trinh Han
	\date		2019-11-05
	\version	1.0.0
	\note		Compiles under Visual C++ v142 (std:c++ 17)

	\brief		Operator class declarations
	*/

#include "operation.hpp"
#include "operand.hpp"


/*! Operator Precedence values. */
enum precedence_type { MIN = 0,
	ASSIGNMENT, LOGOR, LOGXOR, LOGAND, BITOR,
	BITXOR, BITAND, EQUALITY, RELATIONAL, BITSHIFT,
	ADDITIVE, MULTIPLICATIVE,  POWER, UNARY, POSTFIX,
	MAX };



/*! Defines a precedence category method.  Used inside a class declaration. */
#define DEF_PRECEDENCE(category)	public: precedence_type get_precedence() const override { return category; }



/*! Operator token base class. */
class Operator : public Operation {
public:
	DEF_POINTER_TYPE(Operator)
	virtual precedence_type get_precedence() const = 0;
};

		/*! Binary operator token base class. */
		class BinaryOperator : public Operator {
		public:
			virtual unsigned number_of_args() const override { return 2; }
		};

				/*! Right-associative operator base class. */
				class RAssocOperator : public BinaryOperator { };

						/*! Power token. */
						class Power : public RAssocOperator {
						DEF_PRECEDENCE(POWER)
						};

						/*! Assignment token. */
						class Assignment : public RAssocOperator {
						DEF_PRECEDENCE(ASSIGNMENT)
						};


				/*! Left-associative operator base class. */
				class LAssocOperator : public BinaryOperator {};

						/*! Addition token. */
						class Addition : public LAssocOperator {
						DEF_PRECEDENCE(ADDITIVE)
						};

						/*! And token. */
						class And : public LAssocOperator {
						DEF_PRECEDENCE(LOGAND)
						};

						/*! Division token. */
						class Division : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
						};

						/*! Equality token. */
						class Equality : public LAssocOperator {
						DEF_PRECEDENCE(EQUALITY)
						};

						/*! Greater than token. */
						class Greater : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
						};

						/*! Greater than or equal to token. */
						class GreaterEqual : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
						};

						/*! Inequality operator token. */
						class Inequality : public LAssocOperator {
						DEF_PRECEDENCE(EQUALITY)
						};

						/*! Less than operator token. */
						class Less : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
						};

						/*! Less than equal-to operator token. */
						class LessEqual : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
						};

						/*! Multiplication operator token. */
						class Multiplication : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
						};

						/*! Modulus operator token. */
						class Modulus : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
						};

						/*! Nand operator token. */
						class Nand : public LAssocOperator {
						DEF_PRECEDENCE(LOGAND)
						};

						/*! Nor operator token. */
						class Nor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
						};

						/*! Or operator token. */
						class Or : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
						};

						/*! Subtraction operator token. */
						class Subtraction : public LAssocOperator {
						DEF_PRECEDENCE(ADDITIVE)
						};

						/*! XOR operator token. */
						class Xor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
						};

						/*! XNOR operator token. */
						class Xnor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)

						};


		/*! Non-associative operator token base class. */
		class NonAssociative : public Operator { };

				/*! Unary operator token base class. */
				class UnaryOperator : public NonAssociative {
				public: virtual unsigned number_of_args() const override { return 1; }
				DEF_PRECEDENCE(UNARY)
				};

						/*! Identity operator token. */
						class Identity : public UnaryOperator {
						public:
						};

						/*! Negation operator token. */
						class Negation : public UnaryOperator {
						public:
						};

						/*! Not operator token. */
						class Not : public UnaryOperator {
						};

				/*! Postfix Operator token base class. */
				class PostfixOperator : public UnaryOperator { 
				};

						/*! Factorial token base class. */
						class Factorial : public PostfixOperator {
						};

/*=============================================================

Revision History

Version 1.0.0: 2019-11-05
C++ 17 cleanup

Version 0.4.0: 2016-11-02
Added 'override' keyword where appropriate.

Version 0.3.0: 2014-10-30
Removed bitwise operators.

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

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
