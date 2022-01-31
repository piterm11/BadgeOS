#include "../headers/threads.h"

void threads_install()
{
    threads_controller.no_active_threads = 0;
    threads_controller.thread_id = 0;
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads_controller.thread[i].state = TERMINATED;
        if (i == THREAD_COUNT - 1)
            threads_controller.thread[i].next_thread_id = 0;
        else
            threads_controller.thread[i].next_thread_id = i + 1;
    }
}


int start_thread(uint32_t funp, const char *name)
{
    uint32_t temp = -1;
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        if (threads_controller.thread[i].state == TERMINATED)
        {
            temp= i;
            break;
        }
    }
    if (temp == -1)
        print("Threads list is full!\n");
    else
        create_thread(&threads_controller.thread[temp], threads_controller.stacks[temp], funp, name, temp);
    return temp;
}

void create_thread(struct thread_t *new_thread, uint32_t *stack, uint32_t task_addr, const char *name, uint32_t id)
{
    new_thread->stack = (uint32_t)stack;
    new_thread->esp = new_thread->stack + THREAD_STACK_SIZE;
    new_thread->task = task_addr;
    memset(new_thread->thread_name, 0, THREAD_NAME_SIZE);
    memcpy(new_thread->thread_name, name, strlen(name) + 1);
    new_thread->id = id;
    new_thread->state = WAITING;
    push_thread32(new_thread, (uint32_t)kill_thread);
    if (id == threads_controller.no_active_threads)
        threads_controller.thread[id].next_thread_id = 0;
    else
        threads_controller.thread[id].next_thread_id = id + 1;
    if (threads_controller.no_active_threads > 0)
    {
        threads_controller.thread[id - 1].next_thread_id = id;
    }
    threads_controller.no_active_threads++;
}
void kill_thread()
{
    threads_controller.thread[threads_controller.thread_id].state = TERMINATED;
    while (1)
        __asm__("nop");
}
void switch_thread(struct thread_t *current, struct thread_t *next)
{
    __asm__ __volatile__("cli");
    if (next->state == WAITING)
    {
        next->state = SLEEPING;
        switch_stacks_and_jump((uint32_t)current, (uint32_t)next);
    }
    else if (next->state == SLEEPING || RUNNING)
    {
        current->state = SLEEPING;
        next->state = RUNNING;
        switch_stacks((uint32_t)current, (uint32_t)next);
    }
    __asm__ __volatile__("sti");
}

void display_all_threads()
{
    for (unsigned i = 0;i< THREAD_COUNT;i++)
    {
        print("id: %d\tNAME: %s\t\tSTATUS: ", threads_controller.thread[i].id, (strlen(threads_controller.thread[i].thread_name)==0)?"\t":threads_controller.thread[i].thread_name);
        switch (threads_controller.thread[i].state)
        {
        case RUNNING:
            print_ln("RUNNING");
            break;
        case WAITING:
            print_ln("WAITING");
            break;
        case SLEEPING:
            print_ln("SLEEPING");
            break;
        case TERMINATED:
            print_ln("TERMINATED");
            break;
        }
    }
}

void display_threads()
{
    for (unsigned i = 0;; i = threads_controller.thread[i].next_thread_id)
    {
        print("id: %d\tNAME: %s\t\tSTATUS: ", threads_controller.thread[i].id, threads_controller.thread[i].thread_name);
        switch (threads_controller.thread[i].state)
        {
        case RUNNING:
            print_ln("RUNNING");
            break;
        case WAITING:
            print_ln("WAITING");
            break;
        case SLEEPING:
            print_ln("SLEEPING");
            break;
        case TERMINATED:
            print_ln("TERMINATED");
            break;
        }
        if (threads_controller.thread[i].next_thread_id == 0)
            break;
    }
}

static void push_thread8(struct thread_t *t, uint8_t val)
{
    t->esp--;
    uint8_t *addr = (uint8_t *)t->esp;
    *addr = val;
}
static void push_thread32(struct thread_t *t, uint32_t val)
{
    push_thread8(t, (val & 0xFF000000) >> 24);
    push_thread8(t, (val & 0x00FF0000) >> 16);
    push_thread8(t, (val & 0x0000FF00) >> 8);
    push_thread8(t, (val & 0x000000FF) >> 0);
}

void scheduler()
{
    if (threads_controller.no_active_threads > 0)
    {
        __asm__ __volatile__("cli");
        uint32_t temp = threads_controller.thread_id;
        uint32_t temp1 = threads_controller.thread[threads_controller.thread_id].next_thread_id;
        if (threads_controller.thread[temp1].state == TERMINATED)
        {
            threads_controller.thread[temp].next_thread_id = threads_controller.thread[temp1].next_thread_id;
            temp1 = threads_controller.thread[temp1].next_thread_id;
        }
        threads_controller.thread_id = temp1;
        switch_thread(&threads_controller.thread[temp], &threads_controller.thread[temp1]);

    }
}

void mutex_lock(mutex_t *m)
{
    while (!__sync_bool_compare_and_swap(m, 0, 1))
    {
        scheduler();
    }
}
void mutex_unlock(mutex_t *m)
{
    *m = 0;
    scheduler();
}

extern void switch_stacks_and_jump(uint32_t current_thread, uint32_t next_thread);
extern void switch_stacks(uint32_t current_thread, uint32_t next_thread);