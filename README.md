# The 'Sam' Designer Programming Language

The 'Sam' Designer Programming Language was written by Sam Maryland for a Programming Languages class taught by Dr. John Lusth at the University of Alabama in the Spring of 2019. 

The 'Sam' Language is very similar to C, however it is dynamically typed, meaning variable and function types do not need to be specified. The 'Sam' Language also supports classes/objects, arrays with O(1) access time, conditionals, recursion, iteration, anonymous functions, and functions as first-class objects.

Some built-in functions that the 'Sam' Language provides includes accessing command line arguments, printing to the console, and reading integers from a file.

## Getting Started

'Sam' files will end with the extension '.sam'
After running the command 'make', a file can be run using:
```
./run input/arrays.sam
```

## Comments, Definitions, and Printing

Comments are used with underscores such as:
```
_ This is a comment. _
```

Definitions:
```
VAR a; _ Declare a variable a. _
VAR b = 5; _ Variable b has a value of 5. _
VAR c = "string"; _ Variable c is a string. _
FUNC f(){} _ Define function f with no parameters. _
```

Print to the console using the built in PRINT function:
```
PRINT("This will print to the console.");
```

### Sample 'Hello, World!' Program:
```
_ helloworld.sam _

FUNC main(){
  VAR a = "Hello";
  VAR b = "World!";
  PRINT(a, " ", b, "/n");
}
```
The output of this program will be:
```
Hello World!
```

## Functions

As stated above, functions are defined using the keyword FUNC. Functions will return the last evaluated expression in their body, unless specified by using the keyword RETURN such as:
```
RETURN 0;
```
Where 0 will be returned.

Function calls are the same as C.

### Sample 'Sum' Program:
```
_ sum.sam _

FUNC sum(VAR a, VAR b){
  RETURN a + b;
}

FUNC main(){
  VAR s = sum(5, 7);
  PRINT("The sum of 5 and 7 is: ", s, "/n");
}
```
The output of this program will be:
```
The sum of 5 and 7 is: 12
```

## Anonymous Functions

Anonymous Functions are defined using the keyword LAMBDA, and can be passed and returned between functions, and called with arguments.

### Sample Lambda Program:
```
_ lambda.sam _

FUNC f(VAR x){
  LAMBDA (VAR y){RETURN x + y;};
}

FUNC main() {
  VAR a = f(3);
  VAR b = f(11);
  PRINT("a(5) should be 8 and is ", a(5));  
  PRINT("/n");   
  PRINT("b(6) should be 17 and is ", b(6)); 
  PRINT("/n");    
  PRINT("a(10) should be 13 and is ", a(10));
  PRINT("/n");    
}
```
The output of this program will be:
```
a(5) should be 8 and is 8
b(6) should be 17 and is 17
a(10) should be 13 and is 13
```

## Conditionals

The 'Sam' Language supports conditionals such as:
* If
```
IF () {}
```
* Else If
```
ELSE IF () {}
```
* Else
```
ELSE {}
```
* Equals
```
==
```
* Not Equals
```
!=
```
* Less Than
```
<
```
* Less Than or Equal To
```
<=
```
* Greater Than
```
>
```
* Greater Than or Equal To
```
>=
```
* And
```
&
```
* Or
```
|
```
### Sample Conditionals Program:
```
_ conditionals.sam _

FUNC conditionals(VAR v) {
  IF (v == "case 1") {
    PRINT(v, " is case 1");
    PRINT("/n");
  } 
  ELSE IF ((v > 10) & (v < 15)) {
    PRINT(v, " must be between 10 and 15");
    PRINT("/n");
  } 
  ELSE IF ((v == 1) | (v == 9)) {
    PRINT(v, " is either 1 or 9");
    PRINT("/n");
  } 
  ELSE IF (v != 0) {
    PRINT(v, " is not equal to 0");
    PRINT("/n");
  } 
  ELSE {
    PRINT(v, " must meet none of the other cases!");
    PRINT("/n");
  }
}

FUNC main() {
  conditionals("case 1");
  conditionals(12);
  conditionals(1);
  conditionals(9);
  conditionals(-1);
  conditionals(0);
}
```
The output of this program will be:
```
case 1 is case 1
12 must be between 10 and 15
1 is either 1 or 9
9 is either 1 or 9
-1 is not equal to 0
0 must meet none of the other cases!
```

## Iteration and Loops
Iteration can be achieved by looping with the keyword WHILE:
```
WHILE () {}
```
### Sample Iteration Program:
```
_ iteration.sam _

FUNC iter(VAR n) {
  PRINT("n begins as: ", n);
  PRINT("/n");
    WHILE (n > 0) {
    --n;
    PRINT("n is now: ", n);
    PRINT("/n");
  }
}

FUNC main() {
  iter(10);
}
```
The output of this program will be:
```
n begins as: 10
n is now: 9
n is now: 8
n is now: 7
n is now: 6
n is now: 5
n is now: 4
n is now: 3
n is now: 2
n is now: 1
n is now: 0
```

## Arrays
There are several built-in functions for arrays in the 'Sam' Language. Arrays support different types, so you can can have one array including strings, integers, and even other arrays!

You can declare an initialized array using:
```
VAR a = array(1, 2, 3, 4);
``` 
Or declare an uninitialized array using:
```
VAR a = arrayOfSize(size);
``` 
You can get the size of an array using:
```
VAR size = sizeArray(a);
```
You can set the value of an array at a certain index using:
```
setArray(a, index, "value");
```
You can get the value of an array at a certain index using:
```
VAR a = getArray(a, 0):
```
### Sample Arrays Program:
```
_ arrays.sam _

FUNC f(VAR a, VAR b) {
  RETURN a * b;
}

FUNC main() {
  _ Declare an array using array(arguments) _
  VAR a = array(1, 3.123, f(3,4), "3", "my name is sam"); 
  PRINT ("Array a is: ");
  PRINT("/n");
  PRINT (a);
  PRINT("/n");
  
  _ Get the size using sizeArray(array) _
  PRINT ("The size of a is: ", sizeArray(a));
  PRINT("/n");
  
  _ Set the value at an index using setArray(array, index, value) _
  setArray(a, 1, "updated value");
  PRINT ("Updated a[1] to 'updated value'");
  PRINT("/n");
  PRINT (a);
  PRINT("/n");
  
  _ Get the value at an index using getArray(array, index) _
  PRINT ("Value at index 4: ", getArray(a, 4));
  PRINT("/n");
}
```
The output of this program will be:
```
Array a is:
(1, 3.123, 12, 3, my name is sam)
The size of a is: 5
Updated a[1] to 'updated value'
(1, updated value, 12, 3, my name is sam)
Value at index 4: my name is sam
```

## Objects
Objects can be declared using the keyword STRUCT such as:
```
STRUCT obj{};
```
Then set to a variable such as:
```
VAR a = obj();
```
You can set and get certain fields using '.' such as:
```
VAR a = obj.data;
```
### Sample Objects Program:
```
_ objects.sam _

STRUCT obj{
  VAR int = 0;
  FUNC setInt(VAR i){int = i;}
  FUNC getInt(){RETURN int;}
};

FUNC main(){
  VAR a = obj();
  VAR b = a.int;
  a.setInt(5);
  VAR d = a.getInt();

  PRINT("b is: ", b, "/n");
  PRINT("d is: ", d, "/n");
}
```
The output of this program will be:
```
b is: 0
d is: 5
```
## Test Problem
The 'Sam' Language was used to create an AVL tree implementation located in 'iAVL'. You can run the sample problem using:
```
./run iAVL input/commands
```
The output of this program will be:
```
1(2+) 2+(3-) [3-] 5(6-) 6-(3-) 7(8+) 8+(6-)
```
## Using the Makefile
* Make commands without an x will print the contents of the source code.
* Make commands that end with an x will run the source code.
* The supplied makefile responds to the commands:
```
make
make error1             _ Showcases Error functionality _
make error1x
make error2
make error2x
make error3
make error3x
make error4
make error4x
make error5
make error5x
make arrays
make arraysx
make conditionals
make conditionalsx
make recursion
make recursionx
make iteration
make iterationx
make functions
make functionsx
make lambda      
make lambdax      
make objects      
make objectsx 
make problem          _ AVL Test Problem _
make problemx
make test             _ Runs all above commands _
make clean
```