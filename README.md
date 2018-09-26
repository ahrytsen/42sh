# 42sh :+1:
This project is about writing the most stable and most complete UNIX(POSIX) shell possible.
There are many other shells, such as bash, csh, tcsh, ksh, ash, etc. 42sh shell tries to replicate there basic behavior.

## What is currently working:
* The following builtins including all their features if they have any (the strict minimum being the features listed in `POSIX` standard):
  * `alias`
  * `!`
  * `history`
  * `export`
  * `read`
  * `exec`
  * `cd`
  * `echo`
  * `exit`
  * `env`
  * `setenv`
  * `unsetenv`
* The following logical operators "&&" and "||".
* The ";" separator.
* Inhibitors: `"` (double quote), `’` (simple quote) and `\` (backslash).
* Redirections: `>`, `>|`, `>>`, `<`, `<>`, `<<`(heredoc), `<<-`, `<<<`(herestr), `>&`, `<&`, `&>`, `&>>`.
* Pipelines: `|`.
* Globbing: `*`, `?`, `[]`, `{}` (without using the `glob(3)` function!).
* Command substitution: `‘` and `$()`.
* Sub shells using the `()` operators.
* Local variables and unset and export builtins.
* Command history and `history` and `!` builtins including all their features.
* Line edition (simple reimplement famous GNU readline library):
  * Edit the line where the cursor is located.
  * Move the cursor left and right to be able to edit the line at a specific location.
  * Use up and down arrows to navigate through the command history which we will then be able to edit if we feel like it (the line, not the history)
  * Cut, copy, and/or paste all or part of a line.
  * Move directly by word to word the left or the right.
  * Go directly to the beginning or the end of a line by pressing home and end.
  * Write AND edit a command over a few lines. (alt+UP and alt+DOWN allow to go from one line to another in the command while remaining in the same column or otherwise the most appropriate column.)
  * Completely manage quotes and double quotes, even on several lines (expansions excluded).
* Dynamic autocompletion.
* File descriptors(`exec`) and the `read` with all its features.
* Shell scripts
* __Job control the `jobs`, `fg` and `bg` builtins, and the `&` operator.__
