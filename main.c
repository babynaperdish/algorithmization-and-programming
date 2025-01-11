#define _CRT_SECURE_NO_WARNINGS
#define N 6

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct BT {
    int val;
    int count;
    struct BT* Left;
    struct BT* Right;
    struct BT* Parent;
};
typedef struct BT bt;

bt *createNode(int key) {
    bt *newNode = (bt *)malloc(sizeof(bt));
    if (!newNode) {
        perror("Unable to allocate memory");
        return NULL;
    }
    newNode->val = key;
    newNode->count = 0; // сколько элементов ПОД узлом НЕ считая его самого
    newNode->Left = NULL;
    newNode->Right = NULL;
    newNode->Parent = NULL;
    return newNode;
}

bt *counting(bt *root) {
    if (root == NULL) return NULL;
    if (root->Left == 0 && root->Right == NULL) return root;
    int leftCount = root->Left != NULL ? root->Left->count + 1 : 0;
    int rightCount = root->Right != NULL ? root->Right->count + 1 : 0;
    root->count = leftCount + rightCount;
    return root;
}

bt *updateCount(bt *root) {
    root->count = (root->Left ? root->Left->count + 1: 0) + (root->Right ? root->Right->count + 1: 0); // 1 для текущего узла + узлы слева и справа.
    if (root->Parent != NULL) return updateCount(root->Parent);
    else return root;
}

int cfactor(bt *p) {
    if (p == NULL) return 0;
    return (p->Right ? p->Right->count + 1 : 0) - (p->Left ? p->Left->count + 1: 0);
}

bt *smallLeftRot(bt *root) {
    bt *newRoot = root->Right;
    root->Right = newRoot->Left;
    if (root->Right) root->Right->Parent = root;
    newRoot->Left = root;
    newRoot->Parent = root->Parent;
    root->Parent = newRoot;

    updateCount(root);
    return newRoot;
}

bt *smallRightRot(bt *root) {
    bt *newRoot = root->Left;
    root->Left = newRoot->Right;
    if (root->Left) root->Left->Parent = root;
    newRoot->Right = root;
    newRoot->Parent = root->Parent;
    root->Parent = newRoot;

    updateCount(root);
    return newRoot;
}

bt *bigLeftRot(bt *root) {
    root->Right = smallRightRot(root->Right);
    return smallLeftRot(root);


}

bt *bigRightRot(bt *root) {
    root->Left = smallLeftRot(root->Left);
    return smallRightRot(root);
}


bt *countNode(bt *root) {
    root = counting(root);
    if (cfactor(root) == 2) {
        if (cfactor(root->Right) <= 0){
            root->Right = smallRightRot(root->Right);

        }
        root = smallLeftRot(root);
        root->Left = countNode(root->Left);
        root->Right = countNode(root->Right);
        return root;
    }
    if (cfactor(root) == -2) {
        if (cfactor(root->Left) >= 0) {
            root->Left = smallLeftRot(root->Left);
        }
        root = smallRightRot(root);
        root->Left = countNode(root->Left);
        root->Right = countNode(root->Right);
        return root;
    }
    return root;
}

bt *findKey(bt* root, int key) {
    if (root == NULL) return NULL;
    if (root->val );
}

bt *addElement(bt *root, int key, bt *par) {
    if (root == NULL) {
        root = createNode(key);
        root->Parent = par;
        if (par && key < par->val) par->Left = root;
        else if (par && key > par->val) par->Right = root;
        return root;
    }
    if (key < root->val) {
        root->Left = addElement(root->Left, key, root);
    } else if (key > root->val) {
        root->Right = addElement(root->Right, key, root);
    }
    else return root;
    return countNode(root);
}

void dump3(bt *root, int space) {
    if (root == NULL) return;
    int COUNT = 5;
    space += COUNT;
    dump3(root->Right, space);
    for (int i = COUNT; i < space; ++i) {
        printf("  ");
    }
    printf("%d\n", root->val);
    dump3(root->Left, space);
}

int main(void) {
    srand(time(NULL));
    bt *Root = createNode(2);
    for (int i = 0; i < N; i++){
        int num = rand()%10 + 1;
        printf("Added: %d\n", num);
        Root = addElement(Root, num, NULL);

    }
    printf("Balanced tree:\n");
    dump3(Root, 0);
    return 0;
}

// ЗАДАНИЕ:
// Построить идеально сбалансированное бинарное дерево поиска, для которого количество элементов любых двух поддеревьев
// отличается не больше, чем на 1.