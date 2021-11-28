# HUFFMAN CODING PROJECT

Huffman coding algorithm implemented in C programming language.

Compressing text files into binary files, and decompressing those binary files back into text files.

## INSTALLATION

Make sure you installed Git, if not :

* **Linux** : https://youtu.be/PLQQ3tJwBJg

* **Windows** : https://youtu.be/2j7fD92g-gE

Clone this repository on your desktop :
```bash
$  cd Desktop
$  git clone https://github.com/RaphaelCausse/Huffman_Coding.git
```

## COMPILATION

Go to the cloned folder :
```bash
$  cd HuffmanCoding
```
**Compile** the project using my Makefile :
```bash
$  make
```

## EXECUTION

To **compress** a (.txt) file, run :
```bash
$  ./bin/huffman -c message.txt encoded.hff
```
To **decompress** a (.hff) file, run :
```bash
$  ./bin/huffman -d encoded.hff decoded.txt
```
**_NOTE:_**

`message.txt`, `encoded.txt` and `decoded.txt` are example files.

### FEATURES

To get **information and help**, run :
```bash
$  ./bin/huffman --help
```
To **clean** the entire project directory, run :
```bash
$  make clean
```

### AUTHORS

Melvyn MUNOZ and Raphael CAUSSE, from CY TECH.

11/2021, developped on Linux Ubuntu, Visual Studio Code.