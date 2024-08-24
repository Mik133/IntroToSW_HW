#!/bin/bash

packets=$(</dev/stdin) # Reads packets into variable 

rules_file=$1 # Get name of rules file into variable

all_rules=$(<$rules_file) # Reads rules file content into variable

# Initialize common_packets variable to store common strings
common_packets="" 
# Clean all rules to we can run them
all_rules=$(echo "$all_rules" | awk '{sub(/#.*/, "", $0); print}' | awk 'NF')
# Each rule has 4 fields the packets will be tested for each rule and then filtered according to the packet that passed all 4
while IFS= read -r rule; do
	# Get rule
    rule_tested="$rule"
    # Split rule to 4 
    rule_1=$(echo "$rule_tested" | cut -d',' -f1 | tr -d ' ') 
    rule_2=$(echo "$rule_tested" | cut -d',' -f2 | tr -d ' ') 
    rule_3=$(echo "$rule_tested" | cut -d',' -f3 | tr -d ' ') 
    rule_4=$(echo "$rule_tested" | cut -d',' -f4 | tr -d ' ') 
	# Run each rule and get results
   	rule_1_result=$(echo "$packets" | ./firewall.exe "$rule_1" | sort | tr -d ' ')
	rule_2_result=$(echo "$packets" | ./firewall.exe "$rule_2" | sort | tr -d ' ')
	rule_3_result=$(echo "$packets" | ./firewall.exe "$rule_3" | sort | tr -d ' ')
	rule_4_result=$(echo "$packets" | ./firewall.exe "$rule_4" | sort | tr -d ' ')  
	# Extract packets that passed all 4
    common_tmp=$(echo -e "$rule_1_result\n$rule_2_result\n$rule_3_result\n$rule_4_result" | sort | uniq -c | grep -E "^\s*4\s+" | awk '{print $2}') 
    # Add them to the final result 
    common_packets+=" $common_tmp"            

done < <(echo "$all_rules" | awk '{sub(/#.*/, "", $0); print}' | awk 'NF')

# clean result for spaces/blank-lines and then sort them
common_packets=$(echo "$common_packets"| tr ' ' '\n' | awk 'NF' | sort)
# Print packets who passed
echo "$common_packets"
