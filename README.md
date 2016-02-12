# AlgsProj1
## Compilation
To compile the code simply run the make command in the root directory. This will compile all of the source files into an executable named **dijkstra**.

## Dependencies
No dependencies other than the standard C/C++ libraries are required.

Working on Ubuntu 14.04 with gnu gcc version 4.8.4<br>
Working on Windows 10 with gnu gcc version 4.9.3 (run using CygWin)<br>
Working on Mac OS 10.11.3

## Usage
Run the program using the **dijkstra** command. By default, it will prompt the user for command line input. If you want to input a file, use the **-f** or **--file** flags followed by the path to the input file. To see the help message use the **-h** or **--help** flags.

### Example
**Input from file:** ./dijkstra -f {file_path}<br>
**Input from console:** ./dijkstra

## Output
The program will output all of the possible optional paths from the source to the destination along with their lengths as well as the shortest path using only existing roads along with its length. Additionally, it will explicitly state which, if any, of the optional paths produces a shorter route from source to destination than the shortest path using only existing roads.
