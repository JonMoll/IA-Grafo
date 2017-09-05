#include <iostream>
#include <limits.h>
#include "CGraph.h"

using namespace std;

struct Traits_1{
	typedef int n;
	typedef string e;
};

int main()
{
    CGraph<Traits_1> cgraph;
	cgraph.insert_node(1);
	cgraph.insert_node(2);
	cgraph.insert_node(3);
	cgraph.insert_node(4);
	cgraph.insert_edge("a",1,2,1);
	cgraph.insert_edge("b",1,3,1);
	cgraph.insert_edge("c",2,3,1);
	cgraph.insert_edge("d",1,4,1);
	cgraph.insert_edge("e",2,4,1);

	cgraph.print();
	cgraph.draw();
    return 0;
	}

