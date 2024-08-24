#include "ip.h"

#define SRC_NAME "src-ip"
#define DST_NAME "dst-ip"
#define IP_FIELDS 4
#define ACTIVE_RULE  true

GenericIp::GenericIp() {
    this->src_rules_saved.active = false;
    this->dst_rules_saved.active = false;
}

void GenericIp::add_rule(GenericString &rule){
    StringArray input_split = rule.split("=");
    int ip_num[IP_FIELDS];
    int ip_bit;
    unsigned int ip_formatted = 0;
    for(int i = 0; i < input_split.get_sa_size();i++)
    {
        if(strcmp(input_split.get_string_array_value(i)->as_string().get_str(),SRC_NAME) == 0)
        {
            StringArray src_ip_fields = input_split.get_string_array_value(i + 1)->split("./");
            src_ip_fields.string_array_trimmer();
            for(int j = 0;j < IP_FIELDS;j++) {
                ip_num[j] = src_ip_fields.get_string_array_value(j)->to_integer();
            }
            ip_bit = src_ip_fields.get_string_array_value(4)->to_integer();
            ip_formatted = ip_num[0] << 24 | ip_num[1] << 16 | ip_num[2] << 8 | ip_num[3];
            this->src_rules_saved.ip_reformatted = ip_formatted;
            this->src_rules_saved.bits = ip_bit;
            this->src_rules_saved.active = ACTIVE_RULE;
            break;
        }
        if(strcmp(input_split.get_string_array_value(i)->as_string().get_str(),DST_NAME) == 0)
        {
            StringArray dst_ip_fields = input_split.get_string_array_value(i + 1)->split("./");
            dst_ip_fields.string_array_trimmer();
            for(int j = 0;j < IP_FIELDS;j++) {
                ip_num[j] = dst_ip_fields.get_string_array_value(j)->to_integer();
            }
            ip_bit = dst_ip_fields.get_string_array_value(4)->to_integer();
            ip_formatted = ip_num[0] << 24 | ip_num[1] << 16 | ip_num[2] << 8 | ip_num[3];
            this->dst_rules_saved.ip_reformatted = ip_formatted;
            this->dst_rules_saved.bits = ip_bit;
            this->dst_rules_saved.active = ACTIVE_RULE;
            break;
        }
    }
}

void GenericIp::disp_ip_rule() const{
    bitset<sizeof (int) * 8> src_binary(this->src_rules_saved.ip_reformatted);
    cout << "ACTIVE:" << this->src_rules_saved.active << " SRC-IP formatted:" <<
    src_binary << "/" << this->src_rules_saved.bits << endl;
    bitset<sizeof (int) * 8> dst_binary(this->dst_rules_saved.ip_reformatted);
    cout << "ACTIVE:" << this->dst_rules_saved.active << " DST-IP formatted:" <<
    dst_binary << "/" << this->dst_rules_saved.bits << endl;
}

bool GenericIp::match(const GenericString &packet) const{
    StringArray packet_split = packet.split(",=");
    packet_split.string_array_trimmer();
    int input_ip[IP_FIELDS];
    unsigned int input_ip_formatted = 0;
    unsigned int rule_ip_to_compare;
    unsigned int rule_ip_filtered;
    const char *port_to_check;
    if(this->src_rules_saved.active) {
        port_to_check = SRC_NAME;
        rule_ip_to_compare = this->src_rules_saved.ip_reformatted;
    }
    else {
        port_to_check = DST_NAME;
        rule_ip_to_compare = this->dst_rules_saved.ip_reformatted;
    }
    for(int i = 0;i < packet_split.get_sa_size();i++)
    {
        if(strcmp(packet_split.get_string_array_value(i)->as_string().get_str(),port_to_check) == 0)
        {
            StringArray input_packet_fields = packet_split.get_string_array_value(i + 1)->split("./");
            input_packet_fields.string_array_trimmer();
            for(int j = 0;j < IP_FIELDS;j++){
                input_ip[j] = input_packet_fields.get_string_array_value(j)->to_integer();
            }
            input_ip_formatted = input_ip[0] << 24 | input_ip[1] << 16 | input_ip[2] << 8 | input_ip[3];
        }
    }
    rule_ip_filtered = input_ip_formatted & rule_ip_to_compare;

    if(rule_ip_filtered == rule_ip_to_compare)
        return true;
    else
        return false;
}

GenericIp::~GenericIp() {}