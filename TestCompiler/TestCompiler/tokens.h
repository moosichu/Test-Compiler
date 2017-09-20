#pragma once

#include "operator.h"

enum class TokenType
{
	INT,
	OPERATOR,
	END_OF_FILE
};

struct Token
{
	TokenType token_type;
	void * token_information;
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

template <class TokenType>
constexpr const TokenType& getTokenValue(const Token& rawToken) {
	if (TokenType::type != rawToken.token_type)
	{
		exit(EXIT_FAILURE);
	}
	return *((TokenType*)rawToken.token_information);
}