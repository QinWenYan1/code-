#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "date.h"
#include "tldlist.h"
#define MAXLINE 1000

struct tldlist{
    Date* enddatep;
    Date* startdatep;
    TLDNode* root; 
    long count; //how many nodes in this tree
};

struct tldnode{
    char* tld; //the tld this node represents
    long count; // how many times this tld appears 
    TLDNode* left;
    TLDNode* right;  
};

struct tlditerator{
    TLDList* list;
    TLDNode** nodearray; 
    int index;  
};

int insert_tldlist(TLDNode* node, TLDNode* root){


    if(root != NULL){
        if(strcmp(root ->tld, node ->tld) > 0){
            /*go to right side*/
            insert_tldlist(node, root->right);
        }else if(strcmp(root ->tld, node ->tld) == 0){
            /*the tld has been recorded in tldlist*/
            (root ->count)++; 
            return 1; /*successful*/
        }else{
            /*go to left side*/
            insert_tldlist(node, root->left);
        }
    }else{
        /*the tld is not in the tldlist
          we shuold add it*/
        root = node; 
        return 1; 
    }
    return 1; 

}

void traverse(TLDNode* root, TLDNode* nodearray[]){
    /*we traverse left to right*/
    if(root != NULL){
        traverse(root->left, nodearray);/*left*/
        *nodearray++ = root; 
        traverse(root->right, nodearray); /*right*/
    }
}

void filter_hostname(char* hostname, char* sp){

    /*now we need to deal with string*/
    while(*(++hostname) != '\0' ){
    }/*iterate to the end of string*/

    int i = 0;
    char c = 0;  
    while((c = *(--hostname)) != '.'){
        *(sp+i) = tolower(c); /*keep case-insensitive*/
        i++; 
    }
        
}

TLDList *tldlist_create(Date *begin, Date *end){
    TLDList* list = (TLDList*)malloc(sizeof(TLDList*));

    if(list && date_compare(end, begin)){
        /*if pointer is valid and end and begin day are valid*/
        list -> startdatep = begin;
        list -> enddatep = end; 
        list -> root = NULL; 
        return list; 
    }
    /*unvalid pointer*/
    return NULL; 
    
}

void tldlist_destroy(TLDList *tld){
    free(tld); 
}

int tldlist_add(TLDList *tld, char *hostname, Date *d){
    int condition1 = date_compare(tld->enddatep, d);
    int condition2 = date_compare(d,tld->startdatep);
    char tldstring[MAXLINE];
    TLDNode* node = (TLDNode*)malloc(sizeof(TLDNode*));
  

    if(condition1 && condition2 && node){/*valid date in range */
        /*now we need to deal with string*/
        filter_hostname(hostname, tldstring); 
        /*string has been done*/
        /*initialize them*/
        (tld -> count)++; 
        node -> tld = tldstring; 
        node -> left = NULL; 
        node -> right = NULL; 
        node -> count = 1; 

        return insert_tldlist(node, tld->root);

    }
    return 0; /*unsuccessful insert*/
     
}

long tldlist_count(TLDList *tld){
    return tld -> count; 
}

TLDIterator *tldlist_iter_create(TLDList *tld){
    TLDIterator* iteratorp = (TLDIterator*)malloc(sizeof(TLDIterator*)); 
    iteratorp -> list = tld; 
    iteratorp -> index = 0;
    iteratorp -> nodearray = NULL; 
    return iteratorp; 
}

TLDNode *tldlist_iter_next(TLDIterator *iter){
    if(!iter->nodearray){/*we have no array to store*/
        TLDNode* arr[MAXLINE]; 
        iter -> nodearray = arr; 
        traverse((iter->list)->root, iter->nodearray);
    
        
    }
    if(iter->nodearray[iter->index]){
            return iter->nodearray[(iter->index)++];
    }else{
            return NULL; 
    }
    
}

void tldlist_iter_destroy(TLDIterator *iter){
    free(iter);
}

char *tldnode_tldname(TLDNode *node){
    return node -> tld; 
}

long tldnode_count(TLDNode *node){
    return node -> count;
}



