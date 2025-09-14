/**
 * @file MultiSets.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the MultiSet class for working with multisets
 * @version 0.1
 * @date 2025-09-09
 * 
 * 
 */

#include <vector>
#include <string>
#include <utility>

/**
 * @class MultiSet
 * @brief Class for working with multisets
 * 
 * Stores elements as strings with their counts.
 * Supports multiset operations: union, 
 * intersection, difference, membership testing, 
 * and boolean creation
 */
class MultiSet{
    std::vector<std::pair<std::string, int>> elInMultiSet;
    /**
     * @brief Private method to add one element to a multiset
     * 
     * @param &element constant reference of the string containing 
     * the element to add to the multiset
     * 
     * @return true
     * @return false
     */
    bool add(const std::string& element);

    /**
     * @brief Private method for parsing a string to bring it to the desired form
     * 
     * @param &string constant reference of the string to parse
     * @return std::vector<std::string> 
     */
    std::vector<std::string> parseMultiSetString(const std::string& string);

    /**
     * @brief Private method to check if a string is valid
     * 
     * @param &string constant reference of the string being checked
     * @return true 
     * @return false 
     */
    bool isValid(const std::string& string) const;

    /**
     * @brief Private constant method to convert a class multiset to a string
     * 
     * @return std::string
     */
    std::string toString() const;

    /**
     * @brief Private intermediate method to remove all 
     * spaces in a string
     * 
     * @param &str constant reference of the image string to form the output 
     * prototype string after removing spaces
     * @return std::string 
     */
    std::string removeSpaces(const std::string& str);
    
    /**
     * @brief Private method to validate element content (letters and digits only)
     * 
     * @param str string to validate
     * @param start starting index of the element
     * @return int end index of the element
     */
    int validateElement(const std::string& str, size_t start) const;
    
    /**
     * @brief Private method to handle bracket characters
     * 
     * @param c current character
     * @param balance reference to bracket balance counter
     * @param expectElement reference to element expectation flag
     * @param afterComma reference to comma flag
     * @return bool true if valid, false otherwise
     */
    bool handleBracket(char c, int& balance, bool& expectElement, bool& afterComma) const;
    
    /**
     * @brief Private method to handle comma character
     * 
     * @param expectElement reference to element expectation flag
     * @param afterComma reference to comma flag
     * @return bool true if valid, false otherwise
     */
    bool handleComma(bool& expectElement, bool& afterComma) const;
    
    public:
    /**
     * @brief Construct a new MultiSet object
     * 
     */
    MultiSet();

    /**
     * @brief Destroy the MultiSet object
     * 
     */
    ~MultiSet();

    /**
     * @brief Public method to remove an element from a multiset
     * 
     * @param &element constant reference of the string to remove element from multiset
     * @return true 
     * @return false 
     */
    bool remove(const std::string& element);

    /**
     * @brief Public method to remove all occurrences of an element from a multiset
     * 
     * @param &element constant reference of the string to remove all occurrences
     * @return int - number of elements removed
     */
    int removeAll(const std::string& element);

    /**
     * @brief Public method to clear the entire multiset
     * 
     */
    void clear();

    /**
     * @brief Public method for getting the cardinality of a multiset (total count of all elements)
     * 
     * @return int 
     */
    int getCardinality() const;

    /**
     * @brief Public method for getting the number of distinct elements in multiset
     * 
     * @return int 
     */
    int getDistinctCount() const;

    /**
     * @brief Public method for getting the count of a specific element
     * 
     * @param &element constant reference to the element
     * @return int - count of the element
     */
    int getCount(const std::string& element) const;

    /**
     * @brief Public constant method for determining whether a multiset is empty
     * 
     * @return true 
     * @return false 
     */
    bool isVoid() const;

    /**
     * @brief Public method for creating a boolean from a multiset
     * 
     * @return MultiSet 
     */
    MultiSet getBoolean();

    /**
     * @brief Constant method to get a constant reference to a vector 
     * of elements with counts in a multiset
     * 
     * @return const std::vector<std::pair<std::string, int>>& 
     */
    const std::vector<std::pair<std::string, int>>& getElInMultiSet() const;

    /**
     * @brief Copy constructor
     * 
     * @param other constant reference to the multiset being copied
     */
    MultiSet(const MultiSet& other);

    /**
     * @brief Assignment operator
     * 
     * @param other constant reference to the multiset being copied
     * @return MultiSet& 
     */
    MultiSet& operator = (const MultiSet& other);

    /**
     * @brief Public operator for filling a multiset with a string
     * 
     * @param elements constant reference to a multiset string
     * @return MultiSet& 
     */
    MultiSet& operator = (const std::string& elements);

    /**
     * @brief Analogue of the operator fill a multiset with a string for working with the data type char
     * 
     * @param elements constant pointer of type char
     * @return MultiSet& 
     */
    MultiSet& operator =( const char* elements);

    /**
     * @brief Public operator for comparing two multisets
     * 
     * @param other constant reference to the multiset being compared
     * @return true 
     * @return false 
     */
    bool operator == (const MultiSet& other);

    /**
     * @brief Constant public operator for checking whether an element is in a multiset
     * 
     * @param isHere constant reference to the string containing the element being checked
     * @return true 
     * @return false 
     */
    bool operator [] (const std::string& isHere) const;

    /**
     * @brief Analog operator checks if an element is present in a multiset for working with a constant char data type
     * 
     * @param isHere constant pointer of type char
     * @return true 
     * @return false 
     */
    bool operator [] (const char* isHere) const;

    /**
     * @brief Public operator for adding elements from another multiset to the current multiset (union operation)
     * 
     * @param other constant reference to the multiset whose elements are being added
     * @return MultiSet&
     */
    MultiSet& operator += (const MultiSet& other);

    /**
     * @brief Public operator for adding a single element represented as a string to the current multiset
     * 
     * @param string constant reference to the string containing the element to add
     * @return MultiSet&
     */
    MultiSet& operator += (const std::string& string);

    /**
     * @brief Public operator for adding a single element represented as a character array to the current multiset
     * 
     * @param elements constant pointer of type char containing the element to add
     * @return MultiSet&
     */
    MultiSet& operator += (const char* elements);

    /**
     * @brief Public operator for union of two multisets
     * 
     * @param other constant reference to the multiset to unite with
     * @return MultiSet
     */
    MultiSet operator + (const MultiSet& other);

    /**
     * @brief Public operator for intersection of two multisets
     * 
     * @param other constant reference to the multiset to intersect with
     * @return MultiSet
     */
    MultiSet operator * (const MultiSet& other);

    /**
     * @brief Public operator for intersection with assignment
     * 
     * @param other constant reference to the multiset to intersect with
     * @return MultiSet&
     */
    MultiSet& operator *= (const MultiSet& other);

    /**
     * @brief Public operator for difference with assignment
     * 
     * @param other constant reference to the multiset to subtract
     * @return MultiSet&
     */
    MultiSet& operator -= (const MultiSet& other);

    /**
     * @brief Public operator for difference of two multisets
     * 
     * @param other constant reference to the multiset to subtract
     * @return MultiSet
     */
    MultiSet operator - (const MultiSet& other);

    /**
     * @brief Friend operator for outputting multiset to output stream
     * 
     * @param os reference to output stream
     * @param set constant reference to the multiset to output
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const MultiSet& set);
    
    /**
     * @brief Friend operator for inputting multiset from input stream
     * 
     * @param is reference to input stream
     * @param set reference to the multiset to input data into
     * @return std::istream&
     */
    friend std::istream& operator>>(std::istream& is, MultiSet& set);
};