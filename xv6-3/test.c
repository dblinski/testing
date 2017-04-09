#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
  printf(1, "testing system call\n");
  memusage();
  void *i = malloc(4096);
  printf(1, "testing again\n");
  memusage();
  free(i);
  exit();
}
