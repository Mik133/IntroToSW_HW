#ifndef PORT_H
#define PORT_H

#include "generic-field.h"
#include "generic-string.h"
#include "string-array.h"
#include "string.h"
#include <iostream>

typedef struct {
    bool active;
    int min_port;
    int max_port;
}src_rules_port;

typedef struct {
    bool active;
    int min_port;
    int max_port;
}dst_rules_port;

class GenericPort : public GenericField{
private:
    src_rules_port saved_dst_rules;
    dst_rules_port saved_src_rules;

public:
    GenericPort();

    void add_rule(GenericString &rule);

    void disp_port_rule();

    bool match(const GenericString &packet) const;

    ~GenericPort();
};

#endif