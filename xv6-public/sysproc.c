#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//return the total number of system calls made since start
int
sys_totalcalls(void)
{
  cprintf("Daniel_Szablinski_A20324724\n");
  char *names[] = {"fork", "exit", "wait", "pipe", "read",
                  "kill", "exec", "fstat", "chdir", "dup",
                  "getpid", "sbrk", "sleep", "uptime",
                  "open", "write", "mknod", "unlink",
                  "link", "mkdir", "close", "totalcalls"};
  int *tmp = proc->count;
  int i;
  for(i = 0; i < 22; i++){
    cprintf("# of %s calls:\t%d\n", names[i], tmp[i]);
  }
  return 1;
}
