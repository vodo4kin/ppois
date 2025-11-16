# Лабораторная работа №3: TravelBooking

### Документация к лабораторной работе располагается по следующей <a href="https://press-cs.ru/PPOIS/TravelBooking">ссылке</a>.

## Класс число_полей число_поведений -> Ассоциации:

Accommodation 6 3

Admin 3 9 -> User, Customer, VipCustomer

AllInclusiveMeal 4 2

Apartment 4 2 -> Accommodation

BarbecueMeal 4 2

Booking 6 4 -> Customer, Tour, Transport

BookingFilter 0 3 -> Booking

BookingManager 1 6 -> Booking

BookingNotification 0 3 -> Booking

BoutiqueHotel 4 3 -> Accommodation

BreakfastBuffet 3 2

Camping 4 4 -> Accommodation

CruiseCabin 4 4 -> Accommodation

Customer 3 3 -> Booking

DateUtils 0 2

DietarySpecificMeal 4 2

EthnicDinner 4 3

EventCatering 4 3

FixedMenuDinner 3 2

GuestHouse 4 4 -> Accommodation

Hostel 4 4 -> Accommodation

Hotl 4 2 -> Accommodation

Invoice 4 2 -> Booking, Payment

Logger 0 3

Meal 5 3

MountainLodge 4 4 -> Accommodation

Payment 5 3

PicnicLunch 3 2

Resort 4 4 -> Accommodation

StringValidation 0 3

TastingMenu 4 1

Tour 8 10 -> Meal, Accommodation

TourGuide 3 0

TourReview 3 0 -> Tour

TourSchedule 3 1 -> Tour

Transport 7 0

TransportManager 2 4 -> TransportReview, TransportSchedule

TransportReview 4 0 -> Transport

TransportSchedule 5 1 -> TransportSchedule

User 10 5

Villa 4 4 -> Accommodation

VipCustomer 2 6 -> Booking, User

### Исключение количество_полей количество_методов:

TravelBookingException 1 1

AccommodationCapacityExceededException 0 0

AccommodationUnavailableException 0 0

InvalidBookingException 0 0

InvalidDataException 0 0

InvalidDateException 0 0

PaymentProcessingException 0 0

ResourceNotFoundException 0 0

SystemOverloadException 0 0

TourCapacityExceededException 0 0

TransportationSchedulingException 0 0

UnderageException 0 0

## Итого:

Поля: 154

Поведения: 129

Ассоциации: 31

Исключения: 12

Классы: 54
