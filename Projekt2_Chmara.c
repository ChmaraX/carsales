#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct zaznam
{
	char oddelovac[2];
	char kategoria[50];
	char znacka[50]; 
	char predajca[100];
	int cena;
	int rok;
	char stav[200];
	struct zaznam *dalsi;
}zaznam;



zaznam *nacitaj(zaznam *zaciatok, int n);
int vypis(zaznam *zaciatok, int n, int inc, int dec);
void pridaj(zaznam *zaciatok);
void hladaj_cena(zaznam *zaciatok);
int vymaz(zaznam *zaciatok);
void del(zaznam *zaciatok, int n);
void exit_p(zaznam *zaciatok);



int main()
{

zaznam *zaciatok = NULL; 

char volba;
int inc=0;
int dec=0;
int n;

n=pocetzaznamov();



do
{
	scanf("%c",&volba);
	
	switch(volba)
	{
		case 'n': zaciatok = nacitaj(zaciatok,n);break;
		case 'v': vypis(zaciatok,n,inc,dec);break;    // dec/inc zvaèšenie/zmenšenie vypisu v zavislosti od poètu pridanych/vymazanych zaznamov
		case 'p': pridaj(zaciatok); inc++; break;
		case 'z': dec=dec+vymaz(zaciatok); break;    //dec predstavuje hodnotu o ko¾ko menej zaznamov sa ma vypísa vo funkcii vypis -> zavisi od poètu vymazanych položiek
		case 'h': hladaj_cena(zaciatok); break;
		case 'k': exit_p(zaciatok); break;
		default:break;
	}
	
}while(volba!='x');


return 0;
   
}

int pocetzaznamov() //zisti pocet zaznamov v txt subore
{

FILE *fp = fopen("auta.txt","r+");
char ch;
int riadky=1;

if(fp == NULL){
		printf("Zaznamy neboli nacitane\n");
		exit(0);}

while(!feof(fp))
{
  ch = fgetc(fp);
  if(ch == '\n')
  {
    riadky++;
  }
}

return (riadky/7);
}

zaznam *nacitaj(zaznam *zaciatok, int n)
{
	FILE *fr; 
	fr = fopen("auta.txt","r"); 
	
	if(fr == NULL){
		printf("Zaznamy neboli nacitane\n");
		exit(0);}
	
	if(zaciatok != NULL)       // uvolnenie pamäe ak zoznam predtym existoval
{	
		 while (zaciatok != NULL)
    { 
        zaznam* pm = zaciatok; 
        zaciatok = zaciatok -> dalsi;
        free(pm);
    }
    
}
		

	zaznam *pom=NULL;
	zaznam *p=NULL;
	int i;
	
	for(i=0;i<n;i++)
	{
		pom=(zaznam*)malloc(sizeof(zaznam));
		fscanf(fr,"%s %[^\n] %[^\n] %[^\n] %d %d %[^\n]",&pom->oddelovac,&pom->kategoria,&pom->znacka,&pom->predajca,&pom->cena,&pom->rok,&pom->stav);
		pom->dalsi = NULL; 
		
		if(zaciatok == NULL)
		{
			zaciatok = pom; 
		}
		else
		{
			p = zaciatok; 
			while(p->dalsi !=NULL)
				p = p->dalsi;
			p->dalsi = pom;
		}
		
	}
	printf("Nacitalo sa %d zaznamov\n",n);
	return zaciatok;
}

int vypis(zaznam *zaciatok, int n, int inc, int dec)
{
	if(zaciatok == NULL){
		return 0;
	}
	
	zaznam *p = zaciatok;
	int i;
	
	for(i=0;i<n+inc-dec;i++)
	{
		printf("%d.\n",i+1);
		printf("kategoria: %s\n",p->kategoria);
		printf("znacka: %s\n",p->znacka);
		printf("predajca: %s\n",p->predajca);
		printf("cena: %d\n",p->cena); 
		printf("rok_vyroby: %d\n",p->rok); 
		printf("stav_vozidla: %s\n",p->stav); 
		
		p = p->dalsi;
	}
}

void pridaj(zaznam *zaciatok)
{
         zaznam *p=zaciatok, *q, *pom=NULL;
       
	     int i=2;
         int pozicia;
         scanf("\n%d\n",&pozicia);
        

        pom = (zaznam *)malloc(sizeof(zaznam));
        
       	scanf("%[^\n]\n",&pom->kategoria);
       	scanf("%[^\n]\n",&pom->znacka);
       	scanf("%[^\n]\n",&pom->predajca);
       	scanf("%d\n",&pom->cena);
       	scanf("%d\n",&pom->rok);
       	scanf("%[^\n]\n",&pom->stav);

	  	if(pozicia==1)
		  {
		  	pom->dalsi = zaciatok;
		  	zaciatok = pom;
			  }	
	  
        while ((p->dalsi!=NULL) && (i!=pozicia)) {
            i++;
            p=p->dalsi;
        } 

        if(p->dalsi==NULL)
		{
        pom->dalsi=NULL;
        p->dalsi = pom;
		}
        else
		{
        q=p->dalsi;
        p->dalsi=pom;
        pom->dalsi=q;
        }
     
        
}

void hladaj_cena(zaznam *zaciatok)
{

zaznam *p=zaciatok;

char cislo[12];
int c;
int i=1;

scanf("%d",&c);

   while(p!=NULL)
{           

    if (p != NULL && (p->cena <= c)) 
	{
        printf("%d.\n",i);
    	printf("kategoria: %s\n",p->kategoria);
		printf("znacka: %s\n",p->znacka);
		printf("predajca: %s\n",p->predajca);
		printf("cena: %d\n",p->cena); 
		printf("rok_vyroby: %d\n",p->rok); 
		printf("stav_vozidla: %s\n",p->stav);
     	i++;
    }
    			p = p->dalsi;
    			
}

if(i==1)
printf("V ponuke su len auta s vyssou cenou");
    
}

int vymaz(zaznam *zaciatok)
{

zaznam *p=zaciatok;

int A[20];
char znacka1[50];
int i=0;
int c=1;

scanf("%s",&znacka1);


   while(p!=NULL)
{           

    if (p != NULL && (strstr(p->znacka,znacka1)) != 0) 
	{
		i++; // pocet zaznamov na zmazanie 
		A[i]=c;
	}
			
    			p = p->dalsi;
    			c++;    //cislo zaznamu na zmazanie
    			
    			
}
	
	printf("Vymazalo sa %d zaznamov\n",i);
	
	
				int x,j;
 				for(j=1;j<=i;j++)
 				{
 					if(j!=1)
 					{
 						x=A[j];
 						x=x-j+1;
 						del(zaciatok,x);
					 }
					else
					{
 						x=A[j];
 						del(zaciatok,x);
 					}
				 }


		return i;
}


void del(zaznam *zaciatok, int n)
{ 
struct zaznam* temp1 = zaciatok; //vymazanie zaznamov


	if(n==1)
	{
		zaciatok=temp1->dalsi;
		free(temp1); 
	}
	
	else
	{
		int i;
		for(i=1;i<=n-2;i++)
		{
			temp1=temp1->dalsi;
		}
		
		struct zaznam *temp2=temp1->dalsi;
		temp1->dalsi=temp2->dalsi;
	}
}


void exit_p(zaznam *zaciatok)
{
	if(zaciatok != NULL)       // uvolnenie pamäe ak zoznam predtym existoval
{	
		 while (zaciatok != NULL)
    { 
        zaznam* pm = zaciatok; 
        zaciatok = zaciatok -> dalsi;
        free(pm);
    }
    
}
	
exit(0);
}



