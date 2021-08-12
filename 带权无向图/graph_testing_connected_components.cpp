#include"graph.hpp"

void test05(Graph<int> g) {
    vector<vector<int>> connected_components = g.get_connected_components();
    g.print_connected_components(connected_components);
}


int main()
{
    //Graph<char> g;
    //g.add_vertex('A');
    //g.add_vertex('B');
    //g.add_vertex('C');
    //g.add_vertex('D');
    //g.add_vertex('E');
    //g.add_vertex('F');
    //g.add_vertex('G');

    //g.add_edge('A', 'B', 7);
    //g.add_edge('A', 'D', 5);
    //g.add_edge('B', 'C', 8);
    //g.add_edge('B', 'D', 9);
    //g.add_edge('B', 'E', 7);
    //g.add_edge('C', 'E', 5);
    //g.add_edge('D', 'E', 15);
    //g.add_edge('D', 'F', 6);
    //g.add_edge('E', 'F', 8);
    //g.add_edge('E', 'G', 9);
    //g.add_edge('F', 'G', 11);

    //g.add_vertex('H');
    //g.add_edge('B', 'H', 9);
    //g.add_edge('A', 'H', 10);
    //g.add_edge('D', 'H', 11);
    //g.add_edge('A', 'H', 12);
    //g.remove_vertex('H');
    //cout << "打印图中顶点及其邻接表的详细信息如下" << endl;
    //g.show();
    //cout << endl;
    
    // test01(g);
    // test02(g);
    // test03(g);
    // test04(g);
  
    Graph<int> g;

    g.add_vertex(0);
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(4);
    g.add_vertex(5);
    g.add_vertex(6);
    g.add_vertex(7);
    g.add_vertex(8);
    g.add_vertex(9);
    g.add_vertex(10);
    g.add_vertex(11);
    g.add_vertex(12);

    g.add_edge(0, 1 , 1);
    g.add_edge(0, 2, 1);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 1);
    g.add_edge(1, 4, 1);
    g.add_edge(3, 6, 1);
    g.add_edge(4, 5, 1);
    g.add_edge(7, 8, 1);
    g.add_edge(7, 9, 1);
    g.add_edge(7, 12, 1);
    g.add_edge(8, 9, 1);
    g.add_edge(8, 12, 1);
    g.add_edge(9, 10, 1);
    g.add_edge(9, 11, 1);
    g.add_edge(9, 12, 1);
    g.add_edge(10, 11, 1);
    cout << "打印图中顶点及其邻接表的详细信息如下" << endl;
    g.show();
    cout << endl;

    test05(g);
    return 0;
}
