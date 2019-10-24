struct jail {
  struct spinlock lock;
  
  uint64 memlim; // memory usage limit in bytes
  uint64 memusage; 
  uint64 disklim; 
  uint64 inodelim;  // not sure how to keep track of usage 
};