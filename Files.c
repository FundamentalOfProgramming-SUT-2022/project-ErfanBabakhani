#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

char c[2000]="";
char cp[2000]="";

//command
char* make_command(char a[1000]){ //this is the function of making string

    //fgets(a,1000,stdin);

    int i=0,c=0;
    char d;
    while (1)
    {
        scanf("%c",&d);
        if(d==' ')
            {c++;}
        if(d=='\n')
            {break;}
        if(c==2)
            {break;}
        a[i]=d;
        i++;
    }


    return a;
 }
//command

//S making the file_name("mkdir C:\\\\Users\\\\Technokade\\\\Documents...")
int make_file_dir_name(char a[],int k){
    int i=k,c=0;//c is the end of the path //filename
    char d;
    int giume=0;
    while (1)
    {
        scanf("%c",&d);
        
        if(giume==0&&d=='"'){//ignore the first giume
            giume++;
            continue;
        }
        if(d=='.'&&a[i-1]=='"'){//ignore the last giume in the file name
            a[i-1]='.';
            giume=0;
            continue;
        }
       if(d=='/'&&a[i-1]=='"'){//ignore the last giume in the directory name
            a[i-1]='\\';
            a[i]='\\';
            c=i-1;
            i++;
            giume=0;
            continue;
        }

        if(((d==' '|| d=='\n')&&giume==0)||(giume!=0&&d=='\n'))
            break;
        if(d=='/'){
            d='\\';
            c=i;
            a[i]='\\';
            i++;
        }
        a[i]=d;
        i++;
    }

    return c;
 }

int inserted_string(char a[],int k){
    
    int i=k,c=0;//c is the end of the path //filename
    char d,b;
    int giume=0;
    while (1)
    {
        scanf("%c",&d);
        
        if(giume==0&&d=='"'){//ignore the first giume
            giume++;
            continue;
        }
        
        if (d==' ')
        {
            if(a[i-1]=='"'){
                a[i-1]='\0';
                break;
            }
            if(giume==0)
                break;
        }


        if(d=='\\'){
            a[i]=d;//i
            i++;
            scanf("%c",&d);//i
            scanf("%c",&b);//i+1
            if(b=='n'&&d=='\\'){// \\n
                a[i]=b;
                i++;
                continue;
            }
            else if(d=='n'){// \n
                a[i-1]='\n';
                a[i]=b;
                i++;
                continue;
            }
            else if(d=='\\'){
                a[i]=b;
                i++;
                continue;
            }
            else{
                a[i]=d;
                i++;
                a[i]=b;
                i++;
                continue;
            }

        }
        

        a[i]=d;
        i++;
        
    }

    return c;
 }
//F making the file_name("mkdir C:\\\\Users\\\\Technokade\\\\Documents...")

////S insert funcions
FILE* insert_check(char file_ful_name[]){//This is for checking the existance of File
    
    FILE *fp;
    fp=fopen(file_ful_name,"r");

    if(!fp){

       printf("We don't have this file please first make it");
        exit(1);
    }
    else{

            fclose(fp);
            return fp;
    }

    fclose(fp);
    return fp;
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
//F insert funcions

//S create funcions
 
void make_dir(char file_ful_name[],int end){

    char dir_ful_name[1000];
    int j=0;
    for(j;j<end;j++){
        dir_ful_name[j]=file_ful_name[j];
    }
    dir_ful_name[j]='\0';
    // printf("%s\n",dir_ful_name);
    
    DIR* di=opendir((dir_ful_name+6));

    if(!di){
       
        system(dir_ful_name);

    }
    else {

    }
    closedir(di);

}


FILE* make_file(char file_ful_name[]){
    FILE *fp;
    printf("%s\n",file_ful_name);
    fp=fopen(file_ful_name,"r");

    if(!fp){

            fp=fopen(file_ful_name,"w");
            printf("we make a file successfuly");
    }
    else{

            printf("This file is already exist");
            return;
    }

    fclose(fp);
    return fp;
 }
 //F create fuctions

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
//F remove function

//S copy function
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
//F copy & cut & paste function


int main(){

    FILE * fp;
    char b[1000]="";
    char file_name[1000]="mkdir C:\\\\Users\\\\Technokade\\\\Documents";
    char file_name_copy[1000]="";// 44
    char file_name_undo[1000]="mkdir C:\\\\Users\\\\Technokade\\\\Documents\\\\undo";// 44 
    int end;

    make_command(b);

    
    
    if(strcmp(b,"createfile --file") == 0){ //0 int the strcmp func means that tow string are equal
        end=make_file_dir_name(file_name,38);// we make a file_name which contain("mkdir C:\\\\Users\\\\Technokade\\\\Documents(and user input string)") we write from 38 index 
        make_dir((file_name),end);
        fp=make_file((file_name+6));

    }


    else if(strcmp(b,"insertstr --file")==0){
        char str[10];
        end=make_file_dir_name(file_name,38);// we make a file_name which contain("mkdir C:\\\\Users\\\\Technokade\\\\Documents(and user input string)") we write from 38 index 
        insert_check(file_name+6);

        scanf("%s ",str);
        
       
        if(strcmp(str,"--str")!=0){
            printf("invalid command");
            return 0;
        }
        
        char end_part[1000]="";
        inserted_string(end_part,0);
        
        char str2[10]="";

        scanf(" %s ",str2);
        if(strcmp(str2,"--pos")!=0){
            printf("invalid command");
            return 0;
        }
        int i=0;
        int pos=0,line=0;
        char d='\0';
        int k=0;//k=0 is for pos and 1 is for line
        while (1)
        {
            scanf("%c",&d);
            if(d=='\n'||d==' ')
                break;
            if(d==':'){
                k++;
                continue;
            }
            if(k==0){
                pos+=d-'0';
                pos*=10;
            }
            else{
                line+=d-'0';
                line*=10;
            }

        }
        
        line/=10;
        pos/=10;

        save_file_txt(file_name+6);
        int j=0;
        insert_txt((file_name+6),pos,line,end_part);
        

    }
    else if(strcmp(b,"cat --file")==0){
        end=make_file_dir_name(file_name,38);
        insert_check(file_name+6);
        save_file_txt(file_name+6);
        int i=0;
        while (1)
        {
            if(c[i]=='\0')
                break;
            printf("%c",c[i]);
            i++;
        }
        

    }
    else if(strcmp(b,"removestr --file")==0){
        end=make_file_dir_name(file_name,38);
        insert_check(file_name+6);
        save_file_txt(file_name+6);
        char str[10]="";
        char d;
        int line;
        int pos;
        int size;
        int i;
        scanf("%s %d%c%d %s %d %c%c",str,&pos,&d,&line,str,&size,&d,&d);
        if(d=='b')
            i=0;
        else if(d=='f')
            i=1;
        char out[2000]="";
        if(line!=1)
            pos+=finde_line_pos(pos,line);
        remove_char((file_name+6),out,i,size,pos);

        
    }
    else if (strcmp(b,"copystr --file")==0)
    {
        
        end=make_file_dir_name(file_name,38);
        insert_check(file_name+6);
        save_file_txt(file_name+6);
        copy_dir(file_name,file_name_copy);
        make_dir(file_name_copy,end);
                
        char str[10]="";
        char d;
        int line;
        int pos;
        int size;
        int i;
        scanf("%s %d%c%d %s %d %c%c",str,&pos,&d,&line,str,&size,&d,&d);
        if(d=='b')
            i=0;
        else if(d=='f')
            i=1;
        char out[1000]="";
        if(line!=1)
            pos+=finde_line_pos(pos,line);
        copy_str((file_name_copy+6),out,i,size,pos);
    }
    
    else if(strcmp(b,"cutstr --file")==0){
        
        end=make_file_dir_name(file_name,38);
        insert_check(file_name+6);
        save_file_txt(file_name+6);
        copy_dir(file_name,file_name_copy);
        make_dir(file_name_copy,end);
        
        char str[10]="";
        char d;
        int line;
        int pos;
        int size;
        int i;
        scanf("%s %d%c%d %s %d %c%c",str,&pos,&d,&line,str,&size,&d,&d);
        if(d=='b')
            i=0;
        else if(d=='f')
            i=1;
        char out[2000]="";
        char out2[2000]="";
        if(line!=1)
            pos+=finde_line_pos(pos,line);
        
        copy_str((file_name_copy+6),out,i,size,pos);
        // FILE *fp=fopen(file_name+6,"w");
        // fprintf(fp,"\0");
        // fclose(fp);
        remove_char(file_name+6,out2,i,size,pos);
    }
    
    else if(strcmp(b,"pastestr --file")==0){
        end=make_file_dir_name(file_name,38);
        insert_check(file_name+6);
        save_file_txt(file_name+6);
        copy_dir(file_name,file_name_copy);
        make_dir(file_name_copy,end);

        char str[10]="";
        // char end_part[2000]="";
        char d;
        int line;
        int pos;
        scanf("%s %d%c%d",str,&pos,&d,&line);
        save_file_txt_copy(file_name_copy+6);
        insert_txt((file_name+6),pos,line,cp);

    }
    
    else if(strcmp(b,"find --str")){
        
        end=make_file_dir_name(file_name,38);
        insert_check(file_name+6);
        save_file_txt(file_name+6);

    }
    
    else{

        printf("invalid command");
    }






    return 0;
}

