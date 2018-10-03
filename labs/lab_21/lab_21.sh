#! /bin/bash

count=1
start_letter=a
tracing=0


if [ -z "$1" ]
	then
	printf "$0: illegal option $1\nusage: $0 [-a INTEGER ] [-c CHAR]... FILE... \nuse -? option for help\n"
	exit 1
else 
while [ -n "$1" ] #while all arguments will not be read
do
	case "$1" in
		-a|--amount) #check count of copies
			shift
			if [ -n "$1" ]
			then
				count=$1
				shift
			fi
		;;
		-t|--tracing) #check tracing
			shift
			tracing=1
		;;
		-c|--char) #check start letter
			shift
			if [ -n "$1" ]
			then
				start_letter=$1
				shift
			fi
		;;
		-?|--help) #check help bar
			shift
			printf "NAME
\t  $0 -- Generate copies of file.

SYNOPSIS
\t  $0 [-a INTEGER ] [-c CHAR]... FILE... 
\t  $0 [-?]

DESCRIPTION
\t  Copies file as much as indicated in parametr -a default is 1, each copy of file will have same name with postfix letter or number.
\t  -a [INTEGER] , --amount [INTEGER]\tselect number of copies. Default is 1. 
\t  -c [CHAR],     --char [CHAR]\tselect start symbol from which names of copies will be generated in lexicographical order.
\t  -t ,--tracing \tenable tracing.
\t  -?, --help\t show help (this menu) and exits\n" 
		exit 1
		;;

		*) 
			if [ ! -f "$1" ]
			then
			    printf "$0: illegal option or file doesn't exist: $1\nusage: $0 [-a INTEGER ] [-c CHAR] [-t]... FILE... \nuse -? option for help\n"
				exit 1 
		    else
		    	file=$1
		    	break	
		    fi
		;;
	esac
	

done #end of reading arguments
fi

#programm

if ![[  -z $file ]]; then
	exit 1
fi

letter=$start_letter

for (( i=0; i < count; i++ ))
do
	if [ $letter = z ]; then
		letter=1
	else
	letter=$(echo "$letter" | tr "0-9a-z" "1-9a-z") #symbol incremeant 
	fi

	length_file_name=${#file}
	pos_of_point_by_the_end=`expr index $(echo "$file"|rev) .`
	beg_file_name=${file:0:((length_file_name-pos_of_point_by_the_end))}
	end_file_name=${file:((length_file_name-pos_of_point_by_the_end))}
	final_file_name=$beg_file_name"_"$letter$end_file_name #add postfix symbol
	if [ $tracing -eq 1 ] 
		then
			echo "cp $file $final_file_name" #set -x
	fi
	cp $file $final_file_name
	
done 
echo "Copying was succesful"

exit 0

