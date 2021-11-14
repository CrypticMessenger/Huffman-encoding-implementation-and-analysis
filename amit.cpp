#include <iostream>
#include <fstream>

#pragma pack(1)
#pragma pack(0)
using namespace std;
int main( int argc, char** argv )
{
 ofstream numFile;
 unsigned int num = 12345;
 numFile.open( "numfile" );
 numFile << num;
 numFile.close();
}