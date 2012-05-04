#!/bin/bash
token=`cat auth_key.txt`

curl -H "Authorization: GoogleLogin auth=$token" "http://translate.google.com/researchapi/translate?sl=en&tl=zh&q=This+is+a+test."
