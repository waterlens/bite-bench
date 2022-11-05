#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

struct closure_env_0_arg_0 {
    void **env;
    long (*f_ptr)(void*);
};

struct closure_env_0_arg_1 {
    void **env;
    long (*f_ptr)(void*);
};

struct closure_env_1_arg_1 {
    void **env;
    long (*f_ptr)(void*);
};

struct closure_env_0_arg_2 {
    void **env;
    long (*f_ptr)(void*, void*);
};

struct tree {
    struct tree *left;
    struct tree *right;
    long value;
};

long tree_filter_size_direct(struct closure_env_0_arg_1* l_yield_tunnel, struct tree *tr, struct closure_env_0_arg_2* f) {
    if (tr == NULL) {
        return 0;
    } else {
        long ls = tree_filter_size_direct(l_yield_tunnel, tr->left, f);
        long rs = tree_filter_size_direct(l_yield_tunnel, tr->right, f);
        long cur = (f->f_ptr(l_yield_tunnel, (void*)tr->value)) ? 1 : 0;
        return ls + rs + cur;
    }
}

long tree_filter_iterate(struct closure_env_0_arg_1* l_yield_tunnel, struct closure_env_1_arg_1* l_yield, struct tree *tr, struct closure_env_0_arg_2* f) {
    if (tr == NULL) {
        return 0;
    } else {
        long ls = tree_filter_iterate(l_yield_tunnel, l_yield, tr->left, f);
        long rs = tree_filter_iterate(l_yield_tunnel, l_yield, tr->right, f);
        if (f->f_ptr(l_yield_tunnel, (void*)tr->value)) {
            l_yield->f_ptr(l_yield->env);
        }
        return 0;
    }
}

long yield_handler_inner(void** env) {
    long *num = (long*)env[0];
    *num = *num + 1;
    return 0;
}

long tree_filter_size_indirect(struct closure_env_0_arg_1* l_yield_tunnel, struct tree *tr, struct closure_env_0_arg_2* f) {
    long num = 0;

    void* yield_handler_inner_env[1] = {(void*)&num};
    struct closure_env_1_arg_1 yield_handler_inner_closure = {&yield_handler_inner_env, &yield_handler_inner};

    tree_filter_iterate(l_yield_tunnel, &yield_handler_inner_closure, tr, f);

    return num;
}

struct tree* generate_tree(long d, long n) {
    if (d == 0) {
        return NULL;
    } else {
        struct tree* lt =  generate_tree(d-1, n-1);
        struct tree* rt =  generate_tree(d-1, n+1);
        struct tree *tr = malloc(sizeof(struct tree));
        *tr = (struct tree){lt, rt, n};
        return tr;
    }
}

long yield_handler_outer(long x) {
    return 0;
}

long f(struct closure_env_0_arg_1* l_yield, long n) {
    l_yield->f_ptr((void*)n);
    return n > 0;
}

int main() {
    struct tree* tree = generate_tree(10, 3);
    struct closure_env_0_arg_1 yield_closure = {NULL, &yield_handler_outer};
    struct closure_env_0_arg_2 f_closure = {NULL, &f};
    long n1 = tree_filter_size_direct(&yield_closure, tree, &f_closure);
    long n2 = tree_filter_size_indirect(&yield_closure, tree, &f_closure);
    printf("%ld\n", n1);
    printf("%ld\n", n2);
}