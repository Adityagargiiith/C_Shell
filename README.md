# Description

# Assumptions
1. A history.txt file is present
2. Pastevents commands are not stored in the text file 
3. System calls like cd, ls~ are not given as input because excevp does not take them as system call
4. In peek command i have assumed that the hidden files will be at the top and no files will start with a special character
5. Not more than 3 arguments will be given in peek command
6. If a command takes more than 2 seconds other than the commands implemented by ourselves, than that command will be displayed
along with its time taken in the next line after enter instead of displaying it in prompt
7.  If -e flag is enabled but the directory does not have access permission (execute) or file does not have read permission, then no output is printed.


