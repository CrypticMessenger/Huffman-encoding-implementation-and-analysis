#include <iostream>
#include <fstream>
using namespace std;
int main( int argc, char** argv )
{
 ifstream theFile;
 unsigned char nextChar;
 theFile.open( "example.bin", ios::binary );
 while ( 1 ) {
 nextChar = theFile.get();
 if (theFile.eof()) break;
 cout << nextChar;
 }
 theFile.close();
}