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
}

// This replaces the C++ BookReadingSession class.
pub struct BookReadingSession {
    pub book_isbn: String,
    pub current_page: usize,
    pub last_access_date: String,
}