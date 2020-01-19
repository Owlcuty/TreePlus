#include "tree.hpp"

int main()
{
  FILE* fdata = fopen("outdata", "r");
  if (!fdata)
  {
    errno = ENOENT;
    perror("fdata(read 'fout.out')");
    return errno;
  }

  fseek(fdata, 0, SEEK_END);
  int flen = ftell(fdata);
  fseek(fdata, 0, SEEK_SET);

  char* data = (char*)calloc(flen + 1, 1);

  fread(data, 1, flen, fdata);
  data[flen] = '\0';

  Node_t* node = create_node(NULL, 255);

  tree_read(data, flen, node, data);

  akinator(node);

  fclose(fdata);

  FILE* fout = fopen("outdata", "w");

  // tree_visit(node, tree_write, PreOrder, 30, fout);
  write_tree(node, fout);

  fclose(fout);
}
