#include "dsl.hpp"

int main()
{
  char* phormula = "(2+3)*(5+8)+4";

  Node_t* node = (Node_t*)calloc(1, sizeof(*node));
  if (!node)
  {
    errno = ENOMEM;
    perror("node");
    return errno;
  }

  node = parse_by_Add(phormula, phormula + strlen(phormula), &node);

  FILE* fout = fopen("fout", "w");

  write_tree(node, fout);

  fclose(fout);
  return 0;
}
