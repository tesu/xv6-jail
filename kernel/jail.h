struct jail {
  struct spinlock lock;
  
  uint64 memlim; // memory usage limit in bytes
  uint64 memusage; 
  uint64 disklim; 
  uint64 diskusage;
  // struct inode *rootdir;
  char rootdir[8];
  uint64 numproc;
  uint64 maxproc; 
};

