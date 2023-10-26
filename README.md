# BigInteger Library

This repository contains a C library for working with arbitrarily large integers, commonly referred to as "big integers." Big integers are used to perform arithmetic operations with integers that exceed the limits of standard data types like `int` or `long`.

## Features

- **Arithmetic Operations**: The library provides functions for addition, subtraction, multiplication, division, and modulus operations on big integers.

- **Initialization**: You can initialize a big integer from a string representation.

- **Comparison**: Compare two big integers.

- **Display**: Print the value of a big integer to the console.

## Getting Started

To use the BigInteger library, follow these steps:

1. Clone the repository to your local machine.

2. Include `BigInteger.c` and `BigInteger.h` in your C project.

3. Initialize big integers using the `initialize` function, perform operations, and display results using the provided functions.

4. Make sure to link `BigInteger.c` with your project during compilation.

## Usage

Here's a basic example of using the BigInteger library:

```c
#include <stdio.h>
#include "BigInteger.h"

int main() {
    struct BigInteger a = initialize("123456789012345678901234567890");
    struct BigInteger b = initialize("98765432109876543210987654321");

    printf("Number 1: ");
    display(a);

    printf("Number 2: ");
    display(b);

    struct BigInteger add_result = add(a, b);
    printf("Addition: ");
    display(add_result);

    // Perform other operations as needed

    return 0;
}
