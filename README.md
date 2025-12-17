*This project has been created as part of the 42 curriculum by **oused-da***

# ft_printf

## Description

**ft_printf** is a project at 42 School that involves recoding the standard C library function `printf`. The primary goal of this project is to learn about **variadic functions** in C functions that can take a variable number of arguments and to practice structured memory management and string formatting

This implementation mimics the behavior of the original `printf` for a specific set of format specifiers. It is compiled as a static library (`libftprintf.a`), allowing it to be easily included and reused in future C projects

1. Features:

The function prototype is:
```c
int ft_printf(const char *s, ...);
```
It handles the following conversions:
* `%c` : Prints a single character
* `%s` : Prints a string
* `%p` : The void * pointer argument has to be printed in hexadecimal format
* `%d` : Prints a decimal (base 10) number
* `%i` : Prints an integer in base 10
* `%u` : Prints an unsigned decimal (base 10) number
* `%x` : Prints a number in hexadecimal (base 16) lowercase format
* `%X` : Prints a number in hexadecimal (base 16) uppercase format
* `%%` : Prints a percent sign

2. Technical Details:

This project utilizes the `<stdarg.h>` library to handle variadic arguments:
* `va_start`: Initializes the argument list
* `va_arg`: Retrieves the next argument in the list based on the specified type
* `va_end`: Cleans up the memory associated with the argument list.

## Instructions

1. Compilation:

To compile the library run the following command in the root of the repository:
```Bash
make
```
This will generate the static library file `libftprintf.a`
```bash
make clean  #Removes object files (.o)
make fclean #Removes object files and the library (.a)
make re     #Recompiles the entire project
```
2. Usage:

To use ft_printf in your own code include the header file and link against the library
Example `main.c`:
```c
#include "ft_printf.h"

int main()
{
    ft_printf("Hello, %s! The number is %d.\n", "World", 42);
    ft_printf("Hex: %x, Ptr: %p\n", 255, (void *)0x1234);
}
```
Compiling with your code:
```Bash
cc main.c libftprintf.a -o ft_printf
./ft_printf
```
## Resources:

1. References:
* `man printf`: The standard manual page for printf behavior
* `man 3 stdarg`: Manual page for variable argument lists
* [C Library - <stdarg.h>](https://www.tutorialspoint.com/c_standard_library/stdarg_h.htm): Documentation on variadic macros.
* [Oceano](https://youtu.be/7Sph8JlRo0g) Youtube vedio explaining variadic functions
2. AI Usage:
AI tools (Gemini) were used in the development of this project for the following tasks:
* **Concept Explanation**: To gain a deeper understanding of variadic functions, specifically the underlying mechanisms of the Stack, CPU Registers, and how va_list interacts with system calling conventions
* **Testing**: To generate comprehensive test cases, including edge cases and comparisons against the standard printf behavior to ensure accuracy