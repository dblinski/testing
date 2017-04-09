#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

int main(void){
  printf(1, "testing system call - no mallocs used\n");
  memusage();
  void *i = malloc(3999);
  printf(1, "testing again - malloc(3999)\n");
  memusage();
  free(i);
  i = malloc(4020);
  printf(1, "test 3 - malloc(4020)\n");
  memusage();
  void *j = malloc(40000);
  printf(1, "test 4 - malloc40k\n");
  memusage();
  exit();
}
