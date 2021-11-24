#include "DSString.h"

/**
 * Constructors and destructor
 **/
DSString::DSString() {
    capacity = 1;
    data = new char[1];
    data[0] = '\0';
}
DSString::DSString(int len) {
    capacity = len;
    data = new char[len];
}
DSString::DSString(const char *str) {
    if(str == nullptr) {
        capacity = 1;
        data = new char[capacity];
        data[0] = '\0';
    }
    else {
        capacity = strlen(str) + 1;
        data = new char[capacity];
        strcpy(data, str);
    }

}
DSString::DSString(const DSString &str) {
    if(str.data == NULL || str.data == nullptr) {
        capacity = 1;
        data = new char[capacity];
        data[0] = '\0';
    }
    else {
        capacity = str.capacity;
        data = new char[capacity];
        strcpy(data, str.data);
    }
}
DSString::~DSString() {
    delete[] data;
}

/**
 * Overloaded Assignment Operators
 **/

DSString& DSString::operator= (const char* arg) {
    delete[] data;
    capacity = strlen(arg) + 1;
    data = new char[capacity];
    strcpy(data, arg);

    return *this;
}
DSString& DSString::operator= (const DSString& arg) {
    delete[] data;
    capacity = arg.capacity;
    data = new char[capacity];
    strcpy(data, arg.data);

    return *this;
}

/**
 * Overloaded non-modifying string concat
 **/

DSString DSString::operator+ (DSString& arg) {
    DSString temp;
    temp.data = new char[capacity + arg.capacity + 1];
    strcpy(temp.data, data);
    strcat(temp.data, arg.data);
    temp.capacity = strlen(temp.data);

    return temp;
}
DSString& DSString::operator+= (const DSString& arg) {
    capacity += arg.capacity + 1;
    strcat(data, arg.data);

    return *this;
}
DSString& DSString::operator+= (const char* c) {
    capacity+=1;
    if(this->capacity == 0) capacity += 2;
    char* newdata = new char[capacity];
    strcpy (newdata,data);
    strcat (newdata,c);
    delete data;
    data = newdata;
    data[capacity-1] = '\0';
    return *this;
}
DSString& DSString::operator+=(const char c) {
    capacity += 2;
    strcat(data, reinterpret_cast<const char *>(c));

    return *this;
}

/**
 * Standard relational operators
 **/

bool DSString::operator== (const char* arg) {
    return strcmp(data, arg) == 0;
}
bool DSString::operator== (const DSString& arg) {
    return strcmp(data, arg.data) == 0;
}
bool DSString::operator> (const char* arg) const {
    return strcmp(data, arg) > 0;
}
bool DSString::operator> (const DSString& arg) const {
    return strcmp(data, arg.data) > 0;
}
bool DSString::operator< (const char* arg) const {
    return strcmp(data, arg) < 0;
}
bool DSString::operator< (const DSString& arg) const {
    return strcmp(data, arg.data) < 0;
}

/**
 * Misc.
 **/

char& DSString::operator[] (const int pos) {
    return data[pos];
}
int DSString::contains(const char c) {
    int i = 0;
    while(data[i] != '\0') {
        if(data[i] == c) {
            return i;
        }
        ++i;
    }
    return -1;
}
int DSString::getLength() {
    return strlen(data);
}

/**
     * The substring method returns a string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     **/
DSString DSString::substring(int start, int numChars) {
    char sub[numChars + 1];
    for(int i = 0; i < numChars; ++i)
        sub[i] = data[start + i];
    return sub;
}

/**
    * the c_str function returns a null-terminated c-string holding the
    * contents of this object.
    **/
char* DSString::c_str() {
    return data;
}