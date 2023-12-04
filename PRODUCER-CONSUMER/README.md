# Problem 2: Producer-Consumer
CS471, Old Dominion University, Fall 2023

##  Authors
Ethan Landers<br>
Charles Milroy

## Description
Using the producer-consumer problem from the class textbook as a basis, the program is written in C++ and uses threads. Taking input files which contain wait time, producer threads, and number of consumer threads to generate output to a file. 

## Input Files:
Each line of the input files contain the wait time, producer thread count, consumer thread count.

Three input files are provided:
- `input-2sec-wait.txt`
- `input-4sec-wait.txt`
- `input-6sec-wait.txt`

## Compiling
The program can be compiled using the 'make' command from the PRODUCER-CONSUMER directory.
Executing make will produce in the console:
```
make clean ; g++ source.cpp threads.h -o source -lpthread
make[1]: Entering directory '/home/cs_cmilr001/CS471/CS471Project/PRODUCER-CONSUMER'
rm source
rm: cannot remove 'source': No such file or directory
make[1]: *** [makefile:12: clean] Error 1
make[1]: Leaving directory '/home/cs_cmilr001/CS471/CS471Project/PRODUCER-CONSUMER'
```

## Running the Program
The program can be run using the 'make test' command from the PRODUCER-CONSUMER directory to use the three input files to generate the three output files discussed below. The console will have the output:
```
make ; ./source
make[1]: Entering directory '/home/cs_cmilr001/CS471/CS471Project/PRODUCER-CONSUMER'
make[1]: Nothing to be done for 'all'.
make[1]: Leaving directory '/home/cs_cmilr001/CS471/CS471Project/PRODUCER-CONSUMER'
```

## Output
The program will create three output text files based off the time of the input file:
- `output-2sec-wait.txt`
- `output-4sec-wait.txt`
- `output-6sec-wait.txt`

## Result Summary and Explanation
The files generated will be influenced by their input files providing different times to run, number of producers, and number of consumers.

The more consumers there are, the higher the turnaround time will be up to a point. The consumers can only consume as much as the producers produce so having enough consumers to balance and to consume what the producers produce will influence the turnaround time. 

This follows the description on pages 253 through 257 of the 9th edition of our textbook "Operating System Concepts" by Silberschatz, Galvin, and Gagne.