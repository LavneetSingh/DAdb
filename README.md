# DAdb
This project is a practice project to use modern c++ (smart pointers, C++20 features etc) in data structures and algorithms. 

The idea is to create an in-memory system to facilitate criteria based search, and graphs to begin with. The architecture will look like the following:
1. Database Layer: A generic linked list implementation using smart pointers to create database entities. Every node in linked list points to data. The data could be any arbitrary type provided by the database user
2. Search/Query Layer: Searching a linked list is time consuming. So, for faster search, we'll let user define search criteria (like, search by name, id or some other attribute that the entities stored in database layer has). For each search criteria, we'll build a red-black binary tree. Every node of tree will point to the linked list node that it represents. The binary tree will be built using the criteria specified by user to compare two nodes - the user provides the comparer function.
The search query can then specify the search criteria and the actual query. The criteria will be used to select the right RB Tree and then comparison of nodes can be done with the input query in O(log(n)).
3. Graphs: Next step will be to implement graph representation of the nodes in linked list using graph criterias, like search criteria. For each graph criteria we'll have one graph just like for each search criteria we have one RB tree. Then the idea is to implement graph algos in maybe another layer / class over the DAdb.
