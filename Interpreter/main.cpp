#include <iostream>
#include <string>
#include <cctype>

enum TokenType {
    INTEGER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LEFTPARENTHESIS,
    RIGHTPARENTHESIS,
    MIN,
    MAX,
    COMMA,
    EOF_TOKEN
};

class Token {
public:
    TokenType type;
    std::string value;
    Token(TokenType type, std::string value) : type(type), value(value) {} //constructor
};

class Interpreter {
private:
    std::string text;
    size_t position; //position in the input
    Token current_token;
    char current_char; //gets the current character

    void error() {
        throw std::runtime_error("Error parsing input");
    }
    void moveChar() {
        position++;
        if (position > text.size() - 1) {
            current_char = '\0'; // Indicates end of input
        } else {
            current_char = text[position];
        }
    }
    void skip_whitespace() {
        while (current_char != '\0' && std::isspace(current_char)) {
            moveChar();
        }
    }

    Token getNextToken() {
        while (current_char != '\0') {
            if (std::isspace(current_char)) {
                skip_whitespace();
                continue;
            }

            if (std::isdigit(current_char)) {
                std::string value;
                while (current_char != '\0' && std::isdigit(current_char)) {
                    value += current_char;
                    moveChar();
                }
                return Token(INTEGER, value);
            }

            if (current_char == '+') {
                moveChar();
                return Token(PLUS, "+");
            }

            if (current_char == '-') {
                moveChar();
                return Token(MINUS, "-");
            }

            if (current_char == '*') {
                moveChar();
                return Token(MULTIPLY, "*");
            }

            if (current_char == '/') {
                moveChar();
                return Token(DIVIDE, "/");
            }

            if (current_char == '(') {
                moveChar();
                return Token(LEFTPARENTHESIS, "(");
            }

            if (current_char == ')') {
                moveChar();
                return Token(RIGHTPARENTHESIS, ")");
            }

            if (current_char == ',') {
                moveChar();
                return Token(COMMA, ",");
            }

            if (text.substr(position, 3) == "max") {
                position += 3;
                moveChar();
                return Token(MAX, "max");
            }

            if (text.substr(position, 3) == "min") {
                position += 3;
                moveChar();
                return Token(MIN, "min");
            }
                error();
            return Token(EOF_TOKEN, "");
        }
    }
    void moveToken(TokenType token_type) {
        if (current_token.type == token_type) {
            current_token = getNextToken();
        } else { //if the type does not match it wont procede
            error();
        }
    }
public:
    Interpreter(std::string text) : text(text), position(0), current_token(getNextToken()) {
        current_char = text[position];
    }

    int factor() { //responsible for basic handling like integers and parenthesis
        Token token = current_token;
        if (token.type == INTEGER) {
            moveToken(INTEGER);
            return std::stoi(token.value); //converts to int
        } else if (token.type == LEFTPARENTHESIS) {
            moveToken(LEFTPARENTHESIS);
            int result = expr();
            moveToken(RIGHTPARENTHESIS);
            return result;
        } else if (token.type == MAX) {
        moveToken(MAX);
        moveToken(LEFTPARENTHESIS);
        int left = expr();
        moveToken(COMMA);
        int right = expr();
        moveToken(RIGHTPARENTHESIS);
        return std::max(left, right);
    } else if (token.type == MIN) {
        moveToken(MIN);
        moveToken(LEFTPARENTHESIS);
        int left = expr();
        moveToken(COMMA);
        int right = expr();
        moveToken(RIGHTPARENTHESIS);
        return std::min(left, right);
    }
        error();
    }
    int term() { //responsible for higher order (mult and div)
        int result = factor();
        while (current_token.type == MULTIPLY || current_token.type == DIVIDE) {
            Token token = current_token;
            if (token.type == MULTIPLY) {
                moveToken(MULTIPLY);
                result *= factor();
            } else if (token.type == DIVIDE) {
                moveToken(DIVIDE);
                result /= factor();
            }
        }
        return result;
    }
    int expr() { //responsible for lower order (plus and minus)
        current_token = getNextToken();
        int result = term();
        while (current_token.type == PLUS || current_token.type == MINUS) {
            Token token = current_token;
            if (token.type == PLUS) {
                moveToken(PLUS);
                result += term();
            } else if (token.type == MINUS) {
                moveToken(MINUS);
                result -= term();
            }
        }
        return result;
    }

};
