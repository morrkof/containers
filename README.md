# Practice projects: containers
The goal of this project it to re-write several containers from STL C++, using C++98. 

#### Command to compile containers with my own tests:
`make`

For all containers were used standard allocator. I wrote myself iterators and enable_if (for SFINAE).
#### list of containers:

1. vector (dynamic array)
2. list (doubly-linked list)
3. map (left-leaning red-black tree)

#### And two container adaptors:
1. queue (FIFO)
2. stack (LIFO)
