#include <env.h>
#include <pmap.h>
#include <printk.h>
#include <trap.h>

extern void handle_int(void);
extern void handle_tlb(void);
extern void handle_sys(void);
extern void handle_mod(void);
extern void handle_reserved(void);

void (*exception_handlers[32])(void) = {
    [0 ... 31] = handle_reserved,
    [0] = handle_int,
    [2 ... 3] = handle_tlb,
#if !defined(LAB) || LAB >= 4
    [1] = handle_mod,
    [8] = handle_sys,
#endif
};

/* Overview:
 *   The fallback handler when an unknown exception code is encountered.
 *   'genex.S' wraps this function in 'handle_reserved'.
 */
void do_reserved(struct Trapframe *tf) {
	print_tf(tf);
	panic("Unknown ExcCode %2d", (tf->cp0_cause >> 2) & 0x1f);
}

// 声明 handle 函数
extern void handle_adel(void);
extern void handle_ades(void);

// exception_handlers 请按以下代码实现
void (*exception_handlers[32])(void) = {
	[0 ... 31] = handle_reserved,
	[0] = handle_int,
	[2 ... 3] = handle_tlb,
	[4] = handle_adel,
	[5] = handle_ades,
#if !defined(LAB) || LAB >= 4
	[1] = handle_mod,
	[8] = handle_sys,
#endif
};

void do_adel(struct Trapframe *tf) {
 	// 在此实现相应操作以使修改后指令符合要求
       u_long va = tf->cp0_badvaddr;
       u_long pdxpa = *((PDX*)curenv->env_pgdir + PDX(va));
       u_long pa =  *((PTE*)pa2page(pdxpa) + PTE(va));
       u_long kaddr = pa2kaddr(pa);
       
}

void do_ades(struct Trapframe *tf) {
 	// 在此实现相应操作以使修改后指令符合要求
}
