#!/bin/bash


#crete a list of the urls we are about to check:

list_of_articles=$(wget -q -O- https://www.ynetnews.com/category/3082 | grep -o 'https://www.ynetnews.com/article/[0-9a-zA-Z]\+' | sort | uniq)


#for each url download the page and searc for kewords:

for url in $list_of_articles; do

	echo -n "$url"

	page=$(wget -q -O- "$url")

	netanyahu=$(grep -o "Netanyahu" <<< "$page" | wc -l)

	gantz=$(grep -o "Gantz" <<< "$page" | wc -l)

	if (( netanyahu==0 )) && (( gantz==0 )); then

		echo , -

	else

		echo , Netanyahu, "$netanyahu", Gantz, "$gantz"

	fi

done
