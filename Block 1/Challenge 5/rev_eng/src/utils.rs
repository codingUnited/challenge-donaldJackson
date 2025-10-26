// rustfmt prefers std imports first, then external crates
use std::io::{stdin, stdout, Write};
use chrono::prelude::*;

// Reads an integer from the user within a given range.
// If the user enters an invalid input, it will prompt the user to enter a valid input.
pub fn read_int(low: i32, high: i32) -> i32 {
    if low > high {
        // changed to a panic, since this is a programming error, not a user input error.
        panic!(
            "Invalid range: low ({}) is greater than high ({})",
            low, high
        );
    }

    loop {
        print!("\nEnter an integer between {} and {}", low, high);
        stdout().flush().unwrap(); // Prompt will appear before request for user input.

        let mut choice = String::new();

        if stdin().read_line(&mut choice).is_err() {
            println!("Failed to read line. Input again.");
            continue;
        }

        match choice.trim().parse::<i32>() {
            // Trims the string choice, to get just the number chosen.
            // Then parses it converting to a 32-bit integer.
            Ok(value) if (low..=high).contains(&value) => return value, //  If its successful, return the value.
            //  Match can fail to parse, if for example the user uses a non-integer value.
            //  If that happens print an error message and continue the loop.
            _ => {
                println!("Error: Invalid number...Try again");
            }
        }
    }
}

pub fn show_read_menu(choices: &[&str]) -> i32 {
    print!("\nMenu\n");
    stdout().flush().unwrap(); // Menu will appear before options

    if choices.is_empty() {
        // Sanity check for empty choices array, programmign error not user input error.
        panic!("Called with an empty choices array.");
    }

    // Enumerate then add one for display purposes.
    // Added space for `{` and around `+`
    for (index, choice) in choices.iter().enumerate() {
        println!("\t{}: {}", index + 1, choice);
    }

    // Read an integer from 1 to the length of the choices
    // typecast choices.len to i32 since len() returns a usize by default.
    // Removed extra blank lines
    read_int(1, choices.len() as i32)
}

pub fn get_current_time_and_date() -> String {
    let current_time = Local::now();

    // Format the string to match buggy.cpp format
    current_time.format("%Y-%m-%d %H:%M:%S").to_string()
}

// This is to fix issues with buggy.cpp where cin >> str
// only reads the first word in a title/string.
// technically this is not needed for the challenge as rust's
// read_line reads the whole line by default.
// This handles input sanitization so there are no empty strings inputted.
pub fn read_input_string(prompt: &str) -> String {
    loop {
        print!("{}", prompt);
        stdout().flush().unwrap();

        let mut input = String::new();

        // if read_line has an error, print an error message and continue loop.'
        if stdin().read_line(&mut input).is_err() {
            println!("Error: failed to read line. Try again.");
            continue;
        }

        // otherwise we trim the input and return it.

        let trimmed_input = input.trim().to_string();

        if trimmed_input.is_empty() {
            println!("Error: Input should not be empty. Try again.");
            continue;
        }

        return trimmed_input; // return the trimmed input string when valid.
    }
}
