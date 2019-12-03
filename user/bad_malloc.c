#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  char *m1, *m2;
  m1 = 0;
  while((m2 = malloc(10001)) != 0){
    *(char**)m2 = m1;
    m1 = m2;
  }
  while(m1){
    m2 = *(char**)m1;
    free(m1);
    m1 = m2;
  }
  m1 = malloc(1024*20);
  if(m1 == 0){
    printf("failed to alloc!\n");
    exit(1);
  }
  free(m1);
  printf("successfully allocated\n");
  exit(0);
}
