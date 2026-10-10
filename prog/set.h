#pragma once
#include <iostream>
#include <string>
#include <vector>

class Set {
public:
    Set(){};
    Set(const char* str);
    Set(const std::string& str);
    Set(const Set& other);
    ~Set(){};
    bool isEmpty() const {
        return this->elems.empty();
    }
    int size() const {
        return this->elems.size();
    }
    void add(const std::string& elem);
    void remove(const std::string& elem);
    Set powerSet() const;
    std::string toString() const;
    bool operator[](const std::string& elem) const;
    Set operator+(const Set& other) const;
    Set operator*(const Set& other) const;
    Set operator-(const Set& other) const;
    Set& operator+=(const Set& other);
    Set& operator*=(const Set& other);
    Set& operator-=(const Set& other);
    Set& operator=(const Set& other);
    bool operator==(const Set& other) const;
    bool operator!=(const Set& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Set& set);
    friend std::istream& operator>>(std::istream& is, Set& set);
private:
    std::vector<std::string> elems;
    static std::string trim(const std::string& str);
    static std::string normalize(const std::string& str);
    static std::vector<std::string> split(const std::string& str);
};
