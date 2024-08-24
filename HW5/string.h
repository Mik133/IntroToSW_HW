#ifndef STRING_H
#define STRING_H

#include "generic-string.h"
#include "string-array.h"
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::cerr;

class String : public GenericString{
private:
    char *str;
public:
    String(const char *str = "");//Constructor

    const char* get_str() const;//Getter(My function : Unused in the main())

    ~String() override;//Deconstructor

    //GenericString Functions
    StringArray split(const char *delimiters) const override;//Splitter

    int to_integer() const override;//Turn to integer

    //Specified GenericString functions
    GenericString& operator=(const char *str_in);

    GenericString & trim() override;

    bool operator==(const GenericString &other) const;

    bool operator==(const char *other) const;

    String& as_string();

    const String& as_string() const;

};


#endif