#include <iostream>
#include <bits/stdc++.h>
using namespace std;


//function to print characters and their corresponding encodings.
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
    struct leaf_node *left, *right; //left,right child pointer
};

//function to allocate memory to leaf nodes.
struct leaf_node *make_leaf(char alpha, int freq)
{
    struct leaf_node *n;
    n = (struct leaf_node *)malloc(sizeof(struct leaf_node)); //creating a leaf_node and assigning memory dynamically using malloc function
    n->alpha = alpha;
    n->freq = freq;
    n->left = NULL;
    n->right = NULL;
    return n;
}

//an array of pointer to store the address of nodes.
//we allocate 128 sized memory to heap array because characters can have maximum ASCII value of 128
struct leaf_node **heap = (struct leaf_node **)calloc(128, sizeof(struct leaf_node *));

//sorting the heap elements according to their frequency
struct leaf_node **sort_heap(struct leaf_node **heap)
{
    for (int i = 0; i < 127; ++i)
    {
        for (int j = i + 1; j < 128; ++j)
        {
            //checking if the i-th as well as j-th address in heap is pointing to NULL or not,
            if (heap[i] != NULL && heap[j] != NULL && heap[j]->freq < heap[i]->freq)
            {
                //sorting
                struct leaf_node *temp;
                temp = heap[i];
                heap[i] = heap[j];
                heap[j] = temp;
            }
        }
    }
    return heap;         //return the heap
}

//Inorder traversal of heap by traversing ({root->left} ---> {root} ---> {root->right}) 
//To get the ascending order of frequencies for storing in the MINHEAP
void InorderTrav(struct leaf_node *root)    //recursive inorder traversal
{
    if (root)
    {
        InorderTrav(root->left);
        cout << root->alpha << " : ";
        cout << root->freq << " ";
        InorderTrav(root->right);
    }
}

//boolean function to check if the node is leaf or not
bool is_leaf(struct leaf_node *leaf)
{
    if (leaf->left == NULL && leaf->right == NULL)
    {
        return true;
    }
    return false;
}


int pointer = 0; //declaring a global variable pointer and initialising it to 0.

void printArr(int arr[], int n, struct leaf_node *root, char characters[], string codings[])
{
    int i;
    string str = ""; //creating an empty string

    for (i = 0; i < n; ++i)
    {
        //cout << arr[i];
        str = str + (char)(arr[i] + 48); // converting the elements stored in the array to character string with the help of ASCII value
    }
    //cout << endl;
    characters[pointer] = root->alpha; //storing character in characters array
    codings[pointer] = str;
    ++pointer;
}

//encoding function
void encoder(struct leaf_node *root, int arr[], int top, char characters[], string codings[])
{
    //we start from root of huffmann tree and assing '0' when we move to the left child and assign '1' when we move to the right child,
    //and store the encoding of correspondings character when we reach to the leaf node.
    if (root->left != NULL)
    {
        arr[top] = 0;
        encoder(root->left, arr, top + 1, characters, codings);   //recursively reaching the leaf nodes
    }
    if (root->right != NULL)
    {
        arr[top] = 1;
        encoder(root->right, arr, top + 1, characters, codings);  //recursively reaching the leaf nodes
    }
    if (is_leaf(root))
    {
        printArr(arr, top, root, characters, codings);
    }
}

//function to display encodings of the given characters
string write_encoder(char ch, char characters[], string codings[], int total_node1)
{
    int i;
    //finding at which index character is present
    for (i = 0; i < total_node1; i++)
    {
        if (characters[i] == ch)
        {
            break;
        }
    }
    //returning the string(encoding) present for that index
    return codings[i];
}

int main()
{
    //declaring an array of size 128 because ASCII value can maximum go upto 127 starting from 0.
    //we are not using extended ASCII which is of 8 bits.

    int arr[128]; //used to store frequency of each character
    for (int i = 0; i < 128; i++) //initialising to 0 at start
    {
        arr[i] = 0;
    }
    FILE *fptr, *fout;
    char c;
    fptr = fopen("./input.txt", "r"); //opening the input file in reading mode

    if (fptr == NULL)         //if no file is detected
    {
        cout << "Error! opening file" << endl;
        exit(1);
    }

    while ((c = fgetc(fptr)) != EOF)
    {
        arr[int(c)]++; //we are storing frequency of each character to their corresponding ASCII value
    }

    struct leaf_node *temp;

    int index = 0;
    float initial_size = 0;
    for (int i = 0; i < 128; i++)
    {
        if (arr[i] != 0)
        {
            initial_size+=arr[i];
            //we are storing only those characters to heap array whose frequency is non zero
            temp = make_leaf(i, arr[i]);
            heap[index] = temp;
            index++;
        }
    }

    heap = sort_heap(heap);

    int minm = INT_MAX; //declaring a minm variable to maximum value of integer which is approx "2147483647"

    int heap_size = 0;
    
    cout<<"Character and their corresponding frequency is:"<<endl; //displaying the frequencies

    for (int i = 0; i < 128; i++)
    {
        if (heap[i] != NULL)
        {
            cout << heap[i]->alpha << " : " << heap[i]->freq << endl;
            minm = min(heap[i]->freq, minm); //finding the minimum frequency character in text file
            heap_size++;
        }
    }
    //temporary variables
    int temp_size = heap_size;
    int total_node = heap_size;
    int total_node1 = heap_size;

    //Applying the Huffmann algorithm
    while (temp_size > 1)
    {
        struct leaf_node *temp1 = heap[0];
        struct leaf_node *temp2 = heap[1];
        //creating a new node whose frequency is sum of minimum two frequencies
        struct leaf_node *temp3 = make_leaf(0, (heap[0]->freq) + (heap[1]->freq));
        temp3->left = temp1;
        temp3->right = temp2;

        //we are initialising first two pointers stored in heap to NULL
        heap[0] = NULL;
        heap[1] = NULL;

        heap[heap_size] = temp3; //inserting new node at the end of heap
        struct leaf_node *ptr;

        for (int i = 2; i < heap_size + 1; ++i)
        {
            //After inserting new node at the end we are shifting each pointer two place to the left because first two pointer in heap becomes NULL
            ptr = heap[i];
            heap[i] = heap[i - 2];
            heap[i - 2] = ptr;
        }

        heap_size--;
        heap = sort_heap(heap); //repeatedly sorting the heap array according to frequency of characters
        temp_size--;
    }

    //InorderTrav(heap[0]); //calling inorder function

    //TODO: write it in analysis how we calculated height of huffman tree
    struct leaf_node *root = heap[0];

    total_node = ceil(log2((float)(heap[0]->freq) / minm)) - 1; //calculating the height of huffmann tree according to formula

    int encry[total_node]; //temporary array to store data temporary to find encoding of each character

    int top = 0;

    char characters[total_node1]; //['a','@'...] character array to store each character
    string codings[total_node1];  //["01","0101"] string array for storing encoding of each corresponding character

    encoder(root, encry, top, characters, codings);
    cout << endl;
 
    cout <<"Character and their corresponding encodings: "<< endl; //displaying the encodings
    print_codings(characters, codings, total_node1);

    fclose(fptr);

    fout = fopen("./output.txt", "wb");
    fptr = fopen("./input.txt", "r");

    if (fptr == NULL)      //if no file is detected
    {
        cout << "Error! opening file" << endl;
        exit(1);
    }
    int final_size=0;
    while ((c = fgetc(fptr)) != EOF)
    {
        string temp1 = "";
        int i;
        for (i = 0; i < total_node1; ++i)
        {
            if (characters[i] == c)
                break;
        }
        temp1 += codings[i];
        final_size+=temp1.size();
        for (int j = 0; j < temp1.size(); ++j)
        {
            fprintf(fout, "%c", temp1[j]);
        }
        // fprintf(fout," ");
        // fprintf(fout,"%s",temp1);
        //cout<<temp1<<endl;
    }
    float compression_ratio;   //ratio of input/output sizes (in bits)
    compression_ratio=(float)(initial_size*8)/final_size;
    cout<<"initial size is: "<<8*initial_size<<endl;
    cout<<"final size is: "<<final_size<<endl;
    cout<<"Compression ratio is: "<<compression_ratio<<endl;
    cout<<"Printing encoded text in output.txt ..."<<endl;
    fclose(fout);
    fclose(fptr);

    return 0;
}