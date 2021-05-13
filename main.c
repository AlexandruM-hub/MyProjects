#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

#define d 256
float NrPlag=0.;
int main()
{
    menu();
    return 0;
}

void menu(){
    system("cls");
    printf("___________________________________________________________________________\n");
    printf("|\t\t\t\t\t    Realizat de Mazureac Alexandru|\n");
    printf("|\t\t\t\t\t\t\t\t\t  |\n");
    printf("|\t\t\t\tMENU\t\t\t\t\t  |\n");
    printf("| 1) Verificarea plagiatului pentru 2 stringuri introduse de la trastiera;|\n");
    printf("| 2) Verificarea plagiatului din fisiere;\t\t\t\t  |\n");
    printf("| 3) Iesire din program.\t\t\t\t\t\t  |\n");
    printf("|_________________________________________________________________________|\n\n");
    printf(" \t\t Introduceti optiunea dorita > ");
    int x;
    scanf("%d",&x);
    system("cls");
    switch(x){
        case 1:{
            TwoStringPlagDetail();
            break;
        }
        case 2:{
            MenuText();
            break;
        }
        case 3:{
            exit(0);
        }
        default:{
            printf("Optiune inexistenta!\n");
            exit(1);
        }
    }

}

void search(char pat[], char txt[], int q,int M,int N){
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    for (i = 0; i < M-1; i++) h = (h*d)%q;
    for (i = 0; i < M; i++){
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }
    for (i = 0; i <= N - M; i++){
        if ( p == t ){
            for (j = 0; j < M; j++){
                if (txt[i+j] != pat[j])
                    break;
            }
            if (j == M){
                printf("Pattern found at index %d \n", i);
                NrPlag++;
            }
        }
        if ( i < N-M ){
            t = (d*(t - txt[i]*h) + txt[i+M])%q;
            if (t < 0)t = (t + q);
        }
    }
}

void TwoStringPlagDetail(){
    int LenStr2=FirstOpMenu(0);
    system("cls");
    char *txt=malloc(sizeof(char)*LenStr2);
    ScanStr(txt,false,LenStr2);
    int LenStr1=FirstOpMenu(1);
    char *pat=malloc(sizeof(char)*LenStr1);
    ScanStr(pat,true,LenStr1);
    system("cls");
    int x=MenuSearch();
    if(x==0)StringSearchDetail(pat,txt,true);
    else StringSearchSimple(pat,txt);
}

int MenuSearch(){
    Et1:system("cls");
    printf(" Cum doriti sa fie efectuata cautarea?\n");
    printf(" 1) Pe propozitii(cautare mai rapida);\n");
    printf(" 2) Pe un numar de caractere(cautare mai lenta).\n");
    printf("Introduceti optiunea dorita > ");
    int x;
    scanf("%d",&x);
    if(x==1)return true;
    else if(x==2)return false;
    else {
        printf("Optiune inexistenta! Alegeti inca odata!\n");
        delay(500000000);
        goto Et1;
    }
}

void StringSearchDetail(char *pat, char *txt){
    NrPlag=0;
    system("cls");
    printf("Introduceti numarul de caractere care doriti sa le comparati > ");
    int k;
    scanf("%d",&k);
    float z=(float)strlen(pat)/k;
    char aux[k+1];
    memset(aux, 0, k+1);
    strncpy(aux,pat,k);
    int o=k;
    int SizeM=0;
    while(z>0){
        if(strlen(aux)<o)break;
        search(aux,txt,101,strlen(aux),strlen(txt));
        strncpy(aux,&pat[k],o);
        k+=o;
        z--;
    }
    float result=100*NrPlag/(strlen(pat)/o);
    printf("\n_________________________________________\n");
    if (result==0)printf("Textul nu este plagiat!");
    else printf("Textul este plagiat %.2f procente!",result);
    printf("\n_________________________________________\n");
    printf("Pentru a va reintoarce la meniu tastati enter!\n");
    getch();
    menu();
}

void StringSearchSimple(char *pat, char *txt){
    system("cls");
    NrPlag=0;
    int NrSent=0;
    for(int i=0;i<strlen(pat);i++){
        if(pat[i]=='.'){
            NrSent++;
        }
    }
    char det[]=".";
    char *ptr=strtok(pat,det);
    int k=0;
    while(k<NrSent){
        search(ptr,txt,101,strlen(ptr)-1,strlen(txt)-1);
        ptr=strtok(NULL,det);
        k++;
    }
    float plag=(float)100*NrPlag/NrSent;
    printf("\n__________________________________________\n");
    if(plag==0.)printf("Textul nu este plagiat!");
    else printf("Textul este plagiat in proportie de %.2f!",plag);
    printf("\n__________________________________________\n");
    printf("Tastati enter pentru a va intoarce la meniu!\n");
    getch();
    menu();
}

void ScanStr(char *str,bool flag,int len){
    system("cls");
    if (flag)printf("Introduceti stringul(pattern): \n");
    else printf("Introduceti stringul(text): \n");
    getchar();
    fgets(str,len,stdin);
    fflush(stdin);
    for(int i=0;i<strlen(str)-1;i++){
        str[i]=tolower(str[i]);
    }
    return str;
}

int FirstOpMenu(int flag){
    system("cls");
    if(flag==1)printf("\tStringul 1(pattern) \n");
    else printf("\tStringul 2(text) \n");
    printf(" 1) Introducerea marimii stringului;\n");
    printf(" 2) Setarea lungimii stringului == 10000\n\n");
    printf("      Alegeti una din optiuni > ");
    int x;
    scanf("%d",&x);
    int res;
    system("cls");
    if(x==1){
        printf("Introduceti marimea stringului > ");
        scanf("%d",&res);
        printf("Lungimea stringului a fost setata ca %d!\n",res);
        printf("Atentie! Vor fi salvate primele %d caractere!",res);
        delay(999999999);
    }
    else if(x==2){
        res=10000;
        printf("Valoarea stringului a fost setata ca %d!\n",res);
        printf("Atentie! Vor fi salvate primele %d caractere!",res);
        delay(999999999);
    }
    else {
        printf("Optiune inexistenta! Introduceti inca o data");
        delay(500000000);
        FirstOpMenu(flag);
    }
    return res;
}

void delay(int x){
    for(int i=0;i<x;i++){

    }
}

void FilePos(char *pos,bool flag){
    fflush(stdin);
    system("cls");
    if (flag)printf("Introduceti adresa si denumirea fisierului (Pattern):\n");
    else printf("Introduceti adresa si denumirea fisierului (Text):\n");
    gets(pos);
    fflush(stdin);
    system("cls");
    return pos;
}

void MenuText(){
    system("cls");
    printf("Doriti sa comparati:\n");
    printf(" 1) Un string cu un fisier;\n");
    printf(" 2) Doua fisiere.\n");
    printf("Introduceti optiunea dorita > ");
    int x;
    scanf("%d",&x);
    switch(x){
        case 1:{
            StringText();
            break;
        }
        case 2:{
            FileText();
            break;
        }
        default:{
            printf("Optiune inexistenta! Alegeti inca o data!\n");
            delay(500000000);
            MenuText();
        }
    }
}

void StringText(){
    system("cls");
    printf("Stringul este:\n");
    printf(" 1) Textul cu care trebuie comparat patternul;\n");
    printf(" 2) Pattern.\n");
    printf("Introduceti optiunea dorita > ");
    int x;
    scanf("%d",&x);
    int k=--x;
    if (x<0 || x>1){
        printf("Optiune inexistenta! Introduceti din nou!\n");
        delay(500000000);
        StringText();
    }
    int len=FirstOpMenu(x);
    char *str=malloc(sizeof(char)*len);
    ScanStr(str,x,len);
    char *Position=malloc(sizeof(char)*80);
    FilePos(Position,!x);
    bool flag=MenuSearch();
    int fpsize;
    memory(Position,&fpsize);
    char *StrTxt=malloc(fpsize+1);
    FileOpen(StrTxt,Position,fpsize);
    if(flag && k==0)StringSearchSimple(StrTxt,str);
        else if(flag && k==1)StringSearchSimple(str,StrTxt);
        else if(!flag && k==0)StringSearchDetail(StrTxt,str);
        else StringSearchDetail(str,StrTxt);
}

void FileText(){
    char *Position=malloc(sizeof(char)*80);
    FilePos(Position,false);
    int fpsize;
    memory(Position,&fpsize);
    char *fstr=malloc(fpsize+1);
    FileOpen(fstr,Position,fpsize);
    char *Pos2=malloc(sizeof(char)*80);
    FilePos(Pos2,true);
    memory(Pos2,&fpsize);
    char *SecStr=malloc(fpsize+1);
    FileOpen(SecStr,Pos2,fpsize);
    bool flag=MenuSearch();
    /*printf("Strings from files :\n");
    puts(fstr);
    puts(SecStr);
    getch();*/
    if(flag)StringSearchSimple(SecStr,fstr);
    else StringSearchDetail(SecStr,fstr);
}

void FileOpen(char *StrTxt, char *Position, int fpsize){
    FILE *fp;
    fp=fopen(Position,"rb");
    if(fp==NULL){
        printf("Fisierul nu a putut fi deschis!\n");
        delay(500000000);
        menu();
    }
    fread(StrTxt,fpsize,1,fp);
    fclose(fp);
    StrTxt[fpsize]=0;
    system("cls");
    for(int i=0;i<fpsize;i++){
        StrTxt[i]=tolower(StrTxt[i]);
    }
    return StrTxt;
}

void memory(char *Position, int **fpsize){
    FILE *fp;
    fp=fopen(Position,"rb");
    if(fp==NULL){
        printf("Fisierul nu a putut fi deschis!\n");
        delay(500000000);
        menu();
    }
    fseek(fp,0,SEEK_END);
    *fpsize=ftell(fp);
    fclose(fp);
    return *fpsize;
}



