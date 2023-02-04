// #include<curses.h>
#include <ncurses.h>
#include<dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char c[10000]="";
char cp[10000]="";


char* insert_txt(char file_ful_name[],int pos,int line,char end_part[]){//This is for appending two strings (Final of our work in insert command)
    char save[2000]="";
    // printf("end_part=%s\n",end_part);
    // printf("c=%s]\n",c);
    int q=0;
    int p=0;
    while(line!=1){
        save[q]=c[q];
        if(c[q]=='\n')
            line--;
        q++;
    }

    int i=q,j=0,k=0;
    while (c[i]!='\0'||end_part[j]!='\0')
    {
        if(k!=pos){
            
            save[k+q]=c[i];
            i++;
            k++;
        }
        else if(j==0){
            
            while (end_part[j]!='\0')
            {
                save[k+q]=end_part[j];
                j++;    
                k++;
            }
            
        }

    }
    // printf("[%s]",save);
    FILE *fp=fopen(file_ful_name,"w");
    fprintf(fp,save);
    fclose(fp);
    
    return save;
}

//S find
int finde_line_pos(int pos,int line){
    int k=0;
    int i=0;
    if(line==1)
        return 0;
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
    if(i>0)
        c[i-1]='\0';
    fclose(fp);
    return i;

}

int hilight(int x_pos,int y_pos,int j,char file_ful_name[]){
    
    WINDOW *a=initscr();

    int m=0;
    int q=y_pos+j-1;
    while (1)
    {
        q=(q)/10;
        if(q==0)
            break;
        m++;
    }
    // save_file_txt(file_ful_name);
    
    int k=x_pos-(6+m);
    move(y_pos,x_pos);
    k+=finde_line_pos(k,y_pos+j-1);
    attron(COLOR_PAIR(7));
    // strcpy(c,"");
    // read_line(y_pos+j-1,file_ful_name);
    printw("%c",c[k]);
    // mvprintw(y_pos+j-1,40,"[%d] [%d]",y_pos+j-1,m);
    attroff(COLOR_PAIR(7));
    
    move(y_pos,x_pos);
    endwin();

    return k;
}

int hilight4(int x_index,char file_ful_name[],char tar[]){
    
    start_color();
    attroff(COLOR_PAIR(7));
    init_pair(11,COLOR_WHITE,COLOR_BLACK);
    
    // clear();
    // printw("[%d],[%c]",x_index,c[x_index]);
    // getch();
    int SL3;
    char a[10]="\n";
    int line_num;
    int T=-1;
    
    strcpy(c+x_index,"");
    line_num=find_count(a,&SL3);
    // clear();
    // printw("%d",line_num);
    // getch();

    strcpy(c,"");
    save_file_txt(file_ful_name); 
    if(line_num!=0){
        T=find_at(a,line_num,&SL3);
    }

    line_num++;
    
    int x,y;
    x=x_index;
    y=line_num;
    x=x-T-1;
    
    int m=0;
    int q=y;
    while (1)
    {
        q=(q)/10;
        if(q==0)
            break;
        m++;
    }
    
    // clear();
    strcpy(c,"");
    save_file_txt(file_ful_name);
    // printw("%d  %d [%d]",line_num,T,x);
    // getch();

    save_file_txt(file_ful_name);
    
    

    // move(y,x);
    // clear();
    int i=0;
    int l=strlen(tar);
    // clear();
    // printw("%d",l);
    // getch();
    int CD_x=x+6+m;
    
    while(i<l){
        
        // mvprintw(0,0,"%d %d",l,x+6+m);
        attron(COLOR_PAIR(11));
        // mvprintw(0,50,"%d",x_index);
        
        // clear();
        mvprintw(y+1,x+6+m,"%c",c[x_index+i]);
        // mvprintw(0,0,"asaa");
        // getch();
        attroff(COLOR_PAIR(11));

        x++;
        i++;
        // getch();
    }

    // clear();
    // getch();
    // move(0,0);
    // delch();
    // getch();
    // clear();
    move(y+1,CD_x);
    // getch();

    // getch();

    return;
}

int hilight2(int x_index,char file_ful_name[],char tar[]){
    // clear();
    // printw("[%d],[%c]",x_index,c[x_index]);
    // getch();
    int SL3;
    char a[10]="\n";
    int line_num;
    int T=-1;
    
    strcpy(c+x_index,"");
    line_num=find_count(a,&SL3);
    // clear();
    // printw("%d",line_num);
    // getch();

    strcpy(c,"");
    save_file_txt(file_ful_name); 
    if(line_num!=0){
        T=find_at(a,line_num,&SL3);
    }

    line_num++;
    
    int x,y;
    x=x_index;
    y=line_num;
    x=x-T-1;
    
    int m=0;
    int q=y;
    while (1)
    {
        q=(q)/10;
        if(q==0)
            break;
        m++;
    }
    
    // clear();
    strcpy(c,"");
    save_file_txt(file_ful_name);
    // printw("%d  %d [%d]",line_num,T,x);
    // getch();

    save_file_txt(file_ful_name);
    
    

    // move(y,x);
    // clear();
    int i=0;
    int l=strlen(tar);
    // clear();
    // printw("%d",l);
    // getch();
    int CD_x=x+6+m;
    while(i<l){
        attron(COLOR_PAIR(7));
        // mvprintw(0,50,"%d",x_index);

        mvaddch(y+1,x+6+m,c[x_index+i]);
        attroff(COLOR_PAIR(7));
        x++;
        i++;
    }
    // getch();
    // clear();
    move(y+1,CD_x);
    // getch();

    // getch();

    return;
}
int hilight3(int x_index,char file_ful_name[],char tar[]){
    // clear();
    // printw("[%d],[%c]",x_index,c[x_index]);
    // getch();
    int SL3;
    char a[10]="\n";
    int line_num;
    int T=-1;
    
    strcpy(c+x_index,"");
    line_num=find_count(a,&SL3);
    // clear();
    // printw("%d",line_num);
    // getch();

    strcpy(c,"");
    save_file_txt(file_ful_name); 
    if(line_num!=0){
        T=find_at(a,line_num,&SL3);
    }

    line_num++;
    
    int x,y;
    x=x_index;
    y=line_num;
    x=x-T-1;
    
    int m=0;
    int q=y;
    while (1)
    {
        q=(q)/10;
        if(q==0)
            break;
        m++;
    }
    
    // clear();
    strcpy(c,"");
    save_file_txt(file_ful_name);
    // printw("%d  %d [%d]",line_num,T,x);
    // getch();

    save_file_txt(file_ful_name);
    
    

    // move(y,x);
    // clear();
    int i=0;
    int l=strlen(tar);
    // clear();
    // printw("%d",l);
    // getch();
    int CD_x=x+6+m;
    // while(i<l){
    //     attron(COLOR_PAIR(7));
    //     // mvprintw(0,50,"%d",x_index);

    //     mvaddch(y+1,x+6+m,c[x_index+i]);
    //     attroff(COLOR_PAIR(7));
    //     x++;
    //     i++;
    // }
    // getch();
    // clear();
    move(y+1,CD_x);
    // getch();

    // getch();

    return;
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

void INSERT_mode(int x_pos,int y_pos,char file_ful_name[],int change,int j){//0 is unchanged and 1 is chnged 
    
    char file_name_save[1000]="";
    // char command[1000]="";
    // int V_C;//vas command 1 means do it and 0 means ignore

    strcpy(file_name_save,file_ful_name);
    file_name_save[24]='r';
    file_name_save[25]='o';
    file_name_save[26]='o';
    file_name_save[27]='t';
    int vas=insert_check(file_name_save);
    vas=1;
    clear();
    make_tilda1();
    
    int max_x,max_y;    
    WINDOW *b=initscr();
    
    getmaxyx(b,max_y,max_x);
    // printf("%d %d\n",max_x,max_y);
    // if(vas==0)
    int i;
    j;
    int SL;
    char A[10]="\n";
    int line_num;
    // move(2,0);
    if(vas==1){
        save_file_txt(file_ful_name);
        line_num=find_count(A,&SL);
        strcpy(c,"");

        i=j+1;
        while ((i)<=(line_num+j)&&(i)<=max_y-4+j)
        {
            move(i-j+1,0);
            read_line(i,file_ful_name);
            printw("    %d %s",i,c);
            i++;
        }
    }
    strcpy(c,"");
    read_line(1,file_ful_name);
    if(c[0]=='\0'){
        // mvprintw(1,0,"\n");
        mvprintw(2,0,"    1 ");
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
        printw("INSERT:%s    +",file_ful_name+28);
        attroff(COLOR_PAIR(1));
        refresh();
    }
    else{
        printw("INSERT:%s    ",file_ful_name+28);
        attroff(COLOR_PAIR(1));
        refresh();
    }
    
    noecho();
    attron(COLOR_PAIR(3));
    // mvprintw(max_y-1,0,"Commands Bar:");
    attroff(COLOR_PAIR(3));

    move(1,max_x/2);
    y=y_pos;
    x=x_pos;
    attron(COLOR_PAIR(2));
    printw("THIS IS OUR TEXT EDITOR ENJOY IT");
    
    attroff(COLOR_PAIR(2));
    keypad(stdscr,1);
    
    move(y_pos,x_pos);
    int f;
    int a;    
    while (1){
        // mvprintw(max_y-1,0,"VVV");
        refresh();
        move(y,x);
        noecho();
        a=getch();
        refresh();

        if(a==27){

            endwin();
            exit(1);   
        }
        // else if(a==KEY_BACKSPACE){

            // clear_back(x,y);
            // getyx(b,y,x);

        // }

        else if(a==KEY_UP){
            y--;
            move(y,x);
            getyx(b,y,x);
        }

        else if(a==KEY_DOWN){
            
            y++;
            move(y,x);        
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
        else if(a==KEY_F(2)){
            NORMAL_mode(x,y,file_ful_name,change,j);
        }
        
        else{
            vas=1;
            getyx(b,y,x);
            char A[5]="";
            A[0]=(char)a;
            // strcpy(A,"!");
            int m=0;
            int q=y+j;
            while (1)
            {
                q=q/10;
                if(q==0)
                    break;
                m++;
            }
            int k=x-(6+m);
            
                        
            save_file_txt(file_ful_name);
            // shape_insert(x,y,file_ful_name,1,j);
            insert_txt(file_ful_name,k,y+j-1,A);
            save_file_txt(file_ful_name);
            // clear();
            // mvprintw(0,0,"%s",c);
            // getch();
            refresh();
            shape_insert(x,y,file_ful_name,1,j);
            refresh();
            change=1;
            x++;
            move(y,x);
            // clear();
            save_file_txt(file_ful_name);
            // printw("AASSQQQ::::[%s]",c);
            continue;
        }   
    }        
    
    noecho();
    getch();
    endwin();    
    return;

}

void shape_insert(int x_pos,int y_pos,char file_ful_name[],int change,int j){
    
    char file_name_save[1000]="";
    // char command[1000]="";
    // int V_C;//vas command 1 means do it and 0 means ignore

    strcpy(file_name_save,file_ful_name);
    file_name_save[24]='r';
    file_name_save[25]='o';
    file_name_save[26]='o';
    file_name_save[27]='t';
    // int vas=insert_check(file_name_save);
    
    int vas=1;
    clear();
    make_tilda1();
    
    int max_x,max_y;    
    WINDOW *b=initscr();
    
    getmaxyx(b,max_y,max_x);
    // printf("%d %d\n",max_x,max_y);
    
    int i;
    j;
    int SL;
    char A[10]="\n";
    int line_num;
    // move(2,0);

    if(1){
        save_file_txt(file_ful_name);
        line_num=find_count(A,&SL);
        strcpy(c,"");
        
        i=j+1;
        while ((i)<=(line_num+j)&&(i)<=max_y-4+j)
        {
            // clear();
            // printw("VV");
            // getch();
            move(i-j+1,0);
            read_line(i,file_ful_name);
            printw("    %d %s",i,c);
            refresh();
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
        printw("INSERT:%s    +",file_ful_name+28);
        attroff(COLOR_PAIR(1));
        refresh();
    }
    else{
        printw("INSERT:%s    ",file_ful_name+28);
        attroff(COLOR_PAIR(1));
        refresh();
    }
    
    noecho();
    attron(COLOR_PAIR(3));
    // mvprintw(max_y-1,0,"Commands Bar:");
    attroff(COLOR_PAIR(3));

    move(1,max_x/2);
    y=y_pos;
    x=x_pos;
    attron(COLOR_PAIR(2));
    printw("THIS IS OUR TEXT EDITOR ENJOY IT");
    
    attroff(COLOR_PAIR(2));
    keypad(stdscr,1);
    
    move(y_pos,x_pos);
    return;    
}


void VISUAL_mode(int x_pos,int y_pos,int j,char file_ful_name[],int change){//0 is unsaved and 1 is saved 
    char file_name_save[1000]="";
    strcpy(file_name_save,file_ful_name);
    file_name_save[24]='r';
    file_name_save[25]='o';
    file_name_save[26]='o';
    file_name_save[27]='t';
    int j2=j;
    // char txt_save[1000]="";
    
    int vas=insert_check(file_name_save);
    
    // strcpy(c,"");
    // save_file_txt(file_name_save);
    // strcpy(txt_save,c);
    // FILE *fp_test=fopen(,"w");
    // fprintf(fp_test,"%s",c);
    // fclose(fp_test);

    strcpy(c,"");
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
        save_file_txt(file_ful_name);
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
    init_pair(10,COLOR_WHITE,COLOR_BLACK);//unhilight
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
    // printw("[%d][%d]",x_pos,y_pos);
    
    attroff(COLOR_PAIR(2));
    
    keypad(stdscr,1);
    x=x_pos;
    y=y_pos;
    move(y_pos,x_pos);
    
    // attron(COLOR_PAIR(7));
    save_file_txt(file_ful_name);
    int k=hilight(x_pos,y_pos,j,file_ful_name);// k is a index of x_pos in c[] 
    int k_save=k;
    int l=(int)strlen(c);
    int k_s=k_save;
    int k_f=k_save;

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
            
            if(c[k]=='\n'){
                j2++;
                if(c[k+1]=='\0')
                    continue;
                y++;
                if(y>=max_y-3){
                    j2--;
                    y--;
                    continue;
                }

                k++;
                if(k_f<k)
                    k_f=k;
                if(k_s<k_save){
                    attron(COLOR_PAIR(10));
                    mvaddch(y-1,x,c[k-1]);
                    attroff(COLOR_PAIR(10));
                    k_s++;
                }

                int m=0;
                int q=y+j-1;
                while (1)
                {
                    q=q/10;
                    if(q==0)
                        break;
                    m++;
                }

                x=(6+m);

                hilight(x,y,j,file_ful_name);
                move(y,x);
                
                // strcpy(c,"");
                // read_line(y+j,file_ful_name);
                // l+=(int)strlen(c);
                // x++;
                continue;
            }
            else {
                x++;

                k++;
                if(k_f<k)
                    k_f=k;
                if(k_s<k_save){
                    attron(COLOR_PAIR(10));
                    mvaddch(y,x-1,c[k-1]);
                    attroff(COLOR_PAIR(10));
                    k_s++;
                }

                move(y,x);
                hilight(x,y,j,file_ful_name);
                getyx(b,y,x);
            }
        }
        else if(a==KEY_LEFT){
            // if(k==0){
            //     continue;
            // }

            // x--;
            // k--;
            // if(k_s>k){
            //     k_s--;
            // }


            // hilight(x,y,j,file_ful_name);
            // move(y,x);
            // getyx(b,y,x);
            if(c[k-1]=='\n'){
                j2--;
                // if(c[k-1]=='\0')
                    // continue;
                y--;
                if(y<2){
                    j2++;
                    y++;
                    continue;
                }

                k--;
                if(k_s>k)
                    k_s=k;
                if(k_f>k_save){
                    attron(COLOR_PAIR(10));
                    mvaddch(y+1,x,c[k+1]);
                    attroff(COLOR_PAIR(10));
                    k_f--;
                }

                int m=0;
                int q=y+j-1;
                while (1)
                {
                    q=q/10;
                    if(q==0)
                        break;
                    m++;
                }

                // mvprintw(y,50,"[%d][%d][%d]",x,(int)strlen(c),m);
                strcpy(c,"");
                save_file_txt(file_ful_name);
                
                // hilight(x,y,j,file_ful_name);
                
                strcpy(c,"");
                read_line(y+j-1,file_ful_name);
                x=(6+m)+(int)strlen(c)-1;                
                strcpy(c,"");
                save_file_txt(file_ful_name);
                // mvprintw(y,50,"{%d}",x);
                
                move(y,x);
                // strcpy(c,"");
                // read_line(y+j,file_ful_name);
                // l+=(int)strlen(c);
                // x++;
                // k--;
                continue;
            }
            else {
                x--;
                k--;
                if(k_s>k)
                    k_s=k;
                if(k_f>k_save){
                    attron(COLOR_PAIR(10));
                    mvaddch(y,x+1,c[k+1]);
                    attroff(COLOR_PAIR(10));
                    k_f--;
                }

                move(y,x);
                hilight(x,y,j,file_ful_name);
                getyx(b,y,x);
            }


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
            int size=k_f-k_s+1;
            // k_s+=finde_line_pos(k_s,y_pos+j-1);
            // mvprintw(0,0,"[%d]",k_s);
            // noecho();
            // getch();
            remove_char(file_ful_name,out,1,size,k_s);
            // save_file_txt(file_ful_name);
            // clear();
            // save_file_txt(file_ful_name);
            // mvprintw(0,0,"[%s]",c);
            // getch();
            strcpy(c,"");
            endwin();
            getyx(b,y,x);
            NORMAL_mode(x_pos,y_pos,file_ful_name,1,j);
            endwin();
            // exit(1);
        }
        else if(a=='y'){
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

            strcpy(c,"");
            endwin();
            getyx(b,y,x);
            endwin();
            NORMAL_mode(x_pos,y_pos,file_ful_name,1,j);
            endwin();
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

void NORMAL_mode(int x_pos,int y_pos,char file_ful_name[],int change,int j){//0 is unchanged and 1 is chnged 
    
    char file_name_save[1000]="";
    char command[1000]="";
    int V_C;//vas command 1 means do it and 0 means ignore
    char file_name[100]="";


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
    int x_c=14,y_c=max_y-1;
    
    int i;
    j;
    int SL;
    char A[10]="\n";
    int line_num;
    // move(2,0);
    vas=1;
    if(vas==1){
        save_file_txt(file_ful_name);
        line_num=find_count(A,&SL);
        strcpy(c,"");

        i=j+1;
        while ((i)<=(line_num+j)&&(i)<=max_y-4+j)
        {
            move(i-j+1,0);
            read_line(i,file_ful_name);
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
    y=y_pos;
    x=x_pos;
    attron(COLOR_PAIR(2));
    printw("THIS IS OUR TEXT EDITOR ENJOY IT");
    
    attroff(COLOR_PAIR(2));
    keypad(stdscr,1);
    
    move(y_pos,x_pos);
    int f;
    int a;    



    while (1)
    {
        
        refresh();
        noecho();
        a=getch();
        refresh();

        if(a==27){

            endwin();
            exit(1);   
        }
        // else if(a==KEY_BACKSPACE){

            // clear_back(x,y);
            // getyx(b,y,x);

        // }
        if(V_C==1){// command menu
            /*if(strcmp(command,"auto-indent")){
                char d;
                int C_N=0;
                int rep=1;
                
                // int end=make_file_dir_name_grep(file_name,38,&d);
                // insert_check(file_name+6);
                // printf("%s",file_name+6);
                // int save_SL[100];
                // make_undo(file_name,file_name_undo,end);
                
                make_STD_text(file_ful_name);
                R_fix2(file_ful_name,&C_N,rep);
                make_L_R_save(file_ful_name);
            }*/

            if(strcmp(command,"save")==0){
               
                int vas2=insert_check(file_name_save);
                
                if(vas2==1){
                    strcpy(c,"");
                    save_file_txt(file_ful_name);
                    // int l_s=(int)strlen(file_name_save);
                    // file_name_save[l_s]='.';
                    // file_name_save[l_s+1]='t';
                    // file_name_save[l_s+2]='x';
                    // file_name_save[l_s+3]='t';

                    FILE *fp=fopen(file_name_save,"w");
                    fprintf(fp,"%s",c);
                    fclose(fp);
                    
                    change=0;

                    // refresh();
                    int DOW=strlen(file_name_save+23)+6;
                    move(max_y-3,DOW);
                    delch();
                    x_c++;
                    move(y,x);
                    V_C==0;
                }
                if(vas2==0){
                    // mvprintw(0,0,"%c",file_ful_name[29]);
                    // getch();
                    if(file_ful_name[29]=='n'&&file_ful_name[30]=='e'&&file_ful_name[31]=='w'&&file_ful_name[32]=='f'&&file_ful_name[33]=='i'&&file_ful_name[34]=='l'&&file_ful_name[35]=='e'){
                        mvprintw(max_y-1,x_c+1,"YOU DONT INPUT NAME AND IF YOU DON'WANT WE CAN MAKE IT BY DEFULT NAME BUT IF YOU WANT ENTER NAME: ");
                        int x_c2=x_c;
                        x_c+=99;
                        vas=1;
                        V_C=0;
                        
                        int j=0;
                        do
                        {
                            file_name[j]=getch();
                            mvaddch(y_c,x_c,file_name[j]);
                            x_c++;

                            j++;

                        } while (file_name[j-1]!='\n');
                        file_name[j-1]='\0';
                        move(y_c,x_c);
                        
                        // move(y_c,x_c);
                        int ci=0;
                        while (ci<(int)strlen(command)+100+(int)strlen(file_name)+1)
                        {
                            move(y_c,x_c);
                            delch();
                            x_c--;
                            ci++;
                            
                        }
                        int DOW=strlen(file_name_save+23)+6;
                        move(max_y-3,DOW);
                        delch();
                        
                        strcpy(file_name_save+29,"");
                        strcpy(file_name_save+29,file_name);
                        strcpy(file_ful_name+29,"");
                        strcpy(file_ful_name+29,file_name);
                        
                        FILE *fp=fopen(file_name_save,"w");
                        fprintf(fp,"%s",c);
                        fclose(fp);
                        int k=50;
                        move(max_y-3,50);
                        
                        while (k>7){
                            delch();
                            k--;
                            move(max_y-3,k);
                        }
                        attron(COLOR_PAIR(1));
                        printw("/%s    ",file_name);
                        attroff(COLOR_PAIR(1));
                        move(y,x);
                        change=0;
                    }
                    
                    

                }
                mvprintw(max_y-2,max_x/2,"WE SAVE IT SUCCSESFULY");
                
            }
            else if(command[0]=='s'&&command[1]=='a'&&command[2]=='v'&&command[3]=='e'&&command[4]=='a'&&command[5]=='s'){
                strcpy(file_name,command+7);
                // clear();
                // printw(file_name);
                // getch();
                save_file_txt(file_ful_name);
                strcpy(file_ful_name+29,"");
                strcpy(file_ful_name+29,file_name);
                strcpy(file_name_save+29,"");
                strcpy(file_name_save+29,file_name);
                FILE *g=fopen(file_ful_name,"w");
                fprintf(g,c);
                fclose(g);
                // clear();
                // printw("%s",file_name_save+29);
                // getch();                

                
                strcpy(c,"");
                save_file_txt(file_ful_name);
                // int l_s=(int)strlen(file_name_save);
                // file_name_save[l_s]='.';
                // file_name_save[l_s+1]='t';
                // file_name_save[l_s+2]='x';
                // file_name_save[l_s+3]='t';
                // clear();
                // printw(file_name_save);
                // getch();
                FILE *fp=fopen(file_name_save,"w");
                fprintf(fp,"%s",c);
                fclose(fp);
                
                change=0;
                int ci=0;
                // move(y_c,x_c);
                while (ci<(int)strlen(command)+1)
                {
                    move(y_c,x_c);
                    delch();
                    x_c--;
                    ci++;
                }
                refresh();
                int DOW=strlen(file_name_save+23)+6;
                move(max_y-3,DOW);
                delch();
                x_c++;
                
                int k=50;
                move(max_y-3,50);
                while (k>7){
                    delch();
                    k--;
                    move(max_y-3,k);
                }
                attron(COLOR_PAIR(1));
                printw("/%s    ",file_name);
                attroff(COLOR_PAIR(1));
                mvprintw(max_y-2,max_x/2,"WE SAVE IT SUCCSESFULY");
                move(y,x);

                V_C==0;    
            }//////

            else if(command[0]=='o'&&command[1]=='p'&&command[2]=='e'&&command[3]=='n'){
                // clear();
                // printw("///");
                // getch();
                if(change==1){
                    
                    int vas2=insert_check(file_name_save);
                    if(vas2==1){
                        strcpy(c,"");
                        save_file_txt(file_ful_name);
                        // int l_s=(int)strlen(file_name_save);
                        // file_name_save[l_s]='.';
                        // file_name_save[l_s+1]='t';
                        // file_name_save[l_s+2]='x';
                        // file_name_save[l_s+3]='t';

                        FILE *fp=fopen(file_name_save,"w");
                        fprintf(fp,"%s",c);
                        fclose(fp);
                        
                        change=0;

                        // refresh();
                        int DOW=strlen(file_name_save+23)+6;
                        move(max_y-3,DOW);
                        delch();
                        x_c++;
                        move(y,x);
                        V_C==0;
                    }
                    if(vas2==0){
                        // mvprintw(0,0,"%c",file_ful_name[29]);
                        // getch();
                        if(file_ful_name[29]=='n'&&file_ful_name[30]=='e'&&file_ful_name[31]=='w'&&file_ful_name[32]=='f'&&file_ful_name[33]=='i'&&file_ful_name[34]=='l'&&file_ful_name[35]=='e'){
                            mvprintw(max_y-1,x_c+1,"YOU DONT INPUT NAME AND IF YOU DON'WANT WE CAN MAKE IT BY DEFULT NAME BUT IF YOU WANT ENTER NAME: ");
                            int x_c2=x_c;
                            x_c+=99;
                            vas=1;
                            V_C=0;
                            
                            int j=0;
                            do
                            {
                                file_name[j]=getch();
                                mvaddch(y_c,x_c,file_name[j]);
                                x_c++;

                                j++;

                            } while (file_name[j-1]!='\n');
                            file_name[j-1]='\0';
                            move(y_c,x_c);
                            
                            // move(y_c,x_c);
                            int ci=0;
                            while (ci<(int)strlen(command)+100+(int)strlen(file_name)+1)
                            {
                                move(y_c,x_c);
                                delch();
                                x_c--;
                                ci++;
                                
                            }
                            
                            int DOW=strlen(file_name_save+23)+6;
                            move(max_y-3,DOW);
                            delch();
                            
                            strcpy(file_name_save+29,"");
                            strcpy(file_name_save+29,file_name);
                            strcpy(file_ful_name+29,"");
                            strcpy(file_ful_name+29,file_name);
                            
                            FILE *fp=fopen(file_name_save,"w");
                            fprintf(fp,"%s",c);
                            fclose(fp);
                            
                            int k=50;
                            move(max_y-3,50);
                            
                            while (k>7){
                                delch();
                                k--;
                                move(max_y-3,k);
                            }
                            attron(COLOR_PAIR(1));
                            // printw("/%s    ",file_name);
                            attroff(COLOR_PAIR(1));
                            move(y,x);
                            change=0;
                        }
                        mvprintw(max_y-2,max_x/2,"WE SAVE IT SUCCSESFULY");
                        

                        

                    }    
                
                }
                        int k=50;
                        move(max_y-3,50);
                        while (k>7){
                            delch();
                            k--;
                            move(max_y-3,k);
                        }
                        strcpy(file_name,"");
                        strcpy(file_name,command+5);
                        strcpy(file_ful_name+29,"");
                        strcpy(file_ful_name+29,file_name);
                        strcpy(file_name_save+29,"");
                        strcpy(file_name_save+29,file_name);
                        attron(COLOR_PAIR(1));
                        mvprintw(max_y-3,8,"%s    ",file_name);
                        attroff(COLOR_PAIR(1));
                        NORMAL_mode(0,0,file_ful_name,0,0);
                        // printw("");
                        refresh();
                        // getch();
            }

            else if(command[0]=='/'){
                // mvprintw(0,40,"%s",command+1);
                int SL=-1;
                int SL2;
                int start=-1;
                save_file_txt(file_ful_name);
                int count=find_count(command+1,&SL2);
                if(count==0){
                    getyx(b,y,x);
                    mvprintw(0,0,"NOT FOUND PREES ANY KEY TO CONTINIUE");
                    getch();
                    move(0,0);
                    clrtoeol();
                    
                    move(y,x);
                    // continue;
                    
                }
                int i=0;
                while (i<count)
                {
                    strcpy(c,"");
                    save_file_txt(file_ful_name);
                    


                    start=find_star1(command+1,SL+1,&SL);
                    
                    // clear();
                    // printw("[%d][%s][%d]{%d}",count,command+1,start+1,count);
                    // getch();
                    // clear();
                    // mvprintw(0,0,"{%d  %d} ",start,SL);
                    // getch();
                    // clear();
                    // continue;
                    // if(start!=-1)
                    
                    hilight2(start,file_ful_name,command+1);
                    i++;

                }
                i=0;
                char p;
                SL2=-1;
                int SL3=-1;
                while (1)
                {
                    
                    p=getch();
                    
                    if(p=='n'){
                        // clear();
                        // printw("%s",command+1);
                        // getch();
                        if(i==count){
                            i=0;
                            SL2=-1;
                            
                        }
                        strcpy(c,"");
                        save_file_txt(file_ful_name);
                        start=find_star1(command+1,SL2+1,&SL2);
                        hilight3(start,file_ful_name,command+1);
                        i++;

                    }
                    // else if(p=='n'){
                        // continue;
                    // }
                    else{
                        getyx(b,y,x);
                        int i=0;
                        while (i<count)
                        {
                            strcpy(c,"");
                            save_file_txt(file_ful_name);
                            start=find_star1(command+1,SL3+1,&SL3);
                            hilight4(start,file_ful_name,command+1);
                            i++;
                        }
                        move(y,x);
                        break;
                    }///aaas//
                }
                strcpy(command,"");

            }

            int ci=50;
            while (ci>13)
            {
                move(max_y-1,ci);
                delch();
                
                ci--;
            }


            
            // strcpy(command,"");
            
            int QM=300;
            while (QM>=0)
            {
                command[QM]='\0';
                QM--;
            }
            

            V_C=0;
            x_c=14;
            y_c=max_y-1;
            move(y,x);
            continue;
            
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
                
                strcpy(c,"");

                j--;
                i=j+1;

                while (i<=(line_num+j)&&(i)<max_y-4+j)
                {
                    move(i+1-j,0);
                    read_line(i,file_ful_name);
                    printw("    %d %s",i,c);
                    i++;
                }
                // move(2,0);
                // getyx(b,y,x);
                move(y,x);
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
                
                strcpy(c,"");
                // read_line(1,file_ful_name);
                // mvprintw(2,0,"{%d}%s[%s]",line_num,file_ful_name,c);
                j++;
                i=j+1;
                // move(2,0);
                while (i<=(line_num+j)&&(i)<max_y-4+j)
                {
                    move(i+1-j,0);
                    read_line(i,file_ful_name);
                    printw("    %d %s",i,c);
                    i++;
                }
                // getyx(b,y,x);
                move(y,x);
                continue;
            }
            else if(y!=max_y-4){
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
            endwin();
        }
        
        else if((char)a==':'){
            
            move(y_c,x_c);
            // printw("");
            // move(20,x);
            refresh();
            int B;
            int count=x_c-14;
            
            noecho();
            B=getch();
            if(B=='\n'||B==':'){
                move(y,x);
                continue;
            }
            
            addch(B);
            command[x_c-14]=B;
            V_C=1;
            count++;
            x_c,y_c;
            
            while (1){
                // printw(".");
                noecho();
                getyx(b,y_c,x_c);
                B=getch();
                
                if(B==KEY_BACKSPACE){
                    if(x_c<15)
                        continue;
                    command[count-1]='\0';
                    count--;
                    clear_back(x_c,y_c);
                    // getyx(b,y1,x1);
                    continue;

                }
                
                if(B=='\n'||B==':'){
                    move(y,x);
                    break;
                }
                
                getyx(b,y_c,x_c);
                mvaddch(y_c,x_c,B);
                x_c++;
                move(y_c,x_c);
                command[count]=B;
                count++;
            }
            
            // mvprintw(0,0,"{%s} [%d]",command,V_C);
            continue;
        }

        else if(a==KEY_F(3)){
            // clear();
            // printw("%s",file_ful_name);
            // getch();
            INSERT_mode(x,y,file_ful_name,change,j);
        }

        else if((char)a=='p'){
            // clear();
            // printw("%d %d",x,y+j-1);
            // getch();
            
            getyx(b,y,x);
            char file_name_copy[1000]="";
            char S[1000]="";
            strcpy(file_name_copy,file_ful_name);
            file_name_copy[24]='c';
            file_name_copy[25]='o';
            file_name_copy[26]='p';
            file_name_copy[27]='y';
            strcpy(c,"");
            save_file_txt(file_name_copy);
            strcpy(S,c);
                        // clear();
            // printw("%s",S);
            // getch();

            
            int m=0;
            int q=y+j-1;

            
            while (1)
            {
                q=q/10;
                if(q==0)
                    break;
                m++;
            }


            move(y,x);
            int k=x-(6+m);
            strcpy(c,"");
            save_file_txt(file_ful_name);
            k+=finde_line_pos(x-(6+m),y+j-1);
                        // clear();
            // strcpy(c,"");
            // save_file_txt(file_ful_name);
            // printw("x=%d y=%d m=%d k=%d [%c]",x_sp-(6+m),y+j-1,m,k,c[k]);
            // getch();

            // save_file_txt(file_ful_name);
            insert_txt(file_ful_name,k,1,S);
            clear();
            // save_file_txt(file_ful_name);
            // printw("%s",c);
            // getch();
            NORMAL_mode(x,y,file_ful_name,1,j);
            endwin();
        }

        else{
            // addch(a);
            // getyx(b,y,x);
            // refresh();
            continue;
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
            char pre2[100]="/home/erfan-b/Documents/root/";
            // printw("{%s , %d}",file_name,(int)strlen(file_name));
            if((int)strlen(file_name)==0){
                make_newfile_name(pre);
                strcpy(pre2,pre);
                pre[24]='t';
                pre[25]='e';
                pre[26]='s';
                pre[27]='t';
                endwin();
                FILE *fp=fopen(pre,"w");
                fclose(fp);
                NORMAL_mode(0,2,pre,1,0);
            }
            else{
                int i=29;
                while (file_name[i-29]!='\0')
                {
                    pre[i]=file_name[i-29];
                    pre2[i]=file_name[i-29];
                    i++;
                }
                // printw("[%s]",pre);
                // FILE *fp;
                // fp=fopen(pre,"w");
                // fclose(fp);
                int vas=insert_check(pre2);
                FILE *fp=fopen(pre,"w");
                if(vas==1){
                    save_file_txt(pre2);
                    fprintf(fp,"%s",c);
                }
                fclose(fp);
                endwin();
                if(vas==1)
                    NORMAL_mode(0,2,pre,0,0);
                else
                    NORMAL_mode(0,2,pre,1,0);

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
