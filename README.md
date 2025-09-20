# 🐚 Minishell

Minishell is a **minimal Unix shell** written in C, developed as part of the [42 School](https://42.fr) curriculum.  
The project’s purpose is to **recreate the behavior of Bash** for a subset of features while learning about processes, system calls, parsing, and memory management.  

This project emphasizes:
- Building a robust parser for shell input.
- Implementing redirections, pipes, and environment variable handling.
- Managing processes and signals properly.
- Respecting strict coding and memory management rules.

---

## 📖 Table of Contents
- [Features](#-features)
- [Technical Details](#-technical-details)
- [Installation & Usage](#-installation--usage)
- [Examples](#-examples)
- [Project Rules](#-project-rules)
- [Learning Outcomes](#-learning-outcomes)
- [Authors](#-authors)

---

## 🚀 Features

### 🔹 Prompt & Input
- Displays an interactive prompt while waiting for user input.
- Command line editing and history (through readline).

### 🔹 Command Execution
- Executes binaries found in the `PATH` or provided with absolute/relative paths.
- Expands environment variables (`$HOME`, `$USER`, `$?`, etc.).

### 🔹 Builtin Commands
Implemented builtins reproduce the behavior of Bash:
- `echo` with `-n` option.  
- `cd` with relative or absolute paths.  
- `pwd` with no options.  
- `export` to set environment variables.  
- `unset` to remove environment variables.  
- `env` to display environment variables.  
- `exit` with no options.  

### 🔹 Quotes Handling
- **Single quotes `'`**: prevent any interpretation of enclosed characters.  
- **Double quotes `"`**: prevent interpretation except for `$` expansion.  

### 🔹 Redirections
- `<` : Redirects input from a file.  
- `>` : Redirects output to a file (truncate).  
- `>>`: Redirects output to a file (append).  
- `<<`: Heredoc — reads input until a delimiter is found.  

### 🔹 Pipes
- Implements pipelines (`|`), where the output of one command becomes the input of the next.

### 🔹 Signals
- `ctrl-C`: Displays a new prompt on a new line (without exiting).  
- `ctrl-D`: Exits the shell.  
- `ctrl-\`: Ignored (no action).  

---

## ⚙️ Technical Details

### System Calls & Concepts
- **Process control**: `fork`, `execve`, `wait`, `waitpid`.  
- **File descriptors**: `dup`, `dup2`, `close` for redirections and pipes.  
- **Signals**: `signal`, `sigaction` for handling `SIGINT`, `SIGQUIT`, `EOF`.  
- **Memory management**: strict control with `malloc`, `free`, and no leaks.  
- **Parsing**: splitting commands into tokens, handling quotes, redirections, and environment expansion.  

### Design Constraints
- Written entirely in **C**, following the **Norminette** coding standard.  
- No memory leaks (checked with Valgrind).  
- Maximum **1 global variable** allowed.  
- Behavior must **closely match Bash** for the implemented features.  

---

## 🛠️ Installation & Usage

### Clone the repository
```bash
git clone https://github.com/achnouri/minishell.git

@achnouri 2025