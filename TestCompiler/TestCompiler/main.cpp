#include "main.h"

#include "ast.h"
#include "tokens.h"

int program::start(std::function<void(std::string)> printer)
{
	const char * const language_string = "1 + 1";
	printer(std::string("parsing: "));
	printer(std::string(language_string));
	printer("\n");

	TokenInt token_ints[100];
	size_t int_index = 0;

	TokenOperator token_operators[100];
	size_t operator_index = 0;

	Token tokens[100];
	size_t token_index = 0;

	// Lex the language_string and insert tokens into the tokens array
	// Returns the number of tokens encountered
	const int num_tokens = [
		&language_string,
		&token_ints, &int_index,
		&token_operators, &operator_index,
		&tokens, &token_index
	]() {
		// Produce tokens that need consuming
		const char * character_index = language_string;
		while ((*character_index) != NULL)
		{
			const char character = *character_index;
			if (character == ' ')
			{
				// Ignore whitespace
			}
			else
			{
				// Consume characters
				Token token;
				if (character == '1')
				{
					TokenInt info;
					info.value = 1;
					token_ints[int_index] = info;
					token = { TokenType::INT, &token_ints[int_index] };
					int_index++;
				}
				else if (character == '+')
				{
					TokenOperator info;
					info.value = Operator::PLUS;
					token = { TokenType::OPERATOR, &token_operators[operator_index] };
					operator_index++;
				}
				// Add token to tokens
				tokens[token_index++] = token;
			}
			character_index++;
		}
		tokens[token_index++] = { TokenType::END_OF_FILE, nullptr };
		return token_index;
	}();

	for (Token token : tokens)
	{
		switch (token.token_type)
		{
		case TokenType::INT:
		{
			// const TokenInt& intInfo = *((TokenInt*) token.token_information);
			const TokenInt& intInfo = getTokenValue<TokenInt>(token);
			const AST_Int* ast_int = new AST_Int(intInfo.value);
			// assert(intInfo.type == TokenType::INT);
			// TODO: build AST
		} break;
		case TokenType::OPERATOR:
		{
			const TokenOperator& operatorInfo = getTokenValue<TokenOperator>(token);
		} break;
		case TokenType::END_OF_FILE:
		{
		} break;
		}
	}
	return 0;
}
