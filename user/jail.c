#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


// the jail configuration program
void
jail(int jailid, uint64 memlimit, uint64 disklimit, uint64 inodelimit) {
  jailcfg(jailid, memlimit, disklimit, inodelimit);
  return;
}

int
main(int argc, char *argv[])
{
  if(argc < 2) {
    fprintf(2, "Usage: jail jid [memlimit(MB)] [disklimit(MB)] [inodelimit]...\n");
    exit(0);
  }
  // parse the arguments here
  jail(atoi(argv[1]), 10, 10, 20);
  exit(0);
}