#ifndef __AVLTREE_H
#define __AVLTREE_H

typedef struct avlTreeNode {
    int val;
    int height;
    struct avlTreeNode *lchild;
    struct avlTreeNode *rchild;
} avlTreeNode;

typedef avlTreeNode avlTree;

#endif /* __AVLTREE_H */
