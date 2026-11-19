# Mini Shell Test Plan

## 1. Shell Prompt and Input
- Start the shell and confirm that the prompt appears.
- Press Enter on an empty line and confirm that the shell continues.
- Press Ctrl+D and confirm that the shell exits.

## 2. Command Parsing
- Run `ls -l` and confirm that arguments are handled correctly.
- Run `pwd` and confirm that the command executes.
- Enter an invalid command and confirm that an error is displayed.

## 3. Command Execution
- Run external commands such as `date`, `whoami`, and `ls`.
- Confirm that the shell continues after a command finishes.

## 4. Built-in Commands
- Run `help` and confirm that available commands are displayed.
- Run `cd ..` and confirm that the working directory changes.
- Run `status` and confirm that the previous exit status is displayed.
- Run `exit` and confirm that the shell terminates.

## 5. Background Execution
- Run `sleep 10 &` and confirm that the shell immediately displays another prompt.

## 6. Input and Output Redirection
- Run `echo Hello > output.txt` and confirm that output is saved in the file.
- Run `cat < output.txt` and confirm that the file contents are displayed.

## 7. Signal Handling
- Run `sleep 30` and press Ctrl+C.
- Confirm that the running command is interrupted and the shell remains usable.
