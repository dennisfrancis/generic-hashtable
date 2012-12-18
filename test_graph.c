
#include <stdio.h>

#include "graph.h"
#include "checkTriangleInequality.h"


static void sort( graph_data_t *gData ) {
    int i, j, size = gData->edgeHashTable.num_elements;
    edge_t *tmp;
    for( i=1; i<size; i++ ) {
	tmp = gData->edges[i];
	for( j=i; j>=1 && (gData->edges[j-1]->weight > tmp->weight) ; j-- )
	    gData->edges[j] = gData->edges[j-1];
	gData->edges[j] = tmp;
    }
}

int main() {

    graph_data_t graph_data;
    int i;
    if( parseInputDescription( "sample_input.txt", &graph_data ) == -1 ) {

	printf( "graph.c : Error in parseInputDescription() !\n" );
	return -1;
    }

    printf( "\n\n\nInput file successfully parsed and hashtables populated successfully.\n\n\n" );
    printf( "Graph stats\n" );
    printf("Number of Vertices %d\n", graph_data.numVertices);
    printf("Number of type A edges %d\n", graph_data.edgeHashTable.num_elements);
    printf("Type B edge weight %d\n\n\n", graph_data.typeB_weight);

    printf( "Edges in the array :\n" );
    for( i=0; i<graph_data.edgeHashTable.num_elements; i++ )
	printf( "Edge#%d, <%d, %d> weight : %d\n", i+1, graph_data.edges[i]->vertexId1, graph_data.edges[i]->vertexId2, graph_data.edges[i]->weight );

    printf( "\n\nVertex array :\n" );
    for( i=0; i<graph_data.vertexHashTable.num_elements; i++ )
	printf( "VertexId : %d, VertexName : %s\n", i, graph_data.vertices[i] );

    sort( &graph_data );

    printf( "\n\n\n" );
    printf( "\n\ncheckTriangleInequality() returns %d\n\n\n", checkTriangleInequality( &graph_data ) );

    cleanup_graph_data( &graph_data );
	
    return 0;
}
