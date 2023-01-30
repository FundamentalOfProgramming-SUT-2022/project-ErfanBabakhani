#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include<dirent.h>

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
 int make_file_dir_name_grep(char a[],int k,char *d){
    int i=k,c=0;//c is the end of the path //filename
    int giume=0;
    while (1)
    {
        scanf("%c",&(*d));
        
        if(giume==0&&(*d)=='"'){//ignore the first giume
            giume++;
            continue;
        }
        if((*d)=='.'&&a[i-1]=='"'){//ignore the last giume in the file name
            a[i-1]='.';
            giume=0;
            continue;
        }
       if((*d)=='/'&&a[i-1]=='"'){//ignore the last giume in the directory name
            a[i-1]='\\';
            a[i]='\\';
            c=i-1;
            i++;
            giume=0;
            continue;
        }

        if((((*d)==' '|| (*d)=='\n')&&giume==0)||(giume!=0&&(*d)=='\n'))
            break;
        if((*d)=='/'){
            *d='\\';
            c=i;
            a[i]='\\';
            i++;
        }
        a[i]=*d;
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

//S find functions
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

void find_at_byword(char a[],int N,int *p_SL){
    int F=find_at(a,N,p_SL);
    printf("%d",find_byword(F));
    return;
}

void find_all_byword(char a[],int *p_SL){
    int k=0;
    *p_SL=-1;
    while (1)
    {
        k=find_star1(a,*p_SL+1,p_SL);
        if(k==-1)
            break;
        printf("%d,",find_byword(k));
    }
    return;
    
}
void find_all(char a[],int *p_SL){
    int k=0;
    *p_SL=-1;
    while (1)
    {
        k=find_star1(a,*p_SL+1,p_SL);
        if(k==-1)
            break;
        printf("%d,",k);
    }
    return;
    
}
//F find functions 

//S replace functions
void replace1(char first[],char seccond[],char file_name[],int *p_SL,char out[],int st){
    save_file_txt(file_name);
    st=find_star1(first,0,p_SL);
    int size=(*p_SL)-st+1;

    if(size<0){
        printf("No result to finding\n");
        exit(1);
        return 0;
    }

    remove_char(file_name,out,1,size,st);
    save_file_txt(file_name);
    // printf("%s",c);
    insert_txt(file_name,st,1,seccond);
    
}
void replace2(char first[],char seccond[],char file_name[],int *p_SL,char out[],int st){
    save_file_txt(file_name);
    st=find_star2(first,0,p_SL);
    int size=(*p_SL)-st+1;

    if(size<0){
        printf("No result to finding\n");
        return 0;
    }

    remove_char(file_name,out,1,size,st);
    save_file_txt(file_name);
    // printf("%s",c);
    insert_txt(file_name,st,1,seccond);
    
}
void replace_at(char first[],char seccond[],char file_name[],int *p_SL,char out[],int st,int at){
    save_file_txt(file_name);
    // printf("%d\n",at);
    st=find_at(first,at,p_SL);
    int size=(*p_SL)-st+1;
    // printf("st[%d] size[%d]",st,size);

    if(size<0){
        printf("No result to finding\n");
        return 0;
    }

    remove_char(file_name,out,1,size,st);
    save_file_txt(file_name);
    // printf("%s",c);
    insert_txt(file_name,st,1,seccond);
    // insert_txt(,)
}
void replace_all(char first[],char seccond[],char file_name[],char out[],int st,int at,int *p_SL){
    save_file_txt(file_name);
    int k=0;
    *p_SL=-1;
    // printf("waesrtrhd");
    // printf("\n%s\n",first);
    int num;
    num=find_count(first,p_SL);
    // printf("[%d]",num);
    if(num<1){
        printf("No result to replacing");
        exit(1);
    }
    
    while (num>0)
    {
        // printf("%d ",num);
        replace_at(first,seccond,file_name,p_SL,out,st,num);
        num--;
        // printf("%d,",k);
    }
    return;
    
}
//F replace function

//grep function
void grep2(char file_name[],char a[],int *p_SL,int E){

    int i=1;
    int k=0;
    char d;
    while (1)
    {
        read_line(i,file_name);

        if(c[0]=='\0')
            break;
        k=find_star1(a,0,p_SL);
        if(k==-1){
            i++;
            continue;
        }
        printf("%s: %s",(file_name+E-4),c);
        
        c[0]='\0';
        i++;
    }
    
    return;
}
int grep2_c(char file_name[],char a[],int *p_SL,int E){

    int i=1;
    int k=0;
    char d;
    while (1)
    {
        read_line(i,file_name);

        if(c[0]=='\0')
            break;
        k=find_star1(a,0,p_SL);
        if(k==-1){
            i++;
            continue;
        }
        // printf("%s: %s",(file_name+E-4),c);
        
        c[0]='\0';
        i++;
    }
    // printf("%s: %d",file_name+E-4,i-1);
    
    return i-1;
}
int grep2_I(char file_name[],char a[],int *p_SL,int E){

    int i=1;
    int k=0;
    char d;
    while (1)
    {
        read_line(i,file_name);

        if(c[0]=='\0')
            break;
        k=find_star1(a,0,p_SL);
        if(k==-1){
            i++;
            continue;
        }
        // printf("%s: %s",(file_name+E-4),c);
        
        c[0]='\0';
        i++;
    }
    printf("%s\n",file_name+E-4);
    
    return i-1;
}

int read_line(int line,char file_name[]){
    char S[1000]="";
    if(line<1){
        printf("invalid line");
        return;
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
    return 0;
}
//F grep function

//S undo
void undo_dir(char file_ful_name[],char file_ful_name_undo[]){

    int i=0;
    while (1)
    {
        if (file_ful_name[i]=='\0')
        {
            return ;
        }
        
        if(i==40){
            file_ful_name_undo[40]='u';
            file_ful_name_undo[41]='n';
            file_ful_name_undo[42]='d';
            file_ful_name_undo[43]='o';
            i=44;
            continue;
        }
        file_ful_name_undo[i]=file_ful_name[i];
        i++;
    }
    

}

void make_undo(char file_name[],char file_name_undo[],int end){// file_name is complete(mkdir /root/...) and undo name will be made
    // int end;
    FILE *fp;
    undo_dir(file_name,file_name_undo);
    // printf("%s",file_name_undo);
    make_dir(file_name_undo,end);
    save_file_txt(file_name+6);
    // printf("{%s}\n%s\n",file_name_undo+6,c);
    fp=fopen(file_name_undo+6,"w");
    fprintf(fp,"\0");
    fprintf(fp,"%s",c);
    fclose(fp);
    // printf("[%s]",c);
} 

void undo(char file_name[],char file_name_undo[],int end){
    FILE *fp;
    undo_dir(file_name,file_name_undo);
    // printf("%s",file_name_undo);
    // make_dir(file_name_undo,end);
    save_file_txt(file_name_undo+6);
    // printf("{%s}\n%s\n",file_name_undo+6,c);
    fp=fopen(file_name+6,"w");
    fprintf(fp,"\0");
    fprintf(fp,"%s",c);
    fclose(fp);
    // printf("[%s]",c);

}
//F undo

//S close pairs
void make_STD_text(char file_name[]){
    save_file_txt(file_name);
    char out[10000];
    char out2[10000];
    char out3[10000];
    int st;
    int at;
    int SL=0;
    int count;
    int posb;
    int posf;
    char first[10]="\n";
    char seccond[10]=" ";
    char r[10]="{";
    char l[10]="}";

    count=find_count(first,&SL);

    while(count>0){
        save_file_txt(file_name);
        replace_at(first,seccond,file_name,&SL,out,st,count);
        count--;
    }
    save_file_txt(file_name);
    SL=0;
    int pos;
    count=find_count(r,&SL);

    while (count>0)
    {
        pos=find_at(r,count,&SL);
        clean(file_name,pos);
        count--;
    }
    save_file_txt(file_name);
    SL=0;
    count=find_count(l,&SL);
    while (count>0)
    {
        pos=find_at(l,count,&SL);
        clean(file_name,pos);
        count--;
    }
    

    return;
}

void clean(char file_name[],int pos){
    int size=0;
    int size2=0;
    int j=1;
  
    save_file_txt(file_name);
    while (1)
    {
        if(c[pos-j]==' '){
            size++;
            j++;
        }
        else
            break;
    }
    
    j=1;
    while (1)
    {
        if(c[pos+j]==' ')
            size2++;
        else
            break;
        j++;
    }

    save_file_txt(file_name);
    char out[1000]="";

    remove_char(file_name,out,1,size2,pos+1);
    save_file_txt(file_name);
    
    char out2[1000]="";
    remove_char(file_name,out2,0,size,pos);
    save_file_txt(file_name);
} 

void Close(char file_name[],int R_Save[],int L_Save[]){
    int SL;
    save_file_txt(file_name);

    char R[10]="{";
    char L[10]="}";
    int N_R;
    int N_L;
    int N;
    N_R=find_count(R,&SL);    
    N_L=find_count(L,&SL);
    N=N_R;

    if(N>N_L)
        N=N_L;
    int i=1;
    
    while (i<=N)
    {
        R_Save[i-1]=find_at(R,i,&SL);
        i++;
    }
    i=1;
    while (i<=N)
    {
        L_Save[i-1]=find_at(L,i,&SL);
        i++;
    }

    return;
    
}

void insert_N_tab(char file_name[],int pos,int n){

    int i=0;
    char d;
    int k;
    char end_part[10]="    ";

    while (i<n)
    {
        save_file_txt(file_name);

        insert_txt(file_name,pos,1,end_part);
        i++;
    }
    return;
    
}

void S_and_L(char file_name[],int SL,int i,int *start,int *finish){
    
    *finish=SL-4*i-2;

    int j=*finish;
    save_file_txt(file_name);
    while (c[j]!='\n')
    {
        j--;        
    }
    j+=((i+1)*4+1);
    *start=j;
    return;

}

int mearg(int R_save[],int L_save[],int R_L_save[],int N){
    int i=0;
    int j=0;
    int k=0;

    while (i<N&&j<N)
    {
        if(R_save[i]>L_save[j]){
            R_L_save[k]=L_save[j];
            j++;
        }
        else{
            R_L_save[k]=R_save[i];
            i++;
        }
        k++;
    }
    while (i<N)
    {
        R_L_save[k]=R_save[i];
        i++;
        k++;
    }
    while (j<N)
    {
        R_L_save[k]=L_save[j];
        j++;
        k++;
    }

    return k-1;
    
}

void R_fix2(char file_name[],int *C_N,int rep){
  
    int *back_space=(int *)calloc(1000,sizeof(int));
    int *back_N=(int *)calloc(1000,sizeof(int));

    char space[10]=" ";
    char new_line[10]="\n";

    char out[1000]="";
    int R_Save[1000];
    int L_Save[1000];
    int R_L_Save[1000];
    int k;//the end index of R_L_save
    
    int N_R;
    int N_L;
    int N;
    int SL;
    char R[5]="{";
    char L[5]="}";
    save_file_txt(file_name);

    N_R=find_count(R,&SL);    
    N_L=find_count(L,&SL);
    N=N_R;

    if(N>N_L){
        N=N_L;
    }

    Close(file_name,R_Save,L_Save);

    k=mearg(R_Save,L_Save,R_L_Save,N);

    int i=k;
    int count=0;
    save_file_txt(file_name);
    
    while (i>=0)
    {
        if(c[R_L_Save[i]]=='}'){
            count++;
        }
        else if(c[R_L_Save[i]]=='{'){
            count--;
        }
        if(count==0&&c[R_L_Save[i-1]]=='}'&&i>0){

            back_N[*C_N]=R_L_Save[i-1];
            back_space[*C_N]=R_L_Save[i];
            (*C_N)+=1;
        }
        i--;
    }

        save_file_txt(file_name);// these are the last
        insert_txt(file_name,R_L_Save[k],1,new_line);
        save_file_txt(file_name);
        insert_N_tab(file_name,R_L_Save[k],(rep)-1);

    save_file_txt(file_name);
    i=0;
    while (i<*(C_N))
    {

        if(c[back_space[i]+1]!='}'&&c[back_space[i]+1]!='\n'){

            save_file_txt(file_name);
            insert_N_tab(file_name,back_space[i]+1,rep);

            save_file_txt(file_name);
            insert_txt(file_name,back_space[i]+1,1,new_line);
        }
        if(c[back_space[i]-1]!='}'&&c[back_space[i]-1]!='\0'&&c[back_space[i]+1]!='{'){
            save_file_txt(file_name);
            insert_txt(file_name,back_space[i],1,space);
        }
        save_file_txt(file_name);

        insert_N_tab(file_name,back_N[i]+1,(rep)-1);
        save_file_txt(file_name);
        insert_txt(file_name,back_N[i]+1,1,new_line);
        save_file_txt(file_name);

        insert_txt(file_name,back_N[i],1,new_line);
        save_file_txt(file_name);
        insert_N_tab(file_name,back_N[i]+1,(rep)-1);
        save_file_txt(file_name);


        i++;
    }
            save_file_txt(file_name);
            insert_N_tab(file_name,R_L_Save[0]+1,(rep));
            save_file_txt(file_name);
            insert_txt(file_name,R_L_Save[0]+1,1,new_line);
        if(c[R_L_Save[0]-1]!='\0'&&c[R_L_Save[0]-2]!=' '){
            save_file_txt(file_name);
            insert_txt(file_name,R_L_Save[0],1,space);
        }

    free(back_N);
    free(back_space);
    return;

}

void Close_pair(char file_name[],int rep,int index,char R_Save[],char L_Save[]){

    if(R_Save[0]==-1||L_Save[0]==-1){
        return;
    }

    int C_N=0;

        int *back_space=(int *)calloc(1000,sizeof(int));
        int *back_N=(int *)calloc(1000,sizeof(int));
        char space[10]=" ";
        char new_line[10]="\n";

        char out[1000]="";
        int R_L_Save[1000];
        int k;//the end index of R_L_save
        

        int N=index;
        int SL;
        char R[5]="{";
        char L[5]="}";
        save_file_txt(file_name);

        k=mearg(R_Save,L_Save,R_L_Save,N);
        int i=k;
        int count=0;
        save_file_txt(file_name);

        while (i>=0)
        {
            if(c[R_L_Save[i]]=='}'){
                count++;
            }
            else if(c[R_L_Save[i]]=='{'){
                count--;
            }
            if(count==0&&c[R_L_Save[i-1]]=='}'&&i>0){
                back_N[C_N]=R_L_Save[i-1];
                back_space[C_N]=R_L_Save[i];
                (C_N)+=1;
            }
            i--;
        }

        save_file_txt(file_name);// these are the last
        save_file_txt(file_name);
        insert_N_tab(file_name,R_L_Save[k],(rep)-1);
        save_file_txt(file_name);
        insert_txt(file_name,R_L_Save[k],1,new_line);
        i=0;
        while (i<(C_N))
        {

            if(c[back_space[i]+1]!='}'&&c[back_space[i]+1]!='\n'){
                save_file_txt(file_name);
                insert_N_tab(file_name,back_space[i]+1,rep);
                save_file_txt(file_name);
                insert_txt(file_name,back_space[i]+1,1,new_line);
            }
            if(c[back_space[i]-1]!='}'&&c[back_space[i]-1]!='\0'&&c[back_space[i]+1]!='{'){
                save_file_txt(file_name);
                insert_txt(file_name,back_space[i],1,space);
            }
            save_file_txt(file_name);
            insert_N_tab(file_name,back_N[i]+1,(rep)-1);
            save_file_txt(file_name);
            insert_txt(file_name,back_N[i]+1,1,new_line);
            save_file_txt(file_name);
            insert_txt(file_name,back_N[i],1,new_line);
            save_file_txt(file_name);
            insert_N_tab(file_name,back_N[i]+1,(rep)-1);
            save_file_txt(file_name);

            i++;
        }
        save_file_txt(file_name);
        insert_N_tab(file_name,R_L_Save[0]+1,(rep));
        save_file_txt(file_name);
        insert_txt(file_name,R_L_Save[0]+1,1,new_line);
        if(c[R_L_Save[0]-1]!='\0'&&c[R_L_Save[0]-2]!=' '){
                save_file_txt(file_name);
                insert_txt(file_name,R_L_Save[0],1,space);
        }

        free(back_N);
        free(back_space);
    
    return;
}

int find_pair(char file_name[],int i,int *start,int *finish){
    char test1[20][100];
    strcpy(test1[0],"{\n *\n}");// the contents of reep 1
    strcpy(test1[1],"    *{\n    *\n    }");// the contents of reep 2
    strcpy(test1[2],"        *{\n        *\n        }");// the cntesnts of reep 3
    strcpy(test1[3],"            *{\n            *\n            }");// the contents of reep4
    strcpy(test1[4],"                *{\n                *\n                }");// the contents of reep5
    strcpy(test1[5],"                    *{\n                    *\n                    }");// the contents of reep6
    strcpy(test1[6],"                        *{\n                        *\n                        }");// the contents of reep7 
    strcpy(test1[7],"                            *{\n                            *\n                            }");// the contents of reep8 
    strcpy(test1[8],"                                *{\n                                *\n                                }");// the contents of reep9 

    char *a="{";
    char *b="}";
    int SL;
    int SL2;
    int SL3;
    int first;
    int count;
    int *R_Save=(int *)calloc(1000,sizeof(int));
    int *L_Save=(int *)calloc(1000,sizeof(int));
    R_Save[0]=-1;
    L_Save[0]=-1;
    
    save_file_txt(file_name);
    count=find_count(test1[i],&SL2);
    if(count==0){
        exit(1);
    }
    int j=count;
    SL2=-1;
    while (j>0)
    {

        save_file_txt(file_name);
        find_at(test1[i],j,&SL);

        S_and_L(file_name,SL,i,start,finish);
        int r=*start;
        int l=*start;
        int index_r=0;
        int index_l=0;
        while (1)
        {
            r=find_star1(a,r,&SL2)+1;
            if(SL2>*finish||r==0){
                break;
            }
            if(SL2<=*finish){
                R_Save[index_r]=SL2;
                index_r++;
            }
            if(index_r==20)
                break;

        }
        while (1)
        {
            l=find_star1(b,l,&SL3)+1;
            if(SL3>*finish||l==0){
                break;
            }
            if(SL3<=*finish){
                L_Save[index_l]=SL3;
                index_l++;
            }
            if(index_l==20)
                break;   
        }
        
        Close_pair(file_name,i+2,index_r,R_Save,L_Save);
        
        free(R_Save);
        free(L_Save);
        int *R_Save=(int *)calloc(1000,sizeof(int));
        int *L_Save=(int *)calloc(1000,sizeof(int));
        R_Save[0]=-1;
        L_Save[0]=-1;
        j--;
    }
    
    return count;
}

void make_L_R_save(char file_name[]){
    int i=0;
    int start;
    int finish;
    while (1)
    {

        find_pair(file_name,i,&start,&finish);
        i++;
    }
    
}
//F close pair

//S compare txt
void compare(char file_name[],char file_name2[]){
    
    char save1[1000]="";
    char save2[1000]="";
    char a[10]="\n";
    int SL=0;
    int count1;
    int count2;
    int pos1;
    int pos2;
    save_file_txt(file_name);
    count1=find_count(a,&SL);
    SL=0;
    save_file_txt(file_name2);
    count2=find_count(a,&SL);
    count1++;
    count2++;
    int N=count1;
    if(N>count2)
        N=count2;
    // printf("count1=%d count2=%d\n",count1,count2);
    int i=1;
    strcpy(c,"");
    while(i<=N){
        SL=0;
        read_line(i,file_name);
        pos1=find_star1(a,0,&SL);
        if(pos1!=-1)
            c[pos1]='\0';
        strcpy(save1,c);
        strcpy(c,"");
        read_line(i,file_name2);
        SL=0;
        pos2=find_star1(a,0,&SL);
        if(pos2!=-1)
            c[pos2]='\0';
        // printf("{%d %d}",pos1,pos2);
        strcpy(save2,c);
        strcpy(c,"");
        if(strcmp(save1,save2)!=0){
            printf("============ #%d ============\n",i);
            printf("%s\n",save1);
            printf("%s\n",save2);
        }
        i++;
    }    
    strcpy(c,"");

    if(i<=count1){
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",i,count1);
        while (i<=count1)
        {
            SL=0;
            read_line(i,file_name);
            pos1=find_star1(a,0,&SL);
            if(pos1!=-1)
                c[pos1]='\0';
            strcpy(save1,c);
            strcpy(c,"");
            printf("%s\n",save1);
            i++;
        }
    }
    if(i<=count2){
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",i,count2);
        while (i<=count2)
        {
            SL=0;
            read_line(i,file_name2);
            pos2=find_star1(a,0,&SL);
            if(pos2!=-1)
                c[pos2]='\0';
            strcpy(save2,c);
            strcpy(c,"");
            printf("%s\n",save2);
            i++;
        }
    }

    return;
}
//F compare txt

//S tree
int isDirectoryEmpty(char *dirname) {
  int n = 0;
  struct dirent *d;
  DIR *dir = opendir(dirname);
  if (dir == NULL) //Not a directory or doesn't exist
    return 1;
  while ((d = readdir(dir)) != NULL) {
    if(++n > 2)
      break;
  }
  closedir(dir);
  if (n <= 2) //Directory Empty
    return 1;
  else
    return 0;
}


void make_file_dep_name(char file_name1[],char file_nam2[],char name[]){
    strcpy(file_nam2,file_name1);
    int pos=strlen(file_name1);
     
    file_nam2[pos]='\\';
    pos++;
    file_nam2[pos]='\\';
    pos++;
    int k=strlen(name);
    int i=0;
    while (i<k)
    {
        file_nam2[pos+i]=name[i];
        i++;
    }
    file_nam2[pos+i]='\0';
    
    return;
}

void show_enrtry(char file_name[],int dep,int end_dep){
    if(dep>end_dep){
        
        return;
    }

    DIR *d;
    struct dirent *dir;
    char NAME[300]="";
    unsigned int type;
    char file_name2[300];
    d = opendir(file_name);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        
        {
            strcpy(NAME,dir->d_name);
            type=dir->d_type;
            if(strcmp(NAME,".")==0||strcmp(NAME,"..")==0){
                continue;
            }
            if(type==0){

                if(dep>1){
                    char b[10]="|";

                    show_dep_space(dep);
                    printf("%s_______",b);

                    printf("%s\n",NAME);
                }
                if(dep==1){
                    printf("%s\n",NAME);
                }
                continue;
            }
            if(type==16){
                if(dep>1){
                    char b[10]="|";

                    show_dep_space(dep);
                    printf("%s_______",b);
                    printf("%s\n",NAME);
                }
                if(dep==1){
                    printf("\n%s\n",NAME);
                }

                make_file_dep_name(file_name,file_name2,NAME);

                int check=isDirectoryEmpty(file_name2);
                if(check==1){
                    continue;
                }
                    
                show_enrtry(file_name2,dep+1,end_dep);
                strcpy(file_name2,"");
            }
            
        }
        closedir(d);
    }
    
    return;
}

void show_dep_space(int dep){
    
    char a[20]="_______";
    char b[20]="|";
    char f[20]="        ";

    int i=0;
    while (i<dep-2)
    {
        printf("%s",f);
        i++;
    }

    return;
    
}
//F tree

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

        make_undo(file_name,file_name_undo,end);
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
        make_undo(file_name,file_name_undo,end);
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
        make_undo(file_name,file_name_undo,end);
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
    
    else if(strcmp(b,"find --str")==0){
        
        char str[10]="";
        char str1[10]="";
        char str2[10]="";
        char str3[10]="";
        char str4[10]="";
        char d;
        char end_part[1000]="";
        
        int at=0; 
        int SL=-1;
        
        // scanf(" %s");
        inserted_string(end_part,0);
        scanf(" %s ",str);
        end=make_file_dir_name(file_name,38);
        insert_check(file_name+6);
        save_file_txt(file_name+6);
        scanf("%c",&d);
        
        if(d=='-'){
            // printf("Hrllo");
            str1[0]=d;
            int j=1;
            while (1)
            {
                scanf("%c",&d);
                if(d=='\n'||d==' '){
                    
                    if(strcmp(str1,"--at")==0)
                        scanf("%d ",&at);
                    break;
                }
                str1[j]=d;
                j++;
                printf("%c",str1[j]);
                // if(d==' ')
                    // printf("dfn\n");
                        
            }
            if(d==' '){
                j=0;
                while (1)
                {
                    scanf("%c",&d);
                    if(d=='\n'||d==' '){
                        
                        if(strcmp(str2,"--at")==0)
                            scanf("%d ",&at);
                        break;
                    }
                    str2[j]=d;
                    j++;   
                }
            
            }
            
            if(d==' '){
                j=0;
                while (1)
                {
                    scanf("%c",&d);
                    if(d=='\n'||d==' '){
                        
                        if(strcmp(str3,"--at")==0)
                            scanf("%d ",&at);
                        break;
                    }
                    str3[j]=d;
                    j++;   
                }
            
            }
            
            if(d==' '){
                j=0;
                while (1)
                {
                    scanf("%c",&d);
                    if(d=='\n'||d==' '){
                        
                        if(strcmp(str4,"--at")==0)
                            scanf("%d ",&at);
                        break;
                    }
                    str4[j]=d;
                    j++;   
                }
            
            }
            
        }
        
        if(str1[0]=='\0'&&str2[0]=='\0'&&str3[0]=='\0'&&str4[0]=='\0'){
            // printf("...");
            if(end_part[0]!='*')
                printf("%d\n",find_star1(end_part,0,&SL));
            else
            printf("%d",find_star2(end_part,0,&SL));
        }
        
        else if((strcmp(str1,"--buyword")==0&&strcmp(str2,"--at")==0&&str3[1]=='\0')||(strcmp(str1,"--at")==0&&strcmp(str2,"--buyword")==0&&str3[1]=='\0')){
            // printf("[--%d--]\n",at);
            find_at_byword(end_part,at,&SL);
        }
        else if((strcmp(str1,"--buyword")==0&&strcmp(str2,"--all")==0&&str3[1]=='\0')||(strcmp(str1,"--all")==0&&strcmp(str2,"--buyword")==0&&str3[1]=='\0')){
            find_all_byword(end_part,&SL);
        }
        
        else if(strcmp(str1,"--all")==0&&str2[1]=='\0'){
            find_all(end_part,&SL);
        }
        else if(strcmp(str1,"--buyword")==0&&str2[1]=='\0'){
            printf("%d",find_byword(0));
        }
        else if(strcmp(str1,"--count")==0&&str2[1]=='\0'){
            printf("%d",find_count(end_part,&SL));
        }
        else if(strcmp(str1,"--at")==0&&str2[1]=='\0'){
            printf("%d",find_at(end_part,at,&SL));
        }
        else{
            printf("\nyou can only combine (at and buyword) or (all and buyword) other combenition are not logic \nand maybe you want two commands so please input them seperatly\nfor example (at and count) can't combine but you can input them seperatly");
            printf("\n\n!!Please check your command and try again!!\n\n");
        }

        // printf("\n{%s}{%s}{%s}{%s}\n",str1,str2,str3,str4);
        // printf("(%s)\n",end_part);
        // printf("(%s)",c);
        
    }
    else if(strcmp(b,"replace --str1")==0){
        char first[2000]="";
        char seccond[2000]="";
        char out[2000]="";
        char str[10]="";
        char str2[10]="";
        char str3[10]="";
        char str4[10]="";
        int SL=-10;
        int st;
        int at;
        char d;
        inserted_string(first,0);
        scanf("%s ",str);
        inserted_string(seccond,0);
        scanf("%s ",str2);
        
        end=make_file_dir_name(file_name,38);
        insert_check(file_name+6);
        
        scanf("%c",&d);
        if(d!='\n'){
            str3[0]=d;
            scanf("%s",str3+1);
            scanf("%c",&d);
            if(d==' '){
                scanf("%d",&at);
                scanf("%c",&d);
                if(d!='\n')
                    scanf("%s",str4);
            }
        }
        // printf("%s,%s,%s,%s\n",first,seccond,str3,file_name+6);
        if(str3[1]!='\0',str4[1]!='\0'){
            printf("Wrong command and combinition check your command and try again");
            return 0;
        }
        if(str3[1]=='\0'){
            if(first[0]!='*'){
                make_undo(file_name,file_name_undo,end);
                replace1(first,seccond,file_name+6,&SL,out,st);
            }
            else{
                make_undo(file_name,file_name_undo,end);
                replace2(first,seccond,file_name+6,&SL,out,st);                
            }
        }
        else if(strcmp(str3,"--at")==0){
                make_undo(file_name,file_name_undo,end);
                replace_at(first,seccond,file_name+6,&SL,out,st,at);
        }
        else if(strcmp(str3,"--all")==0){
            // printf("\\%s\\\n",first);
            // printf("\\%s\\\n",c);
            // int num=find_count(first,&SL);
            // printf("((%d)))\n",num);
            make_undo(file_name,file_name_undo,end);
            replace_all(first,seccond,file_name+6,out,st,at,&SL);
        
        }
        // save_file_txt(file_name+6);
        printf("Sccess full command");

    }
    
    else if(strcmp(b,"grep --str")==0){
        char str[10]="";
        char a[1000]="";
        int end;
        int save[100];
        int SL;
        char d;      
        inserted_string(a,0);  
        scanf(" %s ",str);


    while (1)
    {
        end=make_file_dir_name_grep(file_name,38,&d);
        grep2(file_name+6,a,&SL,end);
        if(d=='\n')
            break;
    }

    }
    else if (strcmp(b,"grep -c")==0)
    {
        
        char str[10]="";
        char str1[10]="";
        char a[1000]="";
        int end;
        int save[100];
        int SL;
        char d;      
        scanf(" %s ",str1);
        inserted_string(a,0);  
        scanf("%s ",str);

        int NUM=0;
        while (1)
        {
            end=make_file_dir_name_grep(file_name,38,&d);
            NUM+=grep2_c(file_name+6,a,&SL,end);
            if(d=='\n')
                break;
        }
        printf("%d",NUM);  
    }
    else if(strcmp(b,"grep -I")==0)
    {
        char str[10]="";
        char str1[10]="";
        char a[1000]="";
        int end;
        int save[100];
        int SL;
        char d;      
        scanf(" %s ",str1);
        inserted_string(a,0);  
        scanf("%s ",str);   
        while (1)
        {
            end=make_file_dir_name_grep(file_name,38,&d);
            grep2_I(file_name+6,a,&SL,end);
            if(d=='\n')
                break;
        }
    }
    else if(strcmp(b,"undo --file")==0){
        end=make_file_dir_name(file_name,38);
        // printf("[%s]",file_name);
        insert_check(file_name+6);
        undo(file_name,file_name_undo,end);

    }
    else if(strcmp(b,"auto -indent")==0){
        char d;
        int C_N=0;
        int rep=1;
        
        int end=make_file_dir_name_grep(file_name,38,&d);
        insert_check(file_name+6);
        // printf("%s",file_name+6);
        // int save_SL[100];
        make_undo(file_name,file_name_undo,end);
        
        make_STD_text(file_name+6);
        R_fix2(file_name+6,&C_N,rep);
        make_L_R_save(file_name+6);

    }
    else if (strcmp(b,"compare --files")==0)
    {
        int end2;
        char d;
        char file_name2[1000]="mkdir C:\\\\Users\\\\Technokade\\\\Documents";
        end=make_file_dir_name_grep(file_name,38,&d);
        end2=make_file_dir_name_grep(file_name2,38,&d);
        compare(file_name+6,file_name2+6);
    }
    else if(strcmp(b,"tree --dep")==0){
        int end_dep;
        scanf("%d",&end_dep);
        printf("%d",end_dep);
        
        char NAME[300]="";
        int dep;
        char file_name1[300]="C:\\\\Users\\\\Technokade\\\\Documents\\\\root";
        show_enrtry(file_name1,1,end_dep);

    }

    
    
    else{

        printf("invalid command");
    }






    return 0;
}

