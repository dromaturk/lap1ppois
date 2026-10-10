#include "set.h"
#include <algorithm>

using namespace std;

string Set::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

string Set::normalize(const string& str) {
    string t = trim(str);
    if (!t.empty() && t[0] == '{') return Set(t).toString();
    return t;
}

vector<string> Set::split(const string& str) {
    vector<string> parts;
    string current;
    int depth = 0;
    for (char ch : str) {
        if (ch == '{') depth++;
        if (ch == '}') depth--;
        if (ch == ',' && depth == 0) {
            parts.push_back(current);
            current.clear();
        } else {
            current += ch;
        }
    }
    parts.push_back(current);
    return parts;
}

Set::Set(const string& str) {
    string s = trim(str);
    if (s.size() >= 2 && s.front() == '{' && s.back() == '}') {
        s = s.substr(1, s.size() - 2);
    }
    for (const string& part : split(s)) {
        add(part);
    }
}

Set::Set(const char* str) : Set(string(str)) {}

Set::Set(const Set& other) {
    this->elems = other.elems;
}

void Set::add(const string& elem) {
    string e = normalize(elem);
    if (e.empty()) return;
    auto it = lower_bound(elems.begin(), elems.end(), e);
    if (it != elems.end() && *it == e) return;
    elems.insert(it, e);
}

void Set::remove(const string& elem) {
    string e = normalize(elem);
    auto it = lower_bound(elems.begin(), elems.end(), e);
    if (it != elems.end() && *it == e) elems.erase(it);
}

Set Set::powerSet() const {
    vector<Set> subsets(1);
    for (const string& e : elems) {
        size_t n = subsets.size();
        for (size_t i = 0; i < n; i++) {
            Set copy = subsets[i];
            copy.add(e);
            subsets.push_back(copy);
        }
    }
    Set result;
    for (const Set& s : subsets) {
        result.add(s.toString());
    }
    return result;
}

string Set::toString() const {
    string result = "{";
    for (size_t i = 0; i < elems.size(); i++) {
        if (i > 0) result += ", ";
        result += elems[i];
    }
    return result + "}";
}

bool Set::operator[](const string& elem) const {
    return binary_search(elems.begin(), elems.end(), normalize(elem));
}

Set Set::operator+(const Set& other) const {
    Set result(*this);
    for (const string& e : other.elems) {
        result.add(e);
    }
    return result;
}

Set Set::operator*(const Set& other) const {
    Set result;
    for (const string& e : elems) {
        if (other[e]) result.add(e);
    }
    return result;
}

Set Set::operator-(const Set& other) const {
    Set result;
    for (const string& e : elems) {
        if (!other[e]) result.add(e);
    }
    return result;
}

Set& Set::operator+=(const Set& other) {
    *this = *this + other;
    return *this;
}

Set& Set::operator*=(const Set& other) {
    *this = *this * other;
    return *this;
}

Set& Set::operator-=(const Set& other) {
    *this = *this - other;
    return *this;
}

Set& Set::operator=(const Set& other) {
    if (this == &other) return *this;
    this->elems = other.elems;
    return *this;
}

bool Set::operator==(const Set& other) const {
    return elems == other.elems;
}

bool Set::operator!=(const Set& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& os, const Set& set) {
    os << set.toString();
    return os;
}

istream& operator>>(istream& is, Set& set) {
    string line;
    is >> ws;
    if (getline(is, line)) {
        set = Set(line);
    }
    return is;
}
