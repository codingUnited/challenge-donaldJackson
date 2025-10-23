use crate::utils;


// This replaces the C++ Book class.
pub struct Book{
    pub isbn: String,
    pub title: String,
    pub author: String,
    pub pages: Vec<String>,
}

pub struct User{
    pub username: String,
    pub password: String,
    pub name: String,
    pub email: String,
    pub is_admin: bool,
}

pub struct BookReadingSession{
    // Nothing Here Yet.
}