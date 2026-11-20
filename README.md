# MINI SHELL — C Programming Project

**Student Name:** John Karusa  
**Registration Number:** SCT212-0450/2024  
**Programming Language:** C  
**Operating System:** Linux  
**Repository:** [Mini Shell on GitHub](https://github.com/Bashan-56/msh-SCT212-0450-2024)

---

## 1. Introduction

Mini Shell is a simplified command-line interpreter developed using the C programming language on Linux. The project demonstrates fundamental operating system concepts, including process creation, program execution, process synchronisation, input/output redirection, background execution and signal handling.

The shell provides an interactive environment where users can enter commands, execute external programs and perform basic shell operations.

## 2. Project Objectives

The main objectives of this project are to:

- Understand how command-line shells operate.
- Implement process creation and execution using system calls.
- Understand parent and child process relationships.
- Implement basic command parsing and execution.
- Demonstrate input and output redirection.
- Support background processes.
- Understand and implement basic signal handling.

## 3. Implemented Features

The following features have been implemented:

| No. | Feature | Description | Status |
|---|---|---|---|
| 1 | Command prompt | Displays a prompt and accepts user input. | Completed |
| 2 | Command parsing | Separates commands into arguments. | Completed |
| 3 | Process creation | Uses `fork()` to create child processes. | Completed |
| 4 | Command execution | Uses `execvp()` to execute external programs. | Completed |
| 5 | Built-in commands | Supports `cd`, `help` and `exit`. | Completed |
| 6 | Exit status | Tracks and displays the previous command's exit status using `status`. | Completed |
| 7 | Background execution | Supports commands ending with `&`. | Completed |
| 8 | I/O redirection | Supports input `<` and output `>` redirection. | Completed |
| 9 | Signal handling | Handles Ctrl+C so the shell can remain active when a foreground command is interrupted. | Completed |

## 4. Requirements

To compile and run the project, you need:

- A Linux operating system or compatible Linux environment.
- GCC compiler.
- A terminal.
- Basic knowledge of Linux commands.

## 5. Compilation and Execution

Clone the repository:

```bash
git clone https://github.com/Bashan-56/msh-SCT212-0450-2024.git
```

Navigate into the project directory:

```bash
cd msh-SCT212-0450-2024
```

Compile the source code:

```bash
gcc -Wall -Wextra -o msh main.c
```

Run the shell:

```bash
./msh
```

To exit the shell, enter:

```bash
exit
```

## 6. Design and Implementation

The Mini Shell is implemented in C and uses Linux system calls and standard library functions to provide basic command-line functionality.

The program begins by displaying a command prompt and reading user input using the `getline()` function. This allows the shell to accept commands of different lengths. Empty input is ignored, while end-of-file input is handled to allow the shell to terminate correctly.

After receiving a command, the shell processes the input using string-tokenisation techniques. The `strtok()` function separates the command and its arguments into an argument vector (`argv`), which is terminated with a NULL pointer. This format is required by the `execvp()` function.

For external commands, the shell uses `fork()` to create a child process. The child process executes the requested program using `execvp()`, while the parent process uses `waitpid()` to wait for foreground processes to finish. This separation allows the shell to continue operating after individual commands have completed. Built-in commands such as `cd`, `help`, `status` and `exit` are handled directly by the shell because they affect its internal state or operation.

Background execution is implemented by detecting the `&` symbol at the end of a command. When this symbol is present, the parent shell does not wait for that child process to finish before displaying another prompt.

Input and output redirection are implemented using file-handling system calls. The `open()` function opens the specified file, while `dup2()` redirects the standard input or output to the opened file. The `close()` function is used to close file descriptors that are no longer required.

Finally, signal handling is implemented using `signal()`. The shell ignores the SIGINT signal, while child processes restore the default SIGINT behaviour before executing external commands. This allows Ctrl+C to interrupt a running foreground command without terminating the shell itself.

## 7. Testing

The project was tested using different commands and operations to verify its functionality.

Examples of tests include:

- Executing commands such as `ls`, `pwd` and `date`.
- Testing invalid commands.
- Testing built-in commands.
- Testing command exit status.
- Running background commands using `&`.
- Testing input and output redirection.
- Interrupting a running command using Ctrl+C.
- Testing shell termination using `exit` and Ctrl+D.

A more detailed test plan is available in:

`tests/test_plan.md`

## 8. Project Structure

```text
msh-SCT212-0450-2024/
│
├── main.c
├── README.md
├── .gitignore
│
└── tests/
    └── test_plan.md
```

**File descriptions:**

- `main.c` – Contains the Mini Shell source code and implementation.
- `README.md` – Provides project documentation and instructions.
- `.gitignore` – Specifies files that should not be tracked by Git.
- `tests/test_plan.md` – Contains the test cases used to verify the shell.

## 9. Known Limitations

The Mini Shell implements basic command-line functionality but has some limitations:

- Command pipelines using `|` are not supported.
- Quoted arguments containing spaces are not fully supported.
- Environment-variable expansion is not implemented.
- Advanced shell scripting features are not supported.
- Redirection is limited to basic input (`<`) and output (`>`) operations.
- Background process management is basic. The shell does not implement full job control or actively reap completed background processes while running.
- The shell does not support advanced terminal job management features.

## 10. Conclusion

The project demonstrates the practical application of operating system concepts through the development of a basic command-line shell. It provides an understanding of process management, system calls, command parsing, file descriptors and signal handling.

The implementation also provides a foundation for understanding how more advanced command-line interpreters operate.

## 11. References

1. Linux Manual Pages – `fork(2)`, `execvp(3)`, `waitpid(2)`, `open(2)`, `dup2(2)` and `signal(2)`.
2. GNU C Library Documentation.
3. Linux Programmer's Manual.
4. OpenAI ChatGPT – Used as an AI-assisted learning and documentation support tool. The implementation was tested and reviewed by the student.

## 12. Declaration of AI Assistance

AI assistance was used to support understanding of programming concepts, debugging, and improving project documentation. The student is responsible for reviewing, understanding, testing and presenting the submitted implementation.