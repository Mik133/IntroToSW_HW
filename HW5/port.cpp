#include "port.h"

#define SRC_NAME "src-port"
#define DST_NAME "dst-port"
#define ACTIVE_RULE  true

GenericPort::GenericPort() {
    this->saved_src_rules.active = false;
    this->saved_dst_rules.active = false;
}

void GenericPort::add_rule(GenericString &rule){
    StringArray input_split = rule.split("=");
    input_split.string_array_trimmer();
    int min_val;
    int max_val;
    for(int i = 0;i < input_split.get_sa_size();i++)
    {
        if(strcmp(input_split.get_string_array_value(i)->as_string().get_str(),SRC_NAME) == 0) {
            StringArray src_vals = input_split.get_string_array_value(i + 1)->split("-");
            src_vals.string_array_trimmer();
            min_val = src_vals.get_string_array_value(0)->to_integer();
            max_val = src_vals.get_string_array_value(1)->to_integer();
            this->saved_src_rules.min_port = min_val;
            this->saved_src_rules.max_port = max_val;
            this->saved_src_rules.active = ACTIVE_RULE;
            break;
        }
        if(strcmp(input_split.get_string_array_value(i)->as_string().get_str(),DST_NAME) == 0) {
            StringArray dst_vals = input_split.get_string_array_value(i + 1)->split("-");
            dst_vals.string_array_trimmer();
            min_val = dst_vals.get_string_array_value(0)->to_integer();
            max_val = dst_vals.get_string_array_value(1)->to_integer();
            this->saved_dst_rules.min_port = min_val;
            this->saved_dst_rules.max_port = max_val;
            this->saved_dst_rules.active = ACTIVE_RULE;
            break;
        }
    }
}

void GenericPort::disp_port_rule(){
    cout << "Ports rules: \n";
        cout << "SRC rule:" << "ACTIVE:" << this->saved_src_rules.active  <<
        " RULE IS:"<<  this->saved_src_rules.min_port <<
        "-" << this->saved_src_rules.max_port << endl;
        cout << "DST rule:" << "ACTIVE:" << this->saved_dst_rules.active  <<
        " RULE IS:" << this->saved_dst_rules.min_port <<
        "-" << this->saved_dst_rules.max_port << endl;
}

bool GenericPort::match(const GenericString &packet) const{
    StringArray packet_split = packet.split(",=");
    packet_split.string_array_trimmer();
    int input_port;
    int min_val_allowed;
    int max_val_allowed;
    const char *port_to_check;
    if(this->saved_src_rules.active) {
        port_to_check = SRC_NAME;
        min_val_allowed = this->saved_src_rules.min_port;
        max_val_allowed = this->saved_src_rules.max_port;
    }
    else {
        port_to_check = DST_NAME;
        min_val_allowed = this->saved_dst_rules.min_port;
        max_val_allowed = this->saved_dst_rules.max_port;
    }
    for(int i = 0 ; i < packet_split.get_sa_size();i++)
    {
        if(strcmp(packet_split.get_string_array_value(i)->as_string().get_str(),port_to_check) == 0)
            input_port = packet_split.get_string_array_value(i + 1)->to_integer();
    }
    if( input_port >= min_val_allowed && input_port <= max_val_allowed)
        return true;
    else
        return false;
}

GenericPort::~GenericPort(){

}
