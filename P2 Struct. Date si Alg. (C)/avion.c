#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000000

typedef struct Resursa //structura pt resursa
{
    char *nume;
    int cantitate;
} Resursa;

typedef struct Island //structura pt insula
{
    char *nume;
    int nrResurse;
    Resursa *inventarResurse;
    int nrAvioane;
    int *avioane;
    int tolAvioane;
} Island;

typedef struct //structura pt graf
{
    int V;
    int **a;
} Graph;

void maxres(Island *insule,int n,Resursa* maxresv) //functie care introduce toate resursele disponibile pe insula intr-un vector
{
    int i,j,nr=0;
    for (i=0;i<n;i++)
    {
        for (j=0;j<insule[i].nrResurse;j++)
        {
            maxresv[nr].nume=malloc(sizeof(char)*(strlen(insule[i].inventarResurse[j].nume)+1));
            strcpy(maxresv[nr].nume,insule[i].inventarResurse[j].nume);
            maxresv[nr].cantitate=insule[i].inventarResurse[j].cantitate;
            nr++;
        }
    }
}

int sortmaxres(Resursa* maxresv,int nrres) //functie care preia vectorul construit la functia anterioara, il sorteaza lexicografic
{                                           //dupa care sterge resursele ce apar de mai multe ori
    int i,j,k;
    Resursa aux;
    for (i=0;i<nrres;i++)
        for (j=i+1;j<nrres;j++) //ordonare lexicografica a resurselor
            if (strcmp(maxresv[i].nume,maxresv[j].nume)>0)
            {
                aux=maxresv[i];
                maxresv[i]=maxresv[j];
                maxresv[j]=aux;
            }
    for (i=0;i<nrres-1;i++) //stergerea resurselor aflate de mai multe ori si inlocuirea cu cantitatea maxima intre cele 2 care se compara
        for (j=i+1;j<nrres;j++)
            if (strcmp(maxresv[i].nume,maxresv[j].nume)==0)
            {
                if (maxresv[i].cantitate>maxresv[j].cantitate)
                    maxresv[j].cantitate=maxresv[i].cantitate;
                for (k=i;k<nrres-1;k++)
                    maxresv[k]=maxresv[k+1];
                nrres--;
                j--;
            }
    return nrres;
}

void maxcant (Resursa *maxresv,FILE *g,Island *insule,char *c, int n, int nrres) //functie ce are rolul de a calcula resursa cu cantitate maxima
{ //si de a cauta mai apoi insulele care contin cantitate maxima pentru a le scrie
    int i,max=0,j;
    for (i=0;i<nrres;i++)
        if (strcmp(maxresv[i].nume,c)==0)
            max=maxresv[i].cantitate;
    for (i=0;i<n;i++)
    {
        for (j=0;j<insule[i].nrResurse;j++)
        {
            if (strcmp(c,insule[i].inventarResurse[j].nume)==0)
                if (insule[i].inventarResurse[j].cantitate==max)
                    fprintf(g,"%s ",insule[i].nume);
        }
    }
}

void timp_zbor(int dist[], int n,int parents[],int d,FILE *g) //functie ce calculeaza distanta dintre 2 insule cu ajutorul vectorului dist
{                           //creat cu ajutorul algoritmului lui dijkstra
    int i,j;
    int *v,helpi=d;
    v=malloc(sizeof(int));
    int nr=0;
    while(helpi!=0 && helpi!=-1)
    {
        v[nr]=parents[helpi];
        nr++;
        v=realloc(v,sizeof(int)*(nr+1));
        helpi=parents[helpi];
    }
    if (dist[d]<MAX)
    {
        fprintf(g,"%d\n",dist[d]);
    }
    else fputs("INF\n",g);
}

void printPath(int parent[], int j,FILE *g) //functie care scrie calea de la o insula la alta
{
    if (parent[j] == - 1)
        return;

    printPath(parent, parent[j],g);

    fprintf(g,"Island%d ", j+1);
}

void min_zbor1(int** matrix,int n,int src,int** matrix2) //functie care creeaza o noua matrice de adiacenta, de data aceasta insa
{     //unde nu exista drum direct se pune MAX, iar daca se intalneste drum intre insule si niciuna din ele nu este sursa cautata
    int i,j;            //pentru cerinta min_zbor, se vor adauga cele 15 min de intarziere; in cazul in care exista drum direct intre
    for(i=0; i<n; i++)      //doua insule, iar una din ele este sursa cautata, nu se vor adauga minutele aferente intarzierii
        for(j=0; j<n; j++)
        {
            if(matrix[i][j])
            {
                if(i!=src && j!=src)
                {
                    matrix2[i][j]=matrix[i][j]+15;
                    matrix2[j][i]=matrix[i][j]+15;
                }
                else
                {
                    matrix2[i][j]=matrix[i][j];
                    matrix2[j][i]=matrix[i][j];
                }
            }
            else
                matrix2[i][j]=MAX;
        }
}

int minDistance(int dist[],  int sptSet[],int V)
{
    int min = MAX, min_index,v;
    for (v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
        {
            min = dist[v],
            min_index = v;
        }
    return min_index;
}

void min_zbor2(int n, int src, int d, int** graph, FILE *g) //functie care ajutandu-se de algoritmul lui dijkstra, calculeaza distanta minima de la
{                   //sursa la orice insula din arhipelag, dupa care scrie distanta in functie de noua matrice creata la functia min_zbor1
    int v,count,i;
    int dist[n];
    int sptSet[n];
    int parent[n];
    for (i = 0; i < n; i++)
    {
        parent[i] = -1;
        dist[i] = MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0;
    for (count = 0; count < n - 1; count++)
    {
        int u = minDistance(dist, sptSet,n);
        sptSet[u] = 1;
        for (v = 0; v < n; v++)
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }
    if (dist[d]<MAX)
        fprintf(g,"%d\n",dist[d]);
}

void dijkstra(int n, int src, int d, int** graph, FILE *g, int dij) //functie care calculeaza distanta minima intre sursa data si fiecare
{                                       //insula din arhipelag
    int v,count,i;
    int dist[n];
    int sptSet[n];
    int parent[n];
    for (i = 0; i < n; i++)
    {
        parent[i] = -1;
        dist[i] = MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0;
    for (count = 0; count < n - 1; count++)
    {
        int u = minDistance(dist, sptSet,n);
        sptSet[u] = 1;
        for (v = 0; v < n; v++)
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }
    if (dij==0)
    {
        if (dist[d]<MAX)
        {
            printPath(parent,d,g);
            fputs("\n",g);
        }
        else fputs("NO\n",g);
    }
    else if (dij==1)
    {
        timp_zbor(dist,n,parent,d,g);
    }
    else
    {
        int** matrix2;
        matrix2=(int **)malloc(sizeof(int*)*n);
        for (i=0;i<n;i++)
            matrix2[i]=calloc(n,sizeof(int));
        min_zbor1(graph,n,src,matrix2);
        min_zbor2(n,src,d,matrix2,g);
    }
}

int numbers(char c[]) //functie care cauta intr-un cuvant secvente numerice si le transforma intr-o variabila int
{
    char *c1;
    int i,s=0,x;
    c1=malloc(sizeof(char));
    for (i=0;i<strlen(c);i++)
    {
        if (c[i]>='0' && c[i]<='9')
        {
            c1=realloc(c1,sizeof(char)*(s+1));
            c1[s]=c[i];
            s++;
        }
    }
    c1=realloc(c1,sizeof(char)*(s+1));
    c1[s]='\0';
    x=atoi(c1);
    return x;
}

void printok(Island* insule2,int n,FILE* g) //functie care printeaza insulele in cazul in care la cerinta 3 nu este nimic de schimbat
{
    int i,j;
    for(i=0; i<n; i++)
    {
        fprintf(g,"Island%d\n",i+1);
        for(j=0; j<insule2[i].nrAvioane; j++)
            fprintf(g,"%d ",insule2[i].avioane[j]);
        fputs("\n",g);
    }
}

void gestiune(Graph *graf,Island *insule2,FILE *g)//functie aferenta cerintei 3
{
    int i,j,k,*over,*overid,nexces=0,insexces=0,bec = 1,x,m;
    for (i=0;i<graf->V;i++) //in acest for se verifica daca vreo insula depaseste toleranta
    {
        if (insule2[i].nrAvioane>insule2[i].tolAvioane)
            bec=0;
    }
    if (bec==1) //in cazul in care nu se depaseste toleranta, se vor scrie fara modificari insulele
    {
        printok(insule2,graf->V,g);
    }
    else //in cazul in care se depaseste toleranta, iar numarul total al avioanelor depaseste toleranta maxima in arhipelag
    {   //se va afisa mesajul corespunzator
        int total=0;
        for (i=0;i<graf->V;i++)
            total+=insule2[i].nrAvioane;
        if (total>((graf->V)*insule2[0].tolAvioane))
        {
        	fputs("Stack overflow!\n",g);
        	return;
        }

    }
    over=calloc(graf->V,sizeof(int)); //vector folosit pentru stocarea numarului in exces de avioane. indicele va fi insula, valoarea numarul de avioane in exces
    for(i=0; i<graf->V; i++)
    {
        if(insule2[i].nrAvioane > insule2[i].tolAvioane)
        {
            over[i]=insule2[i].nrAvioane-insule2[i].tolAvioane;
            nexces+=insule2[i].nrAvioane-insule2[i].tolAvioane;
            insexces++;
        }
    }
    overid=calloc(nexces,sizeof(int)); //vector folosit pentru stocarea id-urilor avioanelor in exces
    k=0;
    for(i=0; i<graf->V; i++)
    {
        if(insule2[i].nrAvioane > insule2[i].tolAvioane)
        {
            for(j=insule2[i].tolAvioane; j<insule2[i].nrAvioane; j++)
            {
                overid[k]=insule2[i].avioane[j]; //se introduc id-urile avioanelor in exces in vectorul declarat mai sus
                k++;
            }
            insule2[i].nrAvioane=insule2[i].tolAvioane;//se reduce nr avioanelor in exces din insula respectiva la toleranta
        }
    }
    for (i=0;i<graf->V;i++) //se cauta pe ce insula sunt avioane in exces
    {
        if (over[i]) //daca se gaseste
        {
            for (j=0;j<graf->V;j++)
            {
                if (graf->a[i][j] && insule2[j].tolAvioane-insule2[j].nrAvioane >= over[i]) //se verifica daca insula j are leg directa cu insula i si daca are loc de alte avioane
                {
                    fprintf(g,"Island%d\n",j+1);
                    x=over[i];
                    while (x>=0) //cat timp exista avioane in plus
                    {
                        m=over[i]-x;
                        while (m>=0) //se scriu toate combinatiile posibile de mutare
                        {
                            bec=0;
                            for (k=0;k<insule2[j].nrAvioane;k++)
                                fprintf(g,"%d ",insule2[j].avioane[k]);
                            for (k=m ; k<m+x ; k++)
                            {
                                fprintf(g,"%d ",overid[k]);
                                bec=1;
                            }
                            fputs("\n",g);
                            if (!bec) break; //bec folosit pentru evitarea scrierii in plus de elemente
                            m--;
                        }
                        x--;
                    }
                }
                else //in cazul in care nu exista leg directa sau nu exista loc de alte avioane, se afiseaza normal insula cu avioanele sale
                {
                    fprintf(g,"Island%d\n",j+1);
                    for (k=0;k<insule2[j].nrAvioane;k++)
                    {
                        fprintf(g,"%d ",insule2[j].avioane[k]);
                    }
                    fputs("\n",g);
                }
            }
        }
    }
    fputs("\n",g);
}

int main(int argc, char **argv) //functia main in care se produc citirile si apelarile aferente cerintelor
{
    Island *insule;
    Graph* graf=malloc(sizeof(Graph));
    Resursa* maxresv=malloc(sizeof(Resursa));
    FILE *f,*g;
    int n,i,j,p,nrres=0,welp=0,destinatie,sursa;
    char c[50];
    f=fopen(argv[1],"r");
    fscanf(f,"%d",&n);
    insule=malloc(sizeof(Island)*n); //se aloca primul vector de insule
    for (i=0;i<n;i++) //se citesc datele fiecarei insule in parte
    {
        fscanf(f,"%s",c);
        insule[i].nume=malloc(sizeof(char)*(strlen(c)+1));
        strcpy(insule[i].nume,c);
        fscanf(f,"%d",&insule[i].nrResurse);
        insule[i].inventarResurse=malloc(sizeof(Resursa)*insule[i].nrResurse);
        nrres=nrres+insule[i].nrResurse;
        for (j=0;j<insule[i].nrResurse;j++)
        {
            fscanf(f,"%s",c);
            insule[i].inventarResurse[j].nume=malloc(sizeof(char)*(strlen(c)+1));
            strcpy(insule[i].inventarResurse[j].nume,c);
            fscanf(f,"%d",&insule[i].inventarResurse[j].cantitate);
        }
    }
    fscanf(f,"%d",&p);
    int **matrix; //se creeaza matricea de adiacenta initiala
    matrix=malloc(sizeof(int*)*n);
    for (i=0;i<n;i++)
        matrix[i]=calloc(n,sizeof(int));
    for (i=0;i<p;i++)
    {
        int x,y,cost;
        fscanf(f,"%s",c);
        x=numbers(c);
        fscanf(f,"%s",c);
        fscanf(f,"%s",c);
        y=numbers(c);
        fscanf(f,"%s",c);
        cost=atoi(c);
        matrix[x-1][y-1]=cost;
        matrix[y-1][x-1]=cost;
    }
    g=fopen(argv[2],"w");
    while (!feof(f)) //de aici incepe citirea comenzilor, cu verificarea fiecarei comenzi in parte si apelarea operatiilor necesare rezolvarii
    {
        int x,y,co,dij;
        c[0]='\0';
        fscanf(f,"%s",c);
        if (strcmp(c,"conexiune")==0)
        {
            fscanf(f,"%s",c);
            x=numbers(c);
            fscanf(f,"%s",c);
            y=numbers(c);
            printf("%d %d %d\n", x, y, matrix[x-1][y-1]);
            if (matrix[x-1][y-1]!=0)
                fputs("OK\n",g);
            else fputs("NO\n",g);
        }
        else if (strcmp(c,"legatura")==0)
        {
            fscanf(f,"%s",c);
            x=numbers(c);
            for (i=0;i<n;i++)
                if (matrix[x-1][i]!=0) fprintf(g,"Island%d ",i+1);
            fputs("\n",g);
        }
        else if (strcmp(c,"adauga_zbor")==0)
        {
            fscanf(f,"%s",c);
            x=numbers(c);
            fscanf(f,"%s",c);
            y=numbers(c);
            fscanf(f,"%s",c);
            co=numbers(c);
            matrix[x-1][y-1]=co;
            matrix[y-1][x-1]=co;
        }
        else if (strcmp(c,"anulare_zbor")==0)
        {
            fscanf(f,"%s",c);
            x=numbers(c);
            fscanf(f,"%s",c);
            y=numbers(c);
            matrix[x-1][y-1]=0;
            matrix[y-1][x-1]=0;
        }
        else if (strcmp(c,"max_resurse")==0)
        {
            if (welp==0)
            {
                maxresv=malloc(sizeof(Resursa)*nrres);
                maxres(insule,n,maxresv);
                nrres=sortmaxres(maxresv,nrres);
                welp++;
            }
            fprintf(g,"%d ",nrres);
            for (i=0;i<nrres;i++)
                fprintf(g,"%s ",maxresv[i].nume);
            fputs("\n",g);
        }
        else if (strcmp(c,"max_cantitate")==0)
        {
            fscanf(f,"%s",c);
            if (welp==0)
            {
                maxresv=malloc(sizeof(Resursa)*nrres);
                maxres(insule,n,maxresv);
                nrres=sortmaxres(maxresv,nrres);
                welp++;
            }
            maxcant(maxresv,g,insule,c,n,nrres);
            fputs("\n",g);
        }
        else if (strcmp(c,"drum_zbor")==0)
        {
            dij=0;
            fscanf(f,"%s",c);
            sursa=numbers(c);
            fscanf(f,"%s",c);
            destinatie=numbers(c);
            dijkstra(n,sursa-1,destinatie-1,matrix,g,dij);
        }
        else if (strcmp(c,"timp_zbor")==0)
        {
            dij=1;
            fscanf(f,"%s",c);
            x=numbers(c);
            fscanf(f,"%s",c);
            y=numbers(c);
            dijkstra(n,x-1,y-1,matrix,g,dij);
        }
        else if (strcmp(c,"min_zbor")==0)
        {
            dij=2;
            fscanf(f,"%s",c);
            x=numbers(c);
            fscanf(f,"%s",c);
            y=numbers(c);
            dijkstra(n,x-1,y-1,matrix,g,dij);
        }
        else if(c[0]>='0' && c[0]<='9') //else decisiv pentru continuarea citirii in cazul in care se trece la cerinta 3
        {
            graf->V=numbers(c);
            Island *insule2=malloc(sizeof(Island)*(graf->V)); //se creeaza al doilea vector de insule, aferent cerintei 3, si se fac citirile coresp.
            fscanf(f,"%d",&x);
            for (i=0;i<graf->V;i++)
                insule2[i].tolAvioane=x;
            for(i=0; i<graf->V; i++)
                fscanf(f,"%d",&insule2[i].nrAvioane); //citeste numarul de avioane dintr-o insula
            for(i=0; i<graf->V; i++)
            {
                insule2[i].avioane=malloc(sizeof(int)*insule2[i].nrAvioane);
                for(j=0; j<insule2[i].nrAvioane; j++)
                    fscanf(f,"%d",&insule2[i].avioane[j]); //citeste avioanele dintr-o insula
            }
            graf->a=(int**)malloc(sizeof(int*)*(graf->V));
            for (i=0; i< graf->V ; i++)
                (graf->a)[i]=malloc(sizeof(int)*(graf->V));
            for (i=0;i<graf->V;i++)
                for (j=0;j<graf->V;j++)
                    fscanf(f,"%d",&graf->a[i][j]);
            gestiune(graf,insule2,g);
        }
    }

    //se elibereaza memoria
    fclose(f);
    free(insule);
    free(maxresv);
    fclose(g);
    free(graf->a);
    free(graf);
    return 0;
}
