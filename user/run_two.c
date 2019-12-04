#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("run_two expects 3 arguments\n");
    exit(0);
  }
  if (fork() == 0) {
    exec(argv[2], argv+2);
  }
  argv[2] = 0;
  exec(argv[1], argv+1);
  exit(0);
}
