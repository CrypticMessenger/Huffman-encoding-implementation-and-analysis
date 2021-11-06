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

void swap(struct leaf_node **ptr1, struct leaf_node **ptr2)
{
    struct leaf_node *temp = *ptr1;
    temp = (*ptr1);
    (*ptr1) = (*ptr2);
    (*ptr2) = temp;
}

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

    // for (int i = 0; i < 128; i++)ṇ
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
    printf("----------------------x---------------------------\n");
    heap = sort_heap(heap);
    int heap_size = 0;
    for (int i = 0; i < 128; i++)
    {
        if (heap[i] != NULL)
        {
            printf("%c: % d\n", heap[i]->alpha, heap[i]->freq);
            heap_size++;
        }
    }
    int temp_size = heap_size;

    while (temp_size > 0)
    {
        struct leaf_node *temp1 = make_leaf(heap[0]->alpha, heap[0]->freq);
        struct leaf_node *temp2 = make_leaf(heap[1]->alpha, heap[1]->freq);
        //!check if there is a need to make 2 new nodes
        struct leaf_node *temp3 = make_leaf(' ', heap[0]->freq + heap[1]->freq);
        temp3->left = temp1;
        temp3->right = temp2;
        // free(heap[0]);
        // free(heap[1]);
        heap[0] = NULL;
        heap[1] = NULL;
        heap[heap_size] = temp3;
        struct leaf_node *ptr;
        for(int i=2;i<heap_size+1;++i)
        {   
            ptr=heap[i];
            heap[i]=heap[i-2];
            heap[i-2]=ptr;
        }
        heap_size--;
        heap = sort_heap(heap);
        temp_size--;
    }
    printf("%d",heap_size);
    fclose(fptr);

    return 0;
}