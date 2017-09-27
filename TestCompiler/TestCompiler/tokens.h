#pragma once

#include "operator.h"

enum class TokenType : uint8_t
{
	INVALID      = 0x00,
	INT          = 0x01,
	OPERATOR     = 0x02,
	L_BRACE      = 0x03, // (
	R_BRACE      = 0x04, // )

	END_OF_FILE  = 0xFF
};

struct TokenInt
{
	static const TokenType type = TokenType::INT;
	int value;
};

struct TokenOperator
{
	static const TokenType type = TokenType::OPERATOR;
	Operator value;
};

struct TokenStub {};

struct Token
{
	TokenType token_type;
	union {
		TokenInt int_information;
		TokenOperator operator_information;
		TokenStub no_info;
	};
};


template <class T>
const Token create_token_from_info(T token_info)
{
	Token token;
	token.token_type = T::type;
	switch (T::type)
	{
	case TokenType::INT:
	{
		token.int_information = *((TokenInt*)((void*)(&token_info)));
	} break;
	case TokenType::OPERATOR:
	{
		token.operator_information = *((TokenOperator*)((void*)(&token_info)));
	} break;
	}
	return token;
}

const Token create_token(TokenType token_type)
{
	Token token;
	token.token_type = token_type;
	token.no_info = {};
	return token;
}

const Token create_token_from_operator(Operator op)
{
	TokenOperator to;
	to.value = op;
	return create_token_from_info(to);
}
