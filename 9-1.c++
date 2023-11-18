#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    double value;
    struct node *lchild;
    struct node *rchild;
};

typedef struct node *treePointer;

treePointer modified_search(treePointer tree, int key)
{
    while (tree != NULL && key != tree->key)
    {
        if (key < tree->key)
        {
            tree = tree->lchild;
        }
        else
        {
            tree = tree->rchild;
        }
    }
    return tree;
}

treePointer insert(treePointer tree, int key, double value)
{
    treePointer new_node = (treePointer)malloc(sizeof(struct node));
    new_node->key = key;
    new_node->value = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;

    if (tree == NULL)
    {
        return new_node;
    }

    treePointer current = tree;
    treePointer parent = NULL;

    while (current != NULL)
    {
        parent = current;
        if (key < current->key)
        {
            current = current->lchild;
        }
        else
        {
            current = current->rchild;
        }
    }

    if (key < parent->key)
    {
        parent->lchild = new_node;
    }
    else
    {
        parent->rchild = new_node;
    }

    return tree;
}

void inorderTraversal(treePointer tree)
{
    if (tree != NULL)
    {
        inorderTraversal(tree->lchild);
        printf("(%d, %.2lf) ", tree->key, tree->value);
        inorderTraversal(tree->rchild);
    }
}

int main()
{
    treePointer root = NULL;

    int keys[] = {5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 12, 11};
    double values[] = {10.5, 20.3, 15.8, 7.2, 13.6, 9.1, 25.0, 18.4, 6.7, 11.2, 16.9, 22.7};
    int num_elements = 12;

    for (int i = 0; i < num_elements; ++i)
    {
        root = insert(root, keys[i], values[i]);
    }

    printf("Inorder 순회 결과: ");
    inorderTraversal(root);
    printf("\n");

    int search_key = 7;
    treePointer result = modified_search(root, search_key);
    if (result != NULL)
    {
        printf("key 값 %d에 대한 검색 결과: (%d, %.2lf)\n", search_key, result->key, result->value);
    }
    else
    {
        printf("key 값 %d는 트리 안에 존재하지 않습니다.\n", search_key);
    }

    return 0;
}
