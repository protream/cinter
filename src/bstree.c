#define TEST
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "bstree.h"

// --------------------------- Recursion -------------------------------

// Add a value to the root, do nothing when out of memory.
bsTreeNode *bsTreeAdd(bsTreeNode *root, int val)
{
    if (!root) {
        if ((root= malloc(sizeof(*root))) == NULL)
            return root;
        root->val = val;
        root->lchild = root->rchild = NULL;
    } else if (val < root->val) {
        root->lchild = bsTreeAdd(root->lchild, val);
    } else if (val > root->val) {
        root->rchild = bsTreeAdd(root->rchild, val);
    }
    return root;
}

// Delete given value's node in the root, if not exists, do nothing.
bsTreeNode *bsTreeDel(bsTreeNode *root, int val)
{
    bsTreeNode *node;

    if (!root)
        return root;
    if (val < root->lchild->val)
        root->lchild = bsTreeDel(root, val);
    if (val > root->rchild->val)
        root->rchild = bsTreeDel(root, val);
    if (root->lchild && root->rchild) {
        node = bsTreeRecFindMin(root->rchild);
        root->val = node->val;
        root->rchild = bsTreeDel(root->rchild, root->val);
    } else {
        node = root;
        if (!root->lchild)
            root = root->rchild;
        if (!root->rchild)
            root = root->lchild;
        free(node);
    }
    return root;
}

// Find the value in root, return a pointer to the node if exists.
bsTreeNode *bsTreeFind(bsTreeNode *root, int val)
{
    if (!root)
        return NULL;
    if (val < root->val)
        return bsTreeFind(root->lchild, val);
    if (val > root->val)
        return bsTreeFind(root->rchild, val);
    return root;
}

// Find the max value in root, return a pointer to the node.
bsTreeNode *bsTreeRecFindMax(bsTreeNode *root)
{
    if (!root)
        return NULL;
    if (!root->rchild)
        return root;
    return bsTreeRecFindMax(root->rchild);
}

// Find the min value in root, return a pointer to the node.
bsTreeNode *bsTreeRecFindMin(bsTreeNode *root)
{
    if (!root)
        return NULL;
    if (!root->lchild)
        return root;
    return bsTreeRecFindMin(root->lchild);
}

void bsTreeRecProdTvs(bsTreeNode *root, nodeProc *proc)
{
    if (!root)
        return;
    proc(root);
    bsTreeRecProdTvs(root->lchild, proc);
    bsTreeRecProdTvs(root->rchild, proc);
}

void bsTreeRecInodTvs(bsTreeNode *root, nodeProc *proc)
{
    if (!root)
        return;
    bsTreeRecInodTvs(root->lchild, proc);
    proc(root);
    bsTreeRecInodTvs(root->rchild, proc);
}

void bsTreeRecPsodTvs(bsTreeNode *root, nodeProc *proc)
{
    if (!root)
        return;
    bsTreeRecPsodTvs(root->lchild, proc);
    bsTreeRecPsodTvs(root->rchild, proc);
    proc(root);
}

// -------------------------- Non-recursion ----------------------------

bsTreeNode *bsTreeFindMin(bsTreeNode *root)
{
    bsTreeNode *min = NULL;

    while (root) {
        min = root;
        root = root->lchild;
    }
    return min;
}

bsTreeNode *bsTreeFindMax(bsTreeNode *root)
{
    bsTreeNode *max = NULL;

    while (root) {
        max = root;
        root = root->rchild;
    }
    return max;
}

void bsTreeProdTvs(bsTreeNode *root, nodeProc *proc)
{
    stack *s = stackCreate();

    while (s->size || root) {
        if (root) {
            proc(root);
            stackPush(s, root);
            root = root->lchild;
        } else {
            root = stackPop(s);
            root = root->rchild;
        }
    }
}

void bsTreeProdTvs2(bsTreeNode *root, nodeProc *proc)
{
    if (root)  {
        stack *s = stackCreate();

        stackPush(s, root);
        while (s->size) {
            root = stackPop(s);
            proc(root);
            if (root->rchild) stackPush(s, root->rchild);
            if (root->lchild) stackPush(s, root->lchild);
        }
    }
}

void bsTreeInodTvs(bsTreeNode *root, nodeProc *proc)
{

    stack *s= stackCreate();

    while (s->size || root) {
        if (root) {
            stackPush(s, root);
            root = root->lchild;
        } else {
            root = stackPop(s);
            proc(root);
            root = root->rchild;
        }
    }
}

// r = s = []
//
// while len(s) or root:
//     if root:
//         s.append(root)
//         r.insert(0, root.val)
//         root = root.right
//     else:
//        root = s.pop().left
// return r
//
//           4
//         /   \
//        2     7
//       / \   / \
//      1   3 6   9
//
//           4
//         /   \
//        7     2
//       / \   / \
//      9   6 3   1
//
//
// balanced binary tree
//
// maximum path num
//
// maximum depth os binary tree
// minimun ...
//
// all paths
//
void bsTreePsodTvs(bsTreeNode *root, nodeProc *proc)
{
    stack *s = stackCreate();
    stack *r = stackCreate();

    while (s->size || root) {
        if (root) {
            stackPush(s, root);
            stackPush(r, root);
            root = root->rchild;
        } else {
            root = stackPop(s);
            root = root->lchild;
        }
    }
    while(r->size) proc(stackPop(r));
}

void bsTreeLevelTvs(bsTreeNode *root, nodeProc *proc)
{
    queue *q = queueCreate();

    if (root) queuePush(q, root);

    while (q->len) {
        bsTreeNode *p = queueFront(q);
        queuePop(q);
        proc(p);
        if (p->lchild) queuePush(q, p->lchild);
        if (p->rchild) queuePush(q, p->rchild);
    }
}

int bsTreeMaxDepth(bsTreeNode *root)
{
    int maxDepth = 0;
    stack *s = stackCreate();

    while (s->size || root) {
        if (root) {
            stackPush(s, root);
            root = root->lchild;
        } else {
            root = stackPop(s);
            if (!root->lchild && !root->rchild) {
                if ((int)s->size > maxDepth || maxDepth == 0) {
                    maxDepth = s->size;
                }
            }
            root = root->rchild;
        }
    }
    free(s);
    return maxDepth;
}

int bsTreeMinDepth(bsTreeNode *root)
{
    int minDepth = 0;
    stack *s = stackCreate();

    while (s->size || root) {
        if (root) {
            stackPush(s, root);
            root = root->lchild;
        } else {
            root = stackPop(s);
            if (!root->lchild && !root->rchild) {
                if (minDepth == 0 || (int)s->size < minDepth) {
                    minDepth = s->size;
                }
            }
            root = root->rchild;
        }
    }
    free(s);
    return minDepth;
}

int bsTreeIsBalanced(bsTreeNode *root)
{
    return (bsTreeMaxDepth(root) - bsTreeMinDepth(root) <= 1 ? 1 : 0);
}

// This is auctually work for binary tree.
int bsTreeSmallestLeaf(bsTreeNode *root)
{
    int smallest = 0;
    stack *s = stackCreate();

    while (s->size || root) {
        if (root) {
            stackPush(s, root);
            root = root->lchild;
        } else {
            root = stackPop(s);
            if (!root->lchild && !root->rchild) {
                if (root->val < smallest || smallest == 0) {
                    smallest = root->val;
                }
            }
            root = root->rchild;
        }
    }
    return smallest;
}

int bsTreeLargestLeaf(bsTreeNode *root)
{
    int largest = 0;
    stack *s = stackCreate();

    while (s->size || root) {
        if (root) {
            stackPush(s, root);
            root = root->lchild;
        } else {
            root = stackPop(s);
            if (!root->lchild && !root->rchild) {
                if (root->val > largest || largest == 0) {
                    largest = root->val;
                }
            }
            root = root->rchild;
        }
    }
    return largest;
}

// assert: 1 <= k <= bst.size
int bsTreeKthSmallest(bsTreeNode *root, int k)
{
    bsTreeNode *node;
    stack *s = stackCreate();

    while (k && (s->size || root)) {
        if (root) {
            stackPush(s, root);
            root = root->lchild;
        } else {
            node = stackPop(s);
            k--;
            root = node->rchild;
        }
    }
    return node->val;
}

// assert: root.size >= 1
// assert: 1 <= k <= bst.size
int bsTreeKthLargest(bsTreeNode *root, int k)
{
    bsTreeNode *node;
    stack *s = stackCreate();

    while (k && (s->size || root)) {
        if (root) {
            stackPush(s, root);
            root = root->rchild;
        } else {
            node = stackPop(s);
            k--;
            root = node->lchild;
        }
    }
    return node->val;
}

#ifdef BSTREE_TEST
#include "testhelper.h"

static void printNode(const bsTreeNode *node)
{
    printf("%d ", node->val);
}

void bsTreeTest(void)
{
    bsTreeNode *root = NULL;
    bsTreeNode *node;

    //           6
    //          / \
    //         2   8
    //        / \ /
    //       1  4 7
    //         /
    //        3

    root = bsTreeAdd(root, 6);
    root = bsTreeAdd(root, 2);
    root = bsTreeAdd(root, 8);
    root = bsTreeAdd(root, 1);
    root = bsTreeAdd(root, 4);
    root = bsTreeAdd(root, 3);
    root = bsTreeAdd(root, 7);

    printf("prod:\n");
    bsTreeProdTvs(root, &printNode);
    printf("\n");
    bsTreeProdTvs2(root, &printNode);
    printf("\n\n");

    printf("inod:\n");
    bsTreeInodTvs(root, &printNode);
    printf("\n\n");

    printf("leve:\n");
    bsTreeLevelTvs(root, &printNode);
    printf("\n\n");

    printf("post:\n");
    bsTreePsodTvs(root, &printNode);
    printf("\n\n");

    node = bsTreeRecFindMin(root);
    printf("min: %d\n", node->val);
    node = bsTreeFindMin(root);
    printf("min: %d\n", node->val);

    node = bsTreeRecFindMax(root);
    printf("max: %d\n", node->val);
    node = bsTreeFindMax(root);
    printf("max: %d\n", node->val);

    /*printf("\n");*/
    /*printf("max depth: %d\n", bsTreeMaxDepth(root));*/
    /*printf("min depth: %d\n", bsTreeMinDepth(root));*/
    /*printf("is balanced: %d\n", bsTreeIsBalanced(root));*/
    /*printf("\n\n");*/

    /*root = bsTreeAdd(root, 9);*/
    /*printf("prod:\n");*/
    /*bsTreeProdTvs(root, &printNode);*/
    /*printf("\n\n");*/
    /*printf("max depth: %d\n", bsTreeMaxDepth(root));*/
    /*printf("min depth: %d\n", bsTreeMinDepth(root));*/
    /*printf("is balanced: %d\n", bsTreeIsBalanced(root));*/

    printf("\n\n");
    printf("smallest leaf: %d\n", bsTreeSmallestLeaf(root));
    printf("\n\n");
    printf("largest leaf: %d\n", bsTreeLargestLeaf(root));

    /*printf("\n\n");*
    /*printf("3th smallest: %d\n", bsTreeKthSmallest(root, 3));*/

    /*printf("\n\n");*/
    /*printf("3th largest: %d\n", bsTreeKthLargest(root, 3));*/


}

#ifdef BSTREE_TEST_MAIN
int main(void)
{
    bsTreeTest();
    return 0;
}
#endif
#endif
