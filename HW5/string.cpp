#include "string.h"

String::String(const char *str)
{
    this->str = new char [strlen(str) + 1];
    strcpy(this->str,str);
}

const char* String::get_str() const{
    return this->str;
}

StringArray String::split(const char *delimiters) const{
    char *str_copy = new char[strlen(this->str) + 1];
    strcpy(str_copy,this->str);//Using copy so the original string will stay the same
    char *str_tokens = strtok(str_copy,delimiters);
    StringArray string_array;
    while(str_tokens != NULL)
    {
        string_array.add_str(str_tokens);
        str_tokens = strtok(NULL,delimiters);
    }
    delete[] str_copy;
    return string_array;
}

int String::to_integer() const{
    return atoi(this->str);
}

String::~String(){
    delete this->str;
}

GenericString &String::operator=(const char *str_in) {
    if(str_in == nullptr)
    {
        delete this->str;
        this->str = nullptr;
    }
    else
    {
        delete this->str;
        this->str = new char[strlen(str_in) + 1];
        strcpy(this->str,str_in);
    }
    return *this;
}

GenericString & String::trim(){
    int size = strlen(this->str);
    int start_index = -1;
    int end_index = -1;
    char space = ' ';
    for(int i = 0;i < size;i++) {
        if (this->str[i] != space)
        {
            start_index = i;
            break;
        }
    }
    for(int i = size - 1; i >= 0; i--)
    {
        if (this->str[i] != space)
        {
            end_index = i ;
            break;
        }
    }
    char * str_copy = new char[strlen(this->str) + 1];
    strcpy(str_copy,this->str);
    delete[] this->str;
    this->str = new char[end_index - start_index + 1];
    int str_index = 0;
    for(int i = start_index ; i < end_index + 1;i++)
    {
        this->str[str_index] = str_copy[i];
        str_index++;
    }
    this->str[str_index] = '\0';
    delete[] str_copy;
    return *this;
}

bool String::operator==(const GenericString &other) const{
    return !strcmp(this->str,other.as_string().str);
}

bool String::operator==(const char *other) const{
    return !strcmp(this->str,other);
}

String& String::as_string(){
    return *dynamic_cast<String*>(this);
}

const String& String::as_string() const{
    return *dynamic_cast<const String*>(this);
}

GenericString* make_string(const char *str){
    String* str_make = new String(str);
    return str_make;
}