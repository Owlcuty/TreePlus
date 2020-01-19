#include "tree.h"

int main()
{
  FILE* fout = fopen("fout.out", "r");
  Node_t* tree = (Node_t*)calloc(8192, sizeof(*tree));
  if (!tree)
  {
    errno = ENOMEM;
    perror("tree");
    return errno;
  }

  fseek(fout, 0, SEEK_END);
  int flen = ftell(fout);
  printf("%i:: flen{%d}" "\n", __LINE__, flen);
  fseek(fout, 0, SEEK_SET);

  char* fdata = (char*)calloc(flen + 1, sizeof(*fdata));
  if (!fdata)
  {
    errno = ENOMEM;
    perror("fdata");
    return errno;
  }

  fread(fdata, 1, flen, fout);
  /** fdata[flen] = '\0'; */
  printf("%i:: %s" "\n", __LINE__, fdata);

  if (tree_init(&tree[0], "", 100))
  {
    return errno;
  }

  printf("%i:: TREE [%X]" "\n", __LINE__, tree);
  size_t buf_size = 1;
  tree_read(&fdata, flen, tree, fdata);
  printf("%i:: Working" "\n", __LINE__);
  printf("%i:: tree[%d]{%zu}, tree[%d]{%zu}" "\n", __LINE__, 0, &tree[0], 1, &tree[1]);
  /** tree_add(&tree[6], &tree[5], &tree[5].left, content[10], strlen(content[10])); */
  printf("%i:: Working" "\n", __LINE__);

  FILE* fwr = fopen("TEST", "w");

  tree_visit(&tree[0], tree_write, PreOrder, 30, fwr);
  printf("%i:: Wow" "\n", __LINE__);

  fclose(fout);
  fclose(fwr);

  return 0;
}
