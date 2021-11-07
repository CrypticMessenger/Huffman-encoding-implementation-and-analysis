#include <iostream>

using namespace std;

//! CONVERT TO C AT LAST
////  Struct start
// TODO: Research about a better alternative of huffman trees and implement it
////T Make huffman tree
struct encoding
{
    char alpha;
    string code;
};

struct leaf_node
{
    char alpha;
    int freq;
    struct leaf_node *left, *right;

    //!
    //string str;

    //!
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

void InorderTrav(struct leaf_node *root)
{
    if (root)
    {
        InorderTrav(root->left);
        printf("%d ", root->freq);
        InorderTrav(root->right);
    }
}

bool is_leaf(struct leaf_node *leaf)
{
    if (leaf->left == NULL && leaf->right == NULL)
    {
        return true;
    }
    return false;
}

int search(char c, struct leaf_node *root)
{
    if (is_leaf(root))
    {
        if(root->alpha == c){
            return 1;
        }
        
    }
    else
    {
        search(c, root->left);
        search(c, root->right);
    }
    return 0;
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
    // for (int i = 0; i < 128; i++)
    // {
    //     if (heap[i] != NULL)
    //     {
    //         printf("%c: % d\n", heap[i]->alpha, heap[i]->freq);
    //     }
    // }

    //printf("----------------------x---------------------------\n");

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

    //printf("%d\n", heap_size);
    int temp_size = heap_size;

    while (temp_size > 1)
    {
        struct leaf_node *temp1 = heap[0];
        struct leaf_node *temp2 = heap[1];

        struct leaf_node *temp3 = make_leaf(0, (heap[0]->freq) + (heap[1]->freq));
        temp3->left = temp1;
        temp3->right = temp2;

        heap[0] = NULL;
        heap[1] = NULL;

        heap[heap_size] = temp3;
        struct leaf_node *ptr;

        for (int i = 2; i < heap_size + 1; ++i)
        {
            ptr = heap[i];
            heap[i] = heap[i - 2];
            heap[i - 2] = ptr;
        }

        heap_size--;
        heap = sort_heap(heap);
        temp_size--;
    }

    //InorderTrav(heap[0]);
    //!

    //!
    printf("%d\n",search('f',heap[0]));
    fclose(fptr);

    return 0;
}