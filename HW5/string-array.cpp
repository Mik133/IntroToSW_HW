#include "string-array.h"


StringArray::StringArray() :string_array(nullptr), size(0), current_loc(0) {
    this->string_array = new GenericString * [sizeof (GenericString)];
}

StringArray::~StringArray() {
    for(int i = 0;i < this->size;i++)
        delete this->string_array[i];

    delete this->string_array;
}

GenericString** StringArray::get_string_array() const
{
    return this->string_array;
}

void StringArray::add_str(char *str_to_add)
{
    GenericString* ge_to_add = make_string(str_to_add);
    this->string_array[this->current_loc] = ge_to_add;
    this->current_loc++;
    this->size = this->current_loc;
}

void StringArray::disp_string_array() const
{
    cout << "Size:" << this->size << endl;
    for(int i = 0 ;i < this->size;i++)
        cout << this->string_array[i]->as_string().get_str() << endl;
}

int StringArray::get_sa_size() const{
    return this->size;
}

void StringArray::string_array_trimmer() const{
    for(int i = 0;i < this->size;i++)
        this->string_array[i]->trim();

}

GenericString * StringArray::get_string_array_value(int index) const{
    if(index < 0 || index > this->size)
    {
        cerr << "Invalid index\n" << endl;
        return nullptr;
    }
    else
        return this->string_array[index];
}

