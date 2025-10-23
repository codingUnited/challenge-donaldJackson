use std::io::{Write, stdin, stdout};

// Reads an integer from the user within a given range.
// If the user enters an invalid input, it will prompt the user to enter a valid input.
pub fn read_int(low: i32, high: i32) -> i32 {
    if low > high {
        println!("Invalid range");
        return -1;
    }

    loop {
        print!("\nEnter an integer between {} and {}", low, high);
        stdout().flush().unwrap(); // Prompt will appear before request for user input.

        let mut choice = String::new();

        if stdin().read_line(&mut choice).is_err() {
            println!("Failed to read line");
            continue;
        }

        match choice.trim().parse::<i32>() {
            // Trims the string choice, to get just the number chosen.
            // Then parses it converting to a 32-bit integer.
            Ok(value) if (low..=high).contains(&value) => return value, //  If its successful, return the value.
            //  Match can fail to parse, if for example the user uses a non-integer value.
            //  If that happens print an error message and continue the loop.
            _ => {
                println!("Error: invalid number...Try again");
            }
        }
    }
}

pub fn show_read_menu(choices: &[&str]) -> i32 {
    print!("\nMenu\n");
    stdout().flush().unwrap(); // Menu will appear before options

    // Enumerate then add one for display purposes.
    for (index, choice) in choices.iter().enumerate(){
        println!("\t{}: {}", index +1, choice);
    }


    // Read an integer from 1 to the length of the choices
    // typecast choices.len to i32 since len() returns a usize by default.
    read_int(1, choices.len as i32) 
    
}

pub fn get_current_time_and_date() -> String {
    // Nothing here yet.
}