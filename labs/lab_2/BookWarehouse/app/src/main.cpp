#include <iostream>
#include "Book.hpp"
#include "Order.hpp"
#include "Person.hpp"
#include "WarehouseManager.hpp"

Book module_book_tests(ISBN& isbn, BookTitle& title){
    Book bookOne(isbn, title);
    std::cout << "\nInfo of book:\n" << bookOne.getFullInfo() << std::endl;
    bookOne.addReview(std::make_shared<BookReview>("George", "Good book", "Good book with beautiful imgs^_^", 5, "2025-11-08"));
    std::cout << "\nInfo of book:\n" << bookOne.getFullInfo() << std::endl;
    bookOne.addReview(std::make_shared<BookReview>("George", "Bad book", "Bad book without beautiful imgs-_-", 1, "2025-11-08"));
    std::cout << "\nInfo of book:\n" << bookOne.getFullInfo() << std::endl;
    return bookOne;
}

std::vector<Order> module_order_tests(std::vector<std::shared_ptr<Book>>(books)){
    Order orderOne("504", "2025-01-01");
    Order orderTwo("505", "2025-11-08");
    for(int i = 0; i < books.size(); i++){
        orderOne.addItem(std::make_shared<OrderItem>(books[i], 20, 500, 5.0));
    }
    orderTwo.addItem(std::make_shared<OrderItem>(books[1], 50, 500, 10.0));
    std::cout << "1 ORDER: \n" << orderOne.getInfo() << std::endl;
    std::cout << "2 ORDER: \n" << orderTwo.getInfo() << std::endl;
    return {orderOne, orderTwo};
}

std::vector<Person> module_person_tests(){
    Address addressOne("Brestskaja", "Phanipol", "247710", "Belarus");
    ContactInfo infocontactOne("govorgeorge2007@gmail.com", "+375(33)647-04-02");
    Person userOne("0", "George", "Govor", "2007-02-10", std::make_shared<Address>(addressOne), 
        std::make_shared<ContactInfo>(infocontactOne));
    Address addressTwo("Semashko", "Minsk", "None", "Belarus");
    ContactInfo infocontactTwo("govorgeorge2007@gmail.com", "+375(33)647-04-02");
    Person userTwo("1", "George", "Govor", "2007-02-10", std::make_shared<Address>(addressTwo), 
        std::make_shared<ContactInfo>(infocontactTwo));
    std::cout << "user 1: " << userOne.getInfo() << "\n";
    std::cout << "user 2: " << userTwo.getInfo() << "\n";
    return {userOne, userTwo};
}

Warehouse module_warehouse_tests(std::vector<std::shared_ptr<Book>> books) {
    Warehouse warehouse("Good warehouse for book", "Minsk, Republic library");
    auto location = std::make_shared<StorageLocation>("A-05-B-02", 50);
    auto shelf = std::make_shared<Shelf>("A-05", 5); // 5 locations max
    shelf->addLocation(location);
    auto section = std::make_shared<WarehouseSection>("A", "Books");
    section->addShelf(shelf);
    auto item = std::make_shared<InventoryItem>(books[0], 45, location, "2020-02-20");
    warehouse.addSection(section);
    warehouse.addInventoryItem(item);
    std::cout << "1. ОСНОВНАЯ ИНФОРМАЦИЯ:\n";
    std::cout << "ITEM INFO: " << item->getInfo() << std::endl;
    std::cout << "LOCATION INFO: " << location->getInfo() << std::endl;
    std::cout << "WAREHOUSE INFO: " << warehouse.getInfo() << std::endl;
    std::cout << "\n2. ТЕСТИРОВАНИЕ ПОИСКА:\n";
    std::string testIsbn = books[0]->getISBN().getCode();
    std::cout << testIsbn << std::endl;
    std::cout << "Общее количество книги " << testIsbn << ": " 
              << warehouse.getBookTotalQuantity(testIsbn) << std::endl;
    std::cout << "Книга в наличии: " << (warehouse.isBookInStock(testIsbn) ? "ДА" : "НЕТ") << std::endl;
    auto foundItems = warehouse.findInventoryByBook(testIsbn);
    std::cout << "Найдено записей инвентаря: " << foundItems.size() << std::endl;
    std::cout << "\n3. ТЕСТИРОВАНИЕ СТРУКТУРЫ СКЛАДА:\n";
    std::cout << "Количество секций: " << warehouse.getSectionsCount() << std::endl;
    auto foundSection = warehouse.findSection("A");
    if (foundSection) {
        std::cout << "Секция найдена: " << foundSection->getName() << std::endl;
        std::cout << "Стеллажей в секции: " << foundSection->getShelvesCount() << std::endl;
    }
    std::cout << "\n4. ТЕСТИРОВАНИЕ ЕМКОСТИ:\n";
    std::cout << "Общая емкость склада: " << warehouse.getTotalCapacity() << std::endl;
    std::cout << "Текущая загрузка: " << warehouse.getCurrentLoad() << std::endl;
    std::cout << "Свободное место: " << warehouse.getAvailableSpace() << std::endl;
    std::cout << "Процент заполнения: " << warehouse.getUtilizationPercentage() << "%" << std::endl;
    std::cout << "\n5. ТЕСТИРОВАНИЕ ГРАНИЧНЫХ СЛУЧАЕВ:\n";
    std::cout << "Поиск несуществующей книги: " 
              << warehouse.getBookTotalQuantity("000-000-00000-0") << std::endl;
    std::cout << "Location может вместить еще 10 книг: " 
              << (location->canAccommodate(10) ? "ДА" : "НЕТ") << std::endl;
    std::cout << "Location пуста: " << (location->isEmpty() ? "ДА" : "НЕТ") << std::endl;
    std::cout << "Location полна: " << (location->isFull() ? "ДА" : "НЕТ") << std::endl;
    std::cout << "\n=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===\n" << std::endl;
    return warehouse;
}

int main(){
    std::cout << "====BOOK TEST====\n";
    ISBN isbnOne("2-266-11156-6");
    BookTitle titleOne("New book", "Cool book", "RU");
    ISBN isbnTwo("978-2-266-11156-0");
    BookTitle titleTwo("New book 2", "Cool book 2", "EN");
    auto bookFirst = module_book_tests(isbnOne, titleOne);
    auto bookSecond = module_book_tests(isbnTwo, titleTwo);
    std::vector<std::shared_ptr<Book>> books;
    books.push_back(std::make_shared<Book>(bookFirst));
    books.push_back(std::make_shared<Book>(bookSecond));
    std::cout << "====ORDER TEST====\n";
    auto orders = module_order_tests(books);
    std::cout << "====PERSON TEST====\n";
    auto persons = module_person_tests();
    std::cout << "=== WAREHOUSE TEST ===\n" << std::endl;
    auto warehouse = module_warehouse_tests(books);
    return 0;
}