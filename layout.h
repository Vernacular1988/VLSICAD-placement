#include<GTL/graph.h>
#include<map>
#include<vector>

using namespace std;

class Connect
{
    private:

    int _from;
    int _to;

    public:
    Connect (): _from(0), _to(0) {};
    Connect (int f, int t): _from(f), _to(t) {};
    ~Connect() {};

    int &F() {return _from; };
    int &T() {return _to; };
};

class Layout : public graph
{
    private:

    int     anchor_n;
    int     cell_n;
    int     edge_n;
    double th;

//    vector<double>  b_x (100);
//    vector<double>  b_y (100);


    typedef node_map<int> NodeIndex;
    typedef edge_map<Connect> EdgeS;
    typedef map<int, node> NodeList;
    typedef map<int, edge> EdgeList;
    typedef vector<double> V;

    NodeList  _nodes;
    EdgeList _edges;
    EdgeS _ES;
    NodeIndex _index;

    V _x;
    V _y;





    public:
    Layout(double t, int x, int y, int z) : graph()
    {
        th=t;
        anchor_n=x;
        cell_n=y;
        edge_n=z;

        _index.init(*this);
        _ES.init(*this);

    };

    ~Layout();

    //query parameters;
    inline double T() {return th;};
    inline int A() {return anchor_n;};
    inline int C() {return cell_n;};
    inline int E() {return edge_n;};

    //query edges
    inline int EdgeF(edge e) {return _ES[e].F(); };
    inline int EdgeT(edge e) {return _ES[e].T(); };


    //query nodes position
    inline double NodeX(int n) {return _x[n]; };
    inline double NodeY(int n) {return _y[n]; };


    // Load graph
    void CreateNode(int n, double x, double y);
    void CreateEdge(int n, int from, int to);

    node FindNode(int n);
    int FindIndex(node N);

    //Solve
    void Matrix(double *A, double *bx, double *by);
    void Reset(double *A, double *bx, double *by, double *tx, double *ty);
    void Solve(double *A, double *bx, double *by, double *tx, double *ty);
    void Conv(int *cx, int *cy);
    int Distance(int *cx, int *cy);

};
