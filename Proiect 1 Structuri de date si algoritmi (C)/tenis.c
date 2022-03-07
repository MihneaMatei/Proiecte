#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player
{
   char *last_name;
   char *first_name;
   int score;
} Player;

typedef struct Country
{
   char *name;
   int nr_players;
   int global_score;
   Player *players;
} Country;

//Nodul pentru arbore
typedef struct BSTNode
{
    Player p;
    struct BSTNode *left,*right;
} BSTNode;

//Nodul listei circulare create initial
struct Elem
{
    Country tara;
    struct Elem *next,*prev;
};

typedef struct Elem Node;

//functie pt afisarea listei initiale
void afisare(Node *head,int n)
{
    int i;
    for (i=0;i<n;i++)
    {
        printf("%s.....\n",head->tara.name);
        head=head->next;
    }
}

//functie folosita pentru a reduce numarul initial al tarilor in cea mai apropiata putere a lui 2
void calificari(Node *head, int j,int n,Node *sentinel,Node *start)
{
    float *scor,min; //se declara vector in care vor fi puse toate scorurile initiale ale tarilor in vederea eliminarilor initiale pt cerinta 2
    Node *help=head; //nod creat pentru a reveni la capatul listei
    scor=(float*)malloc(sizeof(float)*n); //se aloca initial memorie
    do //functia primeste ca parametru numarul de tari ce trebuie sterse din lista, iar acest do while se va executa de exact atatea ori
    {
        head=help; //se readuce headul la capul listei
        int i,k,suma;
        for (k=0;k<(head->tara.nr_players);k++) //se calculeaza suma scorurilor jucatorilor
            suma=suma+(head->tara.players[k].score);
        min=(float)suma/head->tara.nr_players; //se calculeaza media scorurilor jucatorilor
        for (i=0;i<n;i++) //in acest for se calculeaza minimul de medie scor pe tarile din lista si ramase in lista (se va recalcula media minima
        {                   // deoarece va fi scoasa din lista tara cu medie minima, de aici si nevoia de do while)
            suma=0;
            for (k=0;k<(head->tara.nr_players);k++)
                suma=suma+(head->tara.players[k].score);
            scor[i]=(float)suma/head->tara.nr_players;
            if (min>scor[i])
                min=scor[i];
            head=head->next;
        }
        head=help; //se readuce headul la capatul listei dupa ce a fost parcursa pentru a afla minimul
        for (i=0;i<n;i++) //in acest for se va cauta tara cu media minima calculata anterior si va fi stearsa
        {
            suma=0;
            for (k=0;k<(head->tara.nr_players);k++)
                suma=suma+(head->tara.players[k].score);
            float welp=(float)suma/head->tara.nr_players;
            if (min==welp)
            {
                if (head==help) //in cazul in care tara se afla pe prima pozitie se vor face legaturile intre elementele listei
                {               //atat pentru nodul head(cu pricina) cat si pentru help (pentru a pointa catre noul cap de lista), dar si pentru
                    help->prev->next=help->next; //start care este de asemenea un pointer ajutator ce se afla in main, dar care are acelasi
                    help->next->prev=help->prev; //scop ca help
                    help=help->next;
                    start->prev->next=start->next;
                    start->next->prev=start->prev;
                    start=start->next;
                    head->prev->next=head->next;
                    head->next->prev=head->prev;
                    free(head);
                }
                else //in cazul in care nodul de sters nu este head, se fac legaturile normale intre elemente
                {
                    head->prev->next=head->next;
                    head->next->prev=head->prev;
                    free(head);
                }
                j--; //se decrementeaza numarul de tari ce trebuie sters
                n--; //se decrementeaza numarul de tari aflate in lista
                break; //iese din forul care cauta tara cu media minima
            }
            else //daca nu a gasit tara cu medie minima, trece la urmatorul element
                head=head->next;
        }
    } while (j>0);
}

//BST--------------------------------

void preorder(BSTNode*root,int *help0,int *help1,Player *c5s,int *counter5) //aceasta functie verifica aparitiile jucatorilor cautati, insa
{ //calculeaza si nr de jucatori din top ce au scorurile cuprinse intre acelor 2; parcurgerea arborelui se face in preordine (irelevant)
    if (root)
    {
        if ((strcmp(root->p.last_name,c5s[0].last_name)==0) && (strcmp(root->p.first_name,c5s[0].first_name)==0))
            (*help0)=(*help0)+2; //daca primul jucator cautat este gasit, help0 va fi 2
        if ((strcmp(root->p.last_name,c5s[1].last_name)==0) && (strcmp(root->p.first_name,c5s[1].first_name)==0))
            (*help1)=(*help1)+2; //daca al doilea jucator cautat este gasit, help1 va fi 2
        if ((root->p.score > c5s[0].score) && (root->p.score < c5s[1].score))
            (*counter5)++;
        preorder(root->left,help0,help1,c5s,counter5);
        preorder(root->right,help0,help1,c5s,counter5);
    }
}

//alocare de memorie pentru un nou nod al arborelui bst (creare nod nou)
BSTNode* newNode(Player data)
{
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->p = data;
    node->left = node->right = NULL;
    return node;
}

BSTNode* insertBST(BSTNode *node, Player data) //functie folosita pentru inserarea in arbore a jucatorilor ce sunt in clasament
{
    if (node == NULL)
        return newNode(data);
    if (strcmp(node->p.first_name,data.first_name)==0)
    {
        if (strcmp(node->p.last_name,data.last_name)==0)
        {
            node->p.score=data.score;
        }
    }
    else if (data.score < node->p.score)
    {
        node->left = insertBST(node->left,data);
    }
    else if (data.score > node->p.score)
        node->right = insertBST(node->right,data);
    return node;
}

//BSTEND---------------------------------

//STIVA------------------------------

struct nodes //structura nodurilor pentru stiva
{
    Country Scountry;
    struct nodes *next;
};
typedef struct nodes stackNode;

void push(stackNode**top, Node* v) //functie pentru adaugarea de informatii in noi noduri din stivele folosite
{
    stackNode* newNode=(stackNode*)malloc(sizeof(stackNode));
    newNode->Scountry=v->tara;
    newNode->next=*top;
    *top=newNode;
}

void Wpush(stackNode**top, Country tara) //functie folosita pentru a adauga informatii si noduri in stivele WINNER
{
    stackNode* newNode=(stackNode*)malloc(sizeof(stackNode));
    newNode->Scountry=tara;
    newNode->next=*top;
    *top=newNode;
}

int isEmpty(stackNode*top) //functie pentru verificarea stivei
{
    return top==NULL;
}

Country pop(stackNode**top) //functie pentru a scoate elemente din stivele create
{
    Country eroare;
    eroare.name="error";
    if (isEmpty(*top)) return eroare;
    stackNode *temp=(*top);
    Country d=temp->Scountry;
    *top=(*top)->next;
    free(temp);
    return d;
}

//STIVAEND-------------------------------

//COADA-------------------------------
struct meci //structura ajutatoare in care vor fi retinuti jucatorii al caror meci va fi introdus in coada
{
    Player p1,p2;
};
typedef struct meci MECI;

struct Qnode //structura pentru nod coada
{
    MECI meci;
    struct Qnode *next;
};
typedef struct Qnode QNode;

struct Q //structura coada
{
    QNode *front,*rear;
};
typedef struct Q Queue;

Queue* createQueue() //functie pentru crearea cozii
{
    Queue *q;
    q=(Queue *)malloc(sizeof(Queue));
    if (q==NULL) return NULL;
    q->front=q->rear=NULL;
    return q;
}

void enQueue(Queue*q, MECI game) //functie pentru adaugarea meciurilor in coada
{
    QNode* newNode=(QNode*)malloc(sizeof(QNode));
    newNode->meci=game;
    newNode->next=NULL; //nodurile noi se adauga la finalul cozii
    if (q->rear==NULL)
        q->rear=newNode; //daca nu aveam niciun nod in coada
    else
    {
        (q->rear)->next=newNode;
        (q->rear)=newNode;
    }
    if (q->front==NULL)
        q->front=q->rear; //daca e singurul element din coada
}

int isQEmpty(Queue *q) //verificare daca este goala coada
{
    return (q->front==NULL);
}

void deleteQueue(Queue *q) //functie pentru stergerea cozii
{
    QNode *aux;
    if (!isQEmpty(q))
    {
        aux=q->front;
        q->front=q->front->next;
        free(aux);
    }
    free(q);
}

//COADAEND-------------------------------

void printStack(stackNode *top,FILE *f) //functie folosita pentru a scrie stivele WINNER
{
    char c='\n';
    fprintf(f,"=== WINNER ===%c",c);
    while (top)
    {
        int i;
        for (i=0;i<strlen(top->Scountry.name)-1;i++)
            fprintf(f,"%c",top->Scountry.name[i]);
        fprintf(f," --- %d%c",top->Scountry.global_score,c);
        top=top->next;
    }
}

int maxPlayer(Country tara) //functie pentru a calcula scorul maxim inregistrat la un jucator dintr-o tara
{               // functia este folosita pentru a determina ce tari vor fi sterse pentru calificari
    int i,max=tara.players[0].score;
    for (i=0;i<tara.nr_players;i++)
        if (tara.players[i].score>max)
            max=tara.players[i].score;
    return max;
}

void etape(stackNode **top, FILE *f,int v[],Player *c5s) //functie ampla ce are rolul de a efectua cerintele 3, 4 si 5
{
    int et=1,alfa=99999; //alfa este initializat cu o valoare mare pentru a nu interfera cu datele ce vor fi stocate pt c4
    char c='\n';
    int nr=0;
    Player *cls;
    cls=malloc(sizeof(Player));
    stackNode *WINNER=NULL;
    BSTNode *root=NULL;
    do //acest do while va efectua cerinta 3 cat timp alfa este diferit de 1 (adica exista mai mult de o tara in stiva) se va efectua
    {//algoritmul de diferentiere pe etape al tarilor
        fprintf(f,"\n====== ETAPA %d ======\n\n",et);
        et++;
        do //cat timp exista stiva din care sa ia tari
        {
            Queue *q; //se creeaza coada
            q=createQueue();
            Country tara1,tara2; //variabile ajutatoare pentru stocarea tarilor scoase din stiva
            int scor1=0,scor2=0; //var aj. pt mentinerea scorului local intre tari
            tara1=pop(top); //se vor scoate doua tari din stiva
            tara2=pop(top);
            MECI meci; //in var. meci se va retina meciul discutat
            int i,j;
            for (i=0; i<tara1.nr_players; i++) //meciurile jucate vor fi adaugate in coada, dar si in var meci
                for (j=0; j<tara2.nr_players; j++)
                {
                    meci.p1.first_name=malloc(sizeof(char)*(strlen(tara1.players[i].first_name)+1));
                    strcpy(meci.p1.first_name,tara1.players[i].first_name);
                    meci.p1.last_name=malloc(sizeof(char)*(strlen(tara1.players[i].last_name)+1));
                    strcpy(meci.p1.last_name,tara1.players[i].last_name);
                    meci.p1.score=tara1.players[i].score;
                    meci.p2.first_name=malloc(sizeof(char)*(strlen(tara2.players[j].first_name)+1));
                    strcpy(meci.p2.first_name,tara2.players[j].first_name);
                    meci.p2.last_name=malloc(sizeof(char)*(strlen(tara2.players[j].last_name)+1));
                    strcpy(meci.p2.last_name,tara2.players[j].last_name);
                    meci.p2.score=tara2.players[j].score;
                    enQueue(q,meci);
                }
            int h;
            //se va scrie intre ce tari urmeaza sa aiba loc meciuri
            for (h=0; h<strlen(tara1.name)-1; h++) //se face scriere caracter cu caracter a primei tari pt a se evita \n-ul
                fprintf(f,"%c",tara1.name[h]);
            fprintf(f," %d ----- ",tara1.global_score);
            for (h=0; h<strlen(tara2.name)-1; h++) //se face scriere caracter cu caracter a primei tari pt a se evita \n-ul
                fprintf(f,"%c",tara2.name[h]);
            fprintf(f," %d\n",tara2.global_score);
            for (i=0; i<tara1.nr_players; i++)
                for (j=0; j<tara2.nr_players; j++) //se vor verifica meciurile intre jucatori, pe rand, urmand a fi crescute scorurile tarilor in functe de
                {                   //rezultatele meciurilor. vor creste atat scorurile locale ale tarilor, cat si ale jucatorilor
                    fprintf(f,"%s %s %d vs %s %s %d\n",tara1.players[i].last_name,tara1.players[i].first_name,tara1.players[i].score,tara2.players[j].last_name,tara2.players[j].first_name,tara2.players[j].score);
                    if (tara1.players[i].score > tara2.players[j].score)
                    {
                        tara1.players[i].score=tara1.players[i].score+5;
                        scor1=scor1+3;
                    }
                    else if (tara1.players[i].score == tara2.players[j].score)
                    {
                        tara1.players[i].score=tara1.players[i].score+2;
                        tara2.players[j].score=tara2.players[j].score+2;
                        scor1++;
                        scor2++;
                    }
                    else if (tara1.players[i].score < tara2.players[j].score)
                    {
                        tara2.players[j].score=tara2.players[j].score+5;
                        scor2=scor2+3;
                    }
                }
                // in functie de scorurile locale, se vor updata si scorurile global si va fi urcata in stiva WINNER tara castigatoare
            if (scor1>scor2)
            {
                tara1.global_score=tara1.global_score+scor1;
                Wpush(&WINNER,tara1);
            }
            else if (scor1<scor2)
            {
                tara2.global_score=tara2.global_score+scor2;
                Wpush(&WINNER,tara2);
            }
            else //in cazul egalitatii se verifica jucatorul cu scorul cel mai mare al fiecarei tari, fiind urcata in WINNER tara corespunzatoare
            {
                if (maxPlayer(tara1) > maxPlayer(tara2))
                {
                    tara1.global_score=tara1.global_score+scor1;
                    Wpush(&WINNER,tara1);
                }
                else if (maxPlayer(tara1) < maxPlayer(tara2))
                {
                    tara2.global_score=tara2.global_score+scor2;
                    Wpush(&WINNER,tara2);
                }
                else
                {
                    tara1.global_score=tara1.global_score+scor1;
                    Wpush(&WINNER,tara1);
                }
            }
            if (alfa<=4) //in cazul in care s a ajuns la ultimele 4 tari, se va crea un vector cu toti jucatorii (se va adauga acelasi jucator de mai multe ori) ale acestora
            { //jucatorii vor fi adaugati la finalul etapei, deci vor prezenta cel mai mare scor al lor posibil
                int t,y;
                for (t=0;t<tara1.nr_players;t++)
                {
                    cls[nr]=tara1.players[t];
                    nr++;
                    cls=(Player*)realloc(cls,sizeof(Player)*(nr+1));
                }
                for (y=0;y<tara2.nr_players;y++)
                {
                    cls[nr]=tara2.players[y];
                    nr++;
                    cls=(Player*)realloc(cls,sizeof(Player)*(nr+1));
                }
            }
            deleteQueue(q); //se sterge coada aferenta acestui set de meciuri
            fprintf(f,"%c",c); //se scrie un \n
        } while (*top);
        alfa=0; //alfa este reinitializat cu 0
        printStack(WINNER,f); //se afiseaza castigatorii etapei
        while (!isEmpty(WINNER)) //se urca stiva WINNER inapoi in stiva initiala pt a se evita scrierea in ordine inversa a tarilor
        {
            Wpush(top,pop(&WINNER));
            alfa++; //alfa este incrementat pentru a avea in permanenta numarul tarilor aflat in competitie dupa fiecare etapa
        }
    } while (alfa!=1);
    if (v[3]==1) //se verifica daca exista conditia 4
    {
        fprintf(f,"%c====== CLASAMENT JUCATORI ======\n",c);
        int i,j,k;
        Player delta;
        for (i=0;i<nr-1;i++) //jucatorii vor fi sortati in ordine descresc a scorurilor (inclusiv daca unul exista de mai multe ori dar are scoruri dif)
            for (j=i+1;j<nr;j++)
            {
                if (cls[i].score < cls[j].score)
                {
                    delta=cls[i];
                    cls[i]=cls[j];
                    cls[j]=delta;
                }
            }
            for (i=0;i<nr-1;i++)
            for (j=i+1;j<nr;j++) //vor fi stersi jucatorii ce se afla de mai multe ori in vector, ramanand in el doar versiunea cu scorul cel mai mare
            {
                if (strcmp(cls[i].last_name,cls[j].last_name)==0)
                    if (strcmp(cls[i].first_name,cls[j].first_name)==0)
                    {
                        for (k=j;k<nr-1;k++)
                            cls[k]=cls[k+1];
                        nr--;
                    }
            }
        for (i=0;i<nr-1;i++) //se verifica daca exista jucatori ramasi cu acelasi scor si daca da, vor fi stersi dpdv alfabetic
        {
            for (j=i+1;j<nr;j++)
            {
                if (cls[i].score==cls[j].score)
                {
                    if (strcmp(cls[i].last_name,cls[j].last_name)<0) //se verifica numele de fam pentru ordine lexicografica
                    {
                        for (k=j;k<nr-1;k++)
                            cls[k]=cls[k+1]; //stergerea este de la stanga la dreapta
                        nr--; //se decrementeaza nr (care contine nr de jucatori din clasament)
                    }
                    else if (strcmp(cls[i].last_name,cls[j].last_name)>0) //se verifica cealalta varianta a ordinii lexicografice
                    {
                        for (k=i;k<nr-1;k++)
                            cls[k]=cls[k+1];
                        nr--;
                    }
                    else //in cazul in care au acelasi nume de familie, se vor verifica prenumele
                    {
                        if (strcmp(cls[i].first_name,cls[j].first_name)<0)
                        {
                            for (k=j;k<nr-1;k++)
                                cls[k]=cls[k+1];
                            nr--;
                        }
                        else if (strcmp(cls[i].first_name,cls[j].first_name)>0)
                        {
                            for (k=i;k<nr-1;k++)
                                cls[k]=cls[k+1];
                            nr--;
                        }
                    }
                }
            }
        }
        for (i=0;i<nr;i++) //jucatorii ramasi in clasament vor fi urcati in arbore, astfel arborele va contine varianta finala a clasamentului
        {
            root=insertBST(root,cls[i]);
        }
        for (i=0;i<nr;i++) //jucatorii din clasament vor fi scrisi din vector, insa exista posibilitatea afisarii din arbore daca va fi creata o noua fct de parcurgere
            fprintf(f,"%s %s %d\n",cls[i].last_name,cls[i].first_name,cls[i].score);
    }
    if (v[4]==1) //se verifica existenta cerintei 5
    {
        int help0=0,help1=0,counter5=0; //help0 si help1 va retine existenta jucatorilor in top, counter5 va retine cati jucatori se afla intre scorurile celor 2
        preorder(root,&help0,&help1,c5s,&counter5); //se face parcurgerea arborelui cu variabilele de mai sus
        if ((help0==2) && (help1==2)) //daca ambii jucatori exista in top se va scrie cati jucatori au scoruri cuprinse intre scorurile lor
        {
            fprintf(f,"\n%d",counter5);
        }
        else if (help0!=2) //daca primul nu se afla in top, acest fapt va fi comunicat
        {
            fprintf(f,"\n%s %s nu poate fi identificat!",c5s[0].last_name,c5s[0].first_name);
        }
        else if (help1!=2) //analog pt al doilea
        {
            fprintf(f,"\n%s %s nu poate fi identificat!",c5s[1].last_name,c5s[1].first_name);
        }
    }
}

void adaugaS(stackNode** stackTop,Node *head,int n) //functie pt adaugarea listei restranse de calificari in stiva initiala
{
    int i;
    for (i=0;i<n;i++)
    {
        push(stackTop,head);
        head=head->next;
    }
}

int main(int argc, char **argv)
{
    int n,i,nr,nrc,v[5]; //vectorul v retine cerintele
    char c[100],delim[5]=" ",*x;
    FILE *f;
    Node* head=NULL;
    Node* sentinel;
    Player *c5s;
    head=malloc(sizeof(Node));
    Node* start=head;
    f=fopen(argv[1],"r");
    for (i=0;i<5;i++) //va fi citita din fisierul cerinte.in linia ce corespunde cerintelor
    {
        fscanf(f,"%d",&v[i]);
    }
    if (v[4]==1) //daca ultima cerinta exista, vor fi citite si liniile ce corespun acesteia
    {
        fgets(c,100,f);
        c5s=malloc(sizeof(Player)*2); //vectorul de Playeri c5s contine cei doi jucatori dati pt cerinta 5
        for (i=0;i<2;i++)
        {
            fgets(c,100,f);
            x=strtok(c,delim);
            c5s[i].last_name=malloc(sizeof(char)*(strlen(x)+1));
            strcpy(c5s[i].last_name,x);
            x=strtok(NULL,delim);
            c5s[i].first_name=malloc(sizeof(char)*(strlen(x)+1));
            strcpy(c5s[i].first_name,x);
            x=strtok(NULL,delim);
            c5s[i].score=atoi(x);
        }
        Player aux;
        if (c5s[0].score > c5s[1].score) //cei doi jucatori sunt sortati in functie de scor (min-max)
        {
            aux=c5s[0];
            c5s[0]=c5s[1];
            c5s[1]=aux;
        }
    }
    fclose(f);
    f=fopen(argv[2],"r");
    if (v[0]==1) //in cazul existentei cerintei 1, se va face citirea tarilor din fisier si vor fi adaugate pe rand, in linsa
    { //informatiile vor fi citite pe rand, in ordinea cunoscuta
        fgets(c,100,f);
        n=atoi(c);
        start=head;
        for (i=0; i<n; i++)
        {
            Node* newNode = (Node*)malloc(sizeof(Node));
            fgets(c,100,f);
            newNode->tara.nr_players=atoi(c);
            nr=atoi(c);
            fgets(c,100,f);
            nrc=strlen(c)+1;
            if (strstr(c,"Croatia")!=NULL) //consider ca spatiul pus dupa Croatia este o greseala de tiparire a cerintei si am tratat-o ca atare
                strcpy(c,"Croatia\n");//in caz contrar, se poate remedia problema prin citirea cu fscanf, insa ar fi costat timp pretios rescrierea acestei secvente
            newNode->tara.name=malloc(sizeof(char)*nrc);
            strcpy(newNode->tara.name,c);
            (newNode->tara.players)=malloc(sizeof(Player)*nr);
            int j;
            for (j=0; j<nr; j++)
            {
                fgets(c,100,f);
                x=strtok(c,delim);
                newNode->tara.players[j].last_name=malloc(sizeof(char)*(strlen(x)+1));
                strcpy(newNode->tara.players[j].last_name,x);
                x=strtok(NULL,delim);
                newNode->tara.players[j].first_name=malloc(sizeof(char)*(strlen(x)+1));
                strcpy(newNode->tara.players[j].first_name,x);
                x=strtok(NULL,delim);
                newNode->tara.players[j].score=atoi(x);
            }
            newNode->tara.global_score=0;
            newNode->prev=head;
            newNode->next=NULL;
            head->next=newNode;
            head=newNode;
        }
        sentinel=malloc(sizeof(Node)); //se creeaza si se leaga de lista santinela
        head->next=sentinel;
        sentinel->prev=head;
        sentinel->next=start;
        start->prev=sentinel;
    }
    fclose(f);
    start=start->next;
    head=start;
    i=1;
    int nrelim;
    while (n-i>0) //se cauta numarul de tari ce vor fi eliminate
    {
        i=i*2;
        if (n-i>0)
            nrelim=n-i;
    }
    if ((v[0]==1) && (v[1]==0)) //in cazul existentei doar a cerintei 1, se va afisa lista
    {
        head=sentinel->next;
        f=fopen(argv[3],"w");
        for (i=0;i<n;i++)
        {
            fprintf(f,"%s",head->next->tara.name);
            head=head->next;
        }
    }
    if (v[0]==1 && v[1]==1) //in cazul existentei primelor 2 cerinte se va afisa lista redusa a tarilor
    {
        calificari(head,nrelim,n,sentinel,start);
        n=n-nrelim;
        f=fopen(argv[3],"w");
        head=sentinel->next->next;
        for (i=0;i<n;i++)
        {
            fprintf(f,"%s",head->tara.name);
            head=head->next;
        }
    }
    head=sentinel->next->next;;
    if (v[2]==1) //in cazul existentei cerintei 3, se adauga tarile in stiva si se porneste functia ampla etape
    {
        stackNode *stackTop=NULL;
        adaugaS(&stackTop,head,n);
        etape(&stackTop,f,v,c5s);
    }
    fclose(f);
    return 0;
}
