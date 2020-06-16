/** @file: parser.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2012-11-13
	@note Compiles under Visual C++ v120
	@student	Sonia Friesen 0813682, v.3.0.0
	@brief Parser class implementation.
	*/

#include "../inc/parser.hpp"
#include "../inc/function.hpp"
#include "../inc/operand.hpp"
#include "../inc/operator.hpp"
#include "../inc/pseudo_operation.hpp"
#include <stack>
using namespace std;

//start here
TokenList Parser::parse(TokenList const& infixTokens) {
	
	//1.create a empty stack and TokenList
	stack<Token::pointer_type> stackOperation;
	TokenList postFix;

	//use a ranged for loop to go through the tokens in list
	for (auto t : infixTokens)
	{
		//is it a operand?
		if (auto operand = dynamic_pointer_cast<Operand>(t)) {
			postFix.push_back(t);
		}//end oeprand
		//is it a function
		else if (auto function = dynamic_pointer_cast<Function>(t)) {
			stackOperation.push(t);
		}//end function
		//is it a Argument Separator
		else if (auto arguSep = dynamic_pointer_cast<ArgumentSeparator>(t))
		{
			while (!dynamic_pointer_cast<LeftParenthesis>(stackOperation.top())) { //is not a left parenthesis
				postFix.push_back(stackOperation.top()); //add to queue
				if (!stackOperation.empty())
					stackOperation.pop();//pop it off the top
			} //end while loop
		}//end argument seperator
		//is it a left parenthesis
		else if (auto leftParnth = dynamic_pointer_cast<LeftParenthesis>(t))
		{
			stackOperation.push(t);
		}//end left parenthesis
		else if (auto rightParnth = dynamic_pointer_cast<RightParenthesis>(t))
		{
			while (!dynamic_pointer_cast<LeftParenthesis>(stackOperation.top())) //if its not a leftparenthesis
			{
				postFix.push_back(stackOperation.top()); //pushit on postFix list
				if (!stackOperation.empty()){
					stackOperation.pop(); //take off stack
				}
				if (stackOperation.empty())
				{
					//exception handling
					throw("Right parenthesis, has no matching left parenthesis");
					break;
				}//end if
			}//end while
			//take parenthesis off the stack
			if (!stackOperation.empty()){
				stackOperation.pop();
			}//end if
			if (!stackOperation.empty()) {
				//if its a function, push to postFix and pop off stack.
				if (auto function = dynamic_pointer_cast<Function>(stackOperation.top())) {
					postFix.push_back(stackOperation.top());
					stackOperation.pop();
				}//end if
			}//end if
		}//right parenthesis
		//is it an operator, if so what is the precedence
		else if (auto isoperator = dynamic_pointer_cast<Operator>(t)) {
			//use a loop until we have an empty stack
			while (!stackOperation.empty()) {
				//check the top for operator
				if (!dynamic_pointer_cast<Operator>(stackOperation.top())) {
					//exit out of loop
					break;
				}
				if (dynamic_pointer_cast<NonAssociative>(t)) // if its non associative
				{
					//exit loop
					break;
				}
				if (auto assocOperator = dynamic_pointer_cast<LAssocOperator>(t)) {
					auto isoperator = dynamic_pointer_cast<Operator>(stackOperation.top());
					//if the token has a high precedence then the top of the stack
					if (assocOperator->get_precedence() > isoperator->get_precedence()) {
						//exit loop
						break;
					}
				}
				if (auto rAssocOperator = dynamic_pointer_cast<RAssocOperator>(t)) {
					auto isoperator = dynamic_pointer_cast<Operator>(stackOperation.top());
					//if the token has a high precedence then the top of the stack
					if (rAssocOperator->get_precedence() >= isoperator->get_precedence()) {
						//exit loop
						break;
					}
				}
				//the top of the stak should have the hiest precedence, pus it to the postfix and take off
				postFix.push_back(stackOperation.top());				
				//check to make sure the stack isnt empty
				if (!stackOperation.empty())
				{
					stackOperation.pop();
				}				
			}//end while loop
			stackOperation.push(t);//push that token on to the stack
		}//end else if operator
		else {
			throw("Unknown token");
			break;
		}
	}//end auto for loop

	//go through stack, add each operation, and pop them off the stack
	while (!stackOperation.empty()) { //while the stack is not empty
		if (auto leftParnth = dynamic_pointer_cast<LeftParenthesis>(stackOperation.top()))
		{
			throw("Missing right-parenthesis");
			break;
		}
		postFix.push_back(stackOperation.top()); //push the top of th estack
		stackOperation.pop(); //remove the operation
	}
	//return the toeklist
	return postFix;
}


/*=============================================================

Revision History

Version 3.0.0 2019-11-05
By Sonia Friesen, Using the Big If

Version 1.0.0: 2014-10-31
Visual C++ 2013

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-02
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
