# minishell

This project is to recreate a "mini" shell using only C.
It asks for user input and tries to execute the command.
It accepts input (heredocs & files), output (files) and command names with or without options.
A basic line a user can type would be : ls -R | grep ".ext" > output_file

We had to code a few builtins functions.
A builtin function is a function that can be called even when no environment variable exists because it is inseparable from the program.
We had to code them with the minishell:
  - Echo
  - Pwd
  - Exit
  - Cd
  - Env
  - Export
  
