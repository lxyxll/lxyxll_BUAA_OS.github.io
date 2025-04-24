#include <env.h>
#include <pmap.h>
#include <printk.h>

/* Overview:
 *   Implement a round-robin scheduling to select a runnable env and schedule it using 'env_run'.
 *
 * Post-Condition:
 *   If 'yield' is set (non-zero), 'curenv' should not be scheduled again unless it is the only
 *   runnable env.
 *
 * Hints:
 *   1. The variable 'count' used for counting slices should be defined as 'static'.
 *   2. Use variable 'env_sched_list', which contains and only contains all runnable envs.
 *   3. You shouldn't use any 'return' statement because this function is 'noreturn'.
 */
void schedule(int yield) {
static int clock = -1; // 当前时间片，从 0 开始计数
	clock++;

	/* (1) 遍历 env_edf_sched_list，如果进程进入了新的运行周期（可通过 clock == env_period_deadline 判断），则更新 env_period_deadline，并将 env_runtime_left 设置为 env_edf_runtime。 */
	/* 在此实现你的代码 */
	struct Env *env; // 循环变量

LIST_FOREACH (env, &env_edf_sched_list, env_edf_sched_link) {
	if (clock == env->env_period_deadline){
		env->env_period_deadline = env->env_edf_runtime + clock;
		env->env_runtime_left = env->env_edf_runtime;
	}
}

	/* (2) 遍历 env_edf_sched_list，选取 env_runtime_left 大于 0 且 env_period_deadline 最小的进程调度（若相同，则选择 env_id 最小的进程）。如果不存在这样的进程，则不进行调度。 */
	/* 在此实现你的代码 */
struct Env *env2; // 循环变量
int min = 10000;
struct Env *chosed;
int flag = 0;
LIST_FOREACH (env2, &env_edf_sched_list, env_edf_sched_link) {
	if (env2->env_runtime_left > 0 && env2->env_period_deadline < min){
         min = env2->env_period_deadline;
	 chosed = env2;
	 flag = 1;
}
else if (env2->env_runtime_left > 0 && env2->env_period_deadline == min)
{
       if (env2->env_id < chosed->env_id){
	       chosed = env2;
       }
}
}
if (flag == 1){
	env_run(chosed);
}
	/* (3) 使用课下实现的 RR 算法调度 env_sched_list 中的进程。 */
        static int count = 0; // remaining time slices of current env
	struct Env *e = lastRR;

	/* We always decrease the 'count' by 1.
	 *
	 * If 'yield' is set, or 'count' has been decreased to 0, or 'e' (previous 'curenv') is
	 * 'NULL', or 'e' is not runnable, then we pick up a new env from 'env_sched_list' (list of
	 * all runnable envs), set 'count' to its priority, and schedule it with 'env_run'. **Panic
	 * if that list is empty**.
	 *
	 * (Note that if 'e' is still a runnable env, we should move it to the tail of
	 * 'env_sched_list' before picking up another env from its head, or we will schedule the
	 * head env repeatedly.)
	 *
	 * Otherwise, we simply schedule 'e' again.
	 *
	 * You may want to use macros below:
	 *   'TAILQ_FIRST', 'TAILQ_REMOVE', 'TAILQ_INSERT_TAIL'
	 */
	/* Exercise 3.12: Your code here. */
    if (yield || count <= 0 || e == NULL || e->env_status != ENV_RUNNABLE) {
		if (e != NULL && e->env_status == ENV_RUNNABLE) {
			TAILQ_REMOVE(&env_sched_list, e, env_sched_link);
			TAILQ_INSERT_TAIL(&env_sched_list, e, env_sched_link);
		}
		if (TAILQ_EMPTY(&env_sched_list)) {
			panic("schedule: no runnable envs");
		}
		e = TAILQ_FIRST(&env_sched_list);
		count = e->env_pri;
	}
	count--;
	lastRR = e;//record lastRR
	env_run(e);
}
