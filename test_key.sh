#!/bin/bash
token=`cat auth_key.txt`

# TEST ERROR
# 

if [ "$1" -eq "1" ]

else

curl -H "Authorization: GoogleLogin auth=$token" "http://translate.google.com/researchapi/translate?sl=en&tl=zh&q=This+is+a+test."
fi