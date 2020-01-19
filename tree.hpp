#define _ADD(left, right) create_node(ADD, left, right)
#define _MUL(left, right) create_node(MUL, left, right)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <assert.h>
#include <errno.h>

typedef double Elem_t;

// typedef struct
// {
//   char*  data;
//   Elem_t ndata;
//   void*  left;
//   void*  right;
//   void*  parent;
//   int type;
/* } Node_t; */

enum VisOrder
{
  PreOrder,
  InOrder,
  PostOrder
};

enum NodeTypes {
  ADD,
  MUL,
  DIV,
  POW,
  END_OPERATION,
  NUM,
  VAR
};

extern const char* STR_Operations[];

extern const int MAX_ARG_LEN;

class Node_t
{
  public:
    char* data;
    Elem_t ndata;
    Node_t* left;
    Node_t* right;
    Node_t* parent;
    int type;

    void operator =(const Node_t & other)
    {
      if (this->data)
        free(this->data);

      this->data = (char*)calloc(strlen(other.data) + 1, 1);
      strcpy(this->data, other.data);

      this->ndata  = other.ndata;
      this->left   = other.left;
      this->right  = other.right;
      this->parent = other.parent;
      this->type   = other.type;
    }

    // Node_t operator+(const Node_t & node1, const Node_t & node2);
    /* { */
      // Node_t node;
      // node = &(_ADD(this, &other));
      // return _ADD(this, &other);
    /* } */
};

// Node_t operator+(const Node_t & node1, const Node_t & node2);
int isnum(const char* str, const size_t n);

Node_t* create_node(const int Type, Node_t* nleft, Node_t* nright);
Node_t* create_node(const Elem_t num);
Node_t* create_node(char* data, const size_t n);

int delete_tree(Node_t* tree);
int edit_node(Node_t* node, const void* data, const size_t szof_d);

void tree_visit(Node_t* node, int (*Func)(Node_t* node, const size_t szof_d, FILE* file), const int order, const size_t szof_d, FILE* file);

int write_tree(Node_t* node, FILE* fout);

int tree_write(Node_t* tree, const size_t szof_d, FILE* fout);
char* find_close_Fbrack(char* left, char* right);
int tree_read(char* tree, size_t len_tree, Node_t* node, char* orig);

int akivis(Node_t* tree, size_t szof_d, Node_t** node_out);
int akinator(Node_t* tree);
