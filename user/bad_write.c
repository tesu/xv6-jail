#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  const int SZ = 256;
  char* s = "a-file";
  char buf[SZ];
  for (int i = 0; i < SZ; i++) buf[SZ] = (char)i;
  for (char c = 'a'; c <= 'z'; c++) {
    s[0] = c;
    int fd = open(s, O_CREATE|O_RDWR);
    if (fd < 0) {
      printf("failed to open %s\n", s);
      exit(1);
    }
    if(write(fd, buf, sizeof(buf)) != sizeof(buf)){
      printf("failed to write to %s\n", s);
      exit(1);
    }
    close(fd);
  }
  printf("successfully finished writing\n");
  exit(0);
}
