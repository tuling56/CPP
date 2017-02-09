/* enum.c -- uses enumerated values */
#include <stdio.h>
#include <string.h>    // for strcmp()
//#include <stdbool.h>   // C99 feature ,这部分没找到，编译器支持出现问题
//#include <Windows.h> //尝试失败
//#include <WinDef.h>  //尝试失败

enum spectrum {red, orange, yellow, green, blue, violet};
const char * colors[] = {"red", "orange", "yellow",
                         "green", "blue", "violet"};
#define LEN 30

//自己定义布尔类型
#define bool int
//注意比较typedef unsigned char BYTE;
#define true 1
#define false 0

int my_enum(void)
{
    char choice[LEN];
    enum spectrum color;
    bool color_is_found = false;

    puts("Enter a color (empty line to quit):");
    while (gets(choice) != NULL && choice[0] != '\0')
    {
        for (color = red; color <= violet; color++)
        {
            if (strcmp(choice, colors[color]) == 0)
            {
                color_is_found = true;
                break;
            }
        }
        if (color_is_found)
            switch(color)
            {
                case red    : puts("Roses are red.");
                              break;
                case orange : puts("Poppies are orange.");
                              break;
                case yellow : puts("Sunflowers are yellow.");
                              break;
                case green  : puts("Grass is green.");
                              break;
                case blue   : puts("Bluebells are blue.");
                              break;
                case violet : puts("Violets are violet.");
                              break;
            }
        else
            printf("I don't know about the color %s.\n", choice);
        color_is_found = false;
        puts("Next color, please (empty line to quit):");
    }
    puts("Goodbye!");
    
    return 0;
}
