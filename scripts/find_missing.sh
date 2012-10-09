#!/bin/bash

path=/data/corpus/wikipedia/all; 

for i in $1; 
do 
	missing_file=./${i}-missing.txt
	\rm $missing_file
	echo $i; 
	cd ${path}/${i}/pages/; 
	#	echo `pwd`; 
	find . -name "*.xml" | while read line; 
		do 
			
			file=/data/corpus/translated-wiki/$i-en/$line
			if [ ! -e "$file" ]
			then
				id=`echo "$line" | cut -f 2 -d . | cut -f 3 -d "/"`
				echo "$id"
				echo "$id" >>$missing_file
			fi
		done; 
done