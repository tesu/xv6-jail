#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  if (argc < 5) {
    fprintf(2, "Usage: jail jid1 exe1 jid2 exe2\n");
    exit(0);
  }
  if (fork() == 0) {
    if (setjail(atoi(argv[3])) < 0) {
      printf("run_two failed.\n");
      exit(-1);
    }
    exec(argv[4], argv+4);
  }
  argv[3] = 0;
  if (setjail(atoi(argv[1])) < 0){
    printf("run_two failed.\n");
    exit(-1);
  }
  exec(argv[2], argv+2);
  exit(0);
}
