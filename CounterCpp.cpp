#include <iostream>

using namespace std;

//! CONVERT TO C AT LAST
////  Struct start
// TODO: Research about a better alternative of huffman trees and implement it
//TODO: Make huffman tree


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

//! here lies node structs if needed
// struct node
// {
//     int data;
//     struct leaf_node *left, *right;
// };
// struct node *make_node(int data)
// {
//     struct node *n;
//     n = (struct node *)malloc(sizeof(struct node));
//     n->left = NULL;
//     n->right = NULL;
//     n->data = data;
//     return n;
// }
//!

struct leaf_node **heap = (struct leaf_node **)calloc(128, sizeof(struct leaf_node *));

struct leaf_node **sort_heap(struct leaf_node **heap)
{
    for (int i = 0; i < 127; ++i)
    {
        for (int j = i + 1; j < 128; ++j)
        {
            if (heap[i] != NULL && heap[j] != NULL && heap[j]->freq < heap[i]->freq)
            {
                struct leaf_node *temp;
                temp = heap[i];
                heap[i] = heap[j];
                heap[j] = temp;
            }
        }
    }
    return heap;
}

int main()
{

    int arr[128];
    for (int i = 0; i < 128; i++)
    {
        arr[i] = 0;
    }
    FILE *fptr;
    char c;
    fptr = fopen("./input.txt", "r");
    if (fptr == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    while ((c = fgetc(fptr)) != EOF)
    {
        arr[int(c)]++;
    }

    // for (int i = 0; i < 128; i++)
    // {
    //     cout << i << " " << arr[i] << " " << endl;
    // }
    struct leaf_node *temp;
    int index = 0;
    for (int i = 0; i < 128; i++)
    {
        if (arr[i] != 0)
        {
            temp = make_leaf(i, arr[i]);
            heap[index] = temp;
            index++;
        }
    }
    for (int i = 0; i < 128; i++)
    {
        if (heap[i] != NULL)
        {
            printf("%c: % d\n", heap[i]->alpha, heap[i]->freq);
        }
    }
    heap = sort_heap(heap);
    for (int i = 0; i < 128; i++)
    {
        if (heap[i] != NULL)
        {
            printf("%c: % d\n", heap[i]->alpha, heap[i]->freq);
        }
    }
    

    fclose(fptr);

    return 0;
}