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

treePointer search(treePointer tree, int key, int *count)
{
    *count = 1;
    while (tree != NULL)
    {
        if (key == tree->key)
        {
            return tree;
        }
        else if (key < tree->key)
        {
            tree = tree->lchild;
        }
        else
        {
            tree = tree->rchild;
        }
        (*count)++;
    }
    return NULL;
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
        printf("(%d, %.6lf) ", tree->key, tree->value);
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

    int input_key;
    treePointer result;
    int count;

    while (1)
    {
        printf("찾고자 하는 key 값을 입력하세요. (-1을 입력하면 종료): ");
        scanf("%d", &input_key);

        if (input_key == -1)
        {
            break;
        }

        result = search(root, input_key, &count);

        if (result != NULL)
        {
            printf("count : %d, key: %d의 value: %.6lf\n", count, result->key, result->value);
        }
        else
        {
            printf("key: %d 노드가 없습니다.\n", input_key);
        }
    }

    return 0;
}
