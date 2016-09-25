struct BstNode {
    struct BstNode * left;
    struct BstNode * right;
    void * key;
    void * data;
};

typedef int (*bst_compare_f)(void * lhs, void * rhs);
typedef void (*bst_traverse_f)(void * key, void * value);
typedef void * (*bst_malloc_f)(size_t);
typedef void (*bst_free_f)(void *);

struct BstTree {
    struct BstNode * root;
    bst_compare_f comparator;
};

void bst_init(struct BstTree * tree, bst_compare_f comparator);
void bst_destroy(struct BstTree * tree);
void bst_set(struct BstTree * tree, void * key, void * value);
void * bst_get(struct BstTree * tree, void * key);
void bst_delete(struct BstTree * tree, void * key);
void bst_traverse(struct BstTree * tree, bst_traverse_f traverser);

extern bst_malloc_f bst_malloc;
extern bst_free_f bst_free;
