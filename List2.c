// Denis STEFANOIU


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include "lista_dubla.h"
#define N_Stud 3 // ziua din data nasterii; daca <10 se aduna 10
#define Nr_Note 2 // se va modifica la 5


// structura unui nod din lista
struct nod{
    void* data;
    struct nod* next;
    struct nod* prev;
};

// structura ce identifica lista
struct lista{
    struct nod* first;
    struct nod* last;
    int dim;
};


// tipul Lista - TAD = structura dinamica (mai multe noduri alocate dinamic)
// este un pointer la o structra ce contine pointeri catre primul si ultimul nod
// structura contine si dimensiunea listei

typedef struct lista* Lista;
typedef struct nod* Iterator;





struct stud {
        char nume[31];
        char prenume[31];
        int note[5];
        float media;
    };




//
// PROTOTIPURILE FUNCTIILOR
//

// creeaza lista (pointer la lista)
Lista NewL();

// intoarce pointer la primul element (nod) al listei
Iterator First(Lista L);

// intoarce pointer la ultimul element (nod) al listei
Iterator Last(Lista L);

// test lista vida
int isEmpty(Lista L);

//functie de verificare a pozitiei unui nod in lista: cauta p in lista L
int verifPoz(Lista L,Iterator p);

// avansare la urmatorul element din lista
Iterator Next(Lista L, Iterator p);

//traversare inapoi a listei: de la primul catre ultimul nod; intoarce adresa ultim nod;
Iterator Back_First(Lista L);

//traversare inapoi a listei: de la ultimul catre primul nod; intoarce adresa primului nod;
Iterator Back_Last(Lista L);

// extragerea unui element dintr-o pozitie data
// verifica intai existenta elementului in lista
void* Get(Lista L, Iterator p);

// modificarea unui element al listei dintr-o pozitie data
// verifica validitatea pozitiei
void Change (Lista L, Iterator p, void* x);

// cautarea unei valori in lista
// traversarea listei, oprirea la gasirea valorii sau
// la epuizarea listei (cand intoarce NULL)

Iterator Find(Lista L, void* x);


//stergerea unui nod din lista
//stergere directa ar invalida iterartorul
// pentru stergere definim un alt iteraror
// actualizam pozitia iteratorului pe elementul urmator, refacand legaturile acestuia
// izolnd nodul sters si apoi eliberam memoria ocupata de acesta

void* Remove(Lista L, Iterator p);


// inserarea unui nod intr-o lista
// la o anumita pozitie
// INSERAREA se face inainte de pozitia p daca p diferit de NULL
// daca p este NULL inserarea se face dupa ultimul element al listei (daca exista)
// deci ADAUGARE la final
// sau se insereaza ca prim element daca lista este vida

void Insert(Lista L, Iterator p,void* x);


// stergerea listei L
void Delete(Lista L);

// goleste lista L
void Empty(Lista L);

//returneaza dimensiunea listei
int Size(Lista L);

//concateneaza doua liste LA si LB
Lista Concat(Lista LA, Lista LB);


// calculeaza media grupei
float MediaGrupa(Lista L);

// afiseaza o linie de separatie pe ecran (50 caractere lungime)
void linie();



// functia main
int main()
{
    struct stud* s;
    Lista LStud=NewL(); // creare lista LStud
      // adaug N_Stud elemente in lista
    printf("Inroduceti date in lista studentilor\n");
    for (int i=1; i<=N_Stud;i++){   //citirea de la tastatura a datelor studentilor din lista LStud si incarcarea listei
        s= (struct stud* ) malloc(sizeof(struct stud));
        if(s == NULL){
            printf("Eroare! Nu se poate aloca memorie.");
            exit(0);
        }
        //citire date student curent
        printf("Student(%d)\n",i);
        fflush(stdin);
        printf("Nume: ");gets(s->nume);
        printf("Prenume: ");gets(s->prenume);
        s->media=0;
        for (int j=0;j<Nr_Note;j++){
            printf("Nota %d: ",j+1);
            scanf("%d",&(s->note[j]));
            s->media +=s->note[j];
        }
        s->media/=Nr_Note;
        Iterator p=NULL;
        Insert(LStud,p,(struct stud*)s);
        printf("\n");        // adaugarea la final in lista
    }
    printf("\n");

    // afisarea elementelor din cele doua liste

    struct stud* pd; // pd - pointer la data din nodul curent in lista
    int promovat=0,nepromovat=0;
    system("cls");
    printf("Lista studentilor este\n\n");
    for (Iterator crt=LStud->first; crt!=NULL;crt=Next(LStud,crt)){ // parcurge lista LStud
        pd=(struct stud*)Get(LStud,crt); // pointer la datele studentului curent
        // puts(pd->nume);
        // puts(pd->prenume);
        printf("Nume: %s\tPrenume:%s\n",pd->nume,pd->prenume);
        // printf("Note: \n");
        for (int j=0;j<Nr_Note;j++){
            printf("N[%d]: %d\t",j+1,pd->note[j]);
        }
        printf("\n\nMedia: %.2f",pd->media);
        if(pd->media>=5){
            promovat++;
            printf("\t (P)\n");
        }
        else{
            nepromovat++;
            printf("\t (NP)\n");
        }
        linie();
        printf("\n");
    }
    printf("Media grupei este: %.2f\n",MediaGrupa(LStud));
    printf("\n\tStudenti Promovati: \t%d\n",promovat);
    printf("\tStudenti Nepromovati: \t%d\n",nepromovat);
    printf("\n");

    Delete(LStud);
    system("pause");
    //return 0;
    return EXIT_SUCCESS;
}



//
// IMPLEMENTAREA FUNCTIILOR
//



//functie pentru crearea listei
// se aloca memorie pentru TAD lista dubla
// la inceput lista are dimensiunea 0
// first - primul nod al listei este NULL
// last - ultimul nod al listei este NULL
// intoarce pointer catre lista dubla

Lista NewL(){
    Lista L=(Lista) malloc(sizeof(struct lista));
    if(L == NULL)
    {
        printf("Eroare! Nu se poate aloca memorie pentru crearea listei.");
        exit(0);
    }

    L->dim=0;
    L->first=NULL;
    L->last=NULL;
    return L;
}

// intoarce pointer la primul element (nod) al listei
Iterator First(Lista L){
    assert(L);
    return L->first;
}

// intoarce pointer la ultimul element (nod) al listei
Iterator Last(Lista L){
    assert(L);
    return L->last;
}

// test lista vida
int isEmpty(Lista L){
    assert(L);
    return L->dim==0;
}


//functie de verificare a pozitiei unui nod in lista: cauta p in lista L
int verifPoz(Lista L,Iterator p){
    assert(L); // verific existenta listei
    Iterator poz=L->first;
    if (p==NULL) return 1;
    while (poz != NULL){
        if (poz==p) return 1;
        poz=poz->next;
    }
    return 0;
}

// avansare la urmatorul element din lista
Iterator Next(Lista L, Iterator p){
    assert(L && !isEmpty(L) && verifPoz(L,p));
    return p->next;
}

//traversare inapoi a listei: de la primul catre ultimul nod; intoarce adresa ultim nod;
Iterator Back_First(Lista L){
    assert(L);
    return L->last;
}

//traversare inapoi a listei: de la ultimul catre primul nod; intoarce adresa primului nod;
Iterator Back_Last(Lista L){
    assert(L);
    return L->first;
}

// extragerea unui element dintr-o pozitie data
// verifica intai existenta elementului in lista
void* Get(Lista L, Iterator p){
    assert((L && !isEmpty(L) && verifPoz(L, p)));
    return p->data;
}


// modificarea unui element al listei dintr-o pozitie data
// verifica validitatea pozitiei
void Change (Lista L, Iterator p, void* x){
    assert((L && !isEmpty(L) && verifPoz(L, p)));
    p->data=x;
}

// cautarea unei valori in lista
// traversarea listei, oprirea la gasirea valorii sau
// la epuizarea listei (cand intoarce NULL)

Iterator Find(Lista L, void* x){
    Iterator p;
    for (p=First(L);p!=Last(L); p=Next(L,p))
        if(Get(L,p)==x)
            return x;
    return NULL;
}

//stergerea unui nod din lista
//stergerea directa ar invalida iterartorul
// pentru stergere definim un alt iteraror
// actualizam pozitia iteratorului pe elementul urmator, refacand legaturile acestuia
// izolnd nodul sters si apoi eliberam memoria ocupata de acesta

void* Remove(Lista L, Iterator p){
    assert(L && !isEmpty(L) && verifPoz(L,p));
    Iterator q=p; // Iterator temporar pentru stergere nod
    p=Next(L,p); //actualizare iterator
    void* x=q->data;
    q->data=NULL;
    if (q->prev) //izolarea nodului sters
        q->prev->next=q->next;
    else
        L->first=q->next;
    if (q->next)
        q->next->prev=q->prev;
    else
        L->last=q->prev;
    free(q);
    L->dim--;
    return x;
}


// inserarea unui nod intr-o lista
// la o anumita pozitie
// INSERAREA se face inainte de pozitia p daca p diferit de NULL
// daca p este NULL inserarea se face dupa ultimul element al listei (daca exista)
// deci ADAUGARE la final
// sau se insereaza ca prim element daca lista este vida
void Insert(Lista L, Iterator p,void* x){
    Iterator nou;
    if (!verifPoz(L,p))
        return; // nu exista pozitia p in lista si (p != NULL)

    nou=(Iterator) malloc(sizeof(struct nod));
    nou->data=x;
    if (p){ // daca pozitia p exista
        nou->next=p;            // nodul nou adaugat are ca urmator nodul cu poz p (cel inaintea caruia s-a facut inserarea
        if (p->prev){           // daca p are anterior
            nou->prev=p->prev;  // reface legaturile pentru ca nodul nou sa aiba anterior pe anteriorul lui p
            p->prev->next=nou;  // anteriorul lui p sa-l aiba urmator pe noul nod
          //  p->prev=nou;        // anteriorul lui p sa fie noul nod
        }
        else{                   // daca p nu are anterior
            nou->prev=NULL;     // nodul nou adaugat nu va avea anterior
            L->first=nou;       // noul prim nod al listei L va fi nodul nou adaugat
        } // de la: else if (p->prev)
        p->prev=nou;            // p il are ca anterior pe noul nod adaugat
    }
    else{   //daca pozitia p nu exista in lista
        nou->next=NULL;         // noul nod nu va avea urmator
        nou->prev=L->last;      // anteriorul noului nod va fi ultimul nod din Lista L
        if (L->last){ // daca ultimul nod al listei L exista
            L->last->next=nou;      // se schimba ultimul nod din lista L
            L->last=nou;            // ultimul nod din lista L va fi noul nod adaugat
        }
        else{ // daca lista L nu are ultim nod (L este vida)
            L->last=L->first=nou;   // noul nod adaugat va fi si primul si ultimul
        } // de la: else if (L->last)
    } // de la: else if(p)
    L->dim++; // creste dimensiunea listei cu 1
}


// stergerea listei L
void Delete(Lista L){
    assert(L);
    Iterator crt, prc;
    crt=L->first;
    while (crt!=NULL){
        prc=crt;
        crt=crt->next;
        free(prc->data);
        free(prc);
    }
    free(L);
}


// goleste lista L
void Empty(Lista L){
    assert(L);
    Iterator crt, prc;
    crt=L->first;
    while (crt!=NULL){
        prc=crt;
        crt=crt->next;
        free(prc->data);
        free(prc);
    }
}

//returneaza dimensiunea listei
int Size(Lista L){
    assert(L);
    return L->dim;
}


//concateneaza doua liste LA si LB
Lista Concat(Lista LA, Lista LB){
    assert(LA && LB && !isEmpty(LA) && !isEmpty(LB)); // pentru concatenare listele trebuie sa existe si sa nu fie vide
    Lista L =(Lista)malloc(sizeof(struct lista));
    if(L == NULL)
    {
        printf("Eroare! Nu se poate aloca memorie pentru crearea listei.");
        exit(0);
    }
    L->dim=Size(LA)+Size(LB);
    L->first=LA->first;
    LA->last->next=LB->first;
    LB->first->prev=LA->last;
    L->last=LB->last;
    return L;
}




// calculeaza media grupei
float MediaGrupa(Lista L){
    struct stud* pdc; // pointer la date curente
    float Med=0;
    int nr=0;
    for (Iterator crt=L->first; crt!=NULL;crt=Next(L,crt)){ // parcursge lista studentilor
        pdc=(struct stud*)Get(L,crt);
        Med+=pdc->media; //adauga la suma mediilor studentilor media studentului curent
        nr++; //creste cu 1 numarul studentilor carora li se calculeaza media pe grupa
    }
    Med/=nr; // media grupei este media aritmetica a mediilor studentilor din grupa
    return Med;
}



// afiseaza o linie de separatie pe ecran (50 caractere lungime)
void linie(){
    for (int i=0; i<50; i++)
        printf("-");
    printf("\n");
}
