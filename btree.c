#include <stdio.h>
#include <assert.h>

//                1
//        2               3
//    4       5       6       7
//  8   9  10   11  12  13  14 15

typedef struct btree_node {
    int val;
} btree_node; 

typedef struct btree {
    int size;
    btree_node* node;
    int (*cmp_fn)(btree_node*, btree_node*);
} btree;

int btree_node_cmp(btree_node* a, btree_node* b)
{
    if (a->val > b->val) {
        return 1;
    } else if (a->val < b->val) {
        return -1;
    } else {
        return 0;
    }
}

void swap_if_greater(btree* tree, btree_node *parent, btree_node *child) {
    if (1 == tree->cmp_fn(parent, child))
    {
        btree_node tmp = *parent;
        *parent = *child;
        *child = tmp;
    }
}

void swap_if_less(btree* tree, btree_node *parent, btree_node *child) {
    if (-1 == tree->cmp_fn(parent, child))
    {
        btree_node tmp = *parent;
        *parent = *child;
        *child = tmp;
    }
}

void heapify(btree* tree, int index, int is_maxheap) {
    assert(tree && index > 0);

    int size = tree->size;
    btree_node *parent = &tree->node[index-1];

    if (2*index <= size) {
        btree_node *left_child = &tree->node[2*index-1];

        if (is_maxheap) {
            swap_if_less(tree, parent, left_child);
        } else {
            swap_if_greater(tree, parent, left_child);
        }

        heapify(tree, 2*index, is_maxheap);
    }
    if (2*index + 1 <= size) {
        btree_node *right_child = &tree->node[2*index];

        if (is_maxheap) {
            swap_if_less(tree, parent, right_child);
        } else {
            swap_if_greater(tree, parent, right_child);
        }

        heapify(tree, 2*index+1, is_maxheap);
    }
    return;
}

void init_max_heap(btree* tree) {
    heapify(tree, 1, 1); // index begin with 1
}

void init_min_heap(btree* tree) {
    heapify(tree, 1, 0); // index begin with 1
}

#if MAIN
void main() {
    btree_node array[16] = {16, 1, 3, 5, 7 , 11, 15, 14, 13, 4, 12, 6, 8, 9, 2, 10};
    btree tree;
    int i;

    tree.size = 16;
    tree.node = &array[0];
    tree.cmp_fn = &btree_node_cmp;

    for(i = 0; i < 16; i++) {
        printf("[%d]: %d\n", i, tree.node[i].val);
    }

    printf("======================\n");

    init_max_heap(&tree);

    for(i = 0; i < 16; i++) {
        printf("[%d]: %d\n", i, tree.node[i].val);
    }
}
#endif
