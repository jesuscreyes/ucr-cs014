#Homework 3

##Data Strucure Used
* Tree

##Description

In this assignment, I created an AVL tree with test cases.

##Specifications:

I constructed an AVL tree of strings that needed to support the following public methods in an AVL class:

```
* void insert(string input);
* void insertAll(list<string> input);
* string find(string input); //returns NULL if could not find
* string remove(string input); //returns NULL if could not remove
* list<string>findAll(list<string> input) //returns NULL if could not find ALL elements in input
* list<string> inOrderTraversal() //returns the in order traversal of the avl tree
```

To test this function, we used the file `words5.dict` which includes a list of 5-letter words.

My deliverables are able to write an AVL tree and provide unit tests for each of the public methods. My `main` function calls the series of unit tests for each of the public methods. For example, to test the `insert` method, I wrote a `testInsert` method.
