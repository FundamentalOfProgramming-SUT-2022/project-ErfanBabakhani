// #include<curses.h>
#include <ncurses.h>
#include<dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char c[10000]="";
char cp[10000]="";


//S find
int finde_line_pos(int pos,int line){
    int k=0;
    int i=0;
    while(1){
    if(c[i]=='\n')
        line --;
    if(!(line>1))
        return k+1;
    k++;
    i++;    
    }

}

int find_star1(char a[],int l,int *p_SL){
int i=l,k=0;
int index=0;
int index_star=0;

while (1){
    // printf("s");
    if(a[k+1]=='\\'&&a[k+2]=='*'){// ignore \\ for (\\*) searching
        k+=2;
        i++;
        continue;
    }
    
    if(c[i]=='\0'&&a[k]!='\0'){return -1;}// these are the end of the searching loop
    if(a[k+1]=='\0'&&a[k]==c[i]){
        if(k==0)
            index=i;
        *p_SL=i;
        return index;
    }    
    
    if(c[i]==a[k]){// we devide the loop in two case equal and not equal cases
        
        if(k==0){// if we find the first char we save it's index for returning in the end 
            index=i;
        }
        
        if(a[k+1]=='*'){// if the next char is (*) we start the ignoring mode while we find the nex part of (*) 
            index_star=k+2;// set the index star to the first char of (*) it means we fined the string before (*) and we are searching the next part
            k+=2;
            i++;
            while (1)
            {
                if(c[i]=='\0'&&a[k]!='\0')// these are the end of the finding func
                    return -1;
                if(a[k+1]=='\0'&&a[k]==c[i]){
                    *p_SL=i;
                    return index;
                }

                if(a[k+1]=='*'){// this is for having a more than one star wildcard mines is becuse we have to plus in the end loop
                    i--;
                    k--;
                    break;
                }

                if(a[k]==c[i]&&a[k+1]==c[i+1]){// this means char of next string of (*) and searching string char are ok
                    i++;
                    k++;
                    continue;
                }

                if(a[k]==c[i]&&a[k+1]=='\0')// end of find func
                    return index;
                
                if(a[k+1]!=c[i+1]&&a[k]==c[i]){// we had a string like our searching string but they were'nt equal so continue from the first char of searching string 
                    if(k==index_star)
                        i++;
                    k=index_star;
                    continue;
                }
                
                i++;
            }
            
        }
        i++;
        k++;
    }

    if(c[i]!=a[k]){
        if(index_star!=k){
            k=index_star;
            continue;
        }
        i++;
    }
}


}

int find_star2(char a[],int l,int *p_SL){//if we have a * at the first of the finding string like (*example) 
int i=l,k=0;
int index=0;
int index_star=0;

while (1){
    
    if(a[k+1]=='\\'&&a[k+2]=='*'){
        k+=2;
        i++;
        continue;
    }

    if(c[i]=='\0'&&a[k]!='\0'){return -1;}
    if(a[k+1]=='\0'&&a[k]==c[i]){
        if(k==0)
            index=i;
        *p_SL=i;
        return l;
    }    
    if(c[i]==a[k]){
        
        if(k==0){
            index=i;
        }
        
        if(a[k+1]=='*'){
            index_star=k+2;
            k+=2;
            i++;

            while (1)
            {
                if(c[i]=='\0'&&a[k]!='\0')
                    return -1;
                if(a[k+1]=='\0'&&a[k]==c[i]){
                    *p_SL=i;
                    return l;
                }
                if(a[k+1]=='*'){
                    i--;
                    k--;
                    break;
                }
                if(a[k]==c[i]&&a[k+1]==c[i+1]){
                    i++;
                    k++;
                    continue;
                }
                if(a[k]==c[i]&&a[k+1]=='\0')
                    return l;
                if(a[k+1]!=c[i+1]&&a[k]==c[i]){
                    if(k==index_star)
                        i++;
                    k=index_star;
                    continue;
                }
                
                i++;
            }
            
        }
        i++;
        k++;
    }

    if(c[i]!=a[k]){
        if(index_star!=k){
            k=index_star;
            continue;
        }
        i++;
    }
}


}


int find_byword(int F){// F is the return of find_Star
int i=0;
int space=0;
while (i<F)
{
    if(c[i]==' '&&c[i-1]!=' '&&c[i-1]!='\0')
        space++;
    i++;
}
return space;

}


int find_count(char *a,int *p_SL){
    int k=0;
    int n=0;
    *p_SL=-1;
    while (1)
    {
        k=find_star1(a,*p_SL+1,p_SL);
        if(k==-1)
            return n;
        else{
            n++;
        }
    }
    
}

int find_at(char *a,int N,int *p_SL){
    int Num=find_count(a,p_SL);
    if(N>Num||N<1){
        printf("the number %d is not available\nWe have just %d item",N,Num);
    exit(1);
    }
    int k=0;
    int n=1;
    *p_SL=-1;
    while (1)
    {
        k=find_star1(a,*p_SL+1,p_SL);
        if(k==-1)
            return -1;
        else{
            if(n==N)
                return k;
            n++;
        }
    }
}
//F find

//S remove function
void remove_char(char file_ful_name[],char out[],int i,int size,int pos){//i=1 or 0: 1 is f(flag) and 0 is b(flag) 
    int k=0;
    int j=0;
    if(i==1){
        while(c[k]!='\0')
        {
            if(k==pos){
                while (size>0)
                {
                    k++;
                    size--;
                    continue;
                }
            }
            out[j]=c[k];
            k++;
            j++;
        }
    }
    
    if(i==0){
        while (c[k]!='\0')
        {
            if(k==(pos-size)){
                while (size>0)
                {
                    k++;
                    size--;
                    continue;
                }
                       
            }
            out[j]=c[k];
            k++;
            j++;
        }
        
    }
    FILE *fp=fopen(file_ful_name,"w");
    fprintf(fp,out);
    fclose(fp);
    return;
}


//F remove function

//S copy and cut
void copy_dir(char file_ful_name[],char file_ful_name_copy[]){

    int i=0;
    while (1)
    {
        if (file_ful_name[i]=='\0')
        {
            return ;
        }
        
        if(i==40){
            file_ful_name_copy[40]='c';
            file_ful_name_copy[41]='o';
            file_ful_name_copy[42]='p';
            file_ful_name_copy[43]='y';
            i=44;
            continue;
        }
        file_ful_name_copy[i]=file_ful_name[i];
        i++;
    }
    

}

void copy_str(char file_ful_name[],char out[],int i,int size,int pos){//i=1 or 0: 1 is f(flag) and 0 is b(flag) 
    
    int k=0;
    int j=0;
    if(i==1){
        while(c[k]!='\0')
        {
            if(k==pos){
                while (size>0)
                {
                    out[j]=c[k];
                    j++;
                    k++;
                    size--;
                    continue;
                }
            }
            k++;
        }
    }
    
    if(i==0){
        while (c[k]!='\0')
        {
            if(k==(pos-size)){
                while (size>0)
                {
                    out[j]=c[k];
                    j++;
                    k++;
                    size--;
                    continue;
                }
                       
            }
            k++;
        }
        
    }
    
    FILE *fp=fopen(file_ful_name,"w");
    fprintf(fp,out);
    fclose(fp);
    return;
    }
    
int save_file_txt_copy(char file_ful_name[]){// This is for backup the destination File contant
    FILE *fp;
    fp=fopen(file_ful_name,"r");
    int i=0;
    char d;
    while(!feof(fp)){
        d=fgetc(fp);
        cp[i]=d;
        i++;
    }
    cp[i-1]='\0';
    fclose(fp);
    return i;

}
//F copy and cut



/*void save_file(char file_ful_name[]){

    FILE *fp;
    fp=fopen(file_ful_name,"w");
    // fprintf(fp,"%s",c);
    fclose(fp);

    return;
}*/

int read_line(int line,char file_name[]){
    char S[1000]="";
    // strcpy(c,"");
    if(line<1){
        printf("invalid line");
        return -1;
    }
    FILE *fp;
    fp=fopen(file_name,"r");
    
    int i=0;
    while (i<line-1)
    {
        fgets(S,1000,fp);
        i++;
    }

    fgets(c,1000,fp);
    fclose(fp);
    // printf("SUCSSES");
    return 0;
}

int insert_check(char file_ful_name[]){//This is for checking the existance of File
    
    FILE *fp;
    fp=fopen(file_ful_name,"r");

    if(!fp){
        // fclose(fp);
        return 0;
    }
    
    else{

        fclose(fp);
        return 1;
    }

    // fclose(fp);
    // return 1;
 }

int save_file_txt(char file_ful_name[]){// This is for backup the destination File contant
    FILE *fp;
    fp=fopen(file_ful_name,"r");
    int i=0;
    char d;
    while(!feof(fp)){
        d=fgetc(fp);
        c[i]=d;
        i++;
    }
    c[i-1]='\0';
    fclose(fp);
    return i;

}

int hilight(int x_pos,int y_pos,int j,char file_ful_name[]){
    
    WINDOW *a=initscr();

    int m=0;
    int q=y_pos+j;
    while (1)
    {
        q=q/10;
        if(q==0)
            break;
        m++;
    }
    
    
    int k=x_pos-(6+m);
    move(y_pos,x_pos);
    attron(COLOR_PAIR(7));
    strcpy(c,"");
    read_line(y_pos+j-1,file_ful_name);
    printw("%c",c[k]);
    attroff(COLOR_PAIR(7));
    move(y_pos,x_pos);
    endwin();

    return k;
}

int make_newfile_name(char pre[]){
    
    // char a[100]="/home/erfan-b/Documents/root";
    strcpy(pre,"/home/erfan-b/Documents/root");
    // printf("%s\n",a);
    int i = 0;
    DIR *d;
    struct dirent *dir;
    // char NAME[300]="";
    // unsigned int type;
    // char file_name2[300];
    d = opendir(pre);
    if (d)
    {
        while ((dir = readdir(d)) != NULL){
            // printf("%s\n",dir->d_name);
            if(dir->d_name[0]=='n'&&dir->d_name[1]=='e'&&dir->d_name[2]=='w'&&dir->d_name[3]=='f'&&dir->d_name[4]=='i'&&dir->d_name[5]=='l'&&dir->d_name[6]=='e'){
                i++;
            }

        }
        
        closedir(d);           
    }
    i++;
    int k=0;
    int j=0;
    char C;
    char B;
    if(i>=10){
        j=i/10;
        k=i-(10*j);
        C=j+48;
        B=k+48;
        pre[38]=B;
        pre[37]=C;
    }

    if(i<10)
        C=i+48;
    pre[28]='/';
    pre[29]='n';
    pre[30]='e';
    pre[31]='w';
    pre[32]='f';
    pre[33]='i';
    pre[34]='l';
    pre[35]='e';
    pre[36]=' ';
    pre[37]=C;
    // printf("%s\n",a);
    // FILE *fp;
    // fp=fopen(pre,"w");
    // fclose(fp);
    
    return i;
    
}


void clear_back(int x,int y){
    char a[2]="";
    if(x>0){
        move(y,x-1);
        // addch('');// NULL is \0
        // printw("%s",a);
        delch();
        // the we should call remove_char() -b flag and 1 size and save it in our file 
        move(y,x-1);
        return;
    }

}
void make_tilda1(){
    WINDOW *a;
    a=initscr();
    int max_x,max_y;
    int x,y;
    int i=2;
    getmaxyx(a,max_y,max_x);
    x=0;y=2;
    start_color();
    init_pair(4,COLOR_CYAN,COLOR_BLACK);
    attron(COLOR_PAIR(4));
    // init_color(COLOR_RED, 700, 0, 0);
    while(i<max_y-6)
    {
        move(y,x);
        printw("~");
        // printw("~");
        y++;
        i++;
    }
    attroff(COLOR_PAIR(4));
    endwin();
    return;
} 

void CPY(int start,int finish){
    char a[1000]="";
    int i=start;
    int j=0;
    while (i<=finish)
    {
        a[j]=c[i];
        i++;
        j++;
    }
    strcpy(c,"");
    strcpy(c,a);
    return;
}
void VISUAL_mode(int x_pos,int y_pos,int j,char file_ful_name[],int change){//0 is unsaved and 1 is saved 
    char file_name_save[1000]="";
    strcpy(file_name_save,file_ful_name);
    file_name_save[24]='r';
    file_name_save[25]='o';
    file_name_save[26]='o';
    file_name_save[27]='t';
    int vas=insert_check(file_name_save);
    clear();
    make_tilda1();
    int max_x,max_y;    
    
    WINDOW *b=initscr();
    getmaxyx(b,max_y,max_x);
    
    int i;
    int SL;
    char A[10]="\n";
    int line_num;

    if(vas==1){
        save_file_txt(file_name_save);
        line_num=find_count(A,&SL);
        strcpy(c,"");
        // read_line(1,file_ful_name);
        // mvprintw(2,0,"{%d}%s[%s]",line_num,file_ful_name,c);
        // j++;
        i=j+1;
        // move(2,0);
        while (i<=(line_num+j)&&(i)<max_y-4+j)
        {
            move(i+1-j,0);
            read_line(i,file_ful_name);
            printw("    %d %s",i,c);
            i++;
        }
        move(y_pos,x_pos);
                
    }

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3,COLOR_BLACK,COLOR_CYAN);
    init_pair(7,COLOR_BLACK,COLOR_RED);
    init_pair(8,COLOR_WHITE,COLOR_BLACK);
    // init_pair(9,COLOR_BLACK,COLOR_);
    attron(COLOR_PAIR(9));
    
    int x,y;
    
    x=0;y=2;
    move(max_y-3,0);
    // attroff(COLOR_PAIR(1));
    if(vas==0||change==1){
        printw("VISUAL:%s    +",file_ful_name+28);
        attroff(COLOR_PAIR(9));
        refresh();
    }
    else{
        printw("VISUAL:%s    ",file_ful_name+28);
        attroff(COLOR_PAIR(9));
        refresh();
    }
    
    noecho();
    // attron(COLOR_PAIR(3));
    // mvprintw(max_y-1,0,"Commands Bar:");
    // attroff(COLOR_PAIR(3));

    move(1,max_x/2);
    y=2;
    x=0;
    attron(COLOR_PAIR(2));
    printw("[%d][%d]",x_pos,y_pos);
    
    attroff(COLOR_PAIR(2));
    
    keypad(stdscr,1);
    x=x_pos;
    y=y_pos;
    move(y_pos,x_pos);
    
    // attron(COLOR_PAIR(7));
    int k=hilight(x_pos,y_pos,j,file_ful_name);// k is a index of x_pos in c[] 
    int l=(int)strlen(c);
    int k_s=k;
    int k_f=k;

    int f;
    int a;
    while (1){
        noecho();
        a=getch();
        refresh();

        if(a==27){
            // addch(a);
            // break;
            endwin();
            exit(1);   
        }
        // else if(a==KEY_BACKSPACE){
            // noecho();
            // clear_back(x,y);
            // getyx(b,y,x);
            // x--;
        // }
        else if(a==KEY_UP){
            noecho();
            // y--;
            // move(y,x);
            // getyx(b,y,x);
            continue;
        }

        else if(a==KEY_DOWN){
            // noecho();
            // y++;
            // move(y,x);
            // getyx(b,y,x);
            continue;
        }
        else if(a==KEY_RIGHT){
            
            if(k==l||c[k]=='\n'){
                // mvprintw(3,40,".....");
                // move(y,x);
                continue;
            }
            else{
            x++;
            move(y,x);
            // k_f++;
            k++;
            if(k_f<k){
                k_f++;
            }
            hilight(x,y,j,file_ful_name);
            getyx(b,y,x);}
        }
        else if(a==KEY_LEFT){
            if(k==0){
                continue;
            }

            x--;
            k--;
            if(k_s>k){
                k_s--;
            }
            hilight(x,y,j,file_ful_name);
            move(y,x);
            getyx(b,y,x);
        }
        else if(a==KEY_F(0)){
            clear();
            printw("We want go to NORMAL MODE");

        }
        else if(a=='d'){
            // copy_dir(file_ful_name,)
            char copy[1000]="/home/erfan-b/Documents/copy";
            char out[1000]="";
            CPY(k_s,k_f);
            strcpy(copy+28,file_ful_name+28);
            FILE *fp=fopen(copy,"w");
            fprintf(fp,"%s",c);
            // clear();
            // printw("[%s]",c);
            fclose(fp);
            // getch();
            strcpy(c,"");
            save_file_txt(file_ful_name);
            remove_char(file_ful_name,out,1,k_f-k_s+1,k_s);
            strcpy(c,"");
            endwin();
            NORMAL_mode(y,x,file_ful_name,1);
            // exit(1);
        }
        else if(a=='y'){

        }
        else{
            // addch(a);
            getyx(b,y,x);
            refresh();
        }    
    }

    // printw("END\n");        
    noecho();
    getch();
    endwin();    
    return;

}

void NORMAL_mode(int x_pos,int y_pos,char file_ful_name[],int change){//0 is unchanged and 1 is chnged 
    
    char file_name_save[1000]="";
    strcpy(file_name_save,file_ful_name);
    file_name_save[24]='r';
    file_name_save[25]='o';
    file_name_save[26]='o';
    file_name_save[27]='t';
    int vas=insert_check(file_name_save);
    
    clear();
    make_tilda1();
    
    int max_x,max_y;    
    WINDOW *b=initscr();
    
    getmaxyx(b,max_y,max_x);
    // printf("%d %d\n",max_x,max_y);
    
    int i;
    int j=0;
    int SL;
    char A[10]="\n";
    int line_num;

    if(vas==1){
        save_file_txt(file_name_save);
        line_num=find_count(A,&SL);
        strcpy(c,"");

        i=j+1;
        while ((i+j)<=line_num&&(i+j)<=max_y-4)
        {
            move(i+1,0);
            read_line(i,file_name_save);
            printw("    %d %s",i,c);
            i++;
        }
    }

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3,COLOR_BLACK,COLOR_CYAN);
    init_pair(7,COLOR_BLACK,COLOR_RED);
    init_pair(8,COLOR_WHITE,COLOR_BLACK);
    init_pair(9,COLOR_WHITE,COLOR_BLUE);
    // init_pair(9,COLOR_BLACK,COLOR_);
    attron(COLOR_PAIR(1));
    
    int x,y;
    x=0;y=2;
    move(max_y-3,0);

    if(vas==0||change==1){
        printw("NORMAL:%s    +",file_ful_name+28);
        attroff(COLOR_PAIR(1));
        refresh();
    }
    else{
        printw("NORMAL:%s    ",file_ful_name+28);
        attroff(COLOR_PAIR(1));
        refresh();
    }
    
    noecho();
    attron(COLOR_PAIR(3));
    mvprintw(max_y-1,0,"Commands Bar:");
    attroff(COLOR_PAIR(3));

    move(1,max_x/2);
    y=2;
    x=0;
    attron(COLOR_PAIR(2));
    printw("THIS IS OUR TEXT EDITOR ENJOY IT");
    
    attroff(COLOR_PAIR(2));
    keypad(stdscr,1);
    
    move(y,x);
    int f;
    int a;    
    while (1)
    {
        
        noecho();
        a=getch();
        refresh();

        if(a==27){

            endwin();
            exit(1);   
        }
        else if(a==KEY_BACKSPACE){

            clear_back(x,y);
            getyx(b,y,x);

        }
        else if(a==KEY_UP){
            noecho();
            if(y==2&&j>0&&vas==1){
                
                clear();
                make_tilda1();
                attron(COLOR_PAIR(5));
                mvprintw(1,max_x/2,"THIS IS OUR TEXT EDITOR ENJOY IT");
                attroff(COLOR_PAIR(5));
                
                move(max_y-3,0);
                attron(COLOR_PAIR(1));
                if(vas==0){
                    printw("NORMAL:%s    +",file_ful_name+28);
                    attroff(COLOR_PAIR(1));
                    refresh();
                }
                else{
                    printw("NORMAL:%s    ",file_name_save+28);
                    attroff(COLOR_PAIR(1));
                    refresh();
                }
                
                noecho();
                attron(COLOR_PAIR(3));
                mvprintw(max_y-1,0,"Commands Bar:");
                attroff(COLOR_PAIR(3));
                
                strcpy(c,"");

                j--;
                i=j+1;

                while (i<=(line_num+j)&&(i)<max_y-4+j)
                {
                    move(i+1-j,0);
                    read_line(i,file_name_save);
                    printw("    %d %s",i,c);
                    i++;
                }
                move(2,0);
                continue;
            }
            else{
                y--;
                move(y,x);
            }
            getyx(b,y,x);
        }

        else if(a==KEY_DOWN){
            noecho();
            if(y==max_y-4&&line_num>max_y-4+j-1&&vas==1){
                
                clear();
                make_tilda1();
                attron(COLOR_PAIR(5));
                mvprintw(1,max_x/2,"THIS IS OUR TEXT EDITOR ENJOY IT");
                attroff(COLOR_PAIR(5));
                
                move(max_y-3,0);
                attron(COLOR_PAIR(1));
                if(vas==0){
                    printw("NORMAL:%s    +",file_ful_name+28);
                    attroff(COLOR_PAIR(1));
                    refresh();
                }
                else{
                    printw("NORMAL:%s    ",file_name_save+28);
                    attroff(COLOR_PAIR(1));
                    refresh();
                }
                
                noecho();
                attron(COLOR_PAIR(3));
                mvprintw(max_y-1,0,"Commands Bar:");
                attroff(COLOR_PAIR(3));
                
                strcpy(c,"");
                // read_line(1,file_ful_name);
                // mvprintw(2,0,"{%d}%s[%s]",line_num,file_ful_name,c);
                j++;
                i=j+1;
                // move(2,0);
                while (i<=(line_num+j)&&(i)<max_y-4+j)
                {
                    move(i+1-j,0);
                    read_line(i,file_name_save);
                    printw("    %d %s",i,c);
                    i++;
                }
                move(max_y-4,0);
                continue;
            }
            else{
                y++;
                move(y,x);
            }
            getyx(b,y,x);
        }
        else if(a==KEY_RIGHT){
            x++;
            move(y,x);
            getyx(b,y,x);
        }
        else if(a==KEY_LEFT){
            x--;
            move(y,x);
            getyx(b,y,x);
        }
        else if(a==KEY_F(1)){
            getyx(b,y,x);
            clear();
            printw("We want go to VISIUL MODE");
            // getch();
            // endwin();
            // getyx(b,y,x);
            // pri
            endwin();
            VISUAL_mode(x,y,j,file_ful_name,0);
        }
        else{
            addch(a);
            getyx(b,y,x);
            refresh();
        }    
    }

    // printw("END\n");        
    noecho();
    getch();
    endwin();    
    return;

}



void START_mode(){
    int max_x,max_y;
    int x,y;
    WINDOW *a=initscr();
    start_color();
    init_pair(5,COLOR_BLACK,COLOR_WHITE);
    init_pair(6,COLOR_BLACK,COLOR_YELLOW);
    keypad(a,1);
    getmaxyx(a,max_y,max_x);
    attron(COLOR_PAIR(5)|A_BLINK);
    mvprintw(1,max_x/3,"HELLO THIS IS THE START MODE IN WICH YOU CAN SELECT A NAME FOR YOUR FILE AND INPUT ENTER");
    attroff(COLOR_PAIR(5));
    attron(COLOR_PAIR(6));
    mvprintw(max_y/2+1,0,"IF YOU DON'T WANT CHOOSE A NAME JUST INPUT ENTER");    
    mvprintw(max_y/2+3,0,"ENTER NAME:");
    attroff(COLOR_PAIR(6)|A_BLINK);
    getyx(a,y,x);
    
    int d;
    char file_name[100]="";
    while (1)
    {
        getyx(a,y,x);
        noecho();
        d=getch();
        if(d=='\n'){
            // printw("$$$");
            // getch();
            char pre[100]="/home/erfan-b/Documents/test/"; //from 29 index is our file name 
            // printw("{%s , %d}",file_name,(int)strlen(file_name));
            if((int)strlen(file_name)==0){
                make_newfile_name(pre);
                pre[24]='t';
                pre[25]='e';
                pre[26]='s';
                pre[27]='t';
                endwin();
                FILE *fp=fopen(pre,"w");
                fclose(fp);
                NORMAL_mode(0,0,pre,0);
            }
            else{
                int i=29;
                while (file_name[i-29]!='\0')
                {
                    pre[i]=file_name[i-29];
                    i++;
                }
                // printw("[%s]",pre);
                // FILE *fp;
                // fp=fopen(pre,"w");
                // fclose(fp);
                // int vas=insert_check(pre);
                FILE *fp=fopen(pre,"w");
                fclose(fp);
                endwin();
                NORMAL_mode(0,0,pre,0);
                return;

            }
            // getch();
            endwin();
            // printw("{%s}",pre);
            // getch();
            return;
        }
        
        if(d==KEY_BACKSPACE){
    //         // noecho();
            // getyx(a,y,x);
            if(y==max_y/2+3&&x>10){
                file_name[x-12]='\0';
            }
            clear_back(x,y);
            getyx(a,y,x);
    //         // x--;
            continue;
        }
        else if(d==KEY_UP){
    //         // noecho();
            y--;
            move(y,x);
            getyx(a,y,x);
    //         // printw("S");
    //         // refresh();
            continue;
        }

        else if(d==KEY_DOWN){
            noecho();
            y++;
            move(y,x);
            getyx(a,y,x);
            continue;
        }
        else if(d==KEY_RIGHT){
            x++;
            move(y,x);
            getyx(a,y,x);
            continue;
        }
        else if(d==KEY_LEFT){
            x--;
            move(y,x);
            getyx(a,y,x);
            continue;
        }
        // else if(d==KEY_F(1)){
        //     clear();
        //     printw("We want go to VISIUL MODE");
        // }

        // else{
            // addch(a);
            // getyx(a,y,x);
            // refresh();
        // }
        if(y==max_y/2+3&&x>10){
            file_name[x-11]=d;
        }   
        addch(d);
        refresh();
    }
    
    endwin();

}



int main(void)
{
       

    START_mode();
    

    return 0;
}
