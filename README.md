This is a project for my CS101 class where program the program accepts four command line arguments. 
Argument 1 is either “i” or “s”, arguments 2 and 3 are the names of the input files.
The program reads streams of data from the input files until end-of-file. 
If you want it to read integers put argument 1 to “i”. If yoou want it to read strings of visible characters put argument 1 as “s”.
Both kinds of values will be separated by whitespace (blanks, tabs, newlines).
The program sorts the data from both files using mergesort if argument 1 is "i" and quicksort if argument 1 is "s".
The program writes to standard out all the data (integers or strings) that appear in both of the input files.
The data output is sorted in ascending order, either numerically for integers or lexicographically for strings.
The output is one value per line and discards and duplicate values.
It can not process more than 20,000 data items in each file.
