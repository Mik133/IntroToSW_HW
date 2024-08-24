#include "generic-field.h"
#include "generic-string.h"
#include "string-array.h"
#include "string.h"
#include <iostream>
#include <bitset>

using std::bitset;

typedef struct{
    bool active;
    unsigned int ip_reformatted;
    int bits;
}src_rules_ip;

typedef struct{
    bool active;
    unsigned int ip_reformatted;
    int bits;
}dst_rules_ip;

class GenericIp : public GenericField{
private:
    src_rules_ip src_rules_saved;
    dst_rules_ip dst_rules_saved;

public:
    GenericIp();

    void add_rule(GenericString &rule);

    void disp_ip_rule() const;


    virtual bool match(const GenericString &packet) const;


    ~GenericIp();

};