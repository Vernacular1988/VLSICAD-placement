

#include <fstream>
#include <vector>
#include <stdlib.h>
#include "layout.h"



using namespace std;

int main(int argc, char *argv[])
{


    ifstream fin(argv[1]);
    double th,x=0,y=0;
    int anchor_n, cell_n, edge_n,total_n;
    int from=0, to=0;
    int i;
    int MD;


    fin>>th;
    fin>>anchor_n;
    fin>>cell_n;
    fin>>edge_n;

    total_n=anchor_n+cell_n;

    double *A=(double *)malloc(cell_n*cell_n*sizeof(double));
    double bx[cell_n];
    double by[cell_n];
    double tx[cell_n];
    double ty[cell_n];

    int cx[total_n];
    int cy[total_n];



    Layout L (th,anchor_n, cell_n, edge_n);

    L.Reset(A, bx, by, tx, ty);

//    cout<<L.T()<<endl;
//    cout<<L.A()<<endl;
//    cout<<L.C()<<endl;
//    cout<<L.E()<<endl;

// Create Node
     for (i=0;i<total_n;i++)
    {

        if (i<anchor_n)
        {
            fin>>x;
            fin>>y;
            cout<<"Anchor v"<<i<<" at ("<<x<<','<<y<<')'<<endl;
            L.CreateNode(i,x,y);
        }
        else
        {
            L.CreateNode(i,0.0,0.0);
        }

    }
// Create Edge
        for (i=0;i<edge_n;i++)
    {

            fin>>from;
            fin>>to;
            cout<<"Edge e"<<i<<" between vertices v"<<from<<" and v"<<to<<endl;
            L.CreateEdge(i,from,to);
    }

//close

    fin.close();


    L.Matrix(A, bx, by);

    L.Solve(A, bx, by, tx, ty);

    L.Conv(cx,cy);

    MD=L.Distance(cx,cy);

    cout<<"Final Manhattan WL: "<<MD<<endl;

//    
    return (0);
}





