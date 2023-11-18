#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 이진 탐색 트리 노드 구조체 정의
struct node
{
    int key;
    double value;
    struct node *lchild;
    struct node *rchild;
};

typedef struct node *treePointer;

// 이진 탐색 트리 삽입 함수
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

// 이진 탐색 트리 노드 수 계산 함수
int count_node(treePointer ptr)
{
    if (ptr == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + count_node(ptr->lchild) + count_node(ptr->rchild);
    }
}

// 이진 탐색 트리 높이(깊이) 계산 함수
int max(int a, int b)
{
    return (a > b) ? a : b;
}

int count_depth(treePointer ptr)
{
    if (ptr == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + max(count_depth(ptr->lchild), count_depth(ptr->rchild));
    }
}

int count_leaf(treePointer ptr)
{
    if (ptr == NULL)
    {
        return 0;
    }
    else if (ptr->lchild == NULL && ptr->rchild == NULL)
    {
        return 1;
    }
    else
    {
        return count_leaf(ptr->lchild) + count_leaf(ptr->rchild);
    }
}

treePointer make_bst(int n)
{
    treePointer root = NULL;
    srand(time(NULL)); // 시드 설정

    for (int i = 0; i < n; ++i)
    {
        int key = (int)((rand() / (double)RAND_MAX) * 100000000); // key 값 생성
        double value = 1.0 / key;                                 // value 값 생성
        root = insert(root, key, value);                          // 노드 추가
    }

    return root;
}

int main()
{
    int n_values[] = {100, 1000, 10000, 100000, 500000, 1000000};
    int num_sizes = sizeof(n_values) / sizeof(n_values[0]);

    for (int i = 0; i < num_sizes; ++i)
    {
        int n = n_values[i];
        printf("n = %d\n", n);

        treePointer tree = make_bst(n);

        int node_count = count_node(tree);
        int depth = count_depth(tree);
        int leaf_count = count_leaf(tree);

        printf("노드 수: %d\n", node_count);
        printf("트리 깊이: %d\n", depth);
        printf("단말 노드 수: %d\n", leaf_count);
        printf("---------------------------------------------------\n");
    }

    return 0;
}
