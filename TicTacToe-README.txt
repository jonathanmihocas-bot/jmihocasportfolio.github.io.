Tic-Tac-Toe Mini Project
Course: ENGG1410 - Introductory Programming for Engineers
Project: Mini Project #1 (Part 1 & 2)

Description
This project is a C-based simulation of the classic Tic-Tac-Toe game. It supports
customizable grid sizes (from 3x3 to 10x10) and features two game modes:
1.​ Player vs. Player: Two human players alternate turns.
2.​ Player vs. AI: A human player competes against a computer opponent. The AI
utilizes a defense/attack strategy to block winning moves and capitalize on
opportunities.
Additionally, this version includes File I/O capabilities, allowing users to save their
game progress and resume it later.

Files Included
●​ TicTacToe.c: The main source code file containing the game logic, AI, and file
handling.
●​ ticktock.dat: Binary data file used to store saved game states (created
automatically).
●​ README: This documentation file.

Prerequisites & Compilation
This program is written in C. It includes <conio.h>, which is standard for Windows
environments (MinGW/Visual Studio).

How to Compile
You can compile the code using GCC (GNU Compiler Collection) or any standard C
compiler.
Using Command Prompt / Terminal:

gcc TicTacToe.c -o tictactoe​
Note for Non-Windows Users (Linux/Mac):

The source code includes <conio.h>. If you are compiling on Linux or macOS, you may
need to remove that include line if it causes errors, as the core logic relies primarily on
standard <stdio.h> functions (scanf, getchar).

How to Run
After compiling, execute the program from the command line:
Windows:

tictactoe.exe
Linux/Mac:

./tictactoe​

How to Play
Main Menu
Upon starting, you will be presented with a menu:
1.​ New Game: Start a fresh session. You will be asked to enter a grid size (3-10) and
choose the game mode.
2.​ Load Game: Resume a previously saved game from ticktock.dat.
3.​ Exit: Close the application.

In-Game Controls
●​ Grid Coordinates: The board uses 1-based indexing.
●​ Making a Move: When prompted, enter the Row Number followed by the
Column Number separated by a space.
○​ Example: To place a marker in the top-left corner, enter: 1 1

Save & Quit Functionality
To implement the requirement for File I/O, the save feature is triggered during the
input phase.
1.​ Triggering Save: When asked for a "Line" and "Column", enter a negative
number (e.g., -1 -1).
2.​ Confirmation: The game will display: Do you want to save? Y/N.
3.​ Saving: Press Y (or y) to save your current board, scores, and round number. The
game will save to ticktock.dat and exit.

4.​ Loading: Select Option 2 from the main menu next time you run the program to
pick up exactly where you left off.

Notes
●​ AI Logic: The computer analyzes rows, columns, and diagonals to calculate a
"percentage of win." If the threat is high, it defends; otherwise, it attempts to
attack.
●​ Visuals: The game uses ANSI color codes (Green for 'X', Yellow for 'O') for better
visibility in supported terminals.

