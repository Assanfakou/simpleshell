# Simple Shell – Parsing Phase

## Current Status

This Simple implementation completes the entire parsing phase, including tokenization, variable expansion, and command structure creation. The implementation follows the mandatory requirements of the subject specification.

### 1. Tokenization

- Properly splits the input line into tokens:
  - Words
  - Pipes (`|`)
  - Redirection operators: `<`, `>`, `>>`, `<<`
- Preserves quotes inside tokens (e.g., `'abc'`, `"abc"`).
- Ignores whitespace.
- Detects and reports unmatched quotes.

### 2. Variable Expansion

- Supports `$VAR` and `$?`.
- Uses `getenv()` to retrieve environment variable values.
- Skips expansion when the token is wrapped in single quotes.
- Replaces tokens in-place.
- Substitutes undefined variables with an empty string.

### 3. Command Structure Construction

- Converts the token list into a linked list of `t_cmd` structures.
- Each `t_cmd` contains:
  - A null-terminated `argv` array
  - A list of redirections (`t_redir`)
  - A pointer to the next command (used for pipes)
- Properly segments commands based on `|`.

### 4. Syntax Error Detection

- Detects and reports:
  - Unmatched quotes
  - Pipe at the beginning or end of input
  - Consecutive pipes (e.g., `||`)
  - Redirection without a target
  - Redirection followed by another redirection

## What Remains (Execution Phase)

To complete the shell, the following features are required:

### 1. Command Execution

- Use `fork()` and `execve()` to execute external commands.

### 2. Redirections

- Apply file redirection using `dup2()`:
  - `<` for stdin
  - `>` and `>>` for stdout
  - `<<` for heredoc support

### 3. Pipe Handling

- Connect commands with pipes using `pipe()` and proper file descriptor management.

### 4. Built-in Commands

Implement built-ins without calling `execve()`:
- `cd`
- `echo`
- `env`
- `exit`
- `export`
- `unset`

### 5. Environment Management

- Replace usage of `getenv()` with a custom `t_env` list.
- Support adding and removing variables with `export` and `unset`.
- Generate a `char **envp` array for `execve()` from your own environment structure.

## Conclusion

The parsing phase is complete. The shell can now interpret input, expand variables, handle syntax errors, and build a structured representation of the command pipeline. The next step is to implement execution and built-ins.
