## linear search
search elemnts 1 by 1, left to right
linear such always succeeds 
but sucks
O(n)
Omega(1) 

## bubble sort
we compare pair-wise
swap if we need, not if they're okay
Then, the largest element will eventually be "bubbled" to the top, where it should be.
count how many times you swap per loop. If you ever go thru and swap 0 times, you must be finished. 
O(n^2) time worse-case
Omega(n) best-case


## selection sort
find the smallest unsorted element, and add it to the end of the sorted list. Repeat until no elements remain. 
Swap the smallest element with first element of the unsorted part. 
O(n^2) time worse-case
Omega(n^2) best case
So, selection sort seems to suck. 

## recursion 
need a 
- base case
- recursive case

```c
int fact(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n* fact(n-1);
    }
}
```

for 1 line if-else's, we can technically ommit the curly braces:
```c
int fact(int n)
{
    if (n == 1)
        return 1;
    else
        return n* fact(n-1);
}
```

almost any recursive function can be replaced with a loop. 


## merge sort

sort smaller arrays, then combine them in sorted sorted.
Uses recurssion 
It's the most complicated :(
Steps are
1) sort left half
1) sort right half
1) merge the 2 together

```psuedo code
take the array {5, 2, 1, 3, 6, 4}
Let's take the left half: {5, 2, 1}
    well, let's sort the left half on this sub-array: {5}
        well, it's sorted.
    
    now, let's sort the right half sub array: {2, 1}
        Let's sort the left half: {2}
            done
        Let's sort the right half: {1}
            done
        now merge. Btwn {2} and {1}, 1 is the lowest
            add 1 to my return_array
        now, only 2 is left
            add 2 to the return_array
        return {1, 2}
    
    now, let's merge the sorted left half {5} with the sorted right half {1,2}
        btwn {5} and {1}, 1 is lowest
            add 1 to return_array
        btwn 5 and 2, 2 is lowest
            add 2 to return array
        only 5 is left
            add 5 to return array
        return {1, 2, 5}
we have sorted the left portion! Let's put it aside for now
Let's sort the right half: {3, 6, 4}
    Left half is {3}
        3 is sorted
    Right half is {6,4}
        left half is {6}
        right half is {4}
        merge them
            4 is lower
                add 4
            6 remains
                add 6
            return {4, 6}
    merge {3} and {4, 6}
        3 is smallest
            add 3 to return_array
        only the 2nd set remains
            add the whole set, it's already sorted
        return {3, 4, 6}
now, merge {1, 2, 5} with {3, 4, 6}
1 is smaller than 3
    add 1
2 is lower than 3
    add 2
5 is larger than 3
    add 3
5 is larger than 4
    add 4
5 is smaller than 6
    add 5
6 remains
    add 6
```

worse case is O(n*log(n))
best case is Omega(n*log(n))