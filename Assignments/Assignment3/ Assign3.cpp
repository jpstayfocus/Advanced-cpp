/*
 * Name: Jephte Pierre
 * Date: March 10, 2024
 * Description:
 * This program is to implement a custom String class that provides most of the functionality of the STL string.
 * Only ressource used: https://www.geeksforgeeks.org/how-to-create-a-custom-string-class-in-c-with-basic-functionalities/
 *
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdexcept>

class String
{
private:
    char *data;
    size_t length;
    size_t capacity;

    // Helper function to copy data from another string

    void copyFrom(const String &other)
    {
        data = new char[other.capacity];
        std::copy(other.data, other.data + other.length, data);
        length = other.length;
        capacity = other.capacity;
    }

public:
    // Constructors

    String() : data(nullptr), length(0), capacity(0) {}

    String(const char *str) : length(std::strlen(str)), capacity(length)
    {
        data = new char[length];
        std::copy(str, str + length, data);
    }

    String(const String &other)
    {
        copyFrom(other);
    }

    String(String &&other) noexcept : data(other.data), length(other.length), capacity(other.capacity)
    {
        other.data = nullptr;
        other.length = 0;
    }

    // Destructor

    ~String()
    {
        delete[] data;
    }

    // Copy assignment operator

    String &operator=(const String &other)
    {
        if (this != &other)
        {
            delete[] data;
            copyFrom(other);
        }
        return *this;
    }

    // Move assignment operator

    String &operator=(String &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            length = other.length;
            capacity = other.capacity;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    // Operator overloads

    String &operator+=(const String &other)
    {
        size_t newLength = length + other.length;
        char *newData = new char[newLength];
        std::copy(data, data + length, newData);
        std::copy(other.data, other.data + other.length, newData + length);
        delete[] data;
        data = newData;
        length = newLength;
        return *this;
    }

    String operator-(const String &other) const
    {
        String result(*this);
        size_t pos = result.find(other);
        if (pos != std::string::npos)
        {
            result.erase(pos, other.length);
        }
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const String &str)
    {
        os << str.data;
        return os;
    }

    // Other methods

    size_t size() const
    {
        return length;
    }

    bool empty() const
    {
        return length == 0;
    }

    void clear()
    {
        delete[] data;
        data = nullptr;
        length = 0;
        capacity = 0;
    }

    void append(const String &str)
    {
        *this += str;
    }

    void insert(size_t pos, const String &str)
    {
        if (pos > length)
        {
            throw std::out_of_range("Position out of range");
        }

        size_t newLength = length + str.length;
        // +1 for null terminator

        char *newData = new char[newLength + 1];

        // Copy characters before pos

        std::copy(data, data + pos, newData);

        // Insert str
        std::copy(str.data, str.data + str.length, newData + pos);
        // Copy characters after pos

        std::copy(data + pos, data + length, newData + pos + str.length);
        delete[] data;
        data = newData;
        length = newLength;
    }

    void erase(size_t pos, size_t len)
    {
        if (pos >= length)
        {
            throw std::out_of_range("Position out of range");
        }

        // Adjust len if it exceeds the length from pos to end of string

        len = std::min(len, length - pos);

        std::copy(data + pos + len, data + length, data + pos);
        length -= len;

        // Null terminate the string

        data[length] = '\0';
    }

    String substr(size_t pos, size_t len) const
    {
        if (pos >= length)
        {
            throw std::out_of_range("Position out of range");
        }

        len = std::min(len, length - pos);

        String subString;

        // Reserve memory for the substring

        subString.reserve(len);

        // Copy characters from the original string to the substring

        std::copy(data + pos, data + pos + len, subString.data);

        subString.length = len;

        // Null terminate the substring

        subString.data[len] = '\0';

        return subString;
    }

    size_t find(const String &str, size_t pos = 0) const
    {
        if (pos >= length)
        {

            // Return npos if pos is out of range

            return std::string::npos;
        }

        const char *found = std::search(data + pos, data + length, str.data, str.data + str.length);

        if (found != data + length)
        {

            // Return the position of the first character of the found substring

            return found - data;
        }
        else
        {

            // Return npos if str is not found

            return std::string::npos;
        }
    }

    void replace(size_t pos, size_t len, const String &str)
    {
        if (pos > length)
        {
            throw std::out_of_range("Position out of range");
        }

        if (pos + len > length)
        {
            len = length - pos;
        }

        size_t newLength = length - len + str.length;

        if (newLength > capacity)
        {
            reserve(newLength);
        }

        // Shift elements to make space for the new characters

        std::copy_backward(data + pos + len, data + length, data + newLength);

        // Copy the contents of str into the string at the specified position

        std::copy(str.data, str.data + str.length, data + pos);

        // Update the length of the string

        length = newLength;
    }

    void reserve(size_t newCapacity)
    {
        if (newCapacity <= capacity)
        {
            return;
        }

        char *newData = new char[newCapacity];
        std::copy(data, data + length, newData);
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
};

int main()
{
    String str1("Implementation");
    String str2(" of Custom String Class Completed");

    // Copy constructor
    String str3 = str1;
    // Operator+=
    str3 += str2;

    std::cout << "Assignment: " << str3 << std::endl;

    return 0;
}
