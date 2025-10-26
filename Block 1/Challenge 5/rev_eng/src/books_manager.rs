// crates and collections.
use std::collections::HashMap;
use crate::models::Book;


// Fixes the problem with duplicate ISBNs
// while allowing for fast (O(1)) lookups if you have the ISBN.

pub struct BooksManager {
    books: HashMap<String, Book>,
}

impl BooksManager {
    pub fn new() -> Self {
        Self {
            books: HashMap::new(),
        }
    }

    pub fn load_database(&mut self) {
        self.books.clear(); // Clear existing data

        // sample books!
        let book1 = Book::new(
            "The Rust Programming Language".to_string(),
            "Steve Klabnik and Carol Nichols".to_string(),
            "9781718503106".to_string(),
            vec![]
        ); 

        let book2 = Book::new(
            "C++ for Dummies".to_string(),
            "Stephen R. Davis".to_string(),
            "9780470317266".to_string(),
            vec![]
        );

        let book3 = Book::new(
            "Continuous Deployment: Enable Faster Feedback, Safer Releases, and More Reliable Software".to_string(),
            "Valentina Servile".to_string(),
            "9781098146726".to_string(),
            vec![]
        );

        self.add_book(book1);
        self.add_book(book2);
        self.add_book(book3);   
    }

    pub fn add_book(&mut self, book: Book) -> bool {
        if self.books.contains_key(&book.isbn) {
            println!("Book with ISBN {} already exists.", book.isbn);
            return false;
        }
        
        self.books.insert(book.isbn.clone(), book);
        true
    }

    pub fn get_book(&self, isbn: &str) -> Option<&Book> {
        &self.books.get(isbn)
    }

    pub fn list_books(&self) -> &HashMap<String, Book> {
        &self.books
    }
}