#include "parse.hpp"

char* find_close_brack(char* left, char* right)
{
  int cnt_open_brack = 0;
  do
  {
    if (*left == '(')
    {
      cnt_open_brack ++;
    }
    if (*left == ')')
    {
      cnt_open_brack --;
    }
    left ++;
  } while (left <= right && cnt_open_brack > 0);

  return left;
}

Node_t* parse_by_Add(char* left, char* right, Node_t** node)
{
  *node = create_node(left, right - left + 1);
  char* tmpp = NULL;
  int was_op = 0;
  for (char* chr = left; chr < right; chr ++)
  {
      printf("%i:: Here" "\n", __LINE__);
    if (*chr == '(')
    {
      printf("%i:: Here" "\n", __LINE__);
      tmpp = find_close_brack(chr, right);
      if (chr == left && tmpp == right)
      {
        parse_by_Add(left + 1, right - 1, node);
      }

      chr = tmpp;
      printf("%i:: Here" "\n", __LINE__);
    }
    if (*chr == '+')
    {
      fwrite(left, 1, chr - left, stdout);
      printf("\n");
      fwrite(chr + 1, 1, right - chr + 1, stdout);
      printf("\n");
      was_op = 1;
      printf("%i:: Here" "\n", __LINE__);
      *node = _ADD(parse_by_Add(left, chr - 1,  &((*node)->left)),
                   parse_by_Add(chr + 1, right, &((*node)->right)));

      /** node = parse_by_Add(left, chr - 1, &node->left) + parse_by_Add(chr + 1, right, &node->right); */

      printf("%i:: Here {%s}" "\n", __LINE__, (*node)->data);

      return *node;
    }
  }
      printf("%i:: Here" "\n", __LINE__);

  if (!was_op)
  {
    if (isnum(left, right - left))
    {
      (*node)->type = NUM;
      strncpy((*node)->data, left, right - left + 1);
      (*node)->ndata = atof((*node)->data);
      printf("%i:: AddNodeData {%s}" "\n", __LINE__, (*node)->data);
    }
    else
    {
      printf("%i:: Here" "\n", __LINE__);
      printf("%i:: ELSE {%s}" "\n", __LINE__, left);
      *node = parse_by_Mul(left, right, node);
      (*node)->type = MUL;
    }
  }

  return *node;
}

Node_t* parse_by_Mul(char* left, char* right, Node_t** node)
{
  *node = create_node(left, right - left + 1);
  char* tmpp = NULL;
  char* temp_str = (char*)calloc(255, 1);
  int was_op = 0;

  for (char* chr = left; chr && chr < right; chr ++)
  {
    if (*chr == '(')
    {
      tmpp = find_close_brack(chr, right);
      if (tmpp == chr + strlen(chr) - 1 && chr == (*node)->data)
      {
        strcpy(temp_str, (*node)->data + 1);
        strcpy((*node)->data, temp_str);
      }
    }
    if (*chr == '*')
    {
      was_op = 1;
      (*node) = _MUL(parse_by_Mul(left, chr, &((*node)->left)),
                     parse_by_Mul(chr + 1, right, &((*node)->right)));

      return (*node);
    }
  }


  if (!was_op)
  {
    if (isnum(left, right - left))
    {
      (*node)->type = NUM;
      strncpy((*node)->data, left, right - left + 1);
      (*node)->ndata = atof((*node)->data);
      printf("%i:: Mul NodeDAta {%s}" "\n", __LINE__, (*node)->data);
    }
    else
    {
      (*node) = parse_by_Pow(left, right, node);
      (*node)->type = POW;
    }
  }

  free(temp_str);

  return (*node);
}

Node_t* parse_by_Pow(char* left, char* right, Node_t** node)
{
  *node = create_node(left, right - left + 1);
  char* tmpp = NULL;
  char* temp_str = (char*)calloc(255, 1);
  int was_op = 0;

  for (char* chr = left; chr && chr < right; chr ++)
  {
    if (*chr == '(')
    {
      tmpp = find_close_brack(chr, right);
      if (tmpp == chr + strlen(chr) - 1 && chr == (*node)->data)
      {
        strcpy(temp_str, (*node)->data + 1);
        strcpy((*node)->data, temp_str);
      }
    }
    if (*chr == '^')
    {
      was_op = 1;
      (*node) = _MUL(parse_by_Mul(left, chr, &((*node)->left)), parse_by_Mul(chr + 1, right, &((*node)->right)));

      return (*node);
    }
  }

  if (!was_op)
  {
    if (isnum(left, right - left))
    {
      (*node)->type = NUM;
      strncpy((*node)->data, left, right - left + 1);
      (*node)->ndata = atof((*node)->data);
      printf("%i:: {%s}" "\n", __LINE__, (*node)->data);
    }
    else
    {
      (*node)->type = VAR;
      strncpy((*node)->data, left, right - left);
      printf("%i:: NodeData {%s}" "\n", __LINE__, (*node)->data);
    }
  }

  free(temp_str);

  return (*node);
}
