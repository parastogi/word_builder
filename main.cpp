#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;                        // variables required
int co_eff[4],k,n=3;
float x,y,u,blend,rx,ry,rxb,ryb,rxh,ryh,rxe,rye,rxc,ryc,rxo,ryo,rxp,ryp,rxa,rya,rxd,ryd;        // for position control of eacb alphabet
int flag=0,next=0,ex=0,b=0,h=0,e=0,c=0,o=0,p=0,a=0,d=0,reset=0,counter1=0,counter2=0;                          // for storing guessed word
char alpha,select,word[6]={' ',' ',' ',' ',' ','\0'};
char color[][2]={{"B"},{"G"},{"R"}};
char scale[][6]={{"0.5x"},{"1x"},{"1.5x"}};
float action=0.0;
char col;
float co[3]={1.0,0.0,0.0};
                                                                                // ques-ans
int r=rand()%10;
char ques[10][256]={{"a place of residence; a house or home ?"},
                    {"created or done for a particular purpose as necessary ?"},
                    {"a kind of clay used as a building material ?"},
                    {"a pebbly or sandy shore, especially by the sea between high- and low-water marks ?"},
                    {"low in price ?"},
                    {"a particular period of time in history or a person's life ?"},
                    {"cook (an egg) without its shell in or over boiling water ?"},
                    {"a round stone fruit with juicy yellow flesh and downy pinkish-yellow skin ?"},
                    {"(past tense of)move at a particular rate or speed ?"},
                    {"(past tense of)want something to happen or be the case ?"}};

char ans[10][10]={{"abode"},{"adhoc"},{"adobe"},{"beach"},{"cheap"},{"epoch"},{"poach"},{"peach"},{"paced"},{"hoped"}};

void _reset(){
    ex=0;                                                                                     // reset function all value to initial values
    x=0;y=0;u=0;blend=0;rx=0;ry=0;rxb=0;ryb=0;rxh=0;ryh=0;rxe=0;rye=0;rxc=0;ryc=0;rxo=0;ryo=0;rxp=0;ryp=0;rxa=0;rya=0;ryd=0;rxd=0;
    b=0;h=0;e=0;c=0;o=0;p=0;a=0;d=0;
    alpha=' ';
    select=' ';
    word[0]={' '};word[1]={' '};word[2]={' '};word[3]={' '};word[4]={' '};
    reset=0;
    counter1=0;
    counter2=0;
    action=0.0;
    r=rand()%10;
}

void text(char str[],int x,int y){                                                      // to print the text on screen by BITMAP Character
    glRasterPos2f(x,y);
    for(int i=0;i<strlen(str);i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    }
    glutSwapBuffers();
}
                                                                        // bernstein eqn.
void bezierCoefficients(int n,int *c)                                     // to calculate co-eff. for the equation to find the curve points
{
	int k,i;
	for(k=0;k<=n;k++)
	{
		co_eff[k]=1;
		for(i=n;i>=k+1;i--)
		co_eff[k]*=i;
		for(i=n-k;i>=2;i--)
			co_eff[k]/=i;
	}
}
void curve(int b[4][2]){                                                 // to plot the bezier curve by calculatiing curve points
    for(u=0;u<1.0;u+=0.01)
	{
        x=0;y=0;
		for(k=0;k<4;k++)
		{
			blend=co_eff[k]*pow(u,k)*pow(1-u,n-k);
			x+=b[k][0]*blend;
			y+=b[k][1]*blend;
		}
		glVertex2f(x,y);
	}
}
void line(float x,float y,float x1,float y1){                   // function to plot lines for alphabets
	glVertex2f(x1,y1);
	glVertex2f(x,y);
}

void redrawb(int rx,int ry,float co[]){
    int b1[4][2]={{30+rx,500-ry},{90+rx,500-ry},{90+rx,560-ry},{35 +rx,560-ry}};
    int b2[4][2]= {{35+rx,560-ry},{90+rx,560-ry},{90+rx,620-ry},{30+rx,620-ry}};
    int b3[4][2]= {{25+rx,510-ry},{71+rx,500-ry},{71+rx,560-ry},{25+rx,550-ry}};
    int b4[4][2]={{25+rx,570-ry},{71+rx,560-ry},{71+rx,620-ry},{25+rx,610-ry}};
    glColor3f(co[0],co[1],co[2]);
    glBegin(GL_POLYGON);
    line(10+rx,500-ry,10+rx,620-ry);
    line(10+rx,620-ry,30+rx,620-ry);
    curve(b2);
    curve(b1);                                                                // calling function to plot the bezier curve annd lines
    line(10+rx,500-ry,30+rx,500-ry);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    glBegin(GL_POLYGON);
    line(25+rx,570-ry,25+rx,610-ry);
    curve(b4);
    glEnd();
    glFlush();
    glBegin(GL_POLYGON);
    line(25+rx,510-ry,25+rx,550-ry);
    curve(b3);
    glEnd();
    glFlush();
    glColor3f(co[0],co[1],co[2]);
}
                                                                                    //alphabet O
void redrawo(int rx,int ry,float co[]){
    int o1[4][2]={{390+rx,565-ry},{390+rx,480-ry},{470+rx,480-ry},{470+rx,565-ry}};
    int o2[4][2]={{470+rx,565-ry},{470+rx,650-ry},{390+rx,650-ry},{390+rx,565-ry}};
    int o3[4][2]={{455+rx,560-ry},{455+rx,505-ry},{405+rx,505-ry},{405+rx,560-ry}};
    int o4[4][2]={{455+rx,560-ry},{455+rx,625-ry},{405+rx,625-ry},{405+rx,560-ry}};
    glColor3f(co[0],co[1],co[2]);
    glBegin(GL_POLYGON);
    curve(o1);
    curve(o2);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    glBegin(GL_POLYGON);
    curve(o4);
    curve(o3);
    glEnd();
    glFlush();
    glColor3f(co[0],co[1],co[2]);
}
                                                                                    //alphabet H
void redrawh(int rx,int ry,float co[]){
    glColor3f(co[0],co[1],co[2]);
    glBegin(GL_POLYGON);
    glVertex2f(100.0+rx,500.0-ry);
    glVertex2f(115.0+rx,500.0-ry);
    glVertex2f(115.0+rx,552.5-ry);
    glVertex2f(165.0+rx,552.5-ry);
    glVertex2f(165.0+rx,500.0-ry);
    glVertex2f(180.0+rx,500.0-ry);
    glVertex2f(180.0+rx,620.0-ry);
    glVertex2f(165.0+rx,620.0-ry);
    glVertex2f(165.0+rx,567.5-ry);
    glVertex2f(115.0+rx,567.5-ry);
    glVertex2f(115.0+rx,620.0-ry);
    glVertex2f(100.0+rx,620.0-ry);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    glBegin(GL_POLYGON);
    glVertex2f(115.0+rx,500.0-ry);
    glVertex2f(115.0+rx,552.5-ry);
    glVertex2f(165.0+rx,552.5-ry);
    glVertex2f(165.0+rx,500.0-ry);
    glEnd();
    glFlush();
    glBegin(GL_POLYGON);
    glVertex2f(165.0+rx,620.0-ry);
    glVertex2f(165.0+rx,567.5-ry);
    glVertex2f(115.0+rx,567.5-ry);
    glVertex2f(115.0+rx,620.0-ry);
    glEnd();
    glFlush();
    glColor3f(co[0],co[1],co[2]);

}
                                                                                    //alphabet C
void redrawc(int rx,int ry,float co[]){
    int c1[4][2]={{370+rx,620-ry},{265+rx,660-ry},{250+rx,465-ry},{370+rx,510-ry}};
    int c2[4][2]={{370+rx,525-ry},{275+rx,490-ry},{290+rx,635-ry},{370+rx,605-ry}};
    glColor3f(co[0],co[1],co[2]);
    glBegin(GL_POLYGON);
    curve(c1);
    line(370+rx,510-ry,370+rx,525-ry);
    line(370+rx,605-ry,370+rx,620-ry);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    glBegin(GL_POLYGON);
    curve(c2);
    glEnd();
    glFlush();
    glColor3f(co[0],co[1],co[2]);
}
                                                                                    //alphabet P
void redrawp(int rx,int ry,float co[]){
    int p1[4][2]={{90*5+50+rx,560-ry},{90*5+115+rx,560-ry},{90*5+115+rx,630-ry},{90*5+50+rx,630-ry}};
    int p2[4][2]={{90*5+50+rx,575-ry},{90*5+100+rx,575-ry},{90*5+100+rx,615-ry},{90*5+50+rx,615-ry}};
    glColor3f(co[0],co[1],co[2]);
    glBegin(GL_POLYGON);
    curve(p1);
    line(90*5+50+rx,630-ry,90*5+35+rx,630-ry);
    line(90*5+35+rx,630-ry,90*5+35+rx,500-ry);
    line(90*5+35+rx,500-ry,90*5+50+rx,500-ry);
    line(90*5+50+rx,500-ry,90*5+50+rx,560-ry);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    glBegin(GL_POLYGON);
    curve(p2);
    line(90*5+50+rx,615-ry,90*5+50+rx,575-ry);
    glEnd();
    glFlush();
    glColor3f(co[0],co[1],co[2]);
}
                                                                                    //alphabet E
void redrawe(int rx,int ry,float co[]){
    glColor3f(co[0],co[1],co[2]);
    glBegin(GL_POLYGON);
    glVertex2f(200.0+rx,500.0-ry);
    glVertex2f(280.0+rx,500.0-ry);
    glVertex2f(280.0+rx,515.0-ry);
    glVertex2f(215.0+rx,515.0-ry);
    glVertex2f(215.0+rx,552.5-ry);
    glVertex2f(250.0+rx,552.5-ry);
    glVertex2f(250.0+rx,567.5-ry);
    glVertex2f(215.0+rx,567.5-ry);
    glVertex2f(215.0+rx,605.0-ry);
    glVertex2f(280.0+rx,605.0-ry);
    glVertex2f(280.0+rx,620.0-ry);
    glVertex2f(200.0+rx,620.0-ry);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    glBegin(GL_POLYGON);
    glVertex2f(280.0+rx,515.0-ry);
    glVertex2f(215.0+rx,515.0-ry);
    glVertex2f(215.0+rx,552.5-ry);
    glVertex2f(250.0+rx,552.5-ry);
    glEnd();
    glFlush();
    glBegin(GL_POLYGON);
    glVertex2f(255.0+rx,567.5-ry);
    glVertex2f(215.0+rx,567.5-ry);
    glVertex2f(215.0+rx,605.0-ry);
    glVertex2f(280.0+rx,605.0-ry);
    glEnd();
    glFlush();
    glColor3f(co[0],co[1],co[2]);
}
                                                                                    //alphabet A
void redrawa(int rx,int ry,float co[]){
    glColor3f(co[0],co[1],co[2]);
    glBegin(GL_POLYGON);
    glVertex2f(560.0+rx,500.0-ry);
    glVertex2f(575.0+rx,500.0-ry);
    glVertex2f(587+rx,550.0-ry);
    glVertex2f(613+rx,550.0-ry);
    glVertex2f(625.0+rx,500.0-ry);
    glVertex2f(640.0+rx,500.0-ry);
    glVertex2f(610.0+rx,630.0-ry);
    glVertex2f(590.0+rx,630.0-ry);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    glBegin(GL_POLYGON);
    glVertex2f(590.0+rx,563.0-ry);
    glVertex2f(610.0+rx,563.0-ry);
    glVertex2f(600+rx,615.0-ry);
    glEnd();
    glFlush();
    glBegin(GL_POLYGON);
    glVertex2f(575.0+rx,500.0-ry);
    glVertex2f(587+rx,550.0-ry);
    glVertex2f(613+rx,550.0-ry);
    glVertex2f(625.0+rx,500.0-ry);
    glEnd();
    glFlush();
    glColor3f(co[0],co[1],co[2]);
}

void redrawd(int rx,int ry,float co[]){
    int d1[4][2]={{670+rx,500-ry},{745+rx,500-ry},{745+rx,630-ry},{670+rx,630-ry}};
    int d2[4][2]= {{670+rx,515-ry},{725+rx,515-ry},{725+rx,615-ry},{670+rx,615-ry}};
    glColor3f(co[0],co[1],co[2]);
    glBegin(GL_POLYGON);
    line(655+rx,500-ry,655+rx,630-ry);
    line(655+rx,630-ry,670+rx,630-ry);
    curve(d1);
    line(670+rx,500-ry,655+rx,500-ry);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    glBegin(GL_POLYGON);
    curve(d2);
    line(670+rx,515-ry,670+rx,615-ry);
    glEnd();
    glFlush();
     glColor3f(1.0,0.0,0.0);
}

void scalefunc(float s,float x,float y){
    glPushMatrix();
    glTranslatef(-800,0,0.0);
    glScalef(s,s,0.0);
    glTranslatef(x,y,0.0);
}

void display()
{
    bezierCoefficients(n,co_eff);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glLineWidth(2.0);
                                                   // for displaying list of alphabets at top
    if(rxb!=0){
        co[0]=0.0;co[1]=0.67;co[2]=0.0;
        redrawb(0,0,co);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        co[0]=1.0;co[1]=0.0;co[2]=0.0;
        redrawb(0,0,co);
    }
    if(rxa!=0){
        co[0]=0.0;co[1]=0.67;co[2]=0.0;
        redrawa(0,0,co);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        co[0]=1.0;co[1]=0.0;co[2]=0.0;
        redrawa(0,0,co);
    }
    if(rxh!=0){
        co[0]=0.0;co[1]=0.67;co[2]=0.0;
        redrawh(0,0,co);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        co[0]=1.0;co[1]=0.0;co[2]=0.0;
        redrawh(0,0,co);
    }
    if(rxe!=0){
        co[0]=0.0;co[1]=0.67;co[2]=0.0;
        redrawe(0,0,co);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        co[0]=1.0;co[1]=0.0;co[2]=0.0;
        redrawe(0,0,co);
    }
    if(rxc!=0){
        co[0]=0.0;co[1]=0.67;co[2]=0.0;
        redrawc(0,0,co);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        co[0]=1.0;co[1]=0.0;co[2]=0.0;
        redrawc(0,0,co);
    }
    if(rxo!=0){
        co[0]=0.0;co[1]=0.67;co[2]=0.0;
        redrawo(0,0,co);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        co[0]=1.0;co[1]=0.0;co[2]=0.0;
        redrawo(0,0,co);
    }
    if(rxp!=0){
        co[0]=0.0;co[1]=0.67;co[2]=0.0;
        redrawp(0,0,co);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        co[0]=1.0;co[1]=0.0;co[2]=0.0;
        redrawp(0,0,co);
    }
    if(rxd!=0){
        co[0]=0.0;co[1]=0.67;co[2]=0.0;
        redrawd(0,0,co);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        co[0]=1.0;co[1]=0.0;co[2]=0.0;
        redrawd(0,0,co);
    }

    co[0]=1.0;co[1]=0.0;co[2]=0.0;
    redrawb(rxb,ryb,co);                             // for displaying alphabets in GRID
    redrawh(rxh,ryh,co);
    redrawe(rxe,rye,co);
    redrawc(rxc,ryc,co);
    redrawo(rxo,ryo,co);
    redrawp(rxp,ryp,co);
    redrawa(rxa,rya,co);
    redrawd(rxd,ryd,co);
    switch(select){                                  // for displaying alphabet in BOX for resixe and color
        case 'b':if(action==0.5){
                    scalefunc(0.5,2650.0,190.0);
                }
                else if(action==1.5){
                    scalefunc(1.5,180.0,-80.0);
                }
                if(col=='G'){
                    co[0]=0.0;co[1]=0.67;co[2]=0.0;
                }
                else if(col=='B'){
                    co[0]=0.0;co[1]=0.0;co[2]=1.0;
                }
                redrawb(rx,ry,co);
                glPopMatrix();
                break;
        case 'h':if(action==0.5){
                    scalefunc(0.5,2650.0,190.0);
                }
                else if(action==1.5){
                    scalefunc(1.5,180.0,-80.0);
                }
                if(col=='G'){
                    co[0]=0.0;co[1]=0.67;co[2]=0.0;
                }
                else if(col=='B'){
                    co[0]=0.0;co[1]=0.0;co[2]=1.0;
                }
                redrawh(rx,ry,co);
                glPopMatrix();
                break;
        case 'e':if(action==0.5){
                    scalefunc(0.5,2650.0,190.0);
                }
                else if(action==1.5){
                    scalefunc(1.5,180.0,-80.0);
                }
                if(col=='G'){
                    co[0]=0.0;co[1]=0.67;co[2]=0.0;
                }
                else if(col=='B'){
                    co[0]=0.0;co[1]=0.0;co[2]=1.0;
                }
                redrawe(rx,ry,co);
                glPopMatrix();
                break;
        case 'c':if(action==0.5){
                    scalefunc(0.5,2650.0,190.0);
                }
                else if(action==1.5){
                    scalefunc(1.5,180.0,-80.0);
                }
                if(col=='G'){
                    co[0]=0.0;co[1]=0.67;co[2]=0.0;
                }
                else if(col=='B'){
                    co[0]=0.0;co[1]=0.0;co[2]=1.0;
                }
                redrawc(rx,ry,co);
                glPopMatrix();
                break;
        case 'o':if(action==0.5){
                    scalefunc(0.5,2650.0,190.0);
                }
                else if(action==1.5){
                    scalefunc(1.5,180.0,-80.0);
                }
                if(col=='G'){
                    co[0]=0.0;co[1]=0.67;co[2]=0.0;
                }
                else if(col=='B'){
                    co[0]=0.0;co[1]=0.0;co[2]=1.0;
                }
                redrawo(rx,ry,co);
                glPopMatrix();
                break;
        case 'p':if(action==0.5){
                    scalefunc(0.5,2650.0,190.0);
                }
                else if(action==1.5){
                    scalefunc(1.5,180.0,-80.0);
                }
                if(col=='G'){
                    co[0]=0.0;co[1]=0.67;co[2]=0.0;
                }
                else if(col=='B'){
                    co[0]=0.0;co[1]=0.0;co[2]=1.0;
                }
                redrawp(rx,ry,co);
                glPopMatrix();
                break;
        case 'a':if(action==0.5){
                    scalefunc(0.5,2650.0,190.0);
                }
                else if(action==1.5){
                    scalefunc(1.5,180.0,-80.0);
                }
                if(col=='G'){
                    co[0]=0.0;co[1]=0.67;co[2]=0.0;
                }
                else if(col=='B'){
                    co[0]=0.0;co[1]=0.0;co[2]=1.0;
                }
                redrawa(rx,ry,co);
                glPopMatrix();
                break;
        case 'd':if(action==0.5){
                    scalefunc(0.5,2650.0,190.0);
                }
                else if(action==1.5){
                    scalefunc(1.5,180.0,-80.0);
                }
                if(col=='G'){
                    co[0]=0.0;co[1]=0.67;co[2]=0.0;
                }
                else if(col=='B'){
                    co[0]=0.0;co[1]=0.0;co[2]=1.0;
                }
                redrawd(rx,ry,co);
                glPopMatrix();
                break;
    }
// Buttons-
    glColor3f(0.0,0.2,0.4);                           // for SCALE button
    glBegin(GL_POLYGON);
    glVertex2f(1195.0,515.0);
    glVertex2f(1195.0,540.0);
    glVertex2f(1095.0,540.0);
    glVertex2f(1095.0,515.0);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    text("SCALE",1105,520);

    if(counter2!=0){
        for(int i=60;i>=0;i-=30){
            glBegin(GL_POLYGON);
            glColor3f(0.0,0.2,0.4);
            glVertex2f(1300.0,425.0+i);
            glVertex2f(1300.0,450.0+i);
            glVertex2f(1200.0,450.0+i);
            glVertex2f(1200.0,425.0+i);
            glEnd();
            glFlush();
            glColor3f(1.0,0.98,0.50);
            text(color[i/30],1245,430+i);
        }
    }

    glColor3f(0.0,0.2,0.4);                           // for SCALE button
    glBegin(GL_POLYGON);
    glVertex2f(1300.0,515.0);
    glVertex2f(1300.0,540.0);
    glVertex2f(1200.0,540.0);
    glVertex2f(1200.0,515.0);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    text("COLOR",1215,520);

    if(counter1!=0){                                            // for SCALE menu
        for(int i=60;i>=0;i-=30){
            glColor3f(0.0,0.2,0.4);
            glBegin(GL_POLYGON);
            glVertex2f(1195.0,425.0+i);
            glVertex2f(1195.0,450.0+i);
            glVertex2f(1095.0,450.0+i);
            glVertex2f(1095.0,425.0+i);
            glEnd();
            glFlush();
            glColor3f(1.0,0.98,0.50);
            text(scale[i/30],1130,430+i);
        }
    }

    glColor3f(0.0,0.2,0.4);
    glBegin(GL_POLYGON);
    glVertex2f(1300.0,545.0);
    glVertex2f(1300.0,570.0);
    glVertex2f(1095.0,570.0);
    glVertex2f(1095.0,545.0);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    text("RESET",1155,550);
    glColor3f(0.0,0.2,0.4);
    glBegin(GL_POLYGON);
    glVertex2f(1300.0,575.0);
    glVertex2f(1300.0,600.0);
    glVertex2f(1095.0,600.0);
    glVertex2f(1095.0,575.0);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    text("EXIT",1165,580);
    glColor3f(1.0,0.0,0.0);


//grid
    glColor3f(0.0,0.2,0.4);
    for(int i=0;i<=600;i+=150){
    glBegin(GL_LINE_LOOP);
    glVertex2f(100.0+i,200.0);
    glVertex2f(250.0+i,200.0);
    glVertex2f(250.0+i,400.0);
    glVertex2f(100.0+i,400.0);
    glEnd();
    glFlush();
    }
// box
    glBegin(GL_LINE_LOOP);
    glVertex2f(880.0,50.0);
    glVertex2f(1250.0,50.0);
    glVertex2f(1250.0,400.0);
    glVertex2f(880.0,400.0);
    glEnd();
    glFlush();
    glColor3f(1.0,0.0,0.0);
//------------------
    if(word[0]==' '||word[1]==' '||word[2]==' '||word[3]==' '||word[4]==' ')
    {
        char tem[]="WRITE A 5 LETTER WORD FOR:";
        text(tem,100,130);
        text(ques[r],100,100);
    }
    else{
        char str[]="YOUR GUESSED WORD IS:";
        strcat(str,word);
        text(str,100,130);
        if(strcmp(word,ans[r])==0)
            text("CORRECT",150,100);
        else
            text("INCORRECT",150,100);
    }
}
void text1(char str[],int x,int y)
{

    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(6.0);

    glTranslatef(x,y,0);
    glScalef(1, 1, 1);
    for(int lo=0;lo<strlen(str);lo++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN,str[lo]);
    }
    glutSwapBuffers();
    glPopMatrix();

}

void display1(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    text1("WORDII",500,600);
    text("1. Drag and Drop a letter on the grid.",100,450);
    text("2. Make a word of five letters to satisfy the meaning of the question provided below.",100,410);
    text("3. If correct word formed, CORRECT will be displayed.",100,370);
    text("4. If incorrect word formed, INCORRECT will be displayed.",100,330);
    text("5. Features are provided to scale and change the color of letters.",100,290);
    text("6. NOTE : Each word contain DISTINCT letters.",100,250);
    glEnd();
    glFlush();
    glColor3f(0.0,0.2,0.4);
    glBegin(GL_POLYGON);
    glVertex2f(600.0,200.0);
    glVertex2f(800.0,200.0);
    glVertex2f(800.0,250.0);
    glVertex2f(600.0,250.0);
    glEnd();
    glFlush();
    glColor3f(1.0,0.98,0.50);
    text("START",660,215);
}
void myinit()
{
    glClearColor(1.0,0.98,0.50,0.5);
    glColor3f(1.0,0.0,0.0);
	glPointSize(2.0);
	gluOrtho2D(0.0,1366.0,0.0,738.0);
}
void mousebutton(int button, int state,int x,int y)
{
if(flag!=0)
{
    int ny=738-y;
    if(button == GLUT_LEFT_BUTTON &&state==GLUT_DOWN)
    {
        if(x>1095&&x<1300&&ny>575&&ny<600)
            ex=1;
        if(counter1==1&&x>1095&&x<1195&&ny>425&&ny<450){
            action=0.5;
        }
        else if(counter1==1&&x>1095&&x<1195&&ny>455&&ny<480){
            action=1.0;
        }
        else if(counter1==1&&x>1095&&x<1195&&ny>485&&ny<510){
            action=1.5;
        }
        if(counter2==1&&x>1200&&x<1300&&ny>425&&ny<450){
            col='B';
        }
        else if(counter2==1&&x>1200&&x<1300&&ny>455&&ny<480){
            col='G';
        }
        else if(counter2==1&&x>1200&&x<1300&&ny>485&&ny<510){
            col='R';
        }
        if(x>1095&&x<1195&&ny<540&&ny>515){
            counter1=1;
        }
        if(x>1200&&x<1300&&ny<540&&ny>515){
            counter2=1;
        }
        if(ny>545&&x>1095&&x<1300&&ny<570){
            reset=1;
        }
        else if(x>10&&x<90&&ny>500&&ny<620){
            alpha='b';
        }
        else if(x>100&&x<180&&ny>500&&ny<620){
            alpha='h';
        }
        else if(x>390&&x<470&&ny>500&&ny<620){
            alpha='o';
        }
        else if(x>265&&x<370&&ny>465&&ny<660){
            alpha='c';
        }
        else if(x>485&&x<565&&ny>500&&ny<620){
            alpha='p';
        }
        else if(x>200&&x<280&&ny>500&&ny<620){
            alpha='e';
        }
        else if(x>560&&x<640&&ny>500&&ny<630){
            alpha='a';
        }
        else if(x>670&&x<745&&ny>500&&ny<630){
            alpha='d';
        }
    }
    else if(button == GLUT_LEFT_BUTTON &&state==GLUT_UP)
    {
        if(ex==1&&x>1095&&x<1300&&ny>575&&ny<600)
            exit(0);
        else
            ex=0;
        if(action==0.5&&x>1095&&x<1195&&ny>425&&ny<450){
            action=0.5;
        }
        else if(action==1.0&&x>1095&&x<1195&&ny>455&&ny<480){
            action=1.0;
        }
        else if(action==1.5&&x>1095&&x<1195&&ny>485&&ny<510){
            action=1.5;
        }
        if(col=='B'&&x>1200&&x<1300&&ny>425&&ny<450){
            col='B';
        }
        else if(col=='G'&&x>1200&&x<1300&&ny>455&&ny<480){
            col='G';
        }
        else if(col=='R'&&x>1200&&x<1300&&ny>485&&ny<510){
            col='R';
        }
        if(counter1==1&&x>1095&&x<1195&&ny<540&&ny>515)
            counter1=1;
        else
            counter1=0;

        if(counter2==1&&x>1200&&x<1300&&ny<540&&ny>515)
            counter2=1;
        else
            counter2=0;

        if(ny>540&&x>1095&&x<1300&&ny<575&&reset==1){
            _reset();
        }
        else{
            if(alpha=='b'){alpha=' ';
             if(b==0&&x>100&&x<250&&ny>200&&ny<400&&word[0]==' '){rxb=130;ryb=260;b++;word[0]='b';}
             else if(b==0&&x>250&&x<400&&ny>200&&ny<400&&word[1]==' '){rxb=280;ryb=260;b++;word[1]='b';}
             else if(b==0&&x>400&&x<550&&ny>200&&ny<400&&word[2]==' '){rxb=430;ryb=260;b++;word[2]='b';}
             else if(b==0&&x>550&&x<700&&ny>200&&ny<400&&word[3]==' '){rxb=580;ryb=260;b++;word[3]='b';}
             else if(b==0&&x>700&&x<850&&ny>200&&ny<400&&word[4]==' '){rxb=730;ryb=260;b++;word[4]='b';}
             else if(x>880&&x<1250&&ny>50&&ny<400){rx=1025;ry=340;select='b';}
            }
            else if(alpha=='h'){alpha=' ';
             if(h==0&&x>100&&x<250&&ny>200&&ny<400&&word[0]==' '){rxh=30;ryh=260;h++;word[0]='h';}
             else if(h==0&&x>250&&x<400&&ny>200&&ny<400&&word[1]==' '){rxh=180;ryh=260;h++;word[1]='h';}
             else if(h==0&&x>400&&x<550&&ny>200&&ny<400&&word[2]==' '){rxh=330;ryh=260;h++;word[2]='h';}
             else if(h==0&&x>550&&x<700&&ny>200&&ny<400&&word[3]==' '){rxh=480;ryh=260;h++;word[3]='h';}
             else if(h==0&&x>700&&x<850&&ny>200&&ny<400&&word[4]==' '){rxh=630;ryh=260;h++;word[4]='h';}
             else if(x>880&&x<1250&&ny>50&&ny<400){rx=925;ry=340;select='h';}
            }
            else if(alpha=='o'){alpha=' ';
             if(o==0&&x>100&&x<250&&ny>200&&ny<400&&word[0]==' '){rxo=-260;ryo=260;o++;word[0]='o';}
             else if(o==0&&x>250&&x<400&&ny>200&&ny<400&&word[1]==' '){rxo=-110;ryo=260;o++;word[1]='o';}
             else if(o==0&&x>400&&x<550&&ny>200&&ny<400&&word[2]==' '){rxo=40;ryo=260;o++;word[2]='o';}
             else if(o==0&&x>550&&x<700&&ny>200&&ny<400&&word[3]==' '){rxo=190;ryo=260;o++;word[3]='o';}
             else if(o==0&&x>700&&x<850&&ny>200&&ny<400&&word[4]==' '){rxo=340;ryo=260;o++;word[4]='o';}
             else if(x>880&&x<1250&&ny>50&&ny<400){rx=635;ry=340;select='o';}
            }
            else if(alpha=='c'){alpha=' ';
             if(c==0&&x>100&&x<250&&ny>200&&ny<400&&word[0]==' '){rxc=-150;ryc=260;c++;word[0]='c';}
             else if(c==0&&x>250&&x<400&&ny>200&&ny<400&&word[1]==' '){rxc=1;ryc=260;c++;word[1]='c';}
             else if(c==0&&x>400&&x<550&&ny>200&&ny<400&&word[2]==' '){rxc=150;ryc=260;c++;word[2]='c';}
             else if(c==0&&x>550&&x<700&&ny>200&&ny<400&&word[3]==' '){rxc=300;ryc=260;c++;word[3]='c';}
             else if(c==0&&x>700&&x<850&&ny>200&&ny<400&&word[4]==' '){rxc=450;ryc=260;c++;word[4]='c';}
             else if(x>880&&x<1250&&ny>50&&ny<400){rx=745;ry=340;select='c';}
            }
            else if(alpha=='p'){alpha=' ';
             if(p==0&&x>100&&x<250&&ny>200&&ny<400&&word[0]==' '){rxp=-330;ryp=260;p++;word[0]='p';}
             else if(p==0&&x>250&&x<400&&ny>200&&ny<400&&word[1]==' '){rxp=-180;ryp=260;p++;word[1]='p';}
             else if(p==0&&x>400&&x<550&&ny>200&&ny<400&&word[2]==' '){rxp=-30;ryp=260;p++;word[2]='p';}
             else if(p==0&&x>550&&x<700&&ny>200&&ny<400&&word[3]==' '){rxp=120;ryp=260;p++;word[3]='p';}
             else if(p==0&&x>700&&x<850&&ny>200&&ny<400&&word[4]==' '){rxp=270;ryp=260;p++;word[4]='p';}
             else if(x>880&&x<1250&&ny>50&&ny<400){rx=565;ry=340;select='p';}
            }
            else if(alpha=='e'){alpha=' ';
             if(e==0&&x>100&&x<250&&ny>200&&ny<400&&word[0]==' '){rxe=-70;rye=260;e++;word[0]='e';}
             else if(e==0&&x>250&&x<400&&ny>200&&ny<400&&word[1]==' '){rxe=80;rye=260;e++;word[1]='e';}
             else if(e==0&&x>400&&x<550&&ny>200&&ny<400&&word[2]==' '){rxe=230;rye=260;e++;word[2]='e';}
             else if(e==0&&x>550&&x<700&&ny>200&&ny<400&&word[3]==' '){rxe=380;rye=260;e++;word[3]='e';}
             else if(e==0&&x>700&&x<850&&ny>200&&ny<400&&word[4]==' '){rxe=530;rye=260;e++;word[4]='e';}
             else if(x>880&&x<1250&&ny>50&&ny<400){rx=825;ry=340;select='e';}
            }
            else if(alpha=='a'){alpha=' ';
             if(a==0&&x>100&&x<250&&ny>200&&ny<400&&word[0]==' '){rxa=-430;rya=260;a++;word[0]='a';}
             else if(a==0&&x>250&&x<400&&ny>200&&ny<400&&word[1]==' '){rxa=-280;rya=260;a++;word[1]='a';}
             else if(a==0&&x>400&&x<550&&ny>200&&ny<400&&word[2]==' '){rxa=-130;rya=260;a++;word[2]='a';}
             else if(a==0&&x>550&&x<700&&ny>200&&ny<400&&word[3]==' '){rxa=20;rya=260;a++;word[3]='a';}
             else if(a==0&&x>700&&x<850&&ny>200&&ny<400&&word[4]==' '){rxa=170;rya=260;a++;word[4]='a';}
             else if(x>880&&x<1250&&ny>50&&ny<400){rx=470;ry=340;select='a';}
            }
            else if(alpha=='d'){alpha=' ';
             if(d==0&&x>100&&x<250&&ny>200&&ny<400&&word[0]==' '){rxd=-510;ryd=260;d++;word[0]='d';}
             else if(d==0&&x>250&&x<400&&ny>200&&ny<400&&word[1]==' '){rxd=-360;ryd=260;d++;word[1]='d';}
             else if(d==0&&x>400&&x<550&&ny>200&&ny<400&&word[2]==' '){rxd=-210;ryd=260;d++;word[2]='d';}
             else if(d==0&&x>550&&x<700&&ny>200&&ny<400&&word[3]==' '){rxd=-60;ryd=260;d++;word[3]='d';}
             else if(d==0&&x>700&&x<850&&ny>200&&ny<400&&word[4]==' '){rxd=50;ryd=260;d++;word[4]='d';}
             else if(x>880&&x<1250&&ny>50&&ny<400){rx=370;ry=340;select='d';}
            }
        }
    }
}
else{
    int ny=738-y;
    if(button == GLUT_LEFT_BUTTON &&state==GLUT_DOWN)
    {
        if(x>600&&x<800&&ny<250&&ny>200)
            next=1;
    }
    else if(button == GLUT_LEFT_BUTTON &&state==GLUT_UP)
    {
        if(x>600&&x<800&&ny<250&&ny>200&&next==1)
            flag=1;
        else
            next=0;
    }
}
}
void page(){
    if(flag==0){
        display1();
    }
    else{
        display();
    }
}
int main(int argc, char ** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1366,738);
	glutCreateWindow("Bezier Curve");
    myinit();
	glutMouseFunc(mousebutton);
	glutDisplayFunc(page);
    glutMainLoop();
	return 0;
}
