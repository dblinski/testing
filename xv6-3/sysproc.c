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

// return how much memory the current process is using
// also display the # of pages available and writable
int
sys_memusage(void)
{
  int countP = 0, countW = 0, countU = 0;
  uint i = 0;
  for(i = 0; i < proc->sz; i += PGSIZE){
      uint tmp = V2P(proc->pgdir[i]);
      if(tmp & PTE_P){
          countP++;
      }
      if(tmp & PTE_W){
          countW++;
      }
      if(tmp & PTE_U){
          countU++;
      }
  }
  cprintf("Number of pages: %d = %d bytes\n", countP, (countP * PGSIZE));
  cprintf("Number of writable pages: %d\n", countW);
  cprintf("Number of accessible pages: %d\n", countU);

  return 1;
}