#include "CGraph.h"

int main()
{
    srand(time(NULL));

    CGraph my_graph(100);

    my_graph.searchBlindAux();

    return 0;
}
