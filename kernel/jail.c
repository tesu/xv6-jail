#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
#include "jail.h"

struct jail jail[NJAIL];

int
jailcfg(int jid, uint64 memlim, uint64 disklim, uint64 inodelim) {
  // TODO: add bounds checking...
  if (0) { // if bounds check failed
    return -1;
  }
  struct jail *j = jail + jid;
  j->memlim = memlim;
  j->disklim = disklim;
  j->inodelim = inodelim; 
  return 0;
}


void
lsjails(void)
{
  struct jail *j;
  int i = 0;
  printf("\nlsjails:\n");
  for(j = jail; j < &jail[NJAIL]; j++, i++){
    printf("jail %d:\nmemory\t: %p/%p\ndisk\t: %p/%p\ninodes\t: %p/%p\n", i, j->memusage, j->memlim, j->diskusage, j->disklim, j->inodeusage, j->inodelim);
  }
}

void
setjail(int jid)
{
  struct proc *p = myproc();
  p->jail = jail+jid;
  //p->cwd = idup(p->jail->rootdir);

}

void jailinit(void) // create root directory for each jail
{
  struct jail *j;
  struct inode *ip;
  int i = 0;
  char path[9] = "/jdir/xx";
  path[5] = '\0';
  if ((ip = mkdir(path)) == 0) panic("jailinit: mkdir /jail");
  path[8] = '\0';
  for (j = jail; j < (jail + NJAIL); j++, i++) {
    path[6] = '0' + i / 10;
    path[7] = '0' + i % 10;
    if ((ip = mkdir(path)) == 0) panic("jailinit: mkdir");
    if (jail == j)
    j->rootdir = ip;
  }
}