#include <graphics.h> // 该头文件是TC下的，这里是移植过来的，和graphics.lib分别放在VC的include和lib目录下
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


#define SX     50
#define SY     25
#define Length 10
#define Xnub   50
#define Ynub   40

char BoxColor=3;
char BackColor=0;
char LineColor=4;

char key;
char i,j;
long int k=0;
char String[10];

char UpKey=72;                /*按键设置*/
char ButtonKey=80;
char LeftKey=75;
char RightKey=77;

char StartX;     /*蛇头位置*/
char StartY;
char StartC;
char EndX;       /*蛇尾位置*/
char EndY;
char RandX=0;    /*随机位置*/
char RandY=0;
char RandC=0;
int CurrtX;
int CurrtY;

char MoveFlag=3; /*蛇头移动方向1左 2上 3右 4下*/

struct BoxArrays{
    char x;
    char y;
    char color;
      };                      /*存放所有蛇的位置*/

 struct BoxArrays  BoxArray[500];

int BoxNub=2;                              /* 蛇的长度 */

char FillStye[8]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
int  array[10];
char IsGameOver=1;                         /* 游戏状态 */
/*-----------------------------------------------------函数声明*/
void DrawFrames(char colors);
void FillArea(char x,char y,int colors);
void ScanKey();
void MoveBox();
void GiveFood();
void ClearArea(int x1,int y1,int x2,int y2,int colors);

/*-------------------------------------------------------------*/
void DrawFrames(char colors)
{
    setcolor(colors);
    for(i=0;i<=Xnub;i++)
    {
    line(SX+i*Length,SY,SX+i*Length,SY+Ynub*Length);
    }

    for(i=0;i<=Ynub;i++)
    {
    line(SX,SY+i*Length,SX+Xnub*Length,SY+i*Length);
    }
}
/*-------------------------------------------------------------*/
void GiveFood()
{
 while(1)
 {
 RandX=rand()%Xnub;
 RandY=rand()%Ynub;
 RandC=rand()%15+1;
    for(i=0;i<BoxNub;i++)if(RandX==BoxArray[i].x && RandY==BoxArray[i].y )j=1;
 if(!j)break;
 }
 FillArea(RandX,RandY,RandC);


 itoa(time(NULL),String,10);
 ClearArea(0,0,50,20,BLACK);
 outtextxy(5,5, String);


}
/*-------------------------------------------------------------*/

void MoveBox()
{
if(IsGameOver==1)
{
StartX=BoxArray[0].x;
StartY=BoxArray[0].y;
StartC=BoxArray[BoxNub-1].color;
EndX=BoxArray[BoxNub-1].x;
EndY=BoxArray[BoxNub-1].y;

if(MoveFlag==1 && StartX>0 )StartX=StartX-1;
else if(MoveFlag==3 && StartX<Xnub-1 )StartX=StartX+1;
else if(MoveFlag==2 && StartY>0 )StartY=StartY-1;
else if(MoveFlag==4 && StartY<Ynub-1 )StartY=StartY+1;
else IsGameOver=0;

for(i=0;i<BoxNub;i++)if(StartX==BoxArray[i].x && StartY==BoxArray[i].y)IsGameOver=0;

if(IsGameOver==1)
{
    if(StartX==RandX && StartY==RandY)
    {BoxNub++;
    StartC=RandC;
    GiveFood();
    }

    for(i=BoxNub-1;i>0;i--)
    {BoxArray[i].x=BoxArray[i-1].x;
    BoxArray[i].y=BoxArray[i-1].y;
    BoxArray[i].color=BoxArray[i-1].color;
    }

    BoxArray[0].x=StartX;
    BoxArray[0].y=StartY;
    BoxArray[0].color=StartC;
    for(i=0;i<BoxNub;i++)FillArea(BoxArray[i].x,BoxArray[i].y,BoxArray[i].color);
    FillArea(EndX,EndY,BLACK);

}
}
}
/*-------------------------------------------------------------*/
void FillArea(char x,char y,int colors)
{
 CurrtX=x*Length+SX;
 CurrtY=y*Length+SY;

 array[0]= CurrtX;
 array[1]= CurrtY;
 array[2]= CurrtX+Length;
 array[3]= CurrtY;
 array[4]= CurrtX+Length;
 array[5]= CurrtY+Length;
 array[6]= CurrtX;
 array[7]= CurrtY+Length;
 array[8]= CurrtX;
 array[9]= CurrtY;

 setfillpattern(FillStye,colors);
 fillpoly(5,array);
 setcolor(LineColor);
 rectangle(array[0],array[1],array[4],array[5]);
}
/*----------------------------------------------------------------------*/

void ScanKey()
{
 if(kbhit())
    {
    key=getch();

    if(key==LeftKey ) MoveFlag=1;
    if(key==RightKey ) MoveFlag=3;
    if(key==UpKey) MoveFlag=2;
    if(key==ButtonKey ) MoveFlag=4;

    if(key==27)IsGameOver=27;
    if(key==97)IsGameOver=1;


    }
}
/*----------------------------------------------------------------------*/
void ClearArea(int x1,int y1,int x2,int y2,int colors)
{
 array[0]= x1;
 array[1]= y1;
 array[2]= x2;
 array[3]= y1;
 array[4]= x2;
 array[5]= y2;
 array[6]= x1;
 array[7]= y2;
 array[8]= x1;
 array[9]= y1;
 setfillpattern(FillStye,colors);
 fillpoly(5,array);
}
/*----------------------------------------------------------------------*/
void tanchishe1() 
{



int driver,mode;

BoxArray[0].x=2;
BoxArray[0].y=2;
BoxArray[0].color=2;
BoxArray[1].x=1;
BoxArray[1].y=2;
BoxArray[1].color=3;
driver=DETECT;
mode=0;
initgraph(&driver,&mode,"");
DrawFrames(LineColor); 
srand(time(NULL));
for(i=0;i<BoxNub;i++)FillArea(BoxArray[i].x,BoxArray[i].y,BoxArray[i].color);
GiveFood();

getch();
    while(1)
    {
    k++;
    if(k>60000) MoveBox(),k=0;
    ScanKey();
    if(IsGameOver==27)break;

    }

restorecrtmode();
}


