# Лабораторная работа №2: BookWarehouse

### Документация к лабораторной работе располагается по следующей <a href="https://press-cs.ru/PPOIS/BookWarehouse">ссылке</a>.

### Класс число_полей число_методов -> Ассоциации

Address 4 18

Book 11 29 -> ISBN, BookTitle, BookMetadata, PhysicalProperties, Genre, BookCondition, BookStatistics

BookCollection 4 15

BookCondition 1 8

BookMetadata 4 12

BookReview 5 16

BookSeries 5 11

BookStatistics 5 26

BookTitle 3 8

ContactInfo 4 18

Customer 6 21 -> Address, ContactInfo

CustomerOrder 5 21 -> Customer, ShippingInfo

DateUtils 0 1

Delivery 10 30

Employee 6 23 -> Address, EmploeeRole

EmployeeRole 1 14

Genre 1 5

InventoryItem 4 13 -> Book, StorageLocation

InventoryReport 1 32 -> Warehouse, StorageLocation, WarehouseSection, Shelf

ISBN 1 9

Order 6 27 -> OrderStatus, OrderItem

OrderItem 4 19 -> Book

OrderManager 5 26 -> ShippingInfo, OrderItem, Customer, CustomerOrder, PurchaseOrder

OrderStatus 2 13

Person 6 21 -> Address, ContactInfo

PhysicalProperties 7 16

Publisher 3 10

PurchaseOrder 6 20

Shelf 3 22 -> StorageLocation

ShippingInfo 10 27 -> Address

StockMovement 8 27 -> Warehouse, InventoryItem

StockReceipt 4 15 -> Warehouse

StockTransfer 3 15 -> Warehouse, StorageLocation

StockWriteOff 2 13 -> Warehouse

StorageLocation 4 18

StringValidation 0 4

UserAccount 6 19 -> Person

Warehouse 4 32 -> StockMovement, WarehouseSection, InventoryItem, Book

WarehouseManager 1 18 -> Warehouse, Book, StorageLocation, Delivery

WarehouseSection 7 30 -> SHelf

### Исключение количество_полей количество_методов

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

### Итого

Поля: 171

Методы: 722

Ассоциации: 47

Исключения: 13
