#!/bin/bash

#PASS="abc123"

key=

accept_key () {
	echo $token > Auth.txt
	key=`echo $token | grep -i $key_word | cut -f 2 -d "="`
	echo $key > auth_key.txt
	
	if ! [ -z $1 ]
	then
		$1 $key
	fi
}

read -s -p "Password: " mypassword
echo ""
#[ "$mypassword" == "$PASS" ] && echo "Password accepted" || echo "Access denied"

key_word="Auth="
#token=`curl -d "Email=lingxiang.tang@gmail.com&Passwd=${mypassword}&service=rs2" https://www.google.com/accounts/ClientLogin`
token=`cat Auth.txt`

echo $token | grep -i $key_word > /dev/null

if [ "$?" -eq "0" ]
then
	echo "Result:"
	echo $token
	
	echo -n "Do you want to accept this key ? (y/n)"
	read ans
	[ $ans == "y" ] && echo "Accept this key and $1 storing it into database ......" && accept_key || sleep 2 && exit 0

	
else
	echo $token 
	
fi

