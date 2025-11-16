# Лабораторная работа №2: BookWarehouse

### Документация к лабораторной работе располагается по следующей <a href="https://press-cs.ru/PPOIS/BookWarehouse">ссылке</a>.

## Класс число_полей число_поведений(число_методов) -> Ассоциации:

Address 4 1(18)

Book 11 4(29) -> ISBN, BookTitle, BookMetadata, PhysicalProperties, Genre, BookCondition, BookStatistics

BookCollection 4 3(15)

BookCondition 1 3(8)

BookMetadata 4 3(12)

BookReview 5 4(16)

BookSeries 5 2(11)

BookStatistics 5 5(26)

BookTitle 3 1(8)

ContactInfo 4 2(18)

Customer 6 4(21) -> Address, ContactInfo

CustomerOrder 5 3(21) -> Customer, ShippingInfo

DateUtils 0 1(1)

Delivery 10 4(30)

Employee 6 4(23) -> Address, EmploeeRole

EmployeeRole 1 4(14)

Genre 1 0(5)

InventoryItem 4 2(13) -> Book, StorageLocation

InventoryReport 1 5(32) -> Warehouse, StorageLocation, WarehouseSection, Shelf

ISBN 1 1(9)

Order 6 4(27) -> OrderStatus, OrderItem

OrderItem 4 4(19) -> Book

OrderManager 5 5(26) -> ShippingInfo, OrderItem, Customer, CustomerOrder, PurchaseOrder

OrderStatus 2 2(13)

Person 6 3(21) -> Address, ContactInfo

PhysicalProperties 7 1(16)

Publisher 3 1(10)

PurchaseOrder 6 5(20)

Shelf 3 4(22) -> StorageLocation

ShippingInfo 10 4(27) -> Address

StockMovement 8 5(27) -> Warehouse, InventoryItem

StockReceipt 4 4(15) -> Warehouse

StockTransfer 3 4(15) -> Warehouse, StorageLocation

StockWriteOff 2 3(13) -> Warehouse

StorageLocation 4 4(18)

StringValidation 0 4(4)

UserAccount 6 5(19) -> Person

Warehouse 4 10(32) -> StockMovement, WarehouseSection, InventoryItem, Book

WarehouseManager 1 6(18) -> Warehouse, Book, StorageLocation, Delivery

WarehouseSection 7 6(30) -> SHelf

### Исключение количество_полей количество_методов:

WarehouseException 1 1

AuthenticationException 0 0

AuthorizationException 0 0

BookNotFoundException 0 0

DataValidationException 0 0

DuplicateBookException 0 0

InsufficientStockException 0 0

InvalidISBNException 0 0

InvalidOrderStateException 0 0

OrderProcessingException 0 0

PaymentProcessingException 0 0

ReportGenerationException 0 0

ShippingException 0 0

## Итого:

Поля: 171

Поведения (методы): 148(722)

Ассоциации: 47

Исключения: 13

Классы: 53
