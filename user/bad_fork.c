#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  for (int i = 0; i < 4; i++) {
    if (fork() < 0) {
      printf("failed to fork #%d!\n", i+1);
      exit(1);
    }
  }
  // printf("successfully duplicated file descriptors\n");
  exit(0);
}
