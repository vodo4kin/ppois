#include "books/Book.hpp"
#include <iostream>

using namespace std;

int main(){
    BookTitle title("book", "", "RU");
    ISBN isbn("978-617-8111-27-8");
    Publisher publ("Govor production", "xxxvodo4kaxxx@gmail.com", 2007);
    PhysicalProperties proper(100, 100, 100, 255, 500, PhysicalProperties::CoverType::HARDCOVER, "Paper");
    Genre genr(Genre::Type::HORROR);
    BookSeries series("My series", "Intresting", 5, 2007, 0);
    BookReview rev("Govor George", "Not bad:)", "Book is very nice. Thx^_^", 5, "2025.09.01");
    BookMetadata metd(2001, "ru", 5, "Good");
    BookCondition condition(BookCondition::Condition::LIKE_NEW);
    BookSeries FANTA("NAME_of_SeRiEs", "Good seria", 3, 5, 0);
    Book book(isbn, title, metd, proper, genr, publ, condition, 501.99, 55, FANTA);
    return 0;
}