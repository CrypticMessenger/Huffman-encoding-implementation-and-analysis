#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    FILE *fptr;
    char c;
    fptr = fopen("./input.txt", "w");
    int num;
    cout<<"enter total number of characters: ";
    cin >> num;
    while (num--)
    {
        int n;
        char ch;
        cout<<"Enter Character Frequencies: ";
        cin >> n;
        cout<<"Enter character: ";
        cin >> ch;

        if (fptr == NULL)
        {
            cout << "Error! opening file" << endl;
            exit(1);
        }
        for (int i = 0; i < n; i++)
        {
            fprintf(fptr, "%c", ch);
        }
    }
    fclose(fptr);

    return 0;
}