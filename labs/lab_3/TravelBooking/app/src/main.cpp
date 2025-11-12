#include <iostream>
#include "Booking.hpp"
#include "AllInclusiveMeal.hpp"
#include "Hotel.hpp"

int main() {
    Customer man("George", "govorgeorge2007@gmail.com", "Password123", "2007-02-10");
    auto tourPtr = std::make_shared<Tour>("Weekend in Hawaii", "All-inclusive holiday with stunning sea views", "2026-06-01", "2026-06-10", 1249.99, Tour::Type::RELAXATION);
    Transport transport("BelAvia", "Minsk National Airport", "Honolulu Airport, Hawaii", "2026-05-31", "2026-06-01", 100, Transport::Type::FLIGHT);
    Booking booking(std::make_shared<Customer>(man), tourPtr, std::make_shared<Transport>(transport));
    std::cout << "Total price: " << booking.getTotalPrice() << std::endl;
    std::vector<std::string> tagsMeal;
    tagsMeal.push_back("Tasy");
    tagsMeal.push_back("A lot of");
    std::vector<std::string> resotrans;
    resotrans.push_back("Duke's Waikiki");
    AllInclusiveMeal meal("ALL INCLUSIVE", "very tasty food", 499.99, 2700, tagsMeal, true, true, 5, resotrans);
    tourPtr->addMeal(std::make_shared<AllInclusiveMeal>(meal));
    std::cout << "Total price: " << booking.getTotalPrice() << std::endl;
    Hotel hotel("Good Hotel", "Hawaii", 200.99, 300, 4.5, 4, 1, 1, "Good");
    tourPtr->addAccommodation(std::make_shared<Hotel>(hotel));
    std::cout << "Total price: " << booking.getTotalPrice() << std::endl;
    return 0;
}  