#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define DEFAULT_MLIMIT 64000
#define DEFAULT_DLIMIT 64000
#define DEFAULT_ILIMIT 100

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
  uint64 memlimit   = (argc < 3) ? DEFAULT_MLIMIT : atoi(argv[2]);
  uint64 disklimit  = (argc < 4) ? DEFAULT_DLIMIT : atoi(argv[3]);
  uint64 inodelimit = (argc < 5) ? DEFAULT_ILIMIT : atoi(argv[4]);
  jail(atoi(argv[1]), memlimit, disklimit, inodelimit);
  exit(0);
}
