#include "tree.hpp"

const char* STR_Operations[] = {
  "ADD",
  "MUL",
  "DIV",
  "POW"
};

const int MAX_ARG_LEN = 256;

/*     Node_t operator+(const Node_t & node1, const Node_t & node2) */
    // {
    //   Node_t node;
    //   node = *(_ADD(&node1, &node2));
    //   return node;
    // }
/*  */
int isnum(const char* str, const size_t n)
{
  int was_started = 0;
  int was_point = 0;
  for (char* chr = (char*)str; chr < str + n; chr ++)
  {
    if (isdigit(*chr))
    {
      was_started = 1;
    }
    else if (*chr == '.' && !was_point)
    {
      was_point = 1;
    }
    else if (!(*chr == ' ' && !was_started))
    {
      return 0;
    }
  }

  return 1;
}

Node_t* create_node(const int Type, Node_t* nleft, Node_t* nright)
{
  assert(Type < END_OPERATION);

  Node_t* node = (Node_t*)calloc(1, sizeof(*node));
  if (!node)
  {
    errno = ENOMEM;
    perror("node");
    return NULL;
  }

  printf("%i:: We're here)" "\n", __LINE__);

  node->left  = nleft;
  node->right = nright;

  node->data = (char*)STR_Operations[Type];

  return node;
}

Node_t* create_node(const Elem_t num)
{
  Node_t* node = (Node_t*)calloc(1, sizeof(*node));
  if (!node)
  {
    errno = ENOMEM;
    perror("node");
    return NULL;
  }

  node->type = NUM;
  node->ndata = (Elem_t)num;

  return node;
}

Node_t* create_node(char* data, const size_t n)
{
  if (data && isnum(data, n))
  {
    data[n] = '\0';
    return create_node(atof(data));
  }
  Node_t* node = (Node_t*)calloc(1, sizeof(*node));
  if (!node)
  {
    errno = ENOMEM;
    perror("node");
    return NULL;
  }

  printf("%i:: node[%X], node->data[%X].%d" "\n", __LINE__, node, node->data, n + 1);
  node->data = (char*)calloc(n + 1, sizeof(*node->data));
  printf("%i:: node[%X], node->data[%X]" "\n", __LINE__, node, node->data);
  printf("%i:: Creating data for node" "\n", __LINE__);
  if (!node->data)
  {
    printf("%i:: OOOOOPS!!!" "\n", __LINE__);
    errno = ENOMEM;
    perror("node->data");
    return NULL;
  }

  if (data)
    strncpy(node->data, data, n);

  return node;
}

int delete_tree(Node_t* tree)
{
  assert(tree);

  // if (tree->left)  delete_tree((Node_t*)tree->left);
  if (tree->left)  delete_tree(tree->left);
  // if (tree->right) delete_tree((Node_t*)tree->right);
  if (tree->right) delete_tree(tree->right);

  if ((tree->parent)->left == tree)
  {
    (tree->parent)->left  = NULL;
  }
  else if ((tree->parent)->right == tree)
  {
    (tree->parent)->right  = NULL;
  }
  else
  {
    errno = EINVAL;
    perror("tree->parent->child != tree");
    return errno;
  }
  if (tree->data)
    free(tree->data);
  free(tree);

  return 0;
}

int edit_node(Node_t* node, const void* data, const size_t szof_d)
{
  assert(node);
  assert(node->data);
  assert(data);

  free(node->data);
  node->data = (char*)calloc(1, szof_d + 1);
  memcpy(node->data, data, szof_d);
  node->data[szof_d] = '\0';

  return 0;
}

void tree_visit(Node_t* node, int (*Func)(Node_t* node, size_t szof_d, FILE* file), const int order, const size_t szof_d, FILE* file)
{
  assert(node);
  assert(file);

  printf("%i:: Troubles?" "\n", __LINE__);

  if (order == PreOrder)
  {
    if (!Func(node, szof_d, file))
      return;
  }

  if (node->left) {
    printf("%i:: -----------LEFT------------" "\n", __LINE__);
    tree_visit(node->left, Func, order, szof_d, file);
  }
  if (order == InOrder)
  {
    if (!Func(node, szof_d, file))
      return;
  }

  if (node->right) {
    printf("%i:: ----------RIGHT-------------" "\n", __LINE__);
    tree_visit(node->right, Func, order, szof_d, file);
  }
  if (order == PostOrder)
  {
    if (!Func(node, szof_d, file))
      return;
  }
  return;
}

int tree_write(Node_t* tree, const size_t szof_d, FILE* fout)
{
  assert(fout);

  static int open_br  = 0;
  static int close_br = 0;

  /** if (open_br == close_br) */
  /** { */
  /**   fwrite("\n", 1, 1, fout); */
  /**   open_br  = 0; */
  /**   close_br = 0; */
  /** } */

  printf("%i:: We're in wrtie" "\n", __LINE__);
  /** printf("%i:: Data = %s" "\n", __LINE__, tree->data); */

  /** printf("%i:: ob{%d} cb{%d}" "\n", __LINE__, open_br, close_br); */

  printf("%i:: We're in wrtie" "\n", __LINE__);
  fwrite("{\"", 1, 2, fout);
  open_br ++;
  printf("%i:: We're in wrtie" "\n", __LINE__);
  printf("%i:: TreeData{%s}" "\n", __LINE__, tree->data);
  fwrite(tree->data, 1, strlen(tree->data), fout);
  printf("%i:: We're in wrtie" "\n", __LINE__);
  fwrite("\"", 1, 1, fout);
  printf("%i:: We're in wrtie" "\n", __LINE__);
  if (!tree->left)
  {
    fwrite("*", 1, 1, fout);
  }
  else
    return 1;

  printf("%i:: We're in wrtie" "\n", __LINE__);
  if (!tree->right)
  {
  printf("%i:: We're in wrtie" "\n", __LINE__);
    fwrite("*", 1, 1, fout);
  }
  else
    return 1;
  fwrite("}", 1, 1, fout);
  if (close_br % 2)
  {
  printf("%i:: We're in wrtie" "\n", __LINE__);
    fwrite("}", 1, 1, fout);
    close_br ++;
  }
  close_br ++;
  printf("%i:: We're in wrtie" "\n", __LINE__);

  if (open_br - close_br == 2)
  {
    printf("%i:: ob{%d} cb{%d}" "\n", __LINE__, open_br, close_br);
    printf("%i:: data {%s}" "\n", __LINE__, tree->data);
  }

  return 0;
}

char* find_close_Fbrack(char* left, char* right)
{
  int cnt_open_brack = 0;
  do
  {
    if (*left == '{')
    {
      cnt_open_brack ++;
    }
    if (*left == '}')
    {
      cnt_open_brack --;
    }
    left ++;
  } while (left <= right && cnt_open_brack > 0);

  printf("%i:: HERERERERER -- {%c}" "\n", __LINE__, *left);
  printf("%i:: ~ {%s}" "\n", __LINE__, left - 1);
  return left;
}

int tree_read(char* tree, size_t len_tree, Node_t* node, char* orig)
{
  char* end = NULL;
  char* right_p = NULL;
  printf("%i:: " "\n", __LINE__);
  printf("%i:: %s\n", __LINE__, tree);
  printf("%i:: " "\n", __LINE__);
  printf("%i:: " "\n", __LINE__);
  for (;tree < orig + len_tree - 2; (tree) ++)
  {
    if (*tree == '{')
    {
      right_p = find_close_Fbrack(tree, orig + len_tree);
      (tree) ++;
      /** printf("-%i-%s\n", __LINE__, chr); */
    }
    if (*tree == '"')
    {
      (tree) ++;
      end = strchr(tree, '"');
      printf("%i:: %s\n%s" "\n", __LINE__, tree, end);
      strncpy(node->data, tree, end - tree);

      printf("%i:: Data[%X] = %s" "\n", __LINE__, node->data, node->data);

      tree = end + 1;
    }
    printf("%i:: Tree %s" "\n", __LINE__, tree);
    if (*tree == '}')
    {
      printf("%i:: So Ok" "\n", __LINE__);
      return 0;
    }
    printf("%i:: WTF?! Tree = ---%s---" "\n", __LINE__, tree);
    if (*tree != '*')
    {
      right_p = find_close_Fbrack(tree, orig + len_tree);
      printf("%i:: ----------- LEFT --------------" "\n", __LINE__);
  /** printf("%i:: %s\n", __LINE__, tree); */
      printf("%i:: NODE[%X].DATA[%X]{%s}" "\n", __LINE__, node, node->data, node->data);
      node->left = create_node(NULL, strchr(tree + 2, '"') - (tree + 1));
      printf("%i:: NODE[%X].DATA[%X]{%s}" "\n", __LINE__, node->left, (node->left)->data, (node->left)->data);
      tree_read(tree, len_tree, node->left, orig);
    }
    if (right_p && *right_p != '*')
    {
      printf("%i:: RP {%s}" "\n", __LINE__, right_p);
      printf("%i:: Tree {%s}" "\n", __LINE__, tree);
      if (*tree != '*')
        tree = right_p;
      else
        tree ++;
      if (*tree == '*')
        return 0;
      printf("%i:: RP->tree? {%s}" "\n", __LINE__, tree);
      printf("%i:: --?" "\n", __LINE__);
      printf("%i:: ----------- RIGHT -------------" "\n", __LINE__);
      printf("%i:: TREE {%s}" "\n", __LINE__, tree);
  /** printf("%i:: %s\n", __LINE__, tree); */
      printf("%i:: NODE[%X].DATA[%X]{%s}" "\n", __LINE__, node, node->data, node->data);
      if (!strchr(tree + 2, '"'))
      {
        break;
      }
      node->right = create_node(NULL, strchr(tree + 2, '"') - (tree + 1));
      printf("%i:: NODE[%X].DATA[%X]{%s}" "\n", __LINE__, node->right, (node->right)->data, (node->right)->data);
      tree_read(tree, len_tree, node->right, orig);
      return 0;
    }
    printf("%i:: I don't want)) .TREE ---%s---" "\n", __LINE__, tree);
  }

  return 0;
}

int write_tree(Node_t* node, FILE* fout)
{
  fwrite("{\"", 1, 2, fout);
  fwrite(node->data, 1, strlen(node->data), fout);
  fwrite("\"", 1, 1, fout);

  if (node->left)
  {
    write_tree(node->left, fout);
  }
  else
  {
    fwrite("*", 1, 1, fout);
  }

  if (node->right)
  {
    write_tree(node->right, fout);
  }
  else
  {
    fwrite("*", 1, 1, fout);
  }

  fwrite("}", 1, 1, fout);

  return 0;
}


int akivis(Node_t* tree, size_t szof_d, Node_t** node_out)
{
  if (!(tree->left || tree->right))
  {
    printf("%i:: Is'it %s? [Y/N]: ", __LINE__, tree->data);
    char* req = (char*)malloc(MAX_ARG_LEN);
    scanf("%s", req);
    if (*req == 'y' || *req == 'Y')
    {
      free(req);
      return 0;
    }
    else
    {
      Node_t* node_l = (Node_t*)calloc(1, sizeof(*node_l));
      if (!node_l)
      {
        errno = ENOMEM;
        perror("node_l");
        return errno;
      }
      tree->left = create_node(tree->data, strlen(tree->data));

      Node_t* node_r = (Node_t*)calloc(1, sizeof(*node_r));
      if (!node_r)
      {
        errno = ENOMEM;
        perror("node_r");
        return errno;
      }
      printf("%i:: So, what did you expect?" "\n", __LINE__);
      printf("%i:: Ans: ", __LINE__);
      char* ans_temp = (char*)malloc(MAX_ARG_LEN);
      scanf("%s", ans_temp);
      tree->right = create_node(ans_temp, strlen(ans_temp));
      *node_out = node_r;
      printf("%i:: What was the differense?" "\n", __LINE__);
      printf("%i:: Difs: ", __LINE__);
      scanf("%s", ans_temp);
      free(tree->data);
      tree->data = (char*)malloc(strlen(ans_temp) + 1);
      strcpy(tree->data, ans_temp);
      free(ans_temp);
      return 0;
    }
  }
  else
  {
    printf("%i:: Is it %s: ", __LINE__, tree->data);
    char* res = (char*)malloc(MAX_ARG_LEN);
    scanf("%s", res);
    if (*res == 'Y' || *res == 'y')
    {
      akivis(tree->right, szof_d, node_out);
    }
    else
      akivis(tree->left, szof_d, node_out);
  }

  return 0;
}

int akinator(Node_t* tree)
{
  Node_t* node_in = NULL;

  int res = akivis(tree, MAX_ARG_LEN, &node_in);
  if (res)
  {
    printf("%i:: Smth wrong.." "\n", __LINE__);
  }
  else
  {
    printf("%i:: -------- PROFIT ---------" "\n", __LINE__);
  }

  return 0;
}
