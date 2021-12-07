# <center> HUFFMAN COMPRESSION ALGORITHM IMPLEMENTATION AND ANALYSIS </center>

<center>
<img src="https://img.shields.io/badge/Language-C%2B%2B-yellow">
<img src="https://img.shields.io/badge/Course%20Project-Data%20Structures%20and%20Algorithms-brightgreen">
</center>
<br>


## <center> **Instructions To Run** </center>
- use gcc compiler to compile the program.
- Enter the text that you want to compress in to `input.txt` file.
- If you want to test our code by giving input to a character and it's frequency, then you can do it by using `testBench.cpp` .
  Using this it will generate an input text in `input.txt` accordingly.
- Just by running `Main.cpp`, it will output characters and corresponding frequencies in the text, then it will print encoding of each character, 
  finally the compressed version of the text will be outputed in `output.txt` file which consists of bits(0 and 1).
- We have shown that our text got compressed by calculating the compression ratio which is ratio of (initial file size)/(final file size) which comes out to be >1.

<br>

## <center> **Summary** </center>
<br>

Data in computers is encoded as binary digits of 1s and 0s. In the data storage industries, the main problem posed is to transfer the data in the minimum storage space possible so that the maximum data can be transferred efficiently. The data is transferred using the fewest number of bits in such a way that every encoding is unique (unique prefix code).Thus, there should be a technique which can encode the data using the minimum number of bits. At the heart of every such technique used even in modern times is the “HUFFMAN ENCODING”
It uses the Greedy Algorithm (as it requires the minimum bits) and is an example of variable length encoding. Just like in a typical variable length encoding, it uses a variable number of bits for encoding the characters which is a function of their frequency in some given text. The idea is to assign the character with maximum frequency the least bit code and longer length codes to the characters with the lesser frequencies. The length of codes is maintained in such a manner that total bits required for storage remains optimal.
Here’s a brief procedure followed by us:
-	We take the input from the input.txt file given by the user. That data is read by our code using the normal file handling. The frequencies are also counted for each character.
-	Before building the Huffman Tree, we make a priority queue such that nodes with lowest frequency have the highest priority, this priority queue is implemented using MINHEAP.
-	The characters and their frequency are stored in the leaf nodes.
-	Now, we start building tree with the internal nodes getting the sum of frequencies of its child nodes as key value.
-	Once the tree is built, the encoding is done by assigning 0 to each left child and 1 to each right child, of any node.

<br>

*Under the guidance of Prof. Anil Shukla and mentor Ms. Kirandeep Kaur*
| **Name**      | **Entry Number** | 
| :---        |    :----:   |  
| Amit Kumar   | 2020CSB1070        | 
| Ankit Sharma      | 2020CSB1072       | 
| Tanish Goyal      | 2020CSB1133      | 

