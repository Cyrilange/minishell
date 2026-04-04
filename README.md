# Minishell

A minimal Unix shell written in C, developed as part of the 42 curriculum.  
This project aims to recreate core shell behavior, including command parsing, execution, and process management.

---

## 🚀 Features

- Execution of external commands
- Built-in commands (echo, cd, pwd, export, unset, env, exit)
- Environment variable management
- Pipes (`|`)
- Redirections (`>`, `>>`, `<`)
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
- Exit status handling (`$?`)
- Basic parsing and tokenization

---

## 🛠️ Installation

Clone the repository and compile:

```bash
git clone <your-repo-url>
cd minishell
make
```

---

## ▶️ Usage

Run the shell:

```bash
./minishell
```

Example usage:

```bash
minishell$ echo Hello World
Hello World

minishell$ ls -l | grep minishell

minishell$ cat file.txt > output.txt

minishell$ echo $HOME
```

---

## 🔧 Makefile Commands

```bash
make        # Compile the project
make re     # Recompile everything
make clean  # Remove object files
make fclean # Remove object files and executable
```

---

## 🧠 How it works

Minishell reproduces the behavior of a Unix shell through several steps:

1. **Input reading**
   - Reads user input from the terminal

2. **Parsing**
   - Tokenizes the input (commands, arguments, pipes, redirections)

3. **Execution**
   - Handles built-in commands internally
   - Uses `fork` and `execve` for external commands

4. **Pipes & Redirections**
   - Manages file descriptors
   - Connects commands using pipes

5. **Signal handling**
   - Handles Ctrl+C, Ctrl+D, Ctrl+\ properly

---

## 📦 Example

```bash
$ ./minishell
minishell$ export NAME=Cyril
minishell$ echo $NAME
Cyril
minishell$ ls | grep .c
main.c
parser.c
executor.c
```

---

## 🎯 Project Goals

- Understand how a shell works internally
- Master process management (`fork`, `execve`, `wait`)
- Work with file descriptors and pipes
- Build a parser from scratch
- Handle Unix signals properly

---

## 👨‍💻 Author

Cyrilange, mariogo2
