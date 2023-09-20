# 0x16. C - Simple Shell
This is an implementation of sh, the bourne shell, which is the old standard
installed on all unix systems [more...](https://man7.org/linux/man-pages/man1/sh.1p.html)

The shell is the command interpreter that takes your input, commands and provides output
back to the screen, files, etc, [more...](https://github.com/rcgsheffield/linux-shell/blob/master/README.md)

## TODO:

- [x] No memory leaks
- [x] Add the ability to insert multilines commands using echo
- [x] Fix the issue with the error mimicing
- [x] Fix: non-existed command longer than 2 char.
- ~~[ ] Fix: ctl+c prompt again, and exit in case ./shell | "ls"~~
- [x] Fix: ctl+d exits, and fix "getline: Success"
- [x] Fix: the passed arguments: $ echo arg1 arg2
- [x] Add: implement strcat();
- [x] Add: create a function to free the linked list.
- [x] Fix: _getenv();
- [x] Add: mimic the errors in sh
- [x] Implement the exit built-in, that exits the shell
- [x] Implement the env built-in, that prints the current environment
- [x] Implement the getline function #6
- [x] Implement the strtok function #7
- [x] Handle arguments for the built-in exit #8
- [-] Implement setenv #9
- [-] Implement unsentenv #9
- [-] Implement the builtin command cd #10
- [ ] Handle the command separator ; #11
- [ ] Handle the && and || shell logical operators #12
- [ ] Implement the alias builtin command #13
- [ ] Handle variables replacement, $? and $$ #14
- [ ] Handle comments (#) #15
- [ ] File as input: simple_shell [filename] #16

## NOTES:
