#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <limits.h>


long long char_to_set(char input_letter)
{
    input_letter = tolower(input_letter);
    if(input_letter>'z' || input_letter<'a')
        return 0;
    return 1ll << (input_letter - 'a');
}


int main()
{
	setlocale(LC_ALL,"Russian");
    int c, lastc;
    int bool=1,flaq=0;
    long long set_of_input = 0;

    long long VOW = (1ll << ('a'-'a') | 1ll <<('e'-'a') | 1ll <<('i'-'a') | 1ll <<('o'-'a') | 1ll <<('u'-'a'));
    long long CON = ~(VOW)%134217728;

    while((c = getchar()) != EOF) {
        if(c==' ' || c=='\t' || c==',' || c=='\n')
        {   
            if(set_of_input!=0) {
                if(set_of_input & VOW) {
                    if(char_to_set(lastc) & VOW) {
                        
                        flaq = 1;
                    } 
                }
                if(set_of_input & CON) {
                    if(char_to_set(lastc) & CON) {
                        
                        flaq = 1;
                    } 
                }
            }
            set_of_input = 0;
            bool = 1;
        }
        else if(bool) {
            set_of_input = char_to_set(c);
            bool = 0;
        }
        lastc = c;
    }
    if(flaq)
    {
        printf("Есть слова, начинающиеся и заканчивающиеся гласными(согласными)\n");
    }
    else
    {
        printf("Нет слов, начинающиеся и заканчивающиеся гласными(согласными)\n");
    }

	return 0;
}
