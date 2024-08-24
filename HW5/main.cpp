#include "string.h"
#include "ip.h"
#include "port.h"
#include "input.h"

#include <iostream>

#define IP_RULE "ip"
#define PORT_RULE "port"


int main(int argc,char* argv[]){
    //Rule parser:find out what type of rule is being input:ip or port
    GenericString *rule = make_string(argv[1]);
    StringArray rule_type = rule->split("-=.");
    rule_type.string_array_trimmer();
    const char *rule_name;
    for(int i = 0;i < rule_type.get_sa_size();i++)
    {
        if(strcmp(rule_type.get_string_array_value(i)->as_string().get_str(),IP_RULE) == 0) {
            rule_name = IP_RULE;
            break;
        }
        if(strcmp(rule_type.get_string_array_value(i)->as_string().get_str(),PORT_RULE) == 0){
            rule_name = PORT_RULE;
            break;
        }
    }
    if(strcmp(rule_name,IP_RULE) == 0)
    {
        GenericIp ip_rule_manager;
        ip_rule_manager.add_rule(*rule);
        parse_input(ip_rule_manager);
    }
    else if(strcmp(rule_name,PORT_RULE) == 0)
    {
        GenericPort port_rule_manager;
        port_rule_manager.add_rule(*rule);
        parse_input(port_rule_manager);
    }
    else{
        cerr << "Invalid input \n";
        return 1;
    }
    delete rule;
    return 0;
}