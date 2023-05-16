#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

typedef struct lligada {
    int valor;
    struct lligada *prox;
} *LInt;

// 1

int length(LInt l) {
    if(l == NULL) return 0;
    else return (1 + length(l->prox));
}

//2
void freeL(LInt l){
    while (l)
    {
        LInt temp = l;
        l = l->prox;
        free(temp);
    }
}

//3
void imprimeL(LInt l){
    while (l != NULL){
        printf("%d ", l->valor);
        l = l->prox;
    }
}

//4
LInt reverseL(LInt l) {
    int len = length(l);
    LInt array[len];
    for(int i = 0; i < len; l = l->prox) array[i++] = l;
    for(int i = len - 1; i > 0; i--) array[i]->prox = array[i-1];
    array[0]->prox = NULL;
    return array[len - 1];
}

LInt reverseL2(LInt l) {
    LInt prox = l->prox;
    l->prox = NULL;
    while(prox) {
        LInt temp = prox->prox;
        prox->prox = l;
        l = prox;
        prox = temp;
    }
    return l;
}

//5
void insertOrd (LInt* l, int x) {
    LInt new = malloc(sizeof(struct lligada));
    new->valor = x;
    new->prox = NULL;
    LInt prev = NULL;
    for(;*l && (*l)->valor < x; prev = (*l), l = &((*l)->prox));
    if(prev) {
        new->prox = (*l);
        prev->prox = new;
    }
    else {
        new->prox = (*l);
        *l = new;
    }
}

// 6
int removeOneOrd(LInt *l, int x) {
    LInt prev = NULL;
    for(;*l && x != (*l)->valor; prev = *l, l = &((*l)->prox));
    if(!(*l)) return 1;
    if(!prev) (*l) = (*l)->prox;
    else prev->prox = (*l)->prox;
    return 0;
}

int removeOneOrd2(LInt* l, int x) {
    if((*l)->valor == x) {
        LInt temp = (*l);
        (*l) = (*l)->prox;
        free(temp);
        return 0;
    }
    LInt prev = (*l);
    while(prev->prox) {
        LInt list = prev->prox;
        if(list->valor == x) {
            prev->prox = list->prox;
            free(list);
            return 0;
        }
        prev = prev->prox;
    }
    return 1;
}

// 7
void merge(LInt* r, LInt a, LInt b) {
    if(!a && !b) return;
    if(b == NULL || a != NULL && a->valor < b->valor) {
        (*r) = a;
        merge(&((*r)->prox),a->prox,b);
    }
    else {
        (*r) = b;
        merge(&((*r)->prox),a,b->prox);
    }
}

// 8
void splitQS(LInt l, int x, LInt *mx, LInt *Mx) {
    if(!l) return;
    if(l->valor < x) {
        (*mx) = l;
        (*Mx) = NULL;
        splitQS(l->prox, x, &((*mx)->prox), Mx);
    }
    else {
        (*Mx) = l;
        (*mx) = NULL;
        splitQS(l->prox, x, mx, &((*Mx)->prox));
    }
}

// 9
LInt parteAmeio (LInt *l){
    int meio = length(*l)/2;
    if(meio == 0) return NULL;
    LInt y = (*l);
    LInt prev = NULL;
    for(int i = 0; i < meio; i++) {
        prev = (*l);
        (*l) = (*l)->prox;
    }
    prev->prox = NULL;
    return y;
}

// 10
int removeAll(LInt *l, int x) {
    int rem = 0;
    LInt prev = NULL;
    while(*l) {
        if((*l)->valor == x) {
            if(!prev) (*l) = (*l)->prox;
            else prev->prox = (*l)->prox;
            rem++;
        }
        else {
            prev = (*l);
            l = &((*l)->prox);
        }
    }
    return rem;
}

// 11
int removeDups(LInt *l) {
    int rem = 0;
    for(;*l; l = &((*l)->prox)) {
        LInt prevAux = (*l), aux = (*l)->prox;
        for(; aux; aux = prevAux->prox) {
            if(aux->valor == (*l)->valor) {
                prevAux->prox = aux->prox;
                rem++;
                free(aux);
            }
            else prevAux = aux;
        }
    }
    return rem;
}

// 12
int removeMaiorL(LInt *l) {
    int max = (*l)->valor;
    LInt prev = NULL;
    LInt maxPrev = NULL;
    LInt maxL = (*l);
    LInt list = (*l);
    for(;list; list = list->prox) {
        if(list->valor > max) {
            maxPrev = prev;
            maxL = list;
            max = list->valor;
        }
        prev = list;
    }
    if(!maxPrev) (*l) = (*l)->prox;
    else maxPrev->prox = maxL->prox;
    return max;
}

// 13
void init (LInt *l) {
    LInt prev = NULL;
    for(;(*l)->prox;prev = *l, l = &((*l)->prox));
    if(!prev) {
        free(*l);
        *l = NULL;
    }
    else {
        prev->prox = NULL;
        free(*l);
    }
}

// 14
void appendL (LInt *l, int x) {
    LInt new = malloc(sizeof(struct lligada));
    new->valor = x;
    new->prox = NULL;
    if(!(*l)) (*l) = new;
    else {
        for(;(*l)->prox; l = &((*l)->prox));
        (*l)->prox = new;
    }
}

// 15
void concatL (LInt *a, LInt b) {
    if(*a) concatL(&((*a)->prox),b);
    else (*a) = b;
}

// 16
LInt cloneL (LInt l) {
    if(!l) return NULL; 
    LInt new = malloc(sizeof(struct lligada));
    new->valor = l->valor;
    new->prox = cloneL(l->prox);
    return new;
}

LInt cloneL2 (LInt l) {
    LInt list = NULL, temp = NULL;
    while(l) {
        LInt new = malloc(sizeof(struct lligada));
        new->valor = l->valor;
        new->prox = NULL;
        if(list == NULL) list = temp = new;
        else temp = temp->prox = new;
        l = l->prox;
    }
    return list;
}

// 17
LInt cloneRev (LInt l) {
    if(!l) return NULL;
    int len = length(l);
    LInt array[len];
    for(int i = len - 1; i >= 0; i--) {
        array[i] = malloc(sizeof(struct lligada));
        array[i]->valor = l->valor;
        if(i < len - 1) array[i]->prox = array[i+1];
        else array[i]->prox = NULL;
        l = l->prox;
    }
    return array[0];
}

LInt cloneRev2 (LInt l) {
    LInt list = NULL;
    while(l) {
        LInt new = malloc(sizeof(struct lligada));
        new->valor = l->valor;
        new->prox = list;
        list = new;
        l = l->prox;
    }
    return list;
} 

// 18
int maximo (LInt l) {
    if(!l->prox) return l->valor;
    int m = maximo(l->prox);
    return m > l->valor ? m : l->valor;
}

// 19
int take (int n, LInt *l) {
    int i = 0;
    for(;i < n && *l; i++, l = &((*l)->prox));
    if(!(*l)) return i;
    for(;*l;) {
        LInt temp = (*l)->prox;
        free(*l);
        *l = temp;
    }
    return n;
}

// 20
int drop (int n, LInt *l) {
    int i;
    for(i = 0; i < n && (*l); i++) {
        LInt temp = (*l);
        (*l) = (*l)->prox;
        free(temp);
    }
    return i;
}

// 21
LInt Nforward (LInt l, int N) {
    for(int i = 0; i < N; i++) {
        l = l->prox;
    }
    return l;
}

// 22
int listToArray (LInt l, int v[], int N) {
    int i;
    for(i = 0; i < N && l; l = l->prox) v[i++] = l->valor;
    return i;
}

// 23
LInt arrayToList (int v[], int N) {
    if(N == 0) return NULL;
    LInt new = malloc(sizeof(struct lligada));
    new->valor = (*v);
    new->prox = arrayToList(v + 1, N - 1);
    return new;
}

// 24
LInt somasAcL (LInt l) {
    int sum = 0;
    LInt list = NULL, temp = NULL;
    for(;l; l = l->prox) {
        sum += l->valor;
        LInt new = malloc(sizeof(struct lligada));
        new->valor = sum;
        new->prox = NULL;
        if(!list) list = temp = new;
        else temp = temp->prox = new;
    }
    return list;
}

// 25
void remreps(LInt l) {
    if(l) {
        while(l->prox) {
            if(l->prox->valor == l->valor) {
                LInt temp = l->prox;
                l->prox = temp->prox;
                free(temp);
            }
            else l = l->prox;
        }
    }
}

// 26
LInt rotateL (LInt l) {
    if(!l || !l->prox) return l;
    int len = length(l);
    LInt array[len];
    for(int i = 0; i < len; i++, l = l->prox) array[i] = l;
    array[0]->prox = NULL;
    array[len - 1]->prox = array[0];
    return array[1];
}

LInt rotateL2 (LInt l) {
    if(!l || !(l->prox)) return l;
    LInt temp = l;
    LInt list = l->prox;
    while(temp->prox) temp = temp->prox; 
    temp->prox = l;
    l->prox = NULL;
    return list;
}

// 27
LInt parte(LInt l) {
    if(!l || !l->prox) return NULL;
    LInt newL = l->prox;
    l->prox = l->prox->prox;
    newL->prox = parte(l->prox);
    return newL;
}

LInt parte2 (LInt l) {
    LInt list = NULL, temp = NULL;
    while(l && l->prox) {
        if(!list) list = temp = l->prox;
        else temp = temp->prox = l->prox;
        l = l->prox = l->prox->prox;
        temp->prox = NULL;
    }
    return list;
}