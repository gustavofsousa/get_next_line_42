<h1 align="center">get_next_line</h1>

<p align="center">
  <img src="https://img.shields.io/badge/language-C-blue.svg" alt="Language">
  <img src="https://img.shields.io/badge/42-School-black.svg" alt="42 School">
  <img src="https://img.shields.io/badge/status-complete-brightgreen.svg" alt="Status">
</p>

<p align="center">
  A function that reads one line at a time from any file descriptor — efficiently, with persistent state between calls.
</p>

<p align="center">
  <a href="README.pt-br.md">🇧🇷 Leia em Português</a>
</p>

---

## Why this project matters

> "This project taught me how I/O buffering works at the OS level — why reading from a file or socket is not instant, how buffers prevent redundant system calls, and how static variables can maintain state across function calls in C. These are concepts you encounter in every real-world backend or systems application."

Understanding `read()`, file descriptors, and buffer management is foundational for anyone working with network programming, file processing, or high-performance I/O.

---

## What was built

A single function `get_next_line(int fd)` that:

- Reads from **any file descriptor** (files, stdin, pipes, sockets)
- Returns one complete line per call, including the `\n`
- Returns `NULL` when the file ends or an error occurs
- Uses an internal static buffer to avoid re-reading already-consumed bytes
- Works correctly with **any `BUFFER_SIZE`** — from 1 byte to thousands

### Bonus
The bonus version handles **multiple file descriptors simultaneously**, maintaining independent state per fd. This mirrors how real servers handle concurrent connections.

---

## A standout technical detail

The use of a `static char stash[]` paired with a `move_remains()` function to shift unconsumed bytes to the front of the buffer is a clever approach that avoids dynamic allocation of the stash while still correctly handling lines that span multiple `read()` calls. This pattern is commonly seen in production I/O libraries.

---

## Getting Started

```bash
git clone https://github.com/gustavofsousa/get_next_line_42.git
cd get_next_line_42
```

Include the files in your project:

```c
#include "get_next_line.h"
```

Compile with your preferred `BUFFER_SIZE`:

```bash
gcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_main.c
```

### Usage example

```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## Project structure

```
get_next_line_42/
├── get_next_line.c          # Core logic
├── get_next_line.h          # Header
├── get_next_line_utils.c    # Helper functions
├── get_next_line_bonus.c    # Multi-fd support
├── get_next_line_bonus.h
└── get_next_line_utils_bonus.c
```

---

## Skills demonstrated

- File I/O and system calls (`read`, `open`, `close`)
- Static variables and persistent function state
- Buffer management and partial reads
- Memory management (no leaks between calls)
- Handling edge cases: empty lines, EOF without newline, large files

---

## License

This project was developed as part of the [42 School](https://42.fr) curriculum.

---

<p align="center">Made with ☕ at 42 Rio de Janeiro</p>
