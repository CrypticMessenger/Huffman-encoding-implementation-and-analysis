NAMES OF TEAM MEMBERS:
Amit Kumar (2020CSB1070)
Ankit Sharma (2020CSB1072)
Tanish Goyal (2020CSB1133)

NAME OF MENTOR: Ms Kirandeep Kaur

PROJECT NAME: HUFFMAN ENCODING

SUMMARY:
Data in computers is encoded as binary digits of 1s and 0s. In the data storage industries, the main problem posed is to transfer the data in the minimum storage space possible so that the maximum data can be transferred efficiently. The data is transferred using the fewest number of bits in such a way that every encoding is unique (unique prefix code).Thus, there should be a technique which can encode the data using the minimum number of bits. At the heart of every such technique used even in modern times is the “HUFFMAN ENCODING”
It uses the Greedy Algorithm (as it requires the minimum bits) and is an example of variable length encoding. Just like in a typical variable length encoding, it uses a variable number of bits for encoding the characters which is a function of their frequency in some given text. The idea is to assign the character with maximum frequency the least bit code and longer length codes to the characters with the lesser frequencies. The length of codes is maintained in such a manner that total bits required for storage remains optimal.
Here’s a brief procedure followed by us:
•	We take the input from the input.txt file given by the user. That data is read by our code using the normal file handling. The frequencies are also counted for each character.
•	Before building the Huffman Tree, we make a priority queue such that nodes with lowest frequency have the highest priority, this priority queue is implemented using MINHEAP.
•	The characters and their frequency are stored in the leaf nodes.
•	Now, we start building tree with the internal nodes getting the sum of frequencies of its child nodes as key value.
•	Once the tree is built, the encoding is done by assigning 0 to each left child and 1 to each right child, of any node.

We now display the characters alongwith their frequencies and encodings, input data bits/size and output data bits/size. A ratio of input and output data bits (i.e. the compression ratio) is also displayed to show how efficiently the code works.
The final output obtained from the procedure is displayed in the output.txt
 