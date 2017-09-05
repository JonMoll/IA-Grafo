#ifndef CEDGE_H
#define CEDGE_H

#include <iostream>

template <class G>

class CEdge
{
public:
    typedef typename G::Node Node;
    typedef typename G::E E;

    CEdge(E m_data,Node *a, Node *b, bool m_dir)
    {
        m_node[0]=a;
        m_node[1]=b;
        this->m_data=m_data;
        this->m_dir=m_dir;
    }

    //0 bi 1 un
    bool m_dir;
    E m_data;
    Node* m_node[2];
};

#endif //CEDGE_H