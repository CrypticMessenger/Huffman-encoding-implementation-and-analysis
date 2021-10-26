#include <iostream>

using namespace std;
//!CONVERT TO C AT LAST
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

    for (int i = 0; i < 128; i++)
    {
        cout << i << " " << arr[i] << " " << endl;
    }

    fclose(fptr);

    return 0;
}