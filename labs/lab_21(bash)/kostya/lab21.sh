#!/bin/sh
#DEFAULTS
d='.'	#directory
shi=0	#shift of cipher
up="ABCDEFGHIJKLMNOPQRSTUVWXYZ" #two alphabets
low="abcdefghijklmnopqrstuvwxyz"
######################

#PARAMETERS
until [ -z "$1" ]  #until all arguments are read 
do
	case "$1" in
	-a|--alphabet) #choose alphabets
        	shift
		if [ -n "$1" ]
		then
			up="$1"
			shift
			if [ -n "$1" ]
			then
				low="$1"
			else   
				printf "lab21: no choosen two alphabet strings (wrong used -a)\nusage: $0 [-a STRING STRING ] [-d FILE] [-s INTEGER ][-t] \nuse -? option for help\n"
				exit
			fi 
		else
			printf "lab21: no choosen two alphabet strings (wrong used -a)\nusage: $0 [-a STRING STRING ] [-d FILE] [-s INTEGER ][-t] \nuse -? option for help\n"
			exit
		fi
	;;
	-d|--directory)  #choose directory  
         	shift
		if [ -n "$1" ] 
		then
			d="$1"
		else
			printf "lab21: no choosen directory (wrong used -d)\nusage: $0 [-a STRING STRING ] [-d FILE] [-s INTEGER ][-t] \nuse -? option for help\n"
			exit
		fi
      ;;
     -s|--shift) # shift of encoding
      	shift
      	if [ -n "$1" ] 
		then
			shi="$1"
		else
			printf "lab21: no choosen shift (wrong used -s)\nusage: $0 [-a STRING STRING ] [-d FILE] [-s INTEGER ][-t] \nuse -? option for help\n"
			exit
		fi
      ;;	
    	-t|--tracing)  #start tracing   
          	set -x
     ;;
	-?|--help) #prints help
         	printf "NAME\n\t$0 -- Encoding all text/plain files in directory and all subdirectories with its text using Caesar algorithm\n
SYNOPSIS\n\t$0 [-a STRING STRING ] [-d FILE] [-s INTEGER ][-t] \n\t$0 [-?]\n
DESCRIPTION\n\tRewrites all text/plain files with text encoded by Caesar algorithm using shift by 1. It endcodes only A-Z and a-z symbols and do NOT touch any special symbols and digits.\n
\t-a [STRING] [STRING], --alphabet [STRING] [STRING]\tselect alphabet. You always need to choose exactly two of them. Frame them with \" and use any alone one symbol when second alphabet is not needed
\t-d [FILE], --directory [FILE]\tspecify directory to encode
\t-s [INTEGER], --shift [INTEGER]\tset shift of encoding
\t-t, --tracing\tenable tracing
\t-?, --help\tshow help (this menu) and exits\n"		
		exit
     ;;
     *) #illegal options	
        	printf "lab21: illegal option $a\nusage: $0[-a STRING STRING ] [-d FILE] [-s INTEGER ][-t] \nuse -? option for help\n"
		exit
     ;;
	esac  
  shift
done
##########################

#PROGRAM
Ucount=${#up} #count of letters in alphabets
Lcount=${#low}
twinlow=$low$low #doubled alphabets for cutting
twinup=$up$up
#setting shifts to ( 0 < x < letters count ) frames
Lshi=`echo "(($shi%$Lcount+$Lcount)%$Lcount)" | bc`
Ushi=`echo "(($shi%$Ucount+$Ucount)%$Ucount)" | bc`
temp=`mktemp tmpXXXXXXXXXXXXXXXXXXXXX`
for f in `find $d`
do #for each file in directory    
	if [ -w $f ]	#
	then 
		if [ X`file -i $f |cut -f 2 -d " " | cut -f 1 -d '/' ` = 'Xtext' ]
		then #text format
				tr $up$low ${twinup:$Ushi:$Ucount}${twinlow:$Lshi:$Lcount} < $f > $temp
				cat $temp > $f
				printf "$f encoded\n"
		fi
	fi 
done 
rm $temp
exit 0 
#EXIT SUCCESFULLY



