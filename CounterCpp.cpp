#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//! CONVERT TO C AT LAST
// TODO: Research about a better alternative of huffman trees and implement it



//function to print characters and their corresponsing encodings.
void print_codings(char characters[], string codings[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << characters[i] << " : " << codings[i] << endl;
    }
    cout << endl;
}

//Definition of leaf_node:
struct leaf_node
{
    char alpha;
    int freq;
    struct leaf_node *left, *right;
};

//function to allocate memory to leaf nodes.
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

//
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

// int partition(struct leaf_node **heap,int low,int high)
// {
// int 
// }

// void quickSort(struct leaf_node **heap,int low ,int high)

// {
//     int partitionindex;
//     if(low<high)
//     {
//         partitionindex=partition(heap,low,high);
//         quickSort(heap,low,partitionindex-1);
//         quickSort(heap,partitionindex+1;high);
//     }
// }


void InorderTrav(struct leaf_node *root)
{
    if (root)
    {
        InorderTrav(root->left);
        // printf("%d ", root->freq);
        cout << root->alpha << " : ";
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

void printArr(int arr[], int n, struct leaf_node *root, char characters[], string codings[])
{
    int i;
    string str = "";

    for (i = 0; i < n; ++i)
    {
        cout << arr[i];
        str = str + (char)(arr[i] + 48);
    }
    cout << endl;
    characters[pointer] = root->alpha;
    codings[pointer] = str;
    ++pointer;
}

void encoder(struct leaf_node *root, int arr[], int top, char characters[], string codings[])
{

    if (root->left != NULL)
    {
        arr[top] = 0;
        encoder(root->left, arr, top + 1, characters, codings);
    }
    if (root->right != NULL)
    {
        arr[top] = 1;
        encoder(root->right, arr, top + 1, characters, codings);
    }
    if (is_leaf(root))
    {
        // cout << root->alpha << " : ";
        printArr(arr, top, root, characters, codings);
    }
}

string write_encoder(char ch, char characters[], string codings[], int total_node1)
{
    int i;
    for (i = 0; i < total_node1; i++)
    {
        if (characters[i] == ch)
        {
            break;
        }
    }
    return codings[i];
}

int main()
{

    int arr[128];

    for (int i = 0; i < 128; i++)
    {
        arr[i] = 0;
    }
    FILE *fptr, *fout;
    char c;
    fptr = fopen("./input1.txt", "r");
    

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

    InorderTrav(heap[0]);

    //TODO: write it in analysis how we calculated height of huffman tree
    struct leaf_node *root = heap[0];

    total_node = ceil(log2((float)(heap[0]->freq) / minm)) - 1;

    int encry[total_node];

    int top = 0;
    char characters[total_node1];
    string codings[total_node1];
    encoder(root, encry, top, characters, codings);
    cout << endl;
    //cout << total_node1<< endl;

    print_codings(characters, codings, total_node1);
    
    fclose(fptr);
    
    fout = fopen("./inter.txt", "w");
    fptr = fopen("./input1.txt", "r");

    if (fptr == NULL)
    {
        cout << "Error! opening file" << endl;
        exit(1);
    }
    
    while ((c = fgetc(fptr)) != EOF)
    {   
        string temp1="";
        int i;
        for(i=0;i<total_node1;++i)
        {
            if(characters[i]==c)break;
        }
        temp1+=codings[i];
        for(int j=0;j<temp1.size();++j)
        {
            fprintf(fout,"%c",temp1[j]);
        }
        // fprintf(fout," ");
        // fprintf(fout,"%s",temp1);
        //cout<<temp1<<endl;
    }

    fclose(fout);
    fclose(fptr);

    return 0;
}