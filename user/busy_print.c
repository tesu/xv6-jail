#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  printf("pid: %d\n", getpid());
  while (1) {
    printf(".");
    sleep(10);
  }
  exit(0);
}
