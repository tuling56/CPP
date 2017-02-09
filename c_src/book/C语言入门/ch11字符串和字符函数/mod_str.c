/* mod_str.c 
 * 程程序将字符串的字符转化为大写，并计算一个字符串中的标点个数
 * 
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LIMIT 80
void ToUpper(char *);
int PunctCount(const char *);

int upper_count(void)
{
    char line[LIMIT];

    puts("Please enter a line:");
    gets(line);
    ToUpper(line);
    puts(line);
    printf("That line has %d punctuation characters.\n",
            PunctCount(line));
  
   return 0;
}

void ToUpper(char * str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
}

int PunctCount(const char * str)
{
    int ct = 0;
    while (*str)
    {
        if (ispunct(*str))
            ct++;
        str++;
    }
  
    return ct;
}
