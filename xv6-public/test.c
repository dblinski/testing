#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
  //printf(1, "firstname_lastname_studentid");
  printf(1, "Initial calls\n");
  totalcalls();
  if(fork() == 0){
    printf(1, "testing fork\n");
  }
  else{
    wait();
    printf(1, "wait\n");
  }
  printf(1, "Final calls\n");
  totalcalls();
  exit();
}
