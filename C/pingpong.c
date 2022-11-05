#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static long longjmp_ret;

struct closure_env_0_arg_1 {
    void **env;
    long (*f_ptr)(void*, void*);
};

struct closure_env_0_arg_2 {
    void **env;
    long (*f_ptr)(void*, void*);
};


long pinger(struct closure_env_0_arg_2*, long i, long n);

long ponger(struct closure_env_0_arg_2*, struct closure_env_0_arg_1*);

long pong_handler(struct closure_env_0_arg_2* l_ping, void **env) {
    long i = (long)env[0];
    long n = (long)env[1];
    return pinger(l_ping, i+1, n);
}

long ping_handler(struct closure_env_0_arg_2* l_ping, struct closure_env_0_arg_1* l_pong) {
    return ponger(l_ping, l_pong);
}

long pinger(struct closure_env_0_arg_2* l_ping, long i, long n) {
    if (!(i < n)) {
        return 0;
    }
    void* pong_handler_env[2] = {(void*)i, (void*)n};
    struct closure_env_0_arg_1 pong_handler_closure = {pong_handler_env, &pong_handler};

    return (long)l_ping->f_ptr(l_ping, &pong_handler_closure);
}

long ponger(struct closure_env_0_arg_2* l_ping, struct closure_env_0_arg_1* l_pong) {
    return (long)l_pong->f_ptr(l_ping, l_pong->env);
}

int main(void) {
    struct closure_env_0_arg_2 ping_handler_closure = {NULL, &ping_handler};

    return pinger(&ping_handler_closure, 0, 10);
}