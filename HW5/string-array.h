#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H

#include "generic-string.h"
#include "string.h"


class StringArray{
private:
    GenericString **string_array;
    int size;
    int current_loc;

public:
    StringArray();

    ~StringArray();

    GenericString **get_string_array() const;

    void add_str(char *str_to_add);

    void disp_string_array() const;

    int get_sa_size() const;

    void string_array_trimmer() const;

    GenericString *get_string_array_value(int index) const;

};



#endif