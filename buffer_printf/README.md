# Task
Write a wrapper over printf that will add buffering. The text should be added to a dedicated buffer of some size, after filling which (or with the help of an additional call), a real call to printf should occur with output to the screen.

You can compare the efficiency with std::cout. anything can be used for implementation, the only condition is that work with the buffer itself must be done manually. Selection, re-allocation, freeing, filling, cleaning, reading - all this must be done by hand. For any intermediate steps, you can use at least the entire STL, at least boost.