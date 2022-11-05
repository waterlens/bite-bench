#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

struct closure_env_0_arg_1 {
    void **env;
    long (*f_ptr)(void*);
};

struct closure_env_0_arg_2 {
    void **env;
    long (*f_ptr)(void*, void*);
};

long log_handler1(char *s) {
    return 0;
}

long log_handler2(char *s) {
    printf("%s\n", s);
    return 0;
}

long call_f(struct closure_env_0_arg_1* l_log, long a, struct closure_env_0_arg_2* f) {
    log_handler2("# before call f()");
    long ret = f->f_ptr(l_log, (void*)a);
    log_handler2("# after call f()");
    return ret;
}

long f(struct closure_env_0_arg_1* l_log, long a) {
    char *s = "# do not print to console";
    return l_log->f_ptr(s);
}

int main() {
    struct closure_env_0_arg_2 f_closure = {NULL, &f};
    struct closure_env_0_arg_1 log_handler_closure = {NULL, &log_handler1};
    call_f(&log_handler_closure, 1, &f_closure);
}