#ifndef BSTREE_H_
#define BSTREE_H_


typedef struct bsTreeNode {
    int val;
    struct bsTreeNode *lchild;
    struct bsTreeNode *rchild;
} bsTreeNode;

// callback function
typedef void nodeProc(const bsTreeNode *node);

bsTreeNode *bsTreeAdd(bsTreeNode *root, int val);
bsTreeNode *bsTreeDel(bsTreeNode *root, int val);
bsTreeNode *bsTreeFind(bsTreeNode *root, int val);
bsTreeNode *bsTreeFindMax(bsTreeNode *root);
bsTreeNode *bsTreeFindMin(bsTreeNode *root);

// traversals
void bsTreeProdTvs(bsTreeNode *root, nodeProc *proc); // preoder traversal
void bsTreeInodTvs(bsTreeNode *root, nodeProc *proc); // inoder traversal
void bsTreePsodTvs(bsTreeNode *root, nodeProc *proc); // postoder traversal

void bsTreeLevelTvs(bsTreeNode *root, nodeProc *proc); // postoder traversal
// Recursion
bsTreeNode *bsTreeRecFindMax(bsTreeNode *root);
bsTreeNode *bsTreeRecFindMin(bsTreeNode *root);
void bsTreeRecProd(bsTreeNode *root, nodeProc *proc); // preoder traversal
void bsTreeRecInodTvs(bsTreeNode *root, nodeProc *proc); // inoder traversal
void bsTreeRecPsodTvs(bsTreeNode *root, nodeProc *proc); // postoder traversal
#endif // BSTREE_H_
