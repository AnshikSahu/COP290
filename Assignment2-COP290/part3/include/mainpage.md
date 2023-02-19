/** *@mainpage Introduction to Parallelism using contexts Given N text files, we find the count of every word summed across all the files. This has been done using multithreading and all the results are stored in a hashmap. 
@section Hashmap
 Hashmap is implemented in the file hm.c where we generate a key for each word and store them in a hash table, where each key  has a linked list associated with it, for catering to collisions.
@section Threads 
Used multithreading to count words in multiple files parallely, thereby optimising over the single threading concurrent approach.
@section Locks
 Locks are used to secure a index being used so that another context cannot access it until it is released


BY: Anshik Sahu(2021CS10577), Sanya Mittal(2021CS10565), Aryan Dhaka(2021CS50597)
