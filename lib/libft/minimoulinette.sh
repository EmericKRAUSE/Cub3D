#!/usr/bin/bash

gcc -Wall -Wextra -Werror *.c
for F in files/* ; do
	echo -n "[$F]				"
	if [ "$(cat $F)" == "$(./a.out $F)" ] ; then
		echo OK
   	else
		echo KO
	fi
done
rm ./a.out
