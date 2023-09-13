# Moshe Rubin
# 1/24/2021
# Lecture 5


How do we resize arrays?
Loops over and copy to a new, larger array

. and * can be combined to ->

## Linked Lists
Each number on the list goes anywhere in memeory
It uses a block to store its value
But it uses an additional, "metadata" block to store a pointer to the next element

0x0, "NULL",  signifies the "absense" of any address

These are nodes with pointers

This will cause issues bc it doesn't know what node is yet:

```c
typedef struct
{
    int number;
    node *next;
}
node;
```

This, for some reason, is the solution:

```c
typedef struct node
{
    int number;
    struct node *next;
}
node;
```

To start out story:
```c
node *list = NULL;
```

Get some memory for a node, n:
```c
node *n = malloc(sizeof(node));
```

n is now pointing at a garbage node

```c
if (n != NULL)
{
    (*n).number = 1;
}
```
You should get into the habit of always, ALWAYS checking if your pointer is NULL or not!
So, if the address is valid, go to that address, and go to the variable inside called number, and make the number 1.

We want to also replace the address for n. Right now, it's a garbage value, but we need it to be NULL.
* and . comes with some syntactic sugar:
*

```c
if (n != NULL)
{
    n->number = 1;
    n->next = NULL;
}
```

Right now, n is just a temporary var, I'm just using it for a second to initilize my node. If I wanted to add this node to my linked list:
```c
list = n;
```
Now, list points to where n pointed.

Next:
```c
node *n = malloc(sizeof(node));
if (n != NULL)
{
    n->number = 2;
    n->next = NULL;
}
```
To add this new n to my list:
```c
list->next = n;

```

next:

```c
node *n = malloc(sizeof(node));
if (n != NULL)
{
    n->number = 3;
    n->next = NULL;
}

list->next->next = n;
```

SEE FILE: LIST.C
SEE FILE: LIST2.C

We can use trees for linked list features, and array features
To use binary search, I NEED random access to arrays. Linked lists don't have that dynamic, random access


    4
 2    6
1 3  5 7

SEE FILE: LIST3.C

## Stacks
push and pop
Same as add and remove
LIFO

## Dictionaries
Keys and values




# Shorts

## Singly-Linked Lists
Right now, we have arrays for collections of values
Structures also collect info.

## Hash Tables
Arrays combined w linked lists
Random access of arrays, and grow/shrink like linked lists
Need a hash function to return a natural number hash code
Then, we store in array at that location.

We could get a collision- 2 pieces of data w the same hash code
BAD: Solve with linear probing-- put him +1 away, or +2 away, whereever the next free spot is. This is called "clustering" tho

GOOD: Chaining:
Every element of the array is a pointer to a linked list. 

```c
node* hashtable[10];
hash("Joey"); return 6
hashtable[6]->next = joeys_node

hash("Ross"); returns 2
```

## Tries
```
typedef struct _trie
{
    char university[20];
    struct _trie* paths[10];  // 10 possible places we can go down
}
trie;

root = malloc(sizeof(trie));
// harvard, founded 1636
// 1 path is currently null
// malloc a new node, have 1 point there, then I'm good to go
// on this new trie, build a new node, and have 6 point there
// same at 3
// finally, to the 5th trie after node 6.
// Name this node "Harvard".

// yale, founded 1701
// 1 path already exists, so let's just go down
// now, malloc a trie and have 7 point there. Travel there.
// at node 0, repeat
// at 1, repeat
// name this node "Yale"

// dartmouth, 1769
// 1 path already exists
// 7 path already exists
// malloc path for 6, 6 points there, travel there
// malloc a new node at 9. Travel down. Name this Dartmouth. 
```

## Data Structures
- Arrays
- Linked lists
- Hash tables
- Tries

Arrays
- Insertion is bad
- Deleteion is bad
- Lookup is great
- Easy to sort
- Small in memory
- Fixed size

Linked list
- Insertion is easy
- Deletion is easy
- Lookup is bad- linear search
- Difficult to sort, unless you sort as you construct
- Relatively small 

Hash Tables
- Insertion is easy, two steps
- Deletion is easy
- Lookup is better than Linked Lists
- Not ideal for sorting
- Can be sizable 

Tries
- Inserting is complex, but easier as you go
- Deletion is easy
- Lookup is fast
- Already sorted
- Rapidly becoes huge, even with a little data