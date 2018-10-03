#! /bin/bash

ord() {
  LC_CTYPE=C printf '%d' "'$1"
}

chr() {
  [ "$1" -lt 256 ] || return 1
  printf "\\$(printf '%03o' "$1")"
}

count=1
start_symbol=a
for_type_2=1
type_of_ss=2 #1 is numeral/ 2 is letter
tracing=0


if [ -z "$1" ]
	then
	printf "$0: illegal option $1\nusage: $0 [-a INTEGER ] [-c CHAR] [-t]... FILE... \nuse -? option for help\n"
	exit 1
else 
while [ -n "$1" ] #while all arguments will not be read
do
	case "$1" in
		-a|--amount) #check count of copies
			shift
			if [ -n "$1" ]
			then
				if (echo "$1" | grep -E -q "^?[0-9]+$"); then
				    count=$1
					shift
				else
					printf "$0: illegal option or file doesn't exist: $1\nusage: $0 [-a INTEGER ] [-c CHAR] [-t]... FILE... \nuse -? option for help\n"
					exit 1 
				fi
			else
				printf "$0: illegal option or file doesn't exist: $1\nusage: $0 [-a INTEGER ] [-c CHAR] [-t]... FILE... \nuse -? option for help\n"
				exit 1 
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
				if (echo "$1" | grep -E -q "^?[0-9]+$"); then
				    start_symbol=$1
				    type_of_ss=1
				elif (echo "$1" | grep -E -q "^?[a-z]+$"); then
			    	start_symbol=$1
			    	fst=$(ord "$1")
			    	snd=$(ord "a")
			    	let for_type_2=fst-snd+1
			    	type_of_ss=2
				else 
					printf "$0: illegal option or file doesn't exist: $1\nusage: $0 [-a INTEGER ] [-c CHAR] [-t]... FILE... \nuse -? option for help\n"
					exit 1 
				fi
				shift
			else
				printf "$0: illegal option or file doesn't exist: $1\nusage: $0 [-a INTEGER ] [-c CHAR] [-t]... FILE... \nuse -? option for help\n"
				exit 1 
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
\t  -c [CHAR],     --char [CHAR]\tselect start symbol from letter of the English alphabet or numeral.
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

if [[ -z $file ]]; then
	printf "$0: illegal option or file doesn't exist: $1\nusage: $0 [-a INTEGER ] [-c CHAR] [-t]... FILE... \nuse -? option for help\n"
	exit 1
fi

letter=$start_symbol

for (( i=0; i < count; i++ ))
do
	

	length_file_name=${#file}
	pos_of_point_by_the_end=`expr index $(echo "$file"|rev) .`
	beg_file_name=${file:0:((length_file_name-pos_of_point_by_the_end))}
	end_file_name=${file:((length_file_name-pos_of_point_by_the_end))}
	final_file_name=$beg_file_name"_"$letter$end_file_name #add postfix symbol
	if [ $tracing -eq 1 ] 
		then
			set -x
	fi
	cp $file $final_file_name


	if [ $type_of_ss = 2 ]; then 

		tmp_int=$for_type_2
		tmp_tmp=1
		tmp_letter=""
		letter=""
		while [ $tmp_int -ne 0 ]
		do
			let rem=tmp_int%27
			let tmp_int=tmp_int/27
	
			fst=$(ord "a")
			if [[ rem -eq 0 ]]; then
				let for_type_2=for_type_2+1
				rem=1
			fi
			let tmp_letter=rem+fst-1
		
	    	
	    	# echo "\t this is $letter"
			tmp_letter=$(chr $tmp_letter)
			letter=$tmp_letter$letter
			# printf "$tmp_letter $for_type_2 "
			#int to char
		done
		# printf "$letter\n"
		# echo $for_type_2
		let for_type_2=for_type_2+1


	elif [[ $type_of_ss = 1 ]]; then
		let letter=letter+1
	fi
	
done 
echo "Copying was succesful"

exit 0

