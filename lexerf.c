#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// an enum to keep track of all the possibilities in lexical analysis.
typedef enum
{
    BEGINNING,
    INT,
    KEYWORD,
    SEPARATOR,
    OPERATOR,
    IDENTIFIER,
    STRING,
    COMP,
    END_OF_TOKENS,
} TokenType;

// a struct to keep hold of the tokens that the lexer will generate.
typedef struct
{
    TokenType type;
    char *value;
    size_t line_num;
} Token;

//keeping track of which line of the file the token lies on.
size_t line_number = 0;


//a function to print the token.
void print_token(Token token)
{
    printf("TOKEN VALUE: ");
    printf("'");
    for (int i = 0; token.value[i] != '\0'; i++)
    {
        printf("%c", token.value[i]);
    }
    printf("'");
    printf("\nline number: %zu", token.line_num);

    switch (token.type)
    {
    case INT:
        printf(" TOKEN TYPE: INT\n");
        break;
    case KEYWORD:
        printf(" TOKEN TYPE: KEYWORD\n");
        break;
    case SEPARATOR:
        printf(" TOKEN TYPE: SEPARATOR\n");
        break;
    case OPERATOR:
        printf(" TOKEN TYPE: OPERATOR\n");
        break;
    case IDENTIFIER:
        printf(" TOKEN TYPE: IDENTIFIER\n");
        break;
    case STRING:
        printf(" TOKEN TYPE: STRING\n");
        break;
    case COMP:
        printf(" TOKEN TYPE: COMPARATOR\n");
        break;
    case END_OF_TOKENS:
        printf(" END OF TOKENS\n");
        break;
    case BEGINNING:
        printf("BEGINNING\n");
        break;
    }
}

//a function to generate tokens for numbers, uses the isdigit function.
Token *generate_number(char current, FILE *file){
    Token *token = malloc(sizeof(Token));
    token->line_num = line_number;
    token->type = INT;
    char *value = malloc(sizeof(char)*8);
    int value_index = 0;
    while(isdigit(current) && current != EOF){

        value[value_index++] = current;
        current = fgetc(file);
    }
    value[value_index] = '\0';
    token->value = value;
    // set the file pointer back 1 position.
    fseek(file, -1, SEEK_CUR);
    return token;
}

//a function to generate tokens for keywords or identifiers, uses the isalpha function.
Token *generate_keyword_or_identifier(char current, FILE *file){
    Token *token = malloc(sizeof(Token));
    token->line_num = line_number;
    char *keyword = malloc(sizeof(char) * 8);
    int keyword_index = 0;
    while (isalpha(current) && (current != '\0' &&  current != EOF))
    {
        keyword[keyword_index++] = current;
        current = fgetc(file);
    }
    //set the file pointer back 1 position.
    fseek(file, -1, SEEK_CUR);
    keyword[keyword_index] = '\0';

    // token for exit syscall.
    if (strcmp(keyword, "exit") == 0)
    {
        token->type = KEYWORD;
        token->value = "EXIT";
    }

    //token for int keyword.
    else if (strcmp(keyword, "int") == 0)
    {
        token->type = KEYWORD;
        token->value = "INT";
    }

    //token for conditional keyword.
    else if (strcmp(keyword, "if") == 0)
    {
        token->type = KEYWORD;
        token->value = "IF";
    }

    //token for loop keywords.
    else if (strcmp(keyword, "while") == 0)
    {
        token->type = KEYWORD;
        token->value = "WHILE";
    }

    //token for writing to console.
    else if (strcmp(keyword, "write") == 0)
    {
        token->type = KEYWORD;
        token->value = "WRITE";
    }

    //comparator tokens.
    else if (strcmp(keyword, "eq") == 0)
    {
        token->type = COMP;
        token->value = "EQ";
    }
    else if (strcmp(keyword, "neq") == 0)
    {
        token->type = COMP;
        token->value = "NEQ";
    }
    else if (strcmp(keyword, "less") == 0)
    {
        token->type = COMP;
        token->value = "LESS";
    }
    else if (strcmp(keyword, "greater") == 0)
    {
        token->type = COMP;
        token->value = "GREATER";
    }

    //identifier tokens.
    else
    {
        token->type = IDENTIFIER;
        token->value = keyword;
    }
    return token;
}

// function to generate tokens for strings.
Token *generate_string_token(char current, FILE *file){
    Token* token = malloc(sizeof(Token));
    token->line_num = line_number;
    char *value = malloc(sizeof(char) * 64);
    int value_index = 0;
    current = fgetc(file);
    while(current != '"' && current != EOF && current != '\0'){
        value[value_index++] = current;
        current = fgetc(file);
    }
    value[value_index] = '\0';
    token->value = value;
    token->type = STRING;
    return token;
}

//function to generate tokens for seperators and operators.
Token *generate_separator_or_operator(char current, TokenType type){
    Token *token = malloc(sizeof(Token));
    token->value = malloc(sizeof(char) * 2);
    token->value[0] = current;
    token->value[1] = '\0';
    token->line_num = line_number;
    token->type = type;
    return token;
}

//keeping track of which token we are at.
size_t tokens_index;

//the lexer function using all the above auxilliary functions.
Token *lexer(FILE *file)
{    
    int number_of_tokens = 12;
    int tokens_size = 0;
    Token *tokens = malloc(sizeof(Token) * number_of_tokens);
    tokens_index = 0;
    char current = fgetc(file);
    while (current != '\0' && current != EOF)
    {
        Token *token = malloc(sizeof(Token));
        tokens_size++;
        if (tokens_size > number_of_tokens)
        {
            number_of_tokens *= 1.5;
            tokens = realloc(tokens, sizeof(Token) * number_of_tokens);
        }
        if (current == ';' || current == ',' || current == '(' || current == ')' || current == '{' || current == '}')
        {
            token = generate_separator_or_operator(current, SEPARATOR);
            tokens[tokens_index] = *token;
            tokens_index++;
        }else if (current == '=' || current == '+' || current == '-' || current == '*' || current == '/' || current == '%')
        {   
            token = generate_separator_or_operator(current, OPERATOR);
            tokens[tokens_index] = *token;
            tokens_index++;
        }
        else if (current == '"')
        {
            token = generate_string_token(current, file);
            tokens[tokens_index] = *token;
            tokens_index++;
        }
        else if (isdigit(current))
        {   
            token = generate_number(current, file);
            tokens[tokens_index] = *token;
            tokens_index++;
        }
        else if (isalpha(current))
        {   
            token = generate_keyword_or_identifier(current, file);
            tokens[tokens_index] = *token;
            tokens_index++;
        }
        else if (current == '\n')
        {
            line_number += 1;
        }
        free(token);
        current = fgetc(file);
    }
    tokens[tokens_index].value = '\0';
    tokens[tokens_index].type = END_OF_TOKENS;
    return tokens;
}
