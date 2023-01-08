#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>


 void make_dir(char file_ful_name[],int end){

    char dir_ful_name[1000];
    int j=0;
    for(j;j<end;j++){
        dir_ful_name[j]=file_ful_name[j];
    }
    //printf("[%s]",dir_ful_name);
    DIR* di=opendir((dir_ful_name+6));

    if(!di){

        system(dir_ful_name);

    }
    else {

    }
    closedir(di);

}

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


 int make_string(char a[],int k){
    int i=k,c=0;//c is the end of the path//filename
    char d;
    while (1)
    {
        scanf("%c",&d);
        if(d==' '|| d=='\n')
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



 void make_file(char file_ful_name[]){
    FILE *fp;
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
 }


int main(){

    FILE * a;
    char b[1000]="";
    char file_name[1000]="mkdir C:\\\\Users\\\\Technokade\\\\Documents\\\\";
    char create[100]= "createfile --file";
    int end;
    //printf("%s\n",b);
    //printf("%s\n",create);
    make_command(b);
    end=make_string(file_name,40);
    //printf("%s",b);
    //printf("\n");
    if(strcmp(b,create) == 0){ //0 int the strcmp func means that tow string are equal

        make_dir((file_name),end);
        make_file((file_name+6));

    }
    else{

        printf("invalid command");
    }





    return 0;
}

