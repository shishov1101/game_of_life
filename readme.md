# Game of life

Conway’s Game of Life is a cellular automaton invented by John Conway in 1970. The game world consists of an infinite two-dimensional grid of cells, each of which is either “dead” or “alive” in each “generation.” The game comes with a “rule” that explains how to calculate the state of a cell in the next generation. To find (“evolve”) the next generation, each cell looks at the eight cells next to it (vertically, horizontally or diagonally), checks which of these are dead or alive in the current generation and then uses this rule to decide whether the cell should be alive in the next generation. There are various rules one can use to evolve the next generation. Conway’s rule is as follows:

1. If a cell is alive in the current generation and exactly two or three of its neighbours are alive, then it will be alive in the next generation.

2. If a cell is dead in the current generation and exactly three of its neighbours are alive, then it will be alive in the next generation.

3. Otherwise, the cell will be dead in the next generation.

The file format for valid input and output files: each line represents one row of the grid and each character represents one cell on that row: ‘*’ represents a live cell and ‘.’ represents a dead cell. For example:

.........................

.........................

.........................

........***..............

.........................

.........................


In the functions below, the rows are numbered 0, 1, 2, ... from top to bottom and the columns are numbered 0, 1, 2, ... from left to right. In any valid file, there will be at most 512 columns; the number of rows is not limited.


## Calibration start
Your program must support the following commandline switches:

`-i` `input_filename` to specify that the initial generation of the universe should be read from a file.

`-o` `output_filename` to specify a file into which the final generation should be output.

`-g` `number_of_generations` to specify the number of new generations for which the game should be run.

`-s` to print statistics after the final generation has been output.



Make file has two options `build` and `clean`