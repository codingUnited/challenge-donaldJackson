use crate::utils;

// This replaces the C++ Book class.
pub struct Book {
    pub isbn: String,
    pub title: String,
    pub author: String,
    pub pages: Vec<String>,
}

// This replaces the C++ User class.
pub struct User {
    pub username: String,
    pub password: String,
    pub name: String,
    pub email: String,
    pub is_admin: bool,

    // store the actual reading session rather than a pointer to prevent memory leaks.
    pub reading_sessions: Vec<BookReadingSession>,
}

// This replaces the C++ BookReadingSession class.
pub struct BookReadingSession {
    // store the book's ACTUAL ISBN rather than a pointer to prevent memory leaks.
    pub book_isbn: String,
    pub current_page: usize,
    pub last_access_date: String,
}

impl Book {
    // Constructor for a Book
    pub fn new(isbn: String, title: String, Author: String, pages: Vec<String>) -> Self {
        Self {
            isbn,
            title,
            author,
            pages,
        }
    }

    // replaces the C++ Book::toString() method
    pub fn to_string(&self) -> &str {
        &self.title
    }
}

impl User {
    // Constructor for a user
    pub fn new(username: String, password: String, name: String, email: String, is_admin: bool) -> Self {
        Self {
            username,
            password,
            name,
            email,
            is_admin: false, // Default to not an admin
            reading_sessions: Vec::new(), // Empty to start
        }
    }
    

    // replaces the C++ User::toString() method
    pub fn to_string(&self) -> String {
        let admin_str = if self.is_admin {" | Admin"} else {""};
        format!(
            "Name: {}\nEmail: {}\nUsername:{}{}",
            self.name, self.email, self.username, admin_str
        )
    }
    

    // TODO: Add function to add a session
}

impl BookReadingSession{

    // Constructor for a new reading session

    pub fn new(book_isbn: String) -> Self {
        Self {
            book_isbn,
            current_page: 0,
            last_access_date: utils::current_date_string(),
        }
    }

    // Replicates C++ PageIdxStr() Method
    pub fn page_idx_str(&self, book: &Book) -> String {
        format!("{}/{}", self.current_page + 1, book.pages.len())
    }


    // Getter for content of page, rather than owning a pointer it just borrows the book
    pub fn get_page_content<'a>(&self, book: &'a Book) -> &'a str{
        &book.pages[self]
    }

    // Next page function replication:
    pub fn next_page(&mut self, book: &Book) {
        if self.current_page < book.pages.len() - 1{
            self.current_page += 1;
        }
    }

    // replication of previous page funtion

    pub fn previous_page(&mut self) {
        if self.current_page > 0 {
            self.current_page -= 1;
        }
    }
    

    // Method to reset last access date to current date
    pub fn reset_last_access_date(&mut self) {
        self.last_access_date = utils::current_date_string();
    }

    pub fn to_string(&self, book: &Book) -> String {
        format!(
            "{} Page: {} - {}",
            book.to_string(),
            self.page_idx_str(book),
            self.last_access_date
        )
    }
}