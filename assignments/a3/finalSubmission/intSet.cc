#include "intSet.h"

// Default constructor
intSet::intSet() : data(nullptr), size(0), capacity(0) {}
// Copy constructor
intSet::intSet(const intSet& is) : size(is.size), capacity(is.capacity) {
    data = new int[capacity];
for (int i = 0; i < size; ++i) data[i] = is.data[i];
}
// Move constructor
intSet::intSet(intSet &&is) noexcept : data(is.data), size(is.size), capacity(is.capacity) {
    is.data = nullptr;
    is.size = 0;
    is.capacity = 0;
}
// Copy assignment operator
intSet& intSet::operator=(const intSet& is) {
if (this != &is) {
if (capacity < is.size) {
delete[] data;
            data = new int[is.size];
            capacity = is.size;
        }
        size = is.size;
int i = 0;
while (i < size) {
            data[i] = is.data[i];
            ++i;
        }
    }
return *this;
}
// Move assignment operator
intSet& intSet::operator=(intSet &&is) noexcept {
if (this != &is) {
delete[] data;
        data = is.data;
        size = is.size;
        capacity = is.capacity;
        is.data = nullptr;
        is.size = 0;
        is.capacity = 0;
    }
return *this;
}
// Destructor
intSet::~intSet() {
delete[] data;
}
// Set union
intSet intSet::operator|(const intSet &other) const {
    intSet result = *this;
for (int i = 0; i < other.size; ++i) {
        result.add(other.data[i]);
    }
return result;
}
// Set intersection
intSet intSet::operator&(const intSet &other) const {
    intSet result;
    for (int i = 0; i < size; ++i) {if (other.contains(data[i])) result.add(data[i]); }
return result;
}
// Set equality
bool intSet::operator==(const intSet &other) const {
if (size != other.size) {
return false;
    }
for (int i = 0; i < size; ++i) {
if (!other.contains(data[i])) {
return false;
        }
    }
return true;
}
// Check if s is a subset of *this
bool intSet::isSubset(const intSet &s) const {
for (int i = 0; i < s.size; ++i) {
if (!contains(s.data[i])) {
return false;
        }
    }
return true;
}
// Check if *this contains e
bool intSet::contains(int e) const {
for (int i = 0; i < size; ++i) {
if (data[i] == e) {
return true;
        }
    }
return false;
}
// Add e to this set
void intSet::add(int e) {
if (!contains(e)) {
if (size == capacity) {
int newCapacity = (capacity == 0) ? 4 : capacity * 2;
int* newData = new int[newCapacity];
for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[size++] = e;
    }
}
// Remove e from this set
void intSet::remove(int e) {
for (int i = 0; i < size; ++i) {
if (data[i] == e) {
            data[i] = data[--size];
return;
        }
    }
}
std::ostream& operator<<(std::ostream& out, const intSet& is) {
// Create a copy of the data array
int* sortedData = new int[is.size];
for (int i = 0; i < is.size; ++i) {
        sortedData[i] = is.data[i];
    }
// Sort the copied array using bubble sort
for (int i = 0; i < is.size - 1; ++i) {
for (int j = 0; j < is.size - i - 1; ++j) {
if (sortedData[j] > sortedData[j + 1]) {
// Swap sortedData[j] and sortedData[j + 1]
int temp = sortedData[j];
                sortedData[j] = sortedData[j + 1];
                sortedData[j + 1] = temp;
            }
        }
    }
// Print the sorted elements
    out << "(";
for (int i = 0; i < is.size; ++i) {
if (i > 0) {
            out << ", ";
        }
        out << sortedData[i];
    }
    out << ")";
// Delete the copied array
delete[] sortedData;
return out;
}
