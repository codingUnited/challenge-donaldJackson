# Buggy.cpp Revisions and Reverse Engineering

## Initial Thoughts

This is a simulation of an online reader system but is riddled with bugs and leaks.

### Two Roles: User and Admin

**Users:**
- Sign Up, Log In
- Regular users can view available books and start reading sessions

**Admins:**
- Can add new books to the library
- Can do everything that regular users can

### Design Patterns Observed

- Object-oriented approach
- Constructor/Destructor Pattern
- Setter/Getter Pattern
- Manager Pattern
- Strategy Pattern (if admin then admin view else userview)
- Terminal UI
- View Separation (good practice as we don't want users doing admin tasks)

---

## Step 1: Read the Source Code

Write notes on how functions likely work or are intended to work.

---

## Step 2: Compilation Issues

Compilation does not occur with flags—methods within the `BooksManager` class were not implemented.

To actually have execution occur, `GetBook()`, `UpdateBook()`, and `DeleteBook()` were implemented.

---

## Step 3: Program Execution and Bugs Found

**Issues Discovered:**

- Input sanitization does not lead to prompting new input, instead either an exception is caused or `readInt()` is spammed then the program halts
- `BookReadingSession` class causes a crash due to poor handling of cases where the pointer is null
- User State isn't cleared/reset to be a `nullptr` when logging out—it simply just is a program break
- The program loop being `while true` means there's really no good way to exit the program if for example a memory leak occurs
- `Book::Read` has the same flaw as `readInt()`—entering any non-numeric character breaks this completely. Input sanitization is needed
- `ToString()` methods should be const type, since they do not and will not change
- Nothing is saved. Just overwritten with dummy data so any new sign-up I did is IMMEDIATELY erased
- There are definitely more that I have missed due to manual testing

---

## Step 4: Begin Refactoring in Rust 🦀

Begin refactoring and restructuring of the original C++ codebase within Rust.

Start by recreating the utilities—begin with the `ReadInt()` function:
- Sanitize the user input to ensure it's valid and within range

---

## Step 5: Add .gitignore Files

Add gitignore to top level of repository for general things and a new one within `Block 1/Challenge 5/rev_eng`.

---

## Step 6: Add Linting and Formatting Action

`.github/workflows/rust_lint.yml` uses Clippy and rustfmt to format and lint everything in the project directory.

---

## Step 7: Continue to implement the rest of  `utils.rs`

**Functions Implemented:**

- **`read_int()`** – Now safe from bad input and invalid ranges through input sanitization
- **`show_read_menu()`** – Behaves the same. Unchanged behavior from `Block 1/Challenge 5/buggy_src/Buggy.cpp`
- **`get_current_time_and_date()`** – Uses the Chrono function `now()` then formats it to the same way `Block 1/Challenge 5/buggy_src/Buggy.cpp` does
- **`read_string()`** – ***NEW*** function which helps to read full lines of text, sanitizing for empty inputs and fixing the behavior presented by `cin >> str` within `Block 1/Challenge 5/buggy_src/Buggy.cpp` that caused only the first word of the title to be read

## Step 8: Implementation of the Data Models for Book, User, and BookReadingSession
- **`Book`**: A public struct containing the author, isbn title, and page contents. The class implementation in `Block 1/Challenge 5/rev_eng/src/models.rs` is just a constructor. I Will implement a manager within another file

- **`User`**: A public struct containing the admin status, email, name, password, and username. This constructs a new user, defaulting admin status to false and starting a reading session by being empty. At this point I have not added the ability to add a session.


- **`BookReadingSession`**: A public struct containing the book isbn, current page, and last access date. This receives a critical safety update, instead of owning the book pointer it instead now just borrows the book. 

