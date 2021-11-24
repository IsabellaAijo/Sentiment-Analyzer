#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <cstring>

class DSString{

private:
    char * data;
    int capacity;

public:
    //Constructors and destructor
    DSString();
    DSString(int);
    DSString(const char*);
    DSString(const DSString&);
    ~DSString();

    //Overloaded Assignment Operators
    DSString& operator= (const char*);
    DSString& operator= (const DSString&);

    //Overloaded non-modifying string concat
    DSString operator+ (DSString&);     //since this does not modify a or b in a + b, then result must be in a temp string
    DSString& operator+= (const DSString&);
    DSString& operator+= (const char*);
    DSString& operator+= (const char);

    //Standard relational operators.  Feel free to add additional
    bool operator== (const char*);
    bool operator== (const DSString&);
    bool operator> (const char*) const;
    bool operator> (const DSString&) const;
    bool operator< (const char*) const;
    bool operator< (const DSString&) const;

    /**
     * Subscript operator to access a particular character of a DSString object
     * @return the character requested by reference
     */
    char& operator[] (const int);

    /**
     * Contains(char) returns the first position of the given character in the DSString
     * object. If the character is not found, it returns -1
     */
    int contains(const char);

    /**
     * getLength() returns the number (count) of characters in the string.
     **/
    int getLength();

    /**
     * The substring method:
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy
     * @return a DSString object containing the requested substring
     **/
    DSString substring(int start, int numChars);

    /**
     * the c_str function returns a null-terminated c-string
     **/
    char* c_str();

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument.
     **/
    friend std::ostream& operator<< (std::ostream& out, const DSString& arg) {
        out << arg.data;

        return out;
    };
};

#endif //DSSTRING_H