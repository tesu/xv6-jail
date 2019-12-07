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
jailcfg(int jid, uint64 memlim, uint64 disklim, uint64 proclim) {
  if (myproc()->jail != 0) { // proc is in jail
    return -1; 
  }
  // TODO: add bounds checking...
  if (0) { // if bounds check failed
    return -1;
  }
  struct jail *j = jail + jid;
  j->memlim = memlim;
  j->disklim = disklim;
  j->maxproc = proclim; // TODO
  return 0;
}


void
lsjails(void)
{
  struct jail *j;
  int i = 0;
  printf("\nlsjails:\n");
  for(j = jail; j < &jail[NJAIL]; j++, i++){
    printf("jail %d:\nmemory\t: %p/%p\ndisk\t: %p/%p\nnumprocs: %d/%d\n", 
          i, j->memusage, j->memlim, j->diskusage, j->disklim, j->numproc, j->maxproc);
  }
}

int
setjail(int jid)
{
  struct proc *p = myproc();
  if (p->jail != 0) { // proc is in jail
    return -1; 
  }

  char rootdir[8] = "/jailXX";
  if (jail[jid].rootdir[0] == 0) {
    rootdir[5] = '0' + ((jid / 10) % 10);
    rootdir[6] = '0' + (jid % 10);
    mkdir(rootdir);
  }

  acquire(&jail[jid].lock);
  if (jail[jid].memusage + p->sz > jail[jid].memlim) {
    release(&jail[jid].lock);
    return -1;
  }
  p->jail = jail+jid;
  p->jail->memusage += p->sz;
  p->jail->numproc++;

  if (p->jail->rootdir[0] == 0) {
    safestrcpy(p->jail->rootdir, rootdir, 8);
    // p->jail->rootdir = ip;
    printf("p %s\n", p->jail->rootdir);
  }

  release(&jail[jid].lock);
  return 0;
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
    if (jail == j) {} 
    // j->rootdir = ip;
  }
}
