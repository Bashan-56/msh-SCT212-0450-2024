# Mini Shell

**Student Name:** John Karusa  
**Registration Number:** SCT212-0450/2024  
**Project:** Mini Shell

## 1. Project Description

This project implements a simple command-line shell using the C programming language on Linux. It allows users to enter commands, execute external programs, use built-in commands, run processes in the background, redirect input and output, and handle keyboard interrupts.

## 2. Compilation and Execution

Compile the program:

```bash
gcc -Wall -Wextra -o msh main.c
```

Run the shell:

```bash
./msh
```

## 3. Implemented Tasks

- [x] Display a command prompt and handle user input.
- [x] Parse commands and their arguments.
- [x] Execute external commands using `fork()` and `execvp()`.
- [x] Implement built-in commands: `cd`, `help`, and `exit`.
- [x] Track and display command exit status using `status`.
- [x] Support background execution using `&`.
- [x] Support input (`<`) and output (`>`) redirection.
- [x] Handle Ctrl+C using signal handling.

## 4. Design Explanation

The shell reads commands from the user using `getline()`. It then separates the command into arguments using tokenisation.

For external commands, the shell creates a child process using `fork()`. The child process executes the requested program using `execvp()`, while the parent process waits for foreground commands using `waitpid()`.

Built-in commands such as `cd`, `help`, `status`, and `exit` are handled directly by the shell because they affect its internal state or behaviour.

Background commands are identified using the `&` symbol, allowing the shell to continue accepting commands without waiting for the background process to finish.

Input and output redirection are implemented using `open()` and `dup2()`. Signal handling allows the shell to remain active when Ctrl+C interrupts a running foreground command.

## 5. Known Limitations

- Command parsing does not support advanced shell features such as pipes.
- Quoted arguments and environment-variable expansion are not fully supported.
- Redirection supports basic input and output operations only.
- Background process management is basic.

## 6. Testing

Testing instructions and test cases are provided in `tests/test_plan.md`.

## 7. References

- Linux manual pages: `fork(2)`, `execvp(3)`, `waitpid(2)`, `open(2)`, and `dup2(2)`.
- GNU C Library documentation.
- OpenAI ChatGPT (AI assistance for learning, debugging, and documentation).
