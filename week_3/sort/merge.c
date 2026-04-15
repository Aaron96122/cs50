#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// here we define a random list to check the selection sort algorithm
int number[] = {3, 9, 22, 1, 90, 23, 54, 6, 2};

// here we define a tree
typedef struct node
{
    int *value;
    int len;
    struct node *left;
    struct node *right;
} Tree;

// here we include all the needed prototypes
int get_length(int *numbers);
void subsplit(Tree *input);
void print_tree(Tree *node, int depth);
void merge(Tree *node);

int main(void)
{
    Tree example;
    example.value = number;
    example.len = get_length(number);
    subsplit(&example);
    // print_tree(&example, 0);
    merge(&example);
    print_tree(&example, 0);
}

int get_length(int *numbers)
{
    int i = 0;
    while (numbers[i])
    {
        i++;
    }
    return i;
}

// here we construct the tree of binary split for merge
void subsplit(Tree *input)
{
    int *numbers = input->value;
    int length = get_length(numbers);
    if (length == 1)
    {
        return;
    }

    int l_length = length / 2;
    int r_length = length - l_length;

    // here we construct the left
    int i;
    int *left = malloc(l_length * sizeof(int));
    for (i = 0; i < l_length; i++)
    {
         left[i] = numbers[i];
    }
    struct node *left_node = malloc(sizeof(Tree));
    left_node->value = left;
    left_node->len = l_length;
    input->left = left_node;
    subsplit(left_node);

    // here we construct the right
    int j;
    int *right = malloc(r_length * sizeof(int));
    for (j = 0; j < r_length; j++)
    {
        right[j] = numbers[j + l_length];
    }
    struct node *right_node = malloc(sizeof(Tree));
    right_node->value = right;
    right_node->len = r_length;
    input->right = right_node;
    subsplit(right_node);

    return;
}

// here we do the merge sort
void merge(Tree *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->left == NULL && node->right == NULL)
    {
        return;
    }
    merge(node->left);
    merge(node->right);

    int i = 0;
    int j;
    int l_p = 0;
    int r_p = 0;
    int *merge = malloc(sizeof(int));
    // printf("Length of the node: %i\n", node->len);

    while (i < node->len)
    {
        if (l_p < node->left->len && r_p < node->right->len)
        {
            if (node->left->value[l_p] < node->right->value[r_p])
            {
                merge[i] = node->left->value[l_p];
                l_p++;
                // printf("Left merge value: %i; Left index: %i", merge[i], l_p);
                // printf("\n");
            }
            else
            {
                merge[i] = node->right->value[r_p];
                r_p++;
                // printf("Right merge value: %i; Right index: %i", merge[i], r_p);
                // printf("\n");
            }
        }
        else if(r_p == node->right->len && l_p < node->left->len)
        {
            merge[i] = node->left->value[l_p];
            l_p++;
            // printf("Left remain value: %i; Left index: %i", merge[i], l_p);
            // printf("\n");
        }
        else if (l_p == node->left->len && r_p < node->right->len)
        {
            merge[i] = node->right->value[r_p];
            r_p++;
            // printf("Right remain value: %i; Right index: %i", merge[i], r_p);
            // printf("\n");
        }
        i++;
    }
    // for (int m = 0; m < i; m++)
    // {
    //     printf("%i", merge[m]);
    // }
    // printf("--------------\n");
    node->value = merge;
    node->left = NULL;
    node->right = NULL;
    node->len = i;
    return;
}

// here we check whether the tree is correctly constructed
void print_tree(Tree *node, int depth)
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < depth; i++)
    {
        printf("  ");
    }

    printf("[");
    for (int i = 0; i < node->len; i++)
    {
        printf("%d", node->value[i]);
        if (i < node->len - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");

    print_tree(node->left, depth + 1);
    print_tree(node->right, depth + 1);
}
