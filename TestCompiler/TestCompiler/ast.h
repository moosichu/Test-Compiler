#pragma once

#include "operator.h"

class AST_Expr
{};

struct AST_Operator : public AST_Expr
{
	AST_Operator(const Operator op, const AST_Expr* lhs, const AST_Expr* rhs) :
		op(op), lhs(lhs), rhs(rhs) {}
	const Operator op;
	const AST_Expr* lhs;
	const AST_Expr* rhs;
};

struct AST_Int : public AST_Expr
{
	AST_Int(const int value) :
		value(value) {}
	const int value;
};