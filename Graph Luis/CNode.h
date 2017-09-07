#ifndef CNODE_H
#define CNODE_H

#include <iostream>
#include <vector>

using namespace std;

template <class G>
class CNode{
public:
    typedef typename G::N N;
    typedef typename G::Edge Edge;

    CNode(N m_data_x, N m_data_y){
        this->m_data_x=m_data_x;
        this->m_data_y=m_data_y;
    }

    N m_data_x;
    N m_data_y;

    vector<Edge*> m_nedges;
};

#endif //CNODE_H
