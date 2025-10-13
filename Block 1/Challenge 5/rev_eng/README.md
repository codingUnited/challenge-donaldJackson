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

 2. 