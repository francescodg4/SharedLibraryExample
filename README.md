# Shared library example

An example library to be used as a template project for production.

## ABI-Safe `Array<T>` with Pimpl

This library implements an **ABI-safe `Array<T>`** using the **Pimpl (private implementation) idiom**, ensuring compatibility across different compiler versions.

The `Array<T>` holds a pointer to a forward-declared `ArrayImpl` struct. This approach allows the internal implementation—including complex data structures and STL containers like `std::vector`—to be completely hidden from the user.

To ensure proper resource management and prevent memory leaks, all five special member functions (the **Rule of Five**) are explicitly defined: the constructor, copy constructor, move constructor, copy assignment operator, and move assignment operator, along with the destructor. The **copy-and-swap idiom** is used for the assignment operators to provide strong exception safety.

New `Array<T>` types can only be defined within the library itself. Users cannot define custom `Array<T>` types because the `ArrayImpl` struct, which contains the internal data, must be defined and instantiated internally by the library.

Similarly, methods like `std::vector::emplace_back` are not directly accessible to the user.
