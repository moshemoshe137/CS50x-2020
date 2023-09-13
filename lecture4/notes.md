# 1/20/2021
# Lecture 4
# CS50


## Pointers

## File pointers
```c
FILE* ptr = fopen(<filename>, <opperation>);
```

Opperation is "r", "a", "w". 

```c
fclose(ptr);
```

fgetc gets chars, and the next one...
```
char ch = fgetc(<file pointer>);
```
Only works if you opened in read mode!!

To print the file:

```c
char ch;
while((ch = fgetc(pyr)) != EOF)
    printf("%c", ch)
```
is basicaly the same as cat


fputc writes a character to a file
Only works if you opened in write/append mode!

```c
char ch;
while((ch = fget(ptr)) != EOF)
    fputc(ch, ptr2);

```
is basically the same as cp


A better version of fgetc:
We can get any number at a time with fread()
```c
fread(<buffer>, <size>, <qty>, <file pointer>)
```
ie
```c
int arr[10];
fread(arr, sizeof(int), 10, ptr);
```
or
```c
double* arr2 = malloc(sizeof(double) * 80);
fread(arr2, sizeof(double), 80, ptr);
```

Be careful- if you use fread on a single character, you must pass in a POINTER to the charcter! For example,
```c
char c;
fread(&c, sizeof(char), 1 ptr);
```

fwrite() is the exact same except for writing
```c
fwrite(<buffer>, <size>, <qty>, <file pointer>)
```

```c
int arr[10];
// fill arr
fwrite(arr, sizeof(int), 10, ptr);
```

Same thing with malloc method, and same warning for using chars. 

Also exist:
- fgets()
-   gets strings, like fputc()
- fputs()
-   puts strings, like fputc()
- fprintf()
-   write a formatted string to file
- fseek()
-   rewind or fast forward
- ftell()
-   tells you what byte/position you're on within a file
- feof()
-   tells you if you're at EOF
- ferror()
-   tells you if an error has occurred. 