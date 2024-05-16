# C-SHELL

_Made for an assignment for our Course OS&N 2023-24._

_ The Shell is completely coded in `C`._

## Build & Run
1. `makefile` (For building the executable file)
2. `./a.out` 

## ABOUT
: _This C-SHELL_ is a replica of the existing shell present in linux but has a limited functionalities.

As of right now, it has some of the following features:

- Vibrant shell display that shows the current directory, username, and hostname.
- Capable of executing several built-in commands (with the -a and -l flags) such `cd`, `echo`, `pwd` and ,`ls`}.
- The commands have seperate name like warp for `cd`, peek for `ls` etc.
- Saves `history` for each session for a maximum of 15.
- Error Correction
- Can execute both `background` qand `foreground` processes. (For more shell instructions)
- Executing several commands with `;` in a single line.
- To leave the shell, use `exit`.
- I/O Redirection with <& >/>> and pipes.
- Handling Signals (Ctrl-C, Ctrl-Z, Ctrl-D)

If want to know more about commands and the functionalities the shell can perform , the assignment is present in the following link.
- https://karthikv1392.github.io/cs3301_osn/mini-projects/mp1

