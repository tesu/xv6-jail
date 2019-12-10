#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{ 
  if(argc != 2) {
    fprintf(2, "Usage: demojail [jail root]\n");
    exit(0);
  }
  int num_binaries = 10;
  char* binaries[] = {"/cat", "/echo", "/grep", "/kill", "/ls", "/mkdir", "/rm", "/sh", "/usertests", "/busy_print"};
  char old[MAXPATH], new[MAXPATH]; 
  for (int i = 0; i < num_binaries; i++) {
    const char* bin = binaries[i];
    // int len = strlen(bin);
    strcpy(old, bin);
    strcpy(new, argv[1]);
    strcpy(new + strlen(argv[1]), bin);
    link(old, new);
  }
  exit(0);
}
