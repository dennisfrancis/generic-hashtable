// Copyright (C) 2012 Dennis Francis<dennisfrancis.in@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dll.h"
#include <time.h>

typedef struct VERTEX {

    char id[31];
    unsigned int num_id;
    char type;  // Can be 'I' - Implicit, 'E' - Explicit
    
} vertex_t;

char *get_strkey(void *el) {
    return (((vertex_t *)el)->id);
}

int comp_keys(void *el1, void *el2) {
    register char *t1 = ((vertex_t *)el1)->id;
    register char *t2 = ((vertex_t *)el2)->id;
    return strcmp( t1, t2 );
}


    
int main() {

    list_t lst;
    vertex_t *v;
    vertex_t vert = { "id11345", 123, 'E' };
    void *ret_node;
    int bSuccess = 1;
    int i;
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
    list_init( &lst, comp_keys );
    srand(time(0));
    for( i=0; i<8; i++ ) {
	v = (vertex_t *)malloc(sizeof(vertex_t));
	v->num_id = rand();
	strcpy( v->id, ids[i] );
	v->type = 'E';
	list_insert( &lst, v );
	printf( "Inserted %s\n", ids[i] );
    }
    v =	(vertex_t *)isPresent( &lst, &vert, &ret_node );
    printf( "v = %p, ret_node = %p for the id=id11345\n", v, ret_node );
    if( v ) {
	printf( "Search successful !\nv->id = %s, v->num_id = %d\n", v->id, v->num_id );
	list_delete( &lst, ret_node );
	printf( "Deleted the searched node.\n" );
	v =	(vertex_t *)isPresent( &lst, &vert, &ret_node );
	printf( "Search after delete : v = %p, ret_node = %p for the id=id11345\n", v, ret_node );
        if ( v || ret_node )
            bSuccess = 0;
    } else {
	printf( "Search unsuccessful !\n" );
        bSuccess = 0;
    }

    list_cleanup( &lst );
    return 1-bSuccess;
}
