#include "main.h"

#include <array>

#include "ast.h"
#include "operator.h"
#include "tokens.h"

// TODO: get ASCII codes
// TODO: look at best UniCode format to use

static const char CHAR_0 = 0x30;
static const char CHAR_9 = 0x39;

inline bool is_disruptive_character(const char character)
{
	static char const DISRUPTIVE_CHARACTERS[] =
	{
		' ', '\n', '=', '(', ')', '{', '}', '*', '%', '+', '-'
	};
	for (char const c : DISRUPTIVE_CHARACTERS)
	{
		if (character == c)
		{
			return true;
		}
	}
	return false;
};

char const * consume_whitespace(char const * character_index)
{
	while ((*character_index) == ' ' ||
		   (*character_index) == '\n')
	{
		character_index++;
	}
	return character_index;
}

struct Return_Value_get_token
{
	Token token;
	size_t num_characters_consumed;
};

Return_Value_get_token get_token(char const * const IN_character_index)
{
	char const * character_index = IN_character_index;
	character_index = consume_whitespace(character_index);
	Token token;
	char const character = *character_index;
	switch (character)
	{
	case '(':
	{
		token = create_token(TokenType::L_BRACE);
	} break;
	case ')':
	{
		token = create_token(TokenType::R_BRACE);
	} break;
	case '+':
	{
		token = create_token_from_operator(Operator::PLUS);
	} break;
	case '-':
	{
		token = create_token_from_operator(Operator::MINUS);
	} break;
	case '*':
	{
		token = create_token_from_operator(Operator::MULTIPLY);
	} break;
	case '%':
	{
		token = create_token_from_operator(Operator::DIVIDE);
	} break;
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		// TODO: get token integer value
		int integer_value = 0;
		int integer_size = 0; // TODO(Tom): handle different sized integers
		while (*character_index >= CHAR_0 &&
			   *character_index <= CHAR_9)
		{
			integer_size++;
			integer_value *= 10;
			integer_value += (*character_index) - CHAR_0;
			character_index++;
		}
		character_index--;
		TokenInt info;
		info.value = integer_value;
		token = create_token_from_info(info);
	} break;
	case 0:
	{
		token = create_token(TokenType::END_OF_FILE);
	} break;
	default:
	{
		while (!is_disruptive_character(*character_index))
		{
			// Consume characters
			if (*character_index == '1')
			{
				TokenInt info;
				info.value = 1;
				token = create_token_from_info(info);
			}
			character_index++;
		}
		// Add token to tokens
	}
	}
	character_index++;
	// Make sure we return the number of characters that have been consumed
	Return_Value_get_token return_value;
	return_value.token = token;
	return_value.num_characters_consumed = character_index - IN_character_index;
	return return_value;
};

void assert(bool arg)
{

};

int program::start(std::function<void(std::string)> printer)
{
	char const * const language_string = "(1 + 1) * 3 * (2-1)";
	printer(std::string("parsing: "));
	printer(std::string(language_string));
	printer("\n");

	auto tokens = std::array<Token, 100>();
	size_t token_index = 0;

	// Lex the language_string and insert tokens into the tokens array
	// Returns the number of tokens encountered
	size_t const num_tokens = [
		&language_string,
		&tokens, &token_index
	]() {
		// Produce tokens that need consuming
		char const * character_index = language_string;
		character_index = consume_whitespace(character_index);

		while ((*character_index) != NULL)
		{
			// Get the next token
			Return_Value_get_token get_token_info = get_token(character_index);
			tokens[token_index++] = get_token_info.token;
			character_index += get_token_info.num_characters_consumed;
		}
		tokens[token_index++] = create_token(TokenType::END_OF_FILE);
		return token_index;
	}();

	for (Token token : tokens)
	{
		switch (token.token_type)
		{
		case TokenType::INT:
		{
			const TokenInt& intInfo = token.int_information;
			const AST_Int* ast_int = new AST_Int(intInfo.value);
			// assert(intInfo.type == TokenType::INT);
			// TODO: build AST
		} break;
		case TokenType::OPERATOR:
		{
			const TokenOperator& operatorInfo = token.operator_information;
		} break;
		case TokenType::END_OF_FILE:
		{
		} break;
		}
	}
	return 0;
}
