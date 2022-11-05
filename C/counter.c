#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

struct closure_env_1_arg_1 {
    void **env;
    long (*f_ptr)(void*);
};

struct closure_env_1_arg_2 {
    void **env;
    long (*f_ptr)(void*, void*);
};

struct closure_env_0_arg_3 {
    void **env;
    long (*f_ptr)(void*, void*, void*);
};

long put_handler(long n, void** env) {
    long *s = (long*)env[0];
    *s = n;
    return 0;
}

long get_handler(void** env) {
    long *s = (long*)env[0];
    return *s;
}

long state(long init, struct closure_env_0_arg_3* f) {
    long s = init;

    void* put_handler_env[1] = {(void*)&s};
    struct closure_env_1_arg_2 put_handler_closure = {&put_handler_env, &put_handler};

    void* get_handler_env[1] = {(void*)&s};
    struct closure_env_1_arg_1 get_handler_closure = {&get_handler_env, &get_handler};

    return f->f_ptr(&put_handler_closure, &get_handler_closure, (void*)s);
}

long counter(struct closure_env_1_arg_2* l_put, struct closure_env_1_arg_1* l_get, long c) {
    long i = l_get->f_ptr(l_get->env);
    if (i == 0) {
        return c; 
    } else {
        l_put->f_ptr((void*)i-1, l_put->env);
        return counter(l_put, l_get, c+1);
    }
}

int main() {
    struct closure_env_0_arg_3 counter_closure = {NULL, &counter};

    long ret = state(10, &counter_closure);
    printf("%ld\n", ret);
}