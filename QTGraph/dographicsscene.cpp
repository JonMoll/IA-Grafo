#include "dographicsscene.h"
#include "dolinearectaobject.h"
#include "CHillClimbing.h"

DoGraphicsScene::DoGraphicsScene(QObject *parent, CGraph *my_graph, int algoritmo, int nodo_a, int nodo_b, int *aristas) :QGraphicsScene(parent){
    //srand(time(NULL));

    int zoom = 4;
    *aristas = 0;

    if(algoritmo == 0){
        for(int i = 0; i < my_graph->m_number_nodes; i++){
            for(int j = 0; j < my_graph->m_distances[i].size(); j++){
                int index_node_a = my_graph->m_distances[i][j].index_node_a;
                int index_node_b = my_graph->m_distances[i][j].index_node_b;

                int node_a_x = my_graph->m_nodes[index_node_a].x * zoom;
                int node_a_y = my_graph->m_nodes[index_node_a].y * zoom;

                int node_b_x = my_graph->m_nodes[index_node_b].x * zoom;
                int node_b_y = my_graph->m_nodes[index_node_b].y * zoom;

                QPoint a(node_a_x, node_a_y);
                QPoint b(node_b_x, node_b_y);

                addItem(new DoLineaRectaObject(a, b));
            }
        }
    }

    if(algoritmo == 1){
        CHillClimbing my_search(my_graph);
        vector<int> solution;
        bool hill = my_search.SearchPath(nodo_a, nodo_b, &solution);

        if(hill){
            for(int i = 0; i < solution.size()-1; i++){
                int node_a_x = my_graph->m_nodes[ solution[i] ].x;
                int node_a_y = my_graph->m_nodes[ solution[i] ].y;

                int node_b_x = my_graph->m_nodes[ solution[i+1] ].x;
                int node_b_y = my_graph->m_nodes[ solution[i+1] ].y;

                QPoint a(node_a_x, node_a_y);
                QPoint b(node_b_x, node_b_y);

                addItem(new DoLineaRectaObject(a, b));                
                *aristas = *aristas + 1;
            }
        }
    }

    if(algoritmo == 2){
        my_graph->searchBlindAux(nodo_a, nodo_b);

        for(int i = 0; i < my_graph->path.size() - 1; i++){
            int node_a_x = my_graph->path[i].x;
            int node_a_y = my_graph->path[i].y;

            int node_b_x = my_graph->path[i+1].x;
            int node_b_y = my_graph->path[i+1].y;

            QPoint a(node_a_x, node_a_y);
            QPoint b(node_b_x, node_b_y);

            addItem(new DoLineaRectaObject(a, b));
            *aristas = *aristas + 1;
        }

    }
}
