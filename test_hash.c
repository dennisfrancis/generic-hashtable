
// Copyright (C) 2012 Dennis Francis<dennisfrancis.in@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include <time.h>

typedef struct VERTEX {

    char id[31];
    unsigned long int num_id;
} vertex_t;

typedef struct HASHPARAM {
    unsigned long int seed;
    unsigned long int p;
    unsigned long int m;
    unsigned long int a;
    unsigned long int b;
} hashparam_t;

int primes[] = {
    11177,
    10301,
    11173,
    11933,
    10729,
    10159,
    10357,
    11329,
    11941,
    11047,
    11483,
    11369
};


char *get_strkey(void *el) {
    return (((vertex_t *)el)->id);
}

int comp_keys(void *el1, void *el2) {
    register char *t1 = ((vertex_t *)el1)->id;
    register char *t2 = ((vertex_t *)el2)->id;
    return strcmp( t1, t2 );
}


/*int comp_str_keys(const char *s1, const char *s2) {
    register char *t1;
    register char *t2;
    register char equal = 1;
    for(t1 = s1, t2 = s2; ((*t1) && (*t2)) && equal ; t1++, t2++ )
	if( (*t1) != (*t2) )
	    equal = 0;
    return !equal;
    }*/

void get_hash_param( hashparam_t *h ) {
    srand(time(0));
    h->seed = primes[ rand() % 12 ];
    h->a = ( rand() % ((h->p)-1) )  + 1;
    h->b = ( rand() % (h->p) );
    return;
    
}
unsigned long int hash( void *element, void *params ) {
    int ascii;
    hashparam_t *parm = (hashparam_t *)params;
    char *strkey = ((vertex_t *)element)->id;
    unsigned long int hv = parm->seed;
    while( ( ascii = *(strkey++) ) )
	hv = ((hv<<5) + hv)^ascii;

    return (( (hv*parm->a) + parm->b ) % parm->p ) % parm->m;
}

    
int main() {

    int num_elements;
    vertex_t *v;
    vertex_t **vlist;
    void *ret_node;
    int i;
    int bSuccess = 1;
    char *ids[] = {
	"id12345",
	"id14345",
	"id16345",
	"id17345",
	"id18345",
	"id11345",
	"id10345",
	"id19345"
    };
    hashparam_t parm;
    hashtable_t ht;
    vertex_t vert = { "id11345", 123 };
    parm.p = 5381;
    parm.m = 100;
    printf( "parm : p = %lu, m = %lu, a = %lu, b = %lu, seed = %lu\n", parm.p, parm.m, parm.a, parm.b, parm.seed );
    get_hash_param( &parm );
    hashtable_init(   &ht,
		      parm.m,
		      comp_keys,
		      hash,
		      &parm
		      );
    
    for( i=0; i<8; i++ ) {
	v = (vertex_t *)malloc(sizeof(vertex_t));
	v->num_id = hash( ids[i], &parm );
	strcpy( v->id, ids[i] );
	hashtable_insert( &ht, v, -1 ); // Let it compute hash again
	printf( "Inserted %s : %lu\n", ids[i], v->num_id );
    }
    
    v =	(vertex_t *)is_in_hashtable( &ht, &vert, &ret_node );
    printf( "v = %p, ret_node = %p for the id=id11345\n", v, ret_node );
    if( v ) {
	printf( "Search successful !\nv->id = %s, v->num_id = %lu\n", v->id, v->num_id );
	hashtable_delete( &ht, v->num_id, ret_node );
	printf( "Deleted the searched node.\n" );
	v =	(vertex_t *)is_in_hashtable( &ht, &vert, &ret_node );
	printf( "Search after delete : v = %p, ret_node = %p for the id=id11345\n", v, ret_node );
        if ( v || ret_node )
            bSuccess = 0;
    } else {
	printf( "Search unsuccessful !\n" );
        bSuccess = 0;
    }

    vlist = (vertex_t **)get_elements_in_hashtable( &ht, &num_elements, NULL, NULL );
    if( vlist ) {
	printf( "List of elements in hashtable :\n" );
	for( i=0; i<num_elements; i++ )
	    printf( "<%s, %lu>\n", vlist[i]->id, vlist[i]->num_id );
    } else {
	printf( "Error getting the list of elements in the hashtable\n" );
        bSuccess = 0;
    }
    hashtable_destroy( &ht );
    return 1 - bSuccess;
}
