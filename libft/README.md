# Libft!

**This project aims to code a C library regrouping usual functions that you’ll be use for all your next projects.** 

Libft will clone and compile itself when doing `make` on most of my projects, if you wish to compile the project by itself, the flags for compiling are :

 - make -> Just the mandatory functions
 - make bonus -> mandatory + linked list functions
 - make extra -> all of the above + my extra functions

 **What i've learned doing this project**
 
 How pointers actually work, how to allocate memory correctly, protecting functions from bad / empty inputs...

Also, thanks to [Tripouille](https://github.com/Tripouille/libftTester) for making my life easier with his awersome tests.
 
The following functions are exact implementations of the ones found on libc, to check their exact behaviour and returns, you can check the man page of each function.

|  Name | Description
| -- | -- |
ft_toupper | Converts a lower-case letter to the corresponding upper-case letter. | a
ft_tolower | Converts an upper-case letter to the corresponding lower-case letter.
ft_strchr | locates the first occurrence of c (converted to a char) in the string pointed to by s
ft_strrchr | Identical to strchr(), except it locates the last occurrence of c.
memchr | locates the first occurrence of c (converted to an unsigned char) in string s.
ft_strncmp | lexicographically compares the null-terminated strings s1 and s2. Not more than n characters.
ft_memcmp | function compares byte string s1 against byte string s2.  Both strings are assumed to be n bytes long.
ft_strnstr | Locates the first occurrence of the string needle in the string haystack, where not more than len characters are searched.
ft_atoi | Converts a string into int representation.
ft_isalpha | Checks if the character is a letter of the alphabet.
ft_isdigit | Checks if the character is a number.
ft_isalnum | Checks if the character is a letter of the alphabet or a number.
ft_isascii | Checks if the character is ascii.
ft_isprint | Checks if the character is printable.
ft_strlen | Returns the length of a string
ft_memset | Writes len bytes of value c to the string b.
ft_bzero | Writes n zeroed bytes to the string s.
ft_memcpy | Copies n bytes from memory area src to memory area dst.
ft_memmove | Copies len bytes from string src to string dst.  The two strings may overlap; the copy is always done in a non-destructive manner.
ft_strlcpy | Copies up to dstsize - 1 characters from the string src to dst, NUL-terminating the result if dstsize is not 0.
ft_strlcat | Appends string src to the end of dst.  It will append at most dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless dstsize is 0 or the original dst string was longer than dstsize
|ft_printf | Lightweight version of printf.
#
The following functions are either not included in the libc, or included in a different form.
| Name | Description
| -- | -- |
|ft_substr | Allocates (with malloc) and returns a substring from the string ’s’. The substring begins at index ’start’ and is of maximum size ’len’.
|ft_strjoin | Allocates (with malloc) and returns a new string, which is the result of the concatenation of ’s1’ and ’s2’.
|ft_strtrim | Allocates (with malloc) and returns a copy of ’s1’ with the characters specified in ’set’ removed from the beginning and the end of the string.
|ft_split | Allocates (with malloc) and returns an array of strings obtained by splitting ’s’ using the character ’c’ as a delimiter. The array must be ended by a NULL pointer.
|ft_itoa | Allocates (with malloc) and returns a string representing the integer received as an argument. Negative numbers must be handled.
|ft_strmapi | Applies the function ’f’ to each character of the string ’s’ , and passing its index as first argument to create a new string (with malloc(3)) resulting from successive applications of ’f’.
|ft_striteri | Applies the function f to each character of the string passed as argument, and passing its index as first argument. Each character is passed by address to f to be modified if necessary.
|ft_putchar_fd | Outputs the character ’c’ to the given file descriptor.
| ft_putstr_fd | Outputs the string ’s’ to the given file descriptor.
|ft_putendl_fd | Outputs the string ’s’ to the given file descriptor, followed by a newline.
ft_putnbr_fd | Outputs the integer ’n’ to the given file descriptor.
#
The following functions will allow you to easily create and manipulate lists.
| Name | Description
| -- | -- |
|ft_lstnew | Allocates (with malloc) and returns a new element. The variable ’content’ is initialized with the value of the parameter ’content’. The variable ’next’ is initialized to NULL
|ft_lstadd_front | Adds the element ’new’ at the beginning of the list.
| ft_lstadd_back |Adds the element ’new’ at the end of the list.
|ft_lstsize | Returns the number of elements in a list.
|ft_lstlast | Returns a pointer to the last element of the list.
|ft_lstdelone | Takes as a parameter an element and frees the memory of the element’s content using the function ’del’ given as a parameter and free the element. The memory of ’next’ must not be freed.
| ft_lstclear | Deletes and frees the given element and every successor of that element, using the function ’del’ and free(3). Finally, the pointer to the list must be set to NULL.
|ft_lstiter | Iterates the list ’lst’ and applies the function ’f’ to the content of each element.
| ft_lstmap | Iterates the list ’lst’ and applies the function ’f’ to the content of each element. Creates a new list resulting of the successive applications of the function ’f’. The ’del’ function is used to delete the content of an element if needed.
#
The following functions are extras i've created to make my life easier in the following projects, instead of creating "auxiliar" functions for a particular project, i can easily use this ones in future projects.
Name | Description 
| -- | -- |
|ft_atoi_pointer | Similar to atoi, but instead of returning you the int with the value you wanted to convert it gives you the value pointing the int you send to that value, also, it will return false if the value dosn't fit on a 4-byte int, currently using this this for push_swap.
| ft_isnumber | similar to ft_isdigit, but will also accept '-' and '+'.
| ft_lst_repeat | Return -1 if an element is found two times in the list, should be called everytime you add an element, since it only compares the last to every other element.
| ft_lst_order | Returns -1 if the list isn't in order, using it on push_swap, you should probably only use it with numbers.

> Learn, don't copy
