#Homework 4

##Data Strucure Used
* Hash Maps
* trees

##Description

In this assignment, I created a HashMap using AVL trees to handle collisions. Additionally, I my program prints out statistics regarding average numbers of collisions.

##Specifications:

I constructed a HashMap with `strings` being keys and `ints` being values. My assignment supports the following public methods in my HashMap class:

* void put(string key, int value);
* int get(string key);
* int remove(string key); //returns NULL if could not remove
* list<int> getAll(list<string> keys) //returns NULL if could not find ALL elements in input

I use a dictionary of 5 letter words (`words5.dict`) as a test case.I vary the size of MAX_TABLE_SIZE from 500 to 4000 in increments of 500. My deliverables print out the average number of collisions and the standard deviation of the collision count for `words5.dict`.

My deliverables are to write a HashMap and provide unit tests for each of the public methods.
