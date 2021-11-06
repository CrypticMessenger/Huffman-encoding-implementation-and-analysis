#include <stdio.h>
#include <stdlib.h>
struct leaf_node
{
    char alpha;
    int freq;
    //*adding extra terms
    struct leaf_node *left, *right;
    //*
};

struct leaf_node *make_leaf(char alpha, int freq)
{
    struct leaf_node *n;
    n = (struct leaf_node *)malloc(sizeof(struct leaf_node));
    n->alpha = alpha;
    n->freq = freq;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int main(){
    struct leaf_node **heap = (struct leaf_node **)calloc(128, sizeof(struct leaf_node *));
    printf("%d\n",heap[0]->freq);
    return 0;
}