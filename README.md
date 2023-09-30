# Bombs Excercise

### This repository is a solution to the following problem:

There is a rectangular stack of size R on C. R is the number of rows, and C is the number of columns. The cells in the grid can either be empty or contain a bomb.

The bomb can be installed in any cell of the grid, but if this happens, it will explode in exactly 3 seconds. The exploding bomb is destroyed along with everything that is in the adjacent cells. Ie, if the bomb explodes in some cell, then all cells that have a common side with the exploded one are emptied. If there is a bomb in the conjugate cell, then it is destroyed without an explosion. There is no chain reaction.

The grid lives by the following algorithm:

1. At the very beginning, the bombs are randomly distributed across the grid
2. In the next second, nothing happens.
3. After another second, bombs are installed in all free cells. The grid becomes filled with bombs.
4. After another second, all the bombs that were installed 3 seconds ago explode.
5. Then steps 3 and 4 are repeated indefinitely.

Bombs that are installed in one second are installed at exactly the same moment. They will explode together.

Having the initial state of the grid, calculate its state after a given number of seconds N.

### Input format
Input: input.txt

The first line contains three space-separated numbers specifying R, C, and N.

Each subsequent line of input data contains a sequence of characters that specifies the initial state of the grid for one line. Symbol. sets an empty cell, and the O (ASCII 79) character marks the bomb.

### Restrictions:
1≤R,C≤200

1≤N≤100000

### Output format
Output: output.txt

String representation of the final state of the grid after N seconds. R lines, each of which contains C characters. Characters can only be . or O (ascii 79).

### Example
Input:
```
6 7 3
.......
...O...
....O..
.......
OO.....
OO.....
```
Output:
```
OOO.OOO
OO...OO
OOO...O
..OO.OO
...OOOO
...OOOO
```
### Notes
The initial state of the grid:
```
.......  
...O...  
....O..  
.......  
OO.....  
OO.....
```
Nothing happens in the first second, so the state is one second later:
```
.......  
...O...  
....O..  
.......  
OO.....  
OO.....
```
Bombs are placed in all empty cells so that after 2 seconds the grid state will become:
```
OOOOOOO  
OOOOOOO  
OOOOOOO  
OOOOOOO  
OOOOOOO  
OOOOOOO
```
Bombs set 3 seconds ago explode. The final state of the grid in 3 seconds:
```
OOO.OOO  
OO...OO  
OOO...O  
..OO.OO  
...OOOO  
...OOOO
```
### Evaluation of the result

In addition to the correct operation of the application and its ability to calculate the state of the grig for long periods of time, the quality of the code will also be evaluated: reasonable architecture, maintainability, ease of making changes, etc.
