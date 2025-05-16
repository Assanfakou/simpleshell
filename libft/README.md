# Libft

## Description
Libft is my first project at 42 school. It's a C library that contains a collection of commonly used functions that we'll be allowed to reuse in our future projects. This library is built from scratch and implements both standard C library functions and additional utility functions.

## Functions

### Part 1 - Libc Functions
These functions are direct implementations of standard C library functions:
* `ft_isalpha` - checks if the character is alphabetic
* `ft_isdigit` - checks if the character is a digit
* `ft_isalnum` - checks if the character is alphanumeric
* `ft_isascii` - checks if the character is in ASCII table
* `ft_isprint` - checks if the character is printable
* `ft_strlen` - calculates string length
* `ft_memset` - fills memory with a constant byte
* `ft_bzero` - zeros a byte string
* `ft_memcpy` - copies memory area
* `ft_memmove` - copies memory area with overlap handling
* `ft_strlcpy` - copies string to a specific size
* `ft_strlcat` - concatenates string to a specific size
* `ft_toupper` - converts char to uppercase
* `ft_tolower` - converts char to lowercase
* `ft_strchr` - locates character in string (first occurrence)
* `ft_strrchr` - locates character in string (last occurrence)
* `ft_strncmp` - compares two strings
* `ft_memchr` - scans memory for a character
* `ft_memcmp` - compares memory areas
* `ft_strnstr` - locates a substring in a string
* `ft_atoi` - converts ASCII string to integer

### Part 2 - Additional Functions
These functions are either not in the libc, or are present but in a different form:
* `ft_substr` - creates substring from string
* `ft_strjoin` - concatenates two strings
* `ft_strtrim` - trims characters from string
* `ft_split` - splits string using a delimiter
* `ft_itoa` - converts integer to ASCII string
* `ft_strmapi` - applies function to each character in string
* `ft_striteri` - applies function to each character with index
* `ft_putchar_fd` - outputs character to file descriptor
* `ft_putstr_fd` - outputs string to file descriptor
* `ft_putendl_fd` - outputs string with newline to file descriptor
* `ft_putnbr_fd` - outputs number to file descriptor

### Bonus Part
Additional functions for working with linked lists:
* `ft_lstnew` - creates new list element
* `ft_lstadd_front` - adds element at beginning of list
* `ft_lstsize` - counts elements in list
* `ft_lstlast` - returns last element of list
* `ft_lstadd_back` - adds element at end of list
* `ft_lstdelone` - deletes element from list
* `ft_lstclear` - deletes and frees list
* `ft_lstiter` - applies function to all list elements
* `ft_lstmap` - applies function and creates new list

## Getting Started

### Compilation
Run `make` to compile the library. This will create `libft.a`.
Run `make bonus` to compile with bonus functions.
Run `make clean` to remove object files.
Run `make fclean` to remove object files and the library.
Run `make re` to recompile the library.

### Usage
Include the header in your C project:
```c
#include "libft.h"
```

When compiling your project, link the library:
```bash
gcc your_file.c -L. -lft
```

## Testing
The functions have been tested with various test cases and work as expected. You can create your own tests or use existing test frameworks to verify the functionality.

## Notes
- All functions are implemented according to 42's coding standards (norminette)
- Memory management is handled carefully to avoid leaks
- Functions are written to be as efficient as possible while maintaining readability
