# Treasure Map Decoder Algorithm

### Arshdeep Jaggo ###

### Project *Details* and *Description*:
Used breadth-first traversal on individual pixels of an image to find the shortest path to the point that is farthest from the start in the embedded maze.
The original maze path can not be seen by the naked eye due to little difference between solution pixels and non-solution pixels. Once solution is found it then renders a visible solution for the user to see by following the solution pixels n changing the color of them. An image of all possible solutions can be rendered as well, which essentially gives an image of the maze. Additionally the returned image contains a 7x7 red pixel of where the starting position is.

