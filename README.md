# Doubly Linked List implementation in C++

This project provides a C++ implementation of a Doubly Linked List data structure. The implementation is templated,
allowing it to store any data type. List supports common operations such as insertion, deletion, searching, as well as
utility functions for converting list to a string representation.

## Table of Contents

- [Features](#features)
- [API Documentation](#api-documentation)
- [Example Usage](#example-usage)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Templated Implementation:** Works with any data type.

- **Common Operations:**

    - Insertion at the front (`push_front`) and back (`push_back`).

    - Deletion from the front (`pop_front`) and back (`pop_back`).

    - Removal of specific elements (`remove_specific`).

- **Searching:** Find elements using a custom comparison function or default arithmetic comparison.

- **Indexing:** Access elements using the `[]` operator.

- **String Representation:** Convert the list to a string for easy visualization.

- **Memory Management:** Automatically deallocates memory when the list is destroyed.

## API Documentation

### Class: `DoubLinList<T>`

#### Template Parameters:

- `T`: The type of data stored in the list.

### Public Methods

#### Constructors:

- `DoubLinList()`: Creates an empty list.

#### Destructor:

- `~DoubLinList()`: Automatically deallocates all nodes.

#### Insertion:

- `void push(T data)`: Alias for `push_back` (adds to end).
- `void push_front(T data)`: Inserts `data` at the front.
- `void push_back(T data)`: Inserts `data` at the end.

#### Deletion:

- `bool pop()`: Alias for `pop_front` (removes from front).
- `bool pop_front()`: Removes the front node. Returns `true` if successful.
- `bool pop_back()`: Removes the last node. Returns `true` if successful.
- `bool remove_specific(T key, ...)`: Removes the first occurrence of `key`. Uses `operator==` by default.

#### Search:

- `Node* find(T key, ...)`: Returns the first node containing `key`. Uses `operator==` by default.

## Example Usage

```cpp
#include "DLL.h"
#include <iostream>

int main() {
    DoubLinList<int> list;
    
    list.push_back(10);
    list.push_front(20);
    list.push(30);
    std::cout << list.to_str() << std::endl; // Output: [20, 10, 30]
    
    list.pop_back();
    std::cout << list.to_str() << std::endl; // Output: [20, 10]
    
    std::cout << list[1] << std::endl; // Output: 10
    
    return 0;
}
```

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/nonofare/Doubly_Linked_List.git
   ```

2. **Include the `DLL.h` file in your project.**

3. **Compile your project with a compiler that supports C++17 or later.**

## Contributing

Please open an issue or submit a pull request for any improvements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
