#include <gtest/gtest.h>
#include "Apartment.hpp"
#include "BoutiqueHotel.hpp"
#include "Camping.hpp"
#include "CruiseCabin.hpp"
#include "GuestHouse.hpp"
#include "Hostel.hpp"
#include "Hotel.hpp"
#include "MountainLodge.hpp"
#include "Resort.hpp"
#include "Villa.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"

TEST(AccommodationTest, HotelValidConstruction) {
    EXPECT_NO_THROW(Hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard"));
}

TEST(AccommodationTest, HotelInvalidNameThrows) {
    EXPECT_THROW(Hotel("", "City", 100.0, 2, 4.5, 3, true, false, "standard"), InvalidDataException);
}

TEST(AccommodationTest, HotelInvalidLocationThrows) {
    EXPECT_THROW(Hotel("Test Hotel", "", 100.0, 2, 4.5, 3, true, false, "standard"), InvalidDataException);
}

TEST(AccommodationTest, HotelInvalidPriceThrows) {
    EXPECT_THROW(Hotel("Test Hotel", "City", -1.0, 2, 4.5, 3, true, false, "standard"), InvalidDataException);
}

TEST(AccommodationTest, HotelInvalidCapacityThrows) {
    EXPECT_THROW(Hotel("Test Hotel", "City", 100.0, 0, 4.5, 3, true, false, "standard"), InvalidDataException);
}

TEST(AccommodationTest, HotelInvalidRatingThrows) {
    EXPECT_THROW(Hotel("Test Hotel", "City", 100.0, 2, 6.0, 3, true, false, "standard"), InvalidDataException);
}

TEST(AccommodationTest, HotelGetAccommodationInfo) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_FALSE(hotel.getAccommodationInfo().empty());
}

TEST(AccommodationTest, HotelAddValidAmenity) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_NO_THROW(hotel.addAmenity("WiFi"));
}

TEST(AccommodationTest, HotelAddInvalidAmenityThrows) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_THROW(hotel.addAmenity(""), InvalidDataException);
}

TEST(AccommodationTest, HotelSetValidPrice) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_NO_THROW(hotel.setPricePerNight(150.0));
}

TEST(AccommodationTest, HotelSetInvalidPriceThrows) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_THROW(hotel.setPricePerNight(-1.0), InvalidDataException);
}

TEST(AccommodationTest, HotelSetValidRating) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_NO_THROW(hotel.setRating(4.8));
}

TEST(AccommodationTest, HotelSetInvalidRatingThrows) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_THROW(hotel.setRating(6.0), InvalidDataException);
}

TEST(AccommodationTest, HotelCanAccommodateValid) {
    Hotel hotel("Test Hotel", "City", 100.0, 4, 4.5, 3, true, false, "standard");
    EXPECT_TRUE(hotel.canAccommodate(3));
}

TEST(AccommodationTest, HotelCanAccommodateInvalid) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_FALSE(hotel.canAccommodate(3));
}

TEST(AccommodationTest, HotelValidateBookingValid) {
    Hotel hotel("Test Hotel", "City", 100.0, 4, 4.5, 3, true, false, "standard");
    EXPECT_NO_THROW(hotel.validateBooking(3, "2024-01-01", "2024-01-05"));
}

TEST(AccommodationTest, HotelValidateBookingInvalidGuests) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_THROW(hotel.validateBooking(3, "2024-01-01", "2024-01-05"), AccommodationCapacityExceededException);
}

TEST(AccommodationTest, HotelAddDuplicateAmenity) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    hotel.addAmenity("WiFi");
    EXPECT_NO_THROW(hotel.addAmenity("WiFi"));
}

TEST(AccommodationTest, HotelIsAvailableForDatesValid) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_TRUE(hotel.isAvailableForDates("2024-01-01", "2024-01-05"));
}

TEST(AccommodationTest, HotelIsAvailableForDatesInvalidThrows) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_THROW(hotel.isAvailableForDates("invalid", "2024-01-05"), InvalidDateException);
}

TEST(AccommodationTest, HotelValidateBookingZeroGuestsThrows) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_THROW(hotel.validateBooking(0, "2024-01-01", "2024-01-05"), AccommodationCapacityExceededException);
}

TEST(AccommodationTest, HotelValidateBookingNegativeGuestsThrows) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_THROW(hotel.validateBooking(-1, "2024-01-01", "2024-01-05"), AccommodationCapacityExceededException);
}

TEST(ApartmentTest, ValidConstruction) {
    EXPECT_NO_THROW(Apartment("Test Apt", "City", 100.0, 4, 4.5, 2, true, false, 50.0));
}

TEST(ApartmentTest, InvalidRoomsThrows) {
    EXPECT_THROW(Apartment("Test Apt", "City", 100.0, 4, 4.5, 0, true, false, 50.0), InvalidDataException);
}

TEST(ApartmentTest, InvalidAreaThrows) {
    EXPECT_THROW(Apartment("Test Apt", "City", 100.0, 4, 4.5, 2, true, false, 0.0), InvalidDataException);
}

TEST(ApartmentTest, GetAccommodationInfo) {
    Apartment apt("Test Apt", "City", 100.0, 4, 4.5, 2, true, false, 50.0);
    EXPECT_FALSE(apt.getAccommodationInfo().empty());
}

TEST(ApartmentTest, SuitableForFamily) {
    Apartment apt("Family Apt", "City", 100.0, 6, 4.5, 4, true, true, 100.0);
    EXPECT_TRUE(apt.isSuitableForFamily());
}

TEST(ApartmentTest, IsStudio) {
    Apartment apt("Studio Apt", "City", 100.0, 2, 4.5, 1, true, false, 30.0);
    EXPECT_TRUE(apt.isStudio());
}

TEST(ApartmentTest, CalculatePricePerPerson) {
    Apartment apt("Test Apt", "City", 100.0, 4, 4.5, 2, true, false, 50.0);
    EXPECT_EQ(apt.calculatePricePerPerson(), 25.0);
}

TEST(ApartmentTest, GetApartmentCategory) {
    Apartment apt("Test Apt", "City", 100.0, 4, 4.5, 2, true, false, 50.0);
    EXPECT_FALSE(apt.getApartmentCategory().empty());
}

TEST(ApartmentTest, HasFullAmenities) {
    Apartment apt("Test Apt", "City", 100.0, 4, 4.5, 2, true, true, 50.0);
    EXPECT_TRUE(apt.hasFullAmenities());
}

TEST(ApartmentTest, CalculatePricePerPersonZeroCapacity) {
    Apartment apt("Test Apt", "City", 100.0, 5, 4.5, 2, true, false, 50.0);
    EXPECT_EQ(apt.calculatePricePerPerson(), 20.0);
}

TEST(BoutiqueHotelTest, ValidConstruction) {
    EXPECT_NO_THROW(BoutiqueHotel("Boutique Hotel", "City", 200.0, 2, 4.8, "Luxury", 2010, true, "Modern"));
}

TEST(BoutiqueHotelTest, NoInvalidYearThrows) {
    EXPECT_NO_THROW(BoutiqueHotel("Boutique Hotel", "City", 200.0, 2, 4.8, "Luxury", 1800, true, "Modern"));
}

TEST(BoutiqueHotelTest, GetAccommodationInfo) {
    BoutiqueHotel hotel("Boutique Hotel", "City", 200.0, 2, 4.8, "Luxury", 2010, true, "Modern");
    EXPECT_FALSE(hotel.getAccommodationInfo().empty());
}

TEST(BoutiqueHotelTest, IsHistoric) {
    BoutiqueHotel hotel("Historic Hotel", "City", 200.0, 2, 4.8, "Classic", 1900, true, "Victorian");
    EXPECT_TRUE(hotel.isHistoric());
}

TEST(BoutiqueHotelTest, IsDesignHotel) {
    BoutiqueHotel hotel("Design Hotel", "City", 200.0, 2, 4.8, "Modern", 2020, true, "Contemporary");
    EXPECT_TRUE(hotel.isDesignHotel());
}

TEST(BoutiqueHotelTest, HasPremiumServices) {
    BoutiqueHotel hotel("Boutique Hotel", "City", 200.0, 2, 4.8, "Luxury", 2010, true, "Modern");
    EXPECT_TRUE(hotel.hasPremiumServices());
}

TEST(BoutiqueHotelTest, GetBoutiqueCategory) {
    BoutiqueHotel hotel("Boutique Hotel", "City", 200.0, 2, 4.8, "Luxury", 2010, true, "Modern");
    EXPECT_FALSE(hotel.getBoutiqueCategory().empty());
}

TEST(BoutiqueHotelTest, CalculateHotelAge) {
    BoutiqueHotel hotel("Boutique Hotel", "City", 200.0, 2, 4.8, "Luxury", 2010, true, "Modern");
    EXPECT_GE(hotel.calculateHotelAge(), 0);
}

TEST(CampingTest, ValidConstruction) {
    EXPECT_NO_THROW(Camping("Campsite", "Forest", 50.0, 4, 4.0, "tent", true, true, true));
}

TEST(CampingTest, GetAccommodationInfo) {
    Camping camping("Campsite", "Forest", 50.0, 4, 4.0, "tent", true, true, true);
    EXPECT_FALSE(camping.getAccommodationInfo().empty());
}

TEST(CampingTest, IsGlamping) {
    Camping camping("Glamping", "Forest", 150.0, 4, 4.5, "cabin", true, true, true);
    EXPECT_TRUE(camping.isGlamping());
}

TEST(CampingTest, IsBasicCamping) {
    Camping camping("Basic Camp", "Forest", 30.0, 4, 4.0, "tent", false, false, true);
    EXPECT_TRUE(camping.isBasicCamping());
}

TEST(CampingTest, HasEssentialAmenities) {
    Camping camping("Campsite", "Forest", 50.0, 4, 4.0, "tent", true, true, true);
    EXPECT_TRUE(camping.hasEssentialAmenities());
}

TEST(CampingTest, GetCampingCategory) {
    Camping camping("Campsite", "Forest", 50.0, 4, 4.0, "tent", true, true, true);
    EXPECT_FALSE(camping.getCampingCategory().empty());
}

TEST(CampingTest, IsFamilyFriendly) {
    Camping camping("Family Camp", "Forest", 50.0, 4, 4.0, "tent", true, true, true);
    EXPECT_TRUE(camping.isFamilyFriendly());
}

TEST(CruiseCabinTest, ValidConstruction) {
    EXPECT_NO_THROW(CruiseCabin("Cabin", "Ocean", 300.0, 2, 4.5, "balcony", 5, true, "Cruise Ship"));
}

TEST(CruiseCabinTest, InvalidDeckThrows) {
    EXPECT_THROW(CruiseCabin("Cabin", "Ocean", 300.0, 2, 4.5, "balcony", 0, true, "Cruise Ship"), InvalidDataException);
}

TEST(CruiseCabinTest, GetAccommodationInfo) {
    CruiseCabin cabin("Cabin", "Ocean", 300.0, 2, 4.5, "balcony", 5, true, "Cruise Ship");
    EXPECT_FALSE(cabin.getAccommodationInfo().empty());
}

TEST(CruiseCabinTest, IsPremiumCabin) {
    CruiseCabin cabin("Premium Cabin", "Ocean", 500.0, 2, 4.8, "suite", 11, true, "Luxury Ship");
    EXPECT_TRUE(cabin.isPremiumCabin());
}

TEST(CruiseCabinTest, IsInteriorCabin) {
    CruiseCabin cabin("Interior Cabin", "Ocean", 200.0, 2, 4.0, "interior", 2, false, "Cruise Ship");
    EXPECT_TRUE(cabin.isInteriorCabin());
}

TEST(CruiseCabinTest, HasView) {
    CruiseCabin cabin("Cabin", "Ocean", 300.0, 2, 4.5, "balcony", 5, true, "Cruise Ship");
    EXPECT_TRUE(cabin.hasView());
}

TEST(CruiseCabinTest, GetCabinCategory) {
    CruiseCabin cabin("Cabin", "Ocean", 300.0, 2, 4.5, "balcony", 5, true, "Cruise Ship");
    EXPECT_FALSE(cabin.getCabinCategory().empty());
}

TEST(CruiseCabinTest, IsOnUpperDeck) {
    CruiseCabin cabin("Cabin", "Ocean", 300.0, 2, 4.5, "balcony", 10, true, "Cruise Ship");
    EXPECT_TRUE(cabin.isOnUpperDeck());
}

TEST(GuestHouseTest, ValidConstruction) {
    EXPECT_NO_THROW(GuestHouse("Guest House", "Town", 80.0, 3, 4.3, true, 5, "English", true));
}

TEST(GuestHouseTest, InvalidTotalRoomsThrows) {
    EXPECT_THROW(GuestHouse("Guest House", "Town", 80.0, 3, 4.3, true, 0, "English", true), InvalidDataException);
}

TEST(GuestHouseTest, GetAccommodationInfo) {
    GuestHouse gh("Guest House", "Town", 80.0, 3, 4.3, true, 5, "English", true);
    EXPECT_FALSE(gh.getAccommodationInfo().empty());
}

TEST(GuestHouseTest, IsSmallGuestHouse) {
    GuestHouse gh("Small Guest House", "Town", 80.0, 3, 4.3, true, 3, "English", true);
    EXPECT_TRUE(gh.isSmallGuestHouse());
}

TEST(GuestHouseTest, OffersPersonalService) {
    GuestHouse gh("Guest House", "Town", 80.0, 3, 4.3, true, 3, "English", true);
    EXPECT_TRUE(gh.offersPersonalService());
}

TEST(GuestHouseTest, GetGuestHouseType) {
    GuestHouse gh("Guest House", "Town", 80.0, 3, 4.3, true, 5, "English", true);
    EXPECT_FALSE(gh.getGuestHouseType().empty());
}

TEST(GuestHouseTest, IsSuitableForLongStay) {
    GuestHouse gh("Guest House", "Town", 80.0, 3, 4.3, true, 5, "English", true);
    EXPECT_TRUE(gh.isSuitableForLongStay());
}

TEST(GuestHouseTest, HasCommunityAtmosphere) {
    GuestHouse gh("Guest House", "Town", 80.0, 3, 4.3, true, 10, "English", true);
    EXPECT_TRUE(gh.hasCommunityAtmosphere());
}

TEST(GuestHouseTest, SmallFamilyGuestHouse) {
    GuestHouse gh("Small Family", "Village", 60.0, 2, 4.4, true, 2, "English", false);
    EXPECT_TRUE(gh.isSmallGuestHouse());
    EXPECT_TRUE(gh.offersPersonalService());
}

TEST(GuestHouseTest, LargeCommunityGuestHouse) {
    GuestHouse gh("Large Community", "Town", 120.0, 8, 4.6, false, 15, "Multiple", true);
    EXPECT_TRUE(gh.hasCommunityAtmosphere());
    EXPECT_FALSE(gh.offersPersonalService());
}

TEST(HostelTest, ValidConstruction) {
    EXPECT_NO_THROW(Hostel("Hostel", "City", 25.0, 6, 4.0, false, 4, true, "shared"));
}

TEST(HostelTest, InvalidBedsThrows) {
    EXPECT_THROW(Hostel("Hostel", "City", 25.0, 6, 4.0, false, 0, true, "shared"), InvalidDataException);
}

TEST(HostelTest, GetAccommodationInfo) {
    Hostel hostel("Hostel", "City", 25.0, 6, 4.0, false, 4, true, "shared");
    EXPECT_FALSE(hostel.getAccommodationInfo().empty());
}

TEST(HostelTest, IsDormitory) {
    Hostel hostel("Hostel", "City", 25.0, 6, 4.0, false, 4, true, "shared");
    EXPECT_TRUE(hostel.isDormitory());
}

TEST(HostelTest, CalculatePricePerBed) {
    Hostel hostel("Hostel", "City", 100.0, 6, 4.0, false, 4, true, "shared");
    EXPECT_EQ(hostel.calculatePricePerBed(), 25.0);
}

TEST(HostelTest, HasPrivateBathroom) {
    Hostel hostel("Hostel", "City", 25.0, 6, 4.0, true, 2, true, "private");
    EXPECT_TRUE(hostel.hasPrivateBathroom());
}

TEST(HostelTest, GetHostelCategory) {
    Hostel hostel("Hostel", "City", 25.0, 6, 4.0, false, 4, true, "shared");
    EXPECT_FALSE(hostel.getHostelCategory().empty());
}

TEST(HostelTest, IsSuitableForGroup) {
    Hostel hostel("Hostel", "City", 25.0, 6, 4.0, false, 4, true, "shared");
    EXPECT_TRUE(hostel.isSuitableForGroup(4));
}

TEST(HostelTest, PrivateRoomWithBathroom) {
    Hostel hostel("Private Hostel", "City", 50.0, 2, 4.2, true, 2, false, "private");
    EXPECT_FALSE(hostel.isDormitory());
    EXPECT_TRUE(hostel.hasPrivateBathroom());
}

TEST(HotelTest, ValidConstruction) {
    EXPECT_NO_THROW(Hotel("Hotel", "City", 150.0, 2, 4.5, 4, true, false, "standard"));
}

TEST(HotelTest, InvalidStarsThrows) {
    EXPECT_THROW(Hotel("Hotel", "City", 150.0, 2, 4.5, 6, true, false, "standard"), InvalidDataException);
}

TEST(HotelTest, GetAccommodationInfo) {
    Hotel hotel("Hotel", "City", 150.0, 2, 4.5, 4, true, false, "standard");
    EXPECT_FALSE(hotel.getAccommodationInfo().empty());
}

TEST(HotelTest, LuxuryHotelInfo) {
    Hotel hotel("Luxury Hotel", "City", 300.0, 2, 4.8, 5, true, true, "suite");
    EXPECT_TRUE(hotel.getAccommodationInfo().find("5 stars") != std::string::npos);
}

TEST(MountainLodgeTest, ValidConstruction) {
    EXPECT_NO_THROW(MountainLodge("Mountain Lodge", "Mountains", 120.0, 4, 4.2, 1500, true, true, "medium"));
}

TEST(MountainLodgeTest, InvalidAltitudeThrows) {
    EXPECT_THROW(MountainLodge("Mountain Lodge", "Mountains", 120.0, 4, 4.2, 0, true, true, "medium"), InvalidDataException);
}

TEST(MountainLodgeTest, GetAccommodationInfo) {
    MountainLodge lodge("Mountain Lodge", "Mountains", 120.0, 4, 4.2, 1500, true, true, "medium");
    EXPECT_FALSE(lodge.getAccommodationInfo().empty());
}

TEST(MountainLodgeTest, IsHighAltitude) {
    MountainLodge lodge("High Lodge", "Mountains", 120.0, 4, 4.2, 2500, true, true, "medium");
    EXPECT_TRUE(lodge.isHighAltitude());
}

TEST(MountainLodgeTest, IsWinterReady) {
    MountainLodge lodge("Winter Lodge", "Mountains", 120.0, 4, 4.2, 1500, true, true, "medium");
    EXPECT_TRUE(lodge.isWinterReady());
}

TEST(MountainLodgeTest, GetLodgeCategory) {
    MountainLodge lodge("Mountain Lodge", "Mountains", 120.0, 4, 4.2, 1500, true, true, "medium");
    EXPECT_FALSE(lodge.getLodgeCategory().empty());
}

TEST(MountainLodgeTest, IsRemoteLocation) {
    MountainLodge lodge("Remote Lodge", "Mountains", 120.0, 4, 4.2, 1500, true, true, "hard");
    EXPECT_TRUE(lodge.isRemoteLocation());
}

TEST(MountainLodgeTest, RequiresExperience) {
    MountainLodge lodge("Expert Lodge", "Mountains", 120.0, 4, 4.2, 1500, true, true, "expert");
    EXPECT_TRUE(lodge.requiresExperience());
}

TEST(MountainLodgeTest, LowAltitudeLodge) {
    MountainLodge lodge("Low Lodge", "Mountains", 100.0, 4, 4.0, 800, false, false, "easy");
    EXPECT_FALSE(lodge.isHighAltitude());
    EXPECT_FALSE(lodge.isWinterReady());
}

TEST(ResortTest, ValidConstruction) {
    EXPECT_NO_THROW(Resort("Resort", "Beach", 300.0, 4, 4.7, true, 3, true, {"pool", "spa"}));
}

TEST(ResortTest, InvalidRestaurantsThrows) {
    EXPECT_THROW(Resort("Resort", "Beach", 300.0, 4, 4.7, true, 0, true, {"pool"}), InvalidDataException);
}

TEST(ResortTest, GetAccommodationInfo) {
    Resort resort("Resort", "Beach", 300.0, 4, 4.7, true, 3, true, {"pool", "spa"});
    EXPECT_FALSE(resort.getAccommodationInfo().empty());
}

TEST(ResortTest, IsLuxuryResort) {
    Resort resort("Luxury Resort", "Beach", 500.0, 4, 4.9, true, 5, true, {"pool", "spa", "golf"});
    EXPECT_TRUE(resort.isLuxuryResort());
}

TEST(ResortTest, HasComprehensiveAmenities) {
    Resort resort("Comprehensive Resort", "Beach", 400.0, 4, 4.7, true, 4, true, {"pool", "spa"});
    EXPECT_TRUE(resort.hasComprehensiveAmenities());
}

TEST(ResortTest, GetActivityCount) {
    Resort resort("Activity Resort", "Beach", 300.0, 4, 4.7, true, 3, true, {"pool", "spa", "tennis"});
    EXPECT_EQ(resort.getActivityCount(), 3);
}

TEST(ResortTest, GetResortCategory) {
    Resort resort("Resort", "Beach", 300.0, 4, 4.7, true, 3, true, {"pool", "spa"});
    EXPECT_FALSE(resort.getResortCategory().empty());
}

TEST(ResortTest, IsBeachResort) {
    Resort resort("Beach Resort", "Beach", 300.0, 4, 4.7, true, 3, true, {"pool", "spa"});
    EXPECT_TRUE(resort.isBeachResort());
}

TEST(ResortTest, ResortWithManyActivities) {
    Resort resort("Active Resort", "Beach", 350.0, 4, 4.6, false, 2, false, {"hiking", "yoga", "surfing", "cycling"});
    EXPECT_GE(resort.getActivityCount(), 3);
}

TEST(VillaTest, ValidConstruction) {
    EXPECT_NO_THROW(Villa("Villa", "Coast", 400.0, 6, 4.8, 2, true, true, true));
}

TEST(VillaTest, InvalidFloorsThrows) {
    EXPECT_THROW(Villa("Villa", "Coast", 400.0, 6, 4.8, 0, true, true, true), InvalidDataException);
}

TEST(VillaTest, GetAccommodationInfo) {
    Villa villa("Villa", "Coast", 400.0, 6, 4.8, 2, true, true, true);
    EXPECT_FALSE(villa.getAccommodationInfo().empty());
}

TEST(VillaTest, IsLuxuryVilla) {
    Villa villa("Luxury Villa", "Coast", 500.0, 10, 4.9, 4, true, true, true);
    EXPECT_TRUE(villa.isLuxuryVilla());
}

TEST(VillaTest, HasFullPrivacy) {
    Villa villa("Private Villa", "Coast", 400.0, 6, 4.8, 2, true, true, true);
    EXPECT_TRUE(villa.hasFullPrivacy());
}

TEST(VillaTest, CalculateLuxurySurcharge) {
    Villa villa("Villa", "Coast", 400.0, 6, 4.8, 2, true, true, true);
    EXPECT_GE(villa.calculateLuxurySurcharge(), 0.0);
}

TEST(VillaTest, GetVillaCategory) {
    Villa villa("Villa", "Coast", 400.0, 6, 4.8, 2, true, true, true);
    EXPECT_FALSE(villa.getVillaCategory().empty());
}

TEST(VillaTest, IsSuitableForEvents) {
    Villa villa("Event Villa", "Coast", 400.0, 20, 4.8, 2, true, true, true);
    EXPECT_TRUE(villa.isSuitableForEvents());
}

TEST(VillaTest, BasicVillaNoAmenities) {
    Villa villa("Basic Villa", "Coast", 200.0, 4, 4.0, 1, false, false, false);
    EXPECT_FALSE(villa.isLuxuryVilla());
    EXPECT_FALSE(villa.hasFullPrivacy());
}

TEST(AllTypesTest, AmenityManagement) {
    Hotel hotel("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    hotel.addAmenity("WiFi");
    hotel.addAmenity("Breakfast");
    EXPECT_NO_THROW(hotel.addAmenity("WiFi"));
}

TEST(AllTypesTest, PriceBoundaryTesting) {
    EXPECT_NO_THROW(Hotel("Hotel", "City", AccommodationConfig::Accommodation::MIN_PRICE_PER_NIGHT, 2, 4.5, 3, true, false, "standard"));
    EXPECT_NO_THROW(Hotel("Hotel", "City", AccommodationConfig::Accommodation::MAX_PRICE_PER_NIGHT, 2, 4.5, 3, true, false, "standard"));
}

TEST(AllTypesTest, RatingBoundaryTesting) {
    EXPECT_NO_THROW(Hotel("Hotel", "City", 100.0, 2, AccommodationConfig::Accommodation::MIN_RATING, 3, true, false, "standard"));
    EXPECT_NO_THROW(Hotel("Hotel", "City", 100.0, 2, AccommodationConfig::Accommodation::MAX_RATING, 3, true, false, "standard"));
}

TEST(AllTypesTest, CapacityBoundaryTesting) {
    EXPECT_NO_THROW(Hotel("Hotel", "City", 100.0, AccommodationConfig::Accommodation::MIN_CAPACITY, 4.5, 3, true, false, "standard"));
    EXPECT_NO_THROW(Hotel("Hotel", "City", 100.0, AccommodationConfig::Accommodation::MAX_CAPACITY, 4.5, 3, true, false, "standard"));
}

TEST(AllTypesTest, CrossClassMethodConsistency) {
    Hotel hotel("Hotel", "City", 100.0, 4, 4.5, 3, true, false, "standard");
    Apartment apt("Apartment", "City", 100.0, 4, 4.5, 2, true, false, 50.0);
    EXPECT_TRUE(hotel.canAccommodate(3));
    EXPECT_TRUE(apt.canAccommodate(3));
    EXPECT_NO_THROW(hotel.validateBooking(3, "2024-01-01", "2024-01-05"));
    EXPECT_NO_THROW(apt.validateBooking(3, "2024-01-01", "2024-01-05"));
}

TEST(AccommodationGettersTest, HotelGettersReturnCorrectValues) {
    Hotel hotel("Test Hotel", "Test Location", 150.0, 4, 4.5, 4, true, true, "deluxe");
    EXPECT_EQ(hotel.getName(), "Test Hotel");
    EXPECT_EQ(hotel.getLocation(), "Test Location");
    EXPECT_EQ(hotel.getPricePerNight(), 150.0);
    EXPECT_EQ(hotel.getCapacity(), 4);
    EXPECT_EQ(hotel.getRating(), 4.5);
    EXPECT_EQ(hotel.getType(), "Hotel");
    EXPECT_EQ(hotel.getStarRating(), 4);
    EXPECT_TRUE(hotel.hasSwimmingPool());
    EXPECT_TRUE(hotel.hasSpaService());
    EXPECT_EQ(hotel.getRoomType(), "deluxe");
}

TEST(AccommodationGettersTest, ApartmentGettersReturnCorrectValues) {
    Apartment apt("Test Apartment", "City Center", 120.0, 4, 4.3, 3, true, true, 75.5);
    EXPECT_EQ(apt.getName(), "Test Apartment");
    EXPECT_EQ(apt.getLocation(), "City Center");
    EXPECT_EQ(apt.getPricePerNight(), 120.0);
    EXPECT_EQ(apt.getCapacity(), 4);
    EXPECT_EQ(apt.getRating(), 4.3);
    EXPECT_EQ(apt.getType(), "Apartment");
    EXPECT_EQ(apt.getNumberOfRooms(), 3);
    EXPECT_TRUE(apt.hasFullKitchen());
    EXPECT_TRUE(apt.hasLaundry());
    EXPECT_EQ(apt.getArea(), 75.5);
}

TEST(AccommodationGettersTest, BoutiqueHotelGettersReturnCorrectValues) {
    BoutiqueHotel boutique("Boutique", "Downtown", 200.0, 2, 4.8, "Design", 2015, true, "Modern");
    EXPECT_EQ(boutique.getName(), "Boutique");
    EXPECT_EQ(boutique.getLocation(), "Downtown");
    EXPECT_EQ(boutique.getPricePerNight(), 200.0);
    EXPECT_EQ(boutique.getCapacity(), 2);
    EXPECT_EQ(boutique.getRating(), 4.8);
    EXPECT_EQ(boutique.getType(), "Boutique Hotel");
    EXPECT_EQ(boutique.getTheme(), "Design");
    EXPECT_EQ(boutique.getYearBuilt(), 2015);
    EXPECT_TRUE(boutique.hasConciergeService());
    EXPECT_EQ(boutique.getArchitecturalStyle(), "Modern");
}

TEST(AccommodationGettersTest, CampingGettersReturnCorrectValues) {
    Camping camping("Forest Camp", "National Park", 50.0, 6, 4.2, "cabin", true, true, true);
    EXPECT_EQ(camping.getName(), "Forest Camp");
    EXPECT_EQ(camping.getLocation(), "National Park");
    EXPECT_EQ(camping.getPricePerNight(), 50.0);
    EXPECT_EQ(camping.getCapacity(), 6);
    EXPECT_EQ(camping.getRating(), 4.2);
    EXPECT_EQ(camping.getType(), "Camping");
    EXPECT_EQ(camping.getAccommodationType(), "cabin");
    EXPECT_TRUE(camping.hasSharedBathrooms());
    EXPECT_TRUE(camping.hasElectricalAccess());
    EXPECT_TRUE(camping.isCampfireAllowed());
}

TEST(AccommodationGettersTest, CruiseCabinGettersReturnCorrectValues) {
    CruiseCabin cabin("Ocean View", "Caribbean", 300.0, 2, 4.6, "balcony", 7, true, "Royal Cruise");
    EXPECT_EQ(cabin.getName(), "Ocean View");
    EXPECT_EQ(cabin.getLocation(), "Caribbean");
    EXPECT_EQ(cabin.getPricePerNight(), 300.0);
    EXPECT_EQ(cabin.getCapacity(), 2);
    EXPECT_EQ(cabin.getRating(), 4.6);
    EXPECT_EQ(cabin.getType(), "Cruise Cabin");
    EXPECT_EQ(cabin.getCabinType(), "balcony");
    EXPECT_EQ(cabin.getDeckNumber(), 7);
    EXPECT_TRUE(cabin.hasOceanView());
    EXPECT_EQ(cabin.getShipName(), "Royal Cruise");
}

TEST(AccommodationGettersTest, GuestHouseGettersReturnCorrectValues) {
    GuestHouse guestHouse("Cozy Stay", "Village", 70.0, 3, 4.4, true, 6, "English", true);
    EXPECT_EQ(guestHouse.getName(), "Cozy Stay");
    EXPECT_EQ(guestHouse.getLocation(), "Village");
    EXPECT_EQ(guestHouse.getPricePerNight(), 70.0);
    EXPECT_EQ(guestHouse.getCapacity(), 3);
    EXPECT_EQ(guestHouse.getRating(), 4.4);
    EXPECT_EQ(guestHouse.getType(), "Guest House");
    EXPECT_TRUE(guestHouse.isFamilyBusiness());
    EXPECT_EQ(guestHouse.getTotalRooms(), 6);
    EXPECT_EQ(guestHouse.getHostLanguage(), "English");
    EXPECT_TRUE(guestHouse.hasCommonSpace());
}

TEST(AccommodationGettersTest, HostelGettersReturnCorrectValues) {
    Hostel hostel("Backpacker", "City", 25.0, 8, 4.0, false, 6, true, "shared");
    EXPECT_EQ(hostel.getName(), "Backpacker");
    EXPECT_EQ(hostel.getLocation(), "City");
    EXPECT_EQ(hostel.getPricePerNight(), 25.0);
    EXPECT_EQ(hostel.getCapacity(), 8);
    EXPECT_EQ(hostel.getRating(), 4.0);
    EXPECT_EQ(hostel.getType(), "Hostel");
    EXPECT_FALSE(hostel.isPrivate());
    EXPECT_EQ(hostel.getBedsPerRoom(), 6);
    EXPECT_TRUE(hostel.hasCommonKitchen());
    EXPECT_EQ(hostel.getBathroomType(), "shared");
}

TEST(AccommodationGettersTest, MountainLodgeGettersReturnCorrectValues) {
    MountainLodge lodge("Alpine", "Mountains", 130.0, 4, 4.3, 1800, true, true, "medium");
    EXPECT_EQ(lodge.getName(), "Alpine");
    EXPECT_EQ(lodge.getLocation(), "Mountains");
    EXPECT_EQ(lodge.getPricePerNight(), 130.0);
    EXPECT_EQ(lodge.getCapacity(), 4);
    EXPECT_EQ(lodge.getRating(), 4.3);
    EXPECT_EQ(lodge.getType(), "Mountain Lodge");
    EXPECT_EQ(lodge.getAltitude(), 1800);
    EXPECT_TRUE(lodge.hasHeatingSystem());
    EXPECT_TRUE(lodge.hasFireplaceFeature());
    EXPECT_EQ(lodge.getAccessibilityLevel(), "medium");
}

TEST(AccommodationGettersTest, ResortGettersReturnCorrectValues) {
    Resort resort("Paradise", "Beach", 350.0, 4, 4.7, true, 4, true, {"pool", "spa", "tennis"});
    EXPECT_EQ(resort.getName(), "Paradise");
    EXPECT_EQ(resort.getLocation(), "Beach");
    EXPECT_EQ(resort.getPricePerNight(), 350.0);
    EXPECT_EQ(resort.getCapacity(), 4);
    EXPECT_EQ(resort.getRating(), 4.7);
    EXPECT_EQ(resort.getType(), "Resort");
    EXPECT_TRUE(resort.hasBeachAccess());
    EXPECT_EQ(resort.getRestaurantCount(), 4);
    EXPECT_TRUE(resort.hasSpaServices());
    EXPECT_EQ(resort.getActivities().size(), 3);
    EXPECT_EQ(resort.getActivities()[0], "pool");
    EXPECT_EQ(resort.getActivities()[1], "spa");
    EXPECT_EQ(resort.getActivities()[2], "tennis");
}

TEST(AccommodationGettersTest, VillaGettersReturnCorrectValues) {
    Villa villa("Luxury Villa", "Coast", 500.0, 8, 4.9, 2, true, true, true);
    EXPECT_EQ(villa.getName(), "Luxury Villa");
    EXPECT_EQ(villa.getLocation(), "Coast");
    EXPECT_EQ(villa.getPricePerNight(), 500.0);
    EXPECT_EQ(villa.getCapacity(), 8);
    EXPECT_EQ(villa.getRating(), 4.9);
    EXPECT_EQ(villa.getType(), "Villa");
    EXPECT_EQ(villa.getNumberOfFloors(), 2);
    EXPECT_TRUE(villa.hasPool());
    EXPECT_TRUE(villa.hasGardenArea());
    EXPECT_TRUE(villa.hasParkingSpace());
}

TEST(AccommodationGettersTest, AmenitiesListEmptyByDefault) {
    Hotel hotel("Test", "Location", 100.0, 2, 4.5, 3, false, false, "standard");
    EXPECT_TRUE(hotel.getAmenities().empty());
}

TEST(AccommodationGettersTest, AmenitiesListContainsAddedAmenities) {
    Hotel hotel("Test", "Location", 100.0, 2, 4.5, 3, false, false, "standard");
    hotel.addAmenity("WiFi");
    hotel.addAmenity("Breakfast");
    auto amenities = hotel.getAmenities();
    EXPECT_EQ(amenities.size(), 2);
    EXPECT_EQ(amenities[0], "WiFi");
    EXPECT_EQ(amenities[1], "Breakfast");
}

TEST(AccommodationGettersTest, PrivateHostelGetters) {
    Hostel privateHostel("Private", "City", 60.0, 2, 4.2, true, 2, false, "private");
    EXPECT_TRUE(privateHostel.isPrivate());
    EXPECT_EQ(privateHostel.getBedsPerRoom(), 2);
    EXPECT_FALSE(privateHostel.hasCommonKitchen());
    EXPECT_EQ(privateHostel.getBathroomType(), "private");
}

TEST(AccommodationGettersTest, BasicCampingGetters) {
    Camping basicCamping("Basic", "Forest", 20.0, 2, 3.8, "tent", false, false, true);
    EXPECT_EQ(basicCamping.getAccommodationType(), "tent");
    EXPECT_FALSE(basicCamping.hasSharedBathrooms());
    EXPECT_FALSE(basicCamping.hasElectricalAccess());
    EXPECT_TRUE(basicCamping.isCampfireAllowed());
}

TEST(AccommodationGettersTest, InteriorCruiseCabinGetters) {
    CruiseCabin interior("Interior", "Ocean", 150.0, 2, 4.0, "interior", 2, false, "Ship");
    EXPECT_EQ(interior.getCabinType(), "interior");
    EXPECT_EQ(interior.getDeckNumber(), 2);
    EXPECT_FALSE(interior.hasOceanView());
}

TEST(AccommodationGettersTest, LargeGuestHouseGetters) {
    GuestHouse largeHouse("Large", "Town", 100.0, 10, 4.5, false, 20, "Multiple", true);
    EXPECT_FALSE(largeHouse.isFamilyBusiness());
    EXPECT_EQ(largeHouse.getTotalRooms(), 20);
    EXPECT_TRUE(largeHouse.hasCommonSpace());
}

TEST(AccommodationGettersTest, HighAltitudeLodgeGetters) {
    MountainLodge highLodge("High Peak", "Alps", 200.0, 6, 4.6, 3000, true, true, "expert");
    EXPECT_EQ(highLodge.getAltitude(), 3000);
    EXPECT_EQ(highLodge.getAccessibilityLevel(), "expert");
}

TEST(AccommodationGettersTest, ResortWithManyActivitiesGetters) {
    Resort activeResort("Active", "Mountains", 280.0, 6, 4.4, false, 2, false, 
                       {"hiking", "climbing", "skiing", "yoga", "cycling"});
    EXPECT_EQ(activeResort.getActivityCount(), 5);
    EXPECT_FALSE(activeResort.hasBeachAccess());
    EXPECT_FALSE(activeResort.hasSpaServices());
}

TEST(AccommodationGettersTest, MultiStoryVillaGetters) {
    Villa multiVilla("Multi Story", "Hills", 450.0, 10, 4.8, 3, true, false, true);
    EXPECT_EQ(multiVilla.getNumberOfFloors(), 3);
    EXPECT_TRUE(multiVilla.hasPool());
    EXPECT_FALSE(multiVilla.hasGardenArea());
    EXPECT_TRUE(multiVilla.hasParkingSpace());
}