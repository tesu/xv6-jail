#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAXARG 16

int
main(int argc, char *argv[])
{
  if(argc < 3) {
    fprintf(2, "Usage: jail jid [executable args]\n");
    exit(0);
  }
  if (setjail(atoi(argv[1])) < 0) {
    printf("rijail failed.\n");
    exit(-1);
  }

  char *new_argv[MAXARG];
  for (int i = 0; i < argc - 2; i++) {
    new_argv[i] = argv[i + 2];
  }
  exec(new_argv[0], new_argv);
  return 0;
}
