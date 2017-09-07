#include <iostream>
#include <limits.h>
#include "CGraph.h"

using namespace std;

struct Traits_1{
	typedef int n;
	typedef string e;
};

int main(){
    srand(time(NULL));

    CGraph<Traits_1> cgraph;

    cgraph.generate_graph(10);

    return 0;
}

