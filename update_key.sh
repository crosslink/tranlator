#!/bin/bash

#PASS="abc123"

key=
token=
echo "parameters: $1"

accept_key () {
	echo "$token" > Auth.txt
	key=`echo "$token" | tail -n 1 | cut -f 2 -d "="`
	key=`echo $key`
	echo $key > auth_key_local.txt
	
	if ! [ -z  $1 ]
	then
		echo "using $1 storing key into database..."
		"$1" $key
	fi
}

read -s -p "Password: " mypassword
echo ""
#[ "$mypassword" == "$PASS" ] && echo "Password accepted" || echo "Access denied"

key_word="Auth="
token=`curl -d "Email=lingxiang.tang@gmail.com&Passwd=${mypassword}&service=rs2" https://www.google.com/accounts/ClientLogin`
#token=`cat Auth.txt`

echo $token | grep -i $key_word > /dev/null

if [ "$?" -eq "0" ]
then
	echo "Result:"
	echo ""
	echo "$token"
	echo ""
	echo -n "Do you want to accept this key ? (y/n)"
	read ans
	[ $ans == "y" ] && echo "Accept this key ......" && accept_key $1 || sleep 2 && exit 0

	
else
	echo $token 
	
fi

