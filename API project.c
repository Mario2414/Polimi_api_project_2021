#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct albe{
    unsigned short int color; //nero 0, rosso 1
    unsigned int grafo;
    unsigned int elemento;
    struct albe* p;
    struct albe* left;
    struct albe* right;

} albe;

typedef struct lista{
    unsigned int grafo;
    unsigned int elemento;
    struct lista* successivo;

} lista;

typedef struct {   //definitiva
   unsigned int dist;
   unsigned int prec;
   unsigned int nodo;
   } Node;


// inizio funzioni per RB TREE
albe* inseriscifixup(albe* rad, albe* z, albe* nil);
albe* treeminimum(albe* x, albe* nil);
albe* rbdeletefixup(albe* rad, albe* x, albe* nil);

albe* leftrotate(albe* rad,albe* x, albe* nil){  // t deve essere la radice dell'albero e x deve essere il nodo da ruotare
  albe * y;
  y=x->right;
  x->right=y->left;

  if(y->left!=nil){
    y->left->p=x;
  }
  y->p=x->p;
  if(x->p==nil){
    rad=y;
  }
  else if(x==x->p->left){
    x->p->left=y;
  }
  else x->p->right=y;
  y->left=x;
  x->p=y;
  return rad;
}

albe* rightrotate(albe* rad,albe* x, albe* nil){  // t deve essere la radice dell'albero e x deve essere il nodo da ruotare
  albe * y;
  y=x->left;
  x->left=y->right;

  if(y->right!=nil){
    y->right->p=x;
  }
  y->p=x->p;
  if(x->p==nil){
    rad=y;
  }
  else if(x==x->p->right){
    x->p->right=y;
  }
  else x->p->left=y;
  y->right=x;
  x->p=y;
  return rad;
}
// per inserire un elemento devo creare un nuovo albe e riempire elemento, devo passare un puntatore a rad alrtimenti non lo posso modificare
 albe* inseriscik(albe* rad,albe* z, albe* nil){ // rad è la radice,z è un nodo con il solo parametro elemento riempito
  albe *y, *x;
  x=rad;
  y=nil;
  while(x!=nil){
    y=x;
    if(z->elemento<x->elemento){
      x=x->left;
    }
    else x=x->right;
  }
  z->p=y;
  if(y==nil){
    rad=z;
  }
  else if (z->elemento<y->elemento){
    y->left=z;
  }
  else y->right=z;
  z->left=nil;
  z->right=nil;
  z->color=1; //rosso
  rad=inseriscifixup(rad, z, nil);
  return rad;
}

albe* inseriscifixup(albe* rad, albe* z, albe* nil){
  albe*y;
  while(z->p->color==1){
    if(z->p==z->p->p->left){
      y=z->p->p->right;
      if(y->color==1){
        z->p->color=0;
        y->color=0;
        z->p->p->color=1;
        z=z->p->p;
      }
      else{
        if(z==z->p->right){
          z=z->p;
          rad=leftrotate(rad, z, nil);
        }
        z->p->color=0;
        z->p->p->color=1;
        rad=rightrotate(rad, z->p->p, nil);
      }
    }
    else{
      if(z->p==z->p->p->right){
        y=z->p->p->left;
        if(y->color==1){
          z->p->color=0;
          y->color=0;
          z->p->p->color=1;
          z=z->p->p;
        }
        else{
          if(z==z->p->left){
            z=z->p;
            rad=rightrotate(rad, z, nil);
          }
          z->p->color=0;
          z->p->p->color=1;
          rad=leftrotate(rad, z->p->p, nil);
        }
      }
    }
  }
  rad->color=0;
  return rad;
}

albe* transplant(albe* rad, albe* u, albe*v, albe* nil){
  if(u->p==nil){
    rad=v;
  }
  else if(u==u->p->left){
    u->p->left=v;
  }
  else{
    u->p->right=v;
  }
  v->p=u->p;
  return rad;
}
//dev dare a rb delete il nodo da cancellare
albe* rbdelete(albe* rad, albe* z, albe* nil){
  albe *x, *y;
  unsigned short int y_original_color;
  y=z;
  y_original_color=y->color;
  if(z->left==nil){
    x=z->right;
    rad=transplant(rad,z, z->right, nil);
  }
  else if (z->right==nil){
    x=z->left;
    rad=transplant(rad, z, z->left, nil);
  }
  else{
    y=treeminimum(z->right, nil); //da scrivere
    y_original_color=y->color;
    x=y->right;
    if(y->p==z){
      x->p=y;
    }
    else{
      rad=transplant(rad, y, y->right, nil);
      y->right=z->right;
      y->right->p=y;
    }
    rad=transplant(rad, z, y, nil);
    y->left=z->left;
    y->left->p=y;
    y->color=z->color;
  }
  if(y_original_color==0){
    rad=rbdeletefixup(rad, x, nil);
  }
  return rad;
}

albe* rbdeletefixup(albe* rad, albe* x, albe* nil){
  albe* w;
  while(x!=rad && x->color==0){
    if(x==x->p->left){
      w=x->p->right;
      if(w->color==1){
        w->color=0;
        x->p->color=1;
        rad=leftrotate(rad, x->p, nil);
        w=x->p->right;
      }
      if(w->left->color==0 && w->right->color==0){
        w->color=1;
        x=x->p;
      }
      else{
        if(w->right->color==0){
          w->left->color=0;
          w->color=1;
          rad=rightrotate(rad, w, nil);
          w=x->p->right;
        }
        w->color=x->p->color;
        x->p->color=0;
        w->right->color=0;
        rad=leftrotate(rad, x->p, nil);
        x=rad;
        }
      }
      else{
        w=x->p->left;
        if(w->color==1){
          w->color=0;
          x->p->color=1;
          rad=rightrotate(rad, x->p, nil);
          w=x->p->left;
        }
        if(w->right->color==0 && w->left->color==0){
          w->color=1;
          x=x->p;
        }
        else{
          if(w->left->color==0){
            w->right->color=0;
            w->color=1;
            rad=leftrotate(rad, w, nil);
            w=x->p->left;
          }
          w->color=x->p->color;
          x->p->color=0;
          w->left->color=0;
          rad=rightrotate(rad, x->p, nil);
          x=rad;
          }
      }
    }
    x->color=0;
    return rad;
  }

albe* treeminimum(albe* x, albe* nil){
  while(x->left!=nil){
    x=x->left;
  }
  return x;
}

unsigned int treemaximum(albe* x, albe* nil){
  while(x->right!=nil){
    x=x->right;
  }
  return x->elemento;
}

albe* treesearch(albe*x, unsigned int cerca, albe* nil){ //gli passo l'elemento da cercare e restistuisce il nodo
  while(x!=nil && cerca!=x->elemento){
    if(cerca<x->elemento){
      x=x->left;
    }
    else(x=x->right);
  }
  return x;

  //la riscrivo iterativa
  //if(x==nil || cerca==x->elemento ){
  //  return x;
  //}
  //if(cerca<x->elemento){
  //  return treesearch(x->left, cerca, nil);
  //}
//  else return treesearch(x->right, cerca, nil);
}

void inorderprint(albe*rad, albe*nil, unsigned int flag){ //forse da ottimizzare
  unsigned int temp, y;
  int cont=0;
  char buffer[10];
  temp=0;
  if(rad!=nil){
    inorderprint(rad->left, nil, temp);
    if(flag==1 && rad->right==nil){
      y=rad->grafo;
      if(y==0){
        putchar(48);
      }
      while(y!=0){
        buffer[cont]=48+(y%10);
        y=y/10;
        cont++;
      }
      cont--;
      while (cont>=0) {
        putchar(buffer[cont]);
        cont--;
      }
    }
    else {
      y=rad->grafo;
      if(y==0){
        putchar(48);
      }
      while(y!=0){
        buffer[cont]=48+(y%10);
        y=y/10;
        cont++;
      }
      cont--;
      while (cont>=0) {
        putchar(buffer[cont]);
        cont--;
      }
      putchar(32);
    }
    inorderprint(rad->right, nil, flag);
  }
}

void inorderfree(albe* rad, albe*nil){
  if(rad!=nil){
    inorderfree(rad->left, nil);
    inorderfree(rad->right, nil);
    free(rad);
  }
}
 //fine funzioni rb tree

unsigned int djikstra(Node* coda,unsigned int dadecr,unsigned int numnodi, Node ** nodini, unsigned int *matr);


unsigned int parent(unsigned int i){
  return (i/2);
   }
unsigned int left(unsigned int i){ //definitiva
     if(i==0){return 1;}
     return (i*2);
   }

unsigned int right(unsigned int i){
     if(i==0){return 2;}
     return ((i*2)+1);
   }

void minheap(Node* coda,unsigned int i,unsigned int dim, Node **nodini){ //definitiva
     Node *temp2;
     unsigned int l, r, minimo;
     Node temp;
     l=left(i);
     r=right(i);
     if (l<dim && coda[l].dist<coda[i].dist){
       minimo=l;
     }
     else minimo=i;
     if (r<dim && coda[r].dist<coda[minimo].dist){
       minimo=r;
     }
     if (minimo !=i){
       temp=coda[i];
       coda[i]=coda[minimo];
       coda[minimo]=temp;
       //sposto i posti nell'array di puntatori di supporto, che mi serve per trovare subito i vertici
       temp2=nodini[coda[i].nodo];
       nodini[coda[i].nodo]=nodini[coda[minimo].nodo];
       nodini[coda[minimo].nodo]=temp2;
       // fine array di supporto, vedere se funziona
       minheap(coda,minimo,dim, nodini);
     }
     return;
   }

void buildminheap(Node* coda,unsigned int dim,Node **nodini){ //definitiva, probabilmente non mi serve
     unsigned int mez, i;
     mez=dim/2;
     for (i = mez; i >=0 ; i--) {
       minheap(coda, i, dim, nodini);
     }
     return ;
   }

Node heapextractmin(Node *coda,unsigned int* ddim, Node** nodini){ //decrementa dim e estrae il minimo, bisogna passargli un punatore a dim
     Node *temp2;
     unsigned int dim;
     Node min, acaso;
     dim=*ddim;
     if (dim<1){           //array vuoto
       acaso.nodo=1;
       acaso.dist=UINT_MAX;
       return acaso;
     }
     min=coda[0];
     coda[0]=coda[dim-1];
     coda[dim-1]=min;
     //sposto i posti nell'array di puntprintf("count è %hd\n", count);atori di supporto, che mi serve per trovare subito i vertici
     temp2=nodini[coda[0].nodo];
     nodini[coda[0].nodo]=nodini[coda[dim-1].nodo];
     nodini[coda[dim-1].nodo]=temp2;
     // fine array di supporto, vedere se funziona
     dim=dim-1;
     *ddim=dim;
     minheap(coda,0,dim, nodini);
     return min ;
   }



short int acquisisci(){
  short int count=0;
  unsigned int size=15;
  char letta[15];
  if(fgets(letta, size, stdin )!=NULL){
    while (letta[count]!='\n'){
      count++;
    }
    if (count>4){ //c'è aggiungigrafo
      return 1;
    }
    if(count==4){ // c'è topk
      return 2;
    }
  }
    return 3;
}

void analizzastringa(char *buffer, unsigned int * matr,unsigned int i, unsigned int numnodi); //forse da ottimizzare

unsigned int aggiungigrafo(unsigned int dadecr,unsigned int numnodi,unsigned int *matr, Node* coda, Node ** nodini){
  unsigned int i=0, somma;
  unsigned int size=(10*numnodi)+numnodi-1;
  char buffer[(10*numnodi)+numnodi+1];
    while(i<numnodi){
    if(fgets(buffer, size, stdin )!=NULL){
      analizzastringa(buffer, matr, i, numnodi);
      i++;
      }
    else printf("errore gets 2\n");
    }
      somma=djikstra(coda, dadecr, numnodi, nodini, matr);
      return somma;
  return 0;
}

void analizzastringa(char *buffer, unsigned int * matr,unsigned int i, unsigned int numnodi){
  unsigned int somma, k, n, v;
  k=0;
  v=0;
  while(buffer[k]!='\n'){
    if(buffer[k]==','){
      v++;
    }
    k++;
  }
  k=k-1; //mi sposto dall'ultimo /n
  somma=0;
  while(v>0){
    n=1;
    somma=0;
    while(buffer[k]!=','){
      somma=((unsigned int)buffer[k]-48)*n+somma;
      n=10*n;
      k--;
    }
    k--;
    *(matr+(numnodi*i)+v)=somma;
    v--;
  }
  somma=0;
  n=1;
  while(k!=0){
    somma=((unsigned int)buffer[k]-48)*n+somma;
    n=10*n;
    k--;
  }
  somma=((unsigned int)buffer[k]-48)*n+somma;
  *(matr+(numnodi*i)+v)=somma;
  return;
}

void inizializza(Node *coda,unsigned int numnodi, Node ** nodini){
  unsigned int i;
  for (i = 0; i < numnodi; i++){
    coda[i].dist=UINT_MAX;
    coda[i].prec=UINT_MAX;
    coda[i].nodo=i;
    nodini[i]=coda+i;  // da verificare che funziona (implementarlo in heap)
  }
}

 void decrementachiave(Node* coda, unsigned int i,Node** nodini){
   Node temp, *temp2;
   while(i>0 && coda[parent(i)].dist>coda[i].dist){
     temp=coda[i];
     coda[i]=coda[parent(i)];
     coda[parent(i)]=temp;
     temp2=nodini[coda[i].nodo];
     nodini[coda[i].nodo]=nodini[coda[parent(i)].nodo];
     nodini[coda[parent(i)].nodo]=temp2;
     i=parent(i);
   }
   return;
 }

unsigned int sommacammini(Node ** nodini, unsigned int numnodi){
  unsigned int somma, i;
  somma=0;
  for(i=0; i<numnodi; i++){
    if(nodini[i]->dist!=UINT_MAX){
      //printf("i valori dei nosi sono %u\n",nodini[i]->dist);
      somma=somma+(nodini[i]->dist);
    }
  }
  return somma;
}



unsigned int djikstra(Node* coda,unsigned int dadecr,unsigned int numnodi, Node ** nodini, unsigned int *matr){ //devo implemetare decrementa chiave e fare la somma
  Node  val;
  unsigned int i, j, dist, alt, indice, somma;
  unsigned int *ddim;
  ddim=&dadecr;
  inizializza(coda, numnodi, nodini);
  coda[0].dist=0;
  val.dist=0;
  while(val.dist!=UINT_MAX){
    val=heapextractmin(coda, ddim, nodini);
    if(val.dist==UINT_MAX){
      break;
    }
    i=val.nodo;
    for(j=0; j<numnodi; j++){
      if(matr[(numnodi*i)+j]!=0){
        dist=matr[(numnodi*i)+j];
        alt=val.dist+dist;
        if(alt<(nodini[j]->dist)){
          nodini[j]->dist=alt;
          nodini[j]->prec=i;
          indice=(nodini[j]-&coda[0]);   //calcolo l'indice del valore per passarlo a decrementa FUNZIONA, TESTATO, potrebbe dare problemi con grandi numeri ma non so
          decrementachiave(coda, indice, nodini);
        }
      }
    }
  }
  somma=sommacammini(nodini, numnodi);
  return somma;
}

int main(){
  char c[5];
  short int val;
  albe *new, *nil, *rad;
  Node *coda, **nodini;
  unsigned int *matr;
  unsigned int numnodi, k, dadecr, somma, w=0, max=0, flag=1;
  if(scanf("%u%u",&numnodi,&k)==1){}
  if(fgets(c, 5, stdin )!=NULL){}
  dadecr=numnodi;
  val=acquisisci();
  while(val==2){              //nel caso ho all'inzio topk senza aggiungi grafo
    printf("\n");
    val=acquisisci();
  }
  if(val==3){    //nel caso dopo i parametri iniziali non ho niente
    return 0;
  }
  if(val==1){     //ho il primo aggiungi grafo e quindi posso allocare la memoria che mi serve
    matr=malloc(sizeof(unsigned int)*numnodi*numnodi);
    coda=malloc(sizeof(Node)*numnodi);
    nodini=malloc(sizeof(coda)*numnodi);
    somma=aggiungigrafo(dadecr, numnodi, matr, coda, nodini);
    if(somma>max){
      max=somma;
    }
    nil=(albe*)malloc(sizeof(albe));
    nil->color=0;
    rad=nil;
    if(w<k){
      new=(albe*)malloc(sizeof(albe));
      new->elemento=somma;
      new->grafo=w;
      rad=inseriscik(rad,new, nil);
    }
    w=w+1;
    dadecr=numnodi;
  while(w<k){
    val=acquisisci();
    if(val==1){
      somma=aggiungigrafo(dadecr, numnodi, matr, coda, nodini);
      if(somma>max){
        max=somma;
      }
      new=(albe*)malloc(sizeof(albe));
      new->elemento=somma;
      new->grafo=w;
      rad=inseriscik(rad,new, nil);
      w=w+1;
      dadecr=numnodi;
    }
    if(val==2){
      flag=1;
      inorderprint(rad,nil, flag); // devo chiamarla con flag=1
      printf("\n" );
    }
    if(val==3){
      free(matr);
      free(coda);
      free(nodini);
      inorderfree(rad,nil);
      free(nil);
      return 0;
    }
  }
  while(1){
    val=acquisisci();
    if(val==1){
      somma=aggiungigrafo(dadecr, numnodi, matr, coda, nodini);
      //al posto di cambia topk//
      if(somma<max){
        new=treesearch(rad, max, nil);
        rad=rbdelete(rad, new, nil);
        new->elemento=somma;
        new->grafo=w;
        rad=inseriscik(rad,new, nil);
        max=treemaximum(rad, nil);
      }
      w=w+1;
      dadecr=numnodi;
    }
    if(val==2){
      flag=1;
      inorderprint(rad,nil,flag);
      printf("\n" );
    }
    if(val==3){
      free(matr);
      free(coda);
      free(nodini);
      inorderfree(rad,nil);
      free(nil);
      return 0;
    }
  }
}
}
