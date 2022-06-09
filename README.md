# Virtual Memory
> This is a project for a college subject, Software Infrastructure.

> This is the proposed implementation of the book Operating System Concepts, P-51. It was implemented in C and simulates a Virtual Memory Management, based on a .txt archive with the virtual addresses, the replacemente algorithm for the physical and TLB, this inputs are through command line, beyond the BACKING_STORE.bin that simulates the secondary memory, but it is **not** passed through command line.


## Observations
- It was implemented on **MacOs**.
- Its was tested in MacOs and Linux.
- It was implemented in multiple archives, we will take a look at each one of them.
<br/>

## binTrans.c
It was the first one made and has the purpose of translate the Virtual Address to get the Page and the Offset. It has 3 functions, "getPageAndOffset" that receive the Virtual Address and an array of 2 position as parameters, the array eventually will receive in the first position the page and the offset in the second position. The function "getPageAndOffset" call the other functions, "translateToBinary" and "translateToDecimal", their purposes are to translate a decimal number to binary and the other from binary to decimal.
<br/>
<br/>
## backingStore.c
It has the purpose to get an Page from the BACKING_STORE.bin archive, there is only onde function defined there, it's called "findPageInBackingStore" that receive the Page to get from the archive and an array that will receive the Page.
<br/>
<br/>
## errorHandler.c
It has the purpose to check the arguments passed through command line before the program "actually starts", before the critical part of the program starts and it receive as paramenter the command line arguments the "argc" and "agrv". It cheks the amount of arguments passed, that must be 3, if the passed archive exists and can be open, if the format of the archive is correct, if the 2 replacement algorithm are correct and if the BACKING_STORE.bin exists and can be open.
<br/>
<br/>
## arq.c
This one has the purpose of to create and write the correct.txt, that will have the result of the program, it has 2 functions one to write line by line in this format below:
```
        Virtual address: 16916 Physical address: 20 Value: 0
```
and another one to write in the end of the achive in this format below:
```
        Number of Translated Addresses = 1000
        Page Faults = 538
        Page Fault Rate = 0.538
        TLB Hits = 54
        TLB Hit Rate = 0.054
```
## main.c
Here remains the fun, the logic of the Virtual Memory management is here, also the logic of the replacement algorithms, First In First Out (FIFO) and Least Recently Used (LRU).
<br/>
<br/>

## How to download, compile and run the program.
1. **Download**
```bash
        $ git clone https://github.com/PedroHenr1que/VirtualMemory.git
        $ cd VirtualMemory
```
<br/>

2. **Complie**

```bash
        $ make
```
It's going to generate a executable called "vm".
<br/>
<br/>

3. **Run**

The format to execute the program is the one below:
```
        ./vm X Y Z
```
Where "X" is the text archive (.txt) that has the Virtual Addresses, "Y" is replacement algorithm for the Physical Memory and "Z" is the replacement algorithm for the TLB, the "vm" is the executable created when you run the "make" command, here is an example how you should run the program: 
```bash
        ./vm addresses.txt fifo fifo
```
When you run this command you should see a new archive called "correct.txt" that is the result of the program. 
<br/>
<br/>
## How to clean the compiled archives
Just run the following command.
```bash
        $ make clean
```
