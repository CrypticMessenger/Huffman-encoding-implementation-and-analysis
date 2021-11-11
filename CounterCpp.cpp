#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//! CONVERT TO C AT LAST
////  Struct start
// TODO: Research about a better alternative of huffman trees and implement it
////T Make huffman tree

struct encoding
{
    char alpha;
    // string code;
    char code[8];
};

struct encoding **codes = (struct encoding **)calloc(128, sizeof(struct encoding *));

void print_encoding(struct encoding **codes, int total_node)
{
    for (int i = 0; i < total_node; i++)
    {
        // printf(" %c : %s\n", codes[i]->alpha, codes[i]->code);
        cout << codes[i]->alpha << " : " << codes[i]->code << endl;
    }
}

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
        // printf("%d ", root->freq);
        cout << root->freq << " ";
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
//! Change names and algorithms.
int pointer = 0;

void printArr(int arr[], int n, struct leaf_node *root)
{
    int i;
    //string str = "";
    char codde[n];

    for (i = 0; i < n; ++i)
    {
        // printf("%d", arr[i]);
        cout << arr[i];
        // str += std::to_string(arr[i]);
        codde[i] = (char)(arr[i] + 48);
    }
    struct encoding *temp = (struct encoding *)malloc(sizeof(struct encoding));
    temp->alpha = root->alpha;
    // temp->code = str;
    strcpy(temp->code, codde);
    //temp->code=codde;
    codes[pointer] = temp;
    ++pointer;

    cout << endl;
}

void encoder(struct leaf_node *root, int arr[], int top)
{

    if (root->left != NULL)
    {
        arr[top] = 0;
        encoder(root->left, arr, top + 1);
    }
    if (root->right != NULL)
    {
        arr[top] = 1;
        encoder(root->right, arr, top + 1);
    }
    if (is_leaf(root))
    {
        // printf(" %c : ", root->alpha);
        cout << root->alpha << " : ";
        // printf("top : %d ", top);
        // codes[pointer]=make_encoding(root->alpha,arr,top);
        printArr(arr, top, root);
        // cout<<endl;
    }
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
        cout << "Error! opening file" << endl;
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
    int minm = INT_MAX;
    int heap_size = 0;
    for (int i = 0; i < 128; i++)
    {
        if (heap[i] != NULL)
        {
            cout << heap[i]->alpha << " : " << heap[i]->freq << endl;
            minm = min(heap[i]->freq, minm);
            heap_size++;
        }
    }

    int temp_size = heap_size;

    int total_node = heap_size;
    int total_node1 = heap_size;

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

    // InorderTrav(heap[0]);
    //!

    //!
    //printf("%d\n",search('f',heap[0]));

    //TODO: write it in analysis how we calculated height of huffman tree
    struct leaf_node *root = heap[0];

    total_node = ceil(log2((float)(heap[0]->freq) / minm)) - 1;
    // cout<<total_node<<endl;
    int encry[total_node];

    int top = 0;

    encoder(root, encry, top);
    cout << endl;
    print_encoding(codes, total_node1);
    fclose(fptr);

    return 0;
}