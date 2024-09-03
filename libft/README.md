# Libft

> This project is about understanding the way these functions work,
> implementing and learning to use them. Your will create your own library. It will be
> helpful since you will use it in your next C school assignments.

## Score

<img title="" width="200px" src="https://res.cloudinary.com/dk8lnfjpm/image/upload/v1678097211/42/105_100_dhjneb.png" alt="score" data-align="inline">

## Part 1 - Libc functions

| Function  | Description                                                                                                                                                                                                                                             |
|:---------:|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| `isalpha` | The isalpha() function tests for any character for which isupper(3) or islower(3) is true.  The value of the argument must be representable as an unsigned char or the value of EOF.                                                                    |
| `isdigit` | The isdigit() function tests for a decimal digit character.                                                                                                                                                                                             |
| `isalnum` | The isalnum() function tests for any character for which isalpha(3) or isdigit(3) is true.  The value of the argument must be representable as an unsigned char or the value of EOF.                                                                    |
| `isascii` | The isascii() function tests for an ASCII character, which is any character between 0 and octal 0177 inclusive.                                                                                                                                         |
| `isprint` | The isprint() function tests for any printing character, including space (‘ ’).  The value of the argument must be representable as an unsigned char or the value of EOF.                                                                               |
| `strlen`  | The strlen() function computes the length of the string s.                                                                                                                                                                                              |
| `memset`  | The memset() function writes len bytes of value c (converted to an unsigned char) to the string b.                                                                                                                                                      |
| `bzero`   | The bzero() function writes n zeroed bytes to the string s.  If n is zero, bzero() does nothing.                                                                                                                                                        |
| `memcpy`  | The memcpy() function copies n bytes from memory area src to memory area dst.  If dst and src overlap, behavior is undefined. Applications in which dst and src might overlap should use memmove(3) instead.                                            |
| `memmove` | The memmove() function copies len bytes from string src to string dst.                                                                                                                                                                                  |
| `strlcpy` | The strlcpy() and strlcat() functions copy and concatenate strings with the same input parameters and output result as snprintf(3).                                                                                                                     |
| `strlcat` | The strlcpy() and strlcat() functions copy and concatenate strings with the same input parameters and output result as snprintf(3).                                                                                                                     |
| `toupper` | The toupper() function converts a lower-case letter to the corresponding upper-case letter.  The argument must be representable as an unsigned char or the value of EOF.                                                                                |
| `tolower` | The tolower() function converts an upper-case letter to the corresponding lower-case letter.  The argument must be representable as an unsigned char or the value of EOF.                                                                               |
| `strchr`  | The strchr() function locates the first occurrence of c (converted to a char) in the string pointed to by s.  The terminating null character is considered to be part of the string; therefore if c is ‘\0’, the functions locate the terminating ‘\0’. |
| `strrchr` | The strrchr() function is identical to strchr(), except it locates the last occurrence of c.                                                                                                                                                            |
| `strncmp` | The strcmp() and strncmp() functions lexicographically compare the null-terminated strings s1 and s2.                                                                                                                                                   |
| `memchr`  | The memchr() function locates the first occurrence of c (converted to an unsigned char) in string s.                                                                                                                                                    |
| `memcmp`  | The memcmp() function compares byte string s1 against byte string s2.  Both strings are assumed to be n bytes long.                                                                                                                                     |
| `strnstr` | The strstr() function locates the first occurrence of the null-terminated string needle in the null-terminated string haystack.                                                                                                                         |
| `atoi`    | The atoi() function converts the initial portion of the string pointed to by str to int representation.                                                                                                                                                 |

## Part 2 - Additional functions

| Function        | Description                                                                                                                                                                                  |
|:---------------:|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| `ft_substr`     | Allocates (with malloc(3)) and returns a substring from the string ’s’. The substring begins at index ’start’ and is of maximum size ’len’.                                                  |
| `ft_strjoin`    | Allocates (with malloc(3)) and returns a new string, which is the result of the concatenation of ’s1’ and ’s2’.                                                                              |
| `ft_strtrim`    | Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters specified in ’set’ removed from the beginning and the end of the string.                                           |
| `ft_split`      | Allocates (with malloc(3)) and returns an array of strings obtained by splitting ’s’ using the character ’c’ as a delimiter. The array must end with a NULL pointer.                         |
| `ft_itoa`       | Allocates (with malloc(3)) and returns a string representing the integer received as an argument. Negative numbers must be handled.                                                          |
| `ft_strmapi`    | Applies the function ’f’ to each character of the string ’s’, and passing its index as first argument to create a new string (with malloc(3)) resulting from successive applications of ’f’. |
| `ft_striteri`   | Applies the function ’f’ on each character of the string passed as argument, passing its index as first argument. Each character is passed by address to ’f’ to be modified if necessary.    |
| `ft_putchar_fd` | Outputs the character ’c’ to the given file descriptor.                                                                                                                                      |
| `ft_putstr_fd`  | Outputs the string ’s’ to the given file descriptor.                                                                                                                                         |
| `ft_putendl_fd` | Outputs the string ’s’ to the given file descriptor followed by a newline.                                                                                                                   |
| `ft_putnbr_fd`  | Outputs the integer ’n’ to the given file descriptor.                                                                                                                                        |

## Bonus part

You have to use the following structure to represent a node of your list. Add its
declaration to your libft.h file:

```c
typedef struct s_list
{
  void *content;
  struct s_list *next;
} t_list;
```

| Function          | Description                                                                                                                                                                                                                          |
|:-----------------:|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| `ft_lstnew`       | Allocates (with malloc(3)) and returns a new node. The member variable ’content’ is initialized with the value of the parameter ’content’. The variable ’next’ is initialized to NULL.                                               |
| `ft_lstadd_front` | Adds the node ’new’ at the beginning of the list.                                                                                                                                                                                    |
| `ft_lstsize`      | Counts the number of nodes in a list.                                                                                                                                                                                                |
| `ft_lstlast`      | Returns the last node of the list.                                                                                                                                                                                                   |
| `ft_lstadd_back`  | Adds the node ’new’ at the end of the list.                                                                                                                                                                                          |
| `ft_lstdelone`    | Takes as a parameter a node and frees the memory of the node’s content using the function ’del’ given as a parameter and free the node. The memory of ’next’ must not be freed.                                                      |
| `ft_lstclear`     | Deletes and frees the given node and every successor of that node, using the function ’del’ and free(3). Finally, the pointer to the list must be set to NULL.                                                                       |
| `ft_lstiter`      | Iterates the list ’lst’ and applies the function ’f’ on the content of each node.                                                                                                                                                    |
| `ft_lstmap`       | Iterates the list ’lst’ and applies the function ’f’ on the content of each node. Creates a new list resulting of the successive applications of the function ’f’. The ’del’ function is use delete the content of a node if needed. |
