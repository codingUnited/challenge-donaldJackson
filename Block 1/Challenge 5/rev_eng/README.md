# Buggy.cpp Revisions and Reverse Engineering

## Initial thoughts:
 - This is a simulation of an online reader system but is riddled with bugs and leaks
 - Two  Roles: User and Admin
 - - Users Sign Up, Log In
 - - Regular users can view available books and start reading sessions.
 - - Admins can add new books to the library, and do everything that regular users can.
 - Its using an object oriented approach
 - Constructor/Deconstructor Pattern
 - Setter/Getter Pattern
 - Manager Pattern
 - Strategy Pattern (if admin then admin view else userview)
 - Terminal UI
 - View Separation (good practice as we dont want users doign admin tasks.)


 1. Read the Source Code and write notes on how functions likely work or are intended to work.

 2. Compilation does not occur with flags, methods within the `BooksManager` class were not implemented
 - To actually have execution occur GetBook(), UpdateBook(), and DeleteBook() were implemented.

 3. Implement those methods and execute program. Heres what I found
 - Input sanitization does not lead to prompting new input, instead either an exception is caused or readint is spammed then the program halts.
 - BookReadingSession class causes a crash due to poor handling of cases where the pointer is null
 - User State isn't cleared/reset to be a nullptr when logging out, it simply just is a program break.
 - The program loop being while true means theres really no good way to exit the program if for example a memory leak occurs.
 - Book::Read has the same flaw as readInt().Entering any non-numeric character breaks this completely. Input sanitization is needed.
- ToString() methods should be const type, since they do not and will not change.
- Nothing is saved. Just overwritten with dummy data so any new sign-up i did is IMMEDIATELY erased
- There are definitely more that I have missed due to manual testing.


4. Begin refactoring and restructuring of the original C++ codebase within Rust🦀.
   -- Start by recreating the utilities begin with the ReadInt() function.
   --- Sanitize the user input to ensure its valid and within range.

5. Add gitignore to toplevel of repository for general things and a new one within `Block 1/Challenge 5/rev_eng`

6. Add linting and formatting action
   `.github/workflows/rust_lint.yml` uses Clippy and rustfmt to format and lint everything in the project directory.

7. Implement utils.rs
   -- read_int() which is now safe from bad input and invalid ranges through input sanitization.
   -- show_read_menu() which behaves the same. unchanged behavior from `Block 1/Challenge 5/buggy_src/Buggy.cpp`
   -- get_current_time_and_date() which uses the Chrono function now() then formats it to the same way `Block 1/Challenge 5/buggy_src/Buggy.cpp` does.
   -- ***NEW*** read_string() function which helps to read full lines of text, sanitizing for empty inputs and fixing the behavior presented by `cin >> str` within `Block 1/Challenge 5/buggy_src/Buggy.cpp` that caused only the first word of the title to be read.
