#include <stddef.h>

#include "bst.h"

extern void bst_init(struct BstTree * tree, bst_compare_f comparator) {
    tree->root = NULL;
    tree->comparator = comparator;
}

static void bst_node_destroy(struct BstNode * node) {
    if (!node) return;
    bst_node_destroy(node->left);
    bst_node_destroy(node->right);
    bst_free(node);
}

extern void bst_destroy(struct BstTree * tree) {
    bst_node_destroy(tree->root);
}

static struct BstNode * bst_node_create(void * key, void * data) {
    struct BstNode * new_node = bst_malloc(sizeof(struct BstNode));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->key = key;
    new_node->data = data;
    return new_node;
}

extern void bst_set(struct BstTree * tree, void * key, void * value) {
    struct BstNode * node;
    struct BstNode * new_node = bst_node_create(key, value);
    if (!tree->root) {
        tree->root = new_node;
        return;
    }
    node = tree->root;
    while (1) {
        if (tree->comparator(key, node->key) <= 0) {
            if (node->left) 
                node = node->left;
            else {
                node->left = new_node;
                return;
            }
        } else {
            if (node->right) 
                node = node->right;
            else {
                node->right = new_node;
                return;
            }
        }
    }
}

extern void * bst_get(struct BstTree * tree, void * key) {
    struct BstNode * node;
    char c;
    if (!tree->root) return NULL;
    node = tree->root;
    while (node) {
        c = tree->comparator(key, node->key);
             if (c < 0) node = node->left;
        else if (0 < c) node = node->right;
        else            return node->data;
    }
    return NULL;
}

static void bst_node_delete(struct BstNode ** node) {
    struct BstNode * n = *node;
    struct BstNode * x;
    struct BstNode * y;
    if (!n->left) *node = n->right;
    else if (!n->right) *node = n->left;
    else if (!n->left->right) {
        n->left->right = n->right;
        *node = n->left;
    } else {
        y = n->right;
        x = n->left->right;
        while (x->right) y = x, x = x->right;
        y->right = x->left;
        x->left = n->left;
        x->right = n->right;
        *node = x;
    }
    bst_free(n);
}

extern void bst_delete(struct BstTree * tree, void * key) {
    struct BstNode * node = tree->root;
    struct BstNode * p;
    char c;
    if (!node) return;
    c = tree->comparator(key, node->key);
         if (c < 0) node = node->left;
    else if (0 < c) node = node->right;
    else {
        bst_node_delete(&tree->root);
        return;
    }
    p = tree->root;
    while (node) {
        c = tree->comparator(key, node->key);
             if (c < 0) p = node, node = node->left;
        else if (0 < c) p = node, node = node->right;
        else {
            bst_node_delete(p->left == node ? &p->left : &p->right);
            return;
        }
    }
}

static bst_traverse_f bst_traverser;

static void bst_node_traverse(struct BstNode * node) {
    if (!node) return;
    bst_node_traverse(node->left);
    bst_traverser(node->key, node->data);
    bst_node_traverse(node->right);
}

extern void bst_traverse(struct BstTree * tree, bst_traverse_f traverser) {
    bst_traverser = traverser;
    bst_node_traverse(tree->root);
}
