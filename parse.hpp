#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include "tree.hpp"

char* find_close_brack(char* left, char* right);
Node_t* parse_by_Add(char* left, char* right, Node_t** node);
Node_t* parse_by_Mul(char* left, char* right, Node_t** node);
Node_t* parse_by_Pow(char* left, char* right, Node_t** node);
