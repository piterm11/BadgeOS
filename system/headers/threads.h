#ifndef THREADS_H
#define THREADS_H
#include <stdint.h>
#include "string.h"
#include "print.h"
#include "system.h"


#define THREAD_STACK_SIZE 4096
#define THREAD_COUNT 16

#define THREAD_SWAP 25
#define THREAD_NAME_SIZE 40

enum threads_state_t
{
    WAITING,
    SLEEPING,
    RUNNING,
    TERMINATED
};

struct thread_t
{
    uint32_t esp;
    uint32_t stack;
    uint32_t task;
    uint32_t id;
    uint32_t next_thread_id;
    uint8_t thread_name[THREAD_NAME_SIZE];
    volatile enum threads_state_t state;
};

struct threads_controller_t {
    struct thread_t thread[THREAD_COUNT];
    uint32_t stacks[THREAD_COUNT][THREAD_STACK_SIZE];
    uint8_t no_active_threads;
    uint8_t thread_id;
} threads_controller;

void threads_install();
int start_thread(uint32_t function_pointer, const char *name);
void create_thread(struct thread_t *new_thread, uint32_t *stack, uint32_t task_addr, const char *name, uint32_t id);
void kill_thread();
void switch_thread(struct thread_t *current, struct thread_t *next);

void display_threads();
void display_all_threads();
static void push_thread32(struct thread_t *t, uint32_t val);

void scheduler();

typedef uint8_t mutex_t;
mutex_t m;
void mutex_lock(mutex_t *m);
void mutex_unlock(mutex_t *m);


extern void switch_stacks_and_jump(uint32_t current_thread, uint32_t next_thread);
extern void switch_stacks(uint32_t current_thread, uint32_t next_thread);


#endif 