#Homework 1

##Description

In this assignment, I implemented a reverse polish notation calculator.

##Specifications:

It outputs a single ">" followed by a space to prompt the user to enter an equation. On a separate line, the result is outputted. The program repeats as long as the input stream remains valid.

All tokens are separated by a space. Valid tokens are either numbers of operators. If an invalid token is entered, the output is: `Error: Invalid token.`

If an invalid equation is entered, you must report an error saying why it is invalid. For example, the equation "3 4 5 +" is invalud because after applying the `+` operator, we are left with the equation "3 9" which is not a number. The error message in this case should be `Error: Not enough operators." On the other hand, the equation "3 +" is invalid because `+` needs two parameters to add together. The error message in this case should be: `Error: Not enough parameters.`

The following operators are supported: `+ - * / %`

##Example Output

```
> 3 4 +
7
> 3 -4 +
-1
> 3 4 -
-1
> 3 4 5 +
Error: not enough operators
> 3 +
Error: not enough parameters
> 3 hotel
Error: invalid token
> 3 4 /
0.75
> 3 4 5 + *
27
> 1 2 + 3 4 - / 12 * -1 -
-35
> ^D
```
