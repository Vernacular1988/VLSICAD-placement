#include "layout.h"
#include<stdio.h>

Layout::~Layout(){}



node Layout::FindNode(int n)
{
    return _nodes[n];
}

int Layout::FindIndex(node N)
{
    return _index[N];
}

void Layout::CreateNode(int n, double x, double y)
{
    node N;
    N=this->new_node();

    _nodes[n]=N;
    _index[N]=n;
    _x.push_back(x);
    _y.push_back(y);
}

void Layout::CreateEdge(int n, int from, int to)
{
    edge E=new_edge(_nodes[from], _nodes[to]);
    Connect er=Connect(from, to);
    _ES[E]=er;
    _edges[n]=E;
}

void Layout::Reset(double *A, double *bx, double *by, double *tx, double *ty)
{
    int i,j;
    // reset
    for (i=0;i<cell_n;i++)
    {
        bx[i]=0;
        by[i]=0;
        tx[i]=0;
        ty[i]=0;
        for (j=0;j<cell_n;j++)
        {
            *(A+cell_n*i+j)=0;
        }
    }
}


void Layout::Matrix(double *A, double *bx, double *by)
{
    int i=0,diag=0;
    int n=0,op=0;
    node N,O; //N is the cell, O is the opposite nodes
    node::inout_edges_iterator IE,BE,EE;


    for(i=0;i<cell_n;i++)
    {
        n=anchor_n+i;
        N=_nodes[n];
        diag=0;

        //iterator initial
        BE=N.inout_edges_begin();
        EE=N.inout_edges_end();


        //compute matrix and vectors
        for (IE=BE;IE!=EE;IE++)
        {
            diag=diag+1;
            O=N.opposite(*IE);
            op=_index[O];
            if(op<anchor_n)
            {
                bx[i]=bx[i]+2*NodeX(op);
                by[i]=by[i]+2*NodeY(op);
            }
            else
            {
                *(A+i*cell_n+(op-anchor_n))=(-2);
            }
        }

        *(A+i*cell_n+i)=diag*2;

    }

}

void Layout::Solve(double *A, double *bx, double *by, double *tx, double *ty)
{
    int i,j,n;
    double ce,se;
    double dx,dy;
    double md=999;
    double s1,s2;

    while(md>=th)
    {
        md=0;
        for (i=0;i<cell_n;i++)
        {
            n=anchor_n+i;
            s1=0;
            s2=0;
            se=*(A+cell_n*i+i);
            for (j=0;j<cell_n;j++)
            {
                if (i!=j)
                {
                    ce=*(A+cell_n*i+j);
                    s1=s1+(_x[anchor_n+j]*ce);
                    s2=s2+(_y[anchor_n+j]*ce);
                }
            }

            tx[i]=(bx[i]-s1)/se;
            ty[i]=(by[i]-s1)/se;

            printf("Move vertex v%d at %lf %lf to %lf %lf \n",n,_x[n],_y[n],tx[i],ty[i]);
            //max move
            dx=(tx[i]-_x[n]);
            dy=(ty[i]-_y[n]);
            if(dx<0){dx=(-dx);}
            if(dy<0){dy=(-dy);}

//            cout<<dx<<endl;
//            cout<<dy<<endl;

            if (dx>md) {md=dx;}
            if (dy>md) {md=dy;}
 //           cout<<md<<endl;
        }

        printf("Max move is %lf \n", md);

        for (i=0;i<cell_n;i++)
        {
            n=anchor_n+i;
            _x[n]=tx[i];
            _y[n]=ty[i];
        }
    }


}

void Layout::Conv(int *cx, int *cy)
{
    int i;
    for (i=0;i<(anchor_n+cell_n);i++)
    {
        if (_x[i]>=0) {cx[i]=(int)(_x[i]+0.5);}
        else{cx[i]=(int)(_x[i]-0.5);}
        if (_y[i]>=0) {cy[i]=(int)(_y[i]+0.5);}
        else{cy[i]=(int)(_y[i]-0.5);}

        if(i>=anchor_n)
        {
            printf("FINAL vertex v%d at (%lf,%lf) --> (%d,%d) \n", i, _x[i], _y[i], cx[i], cy[i]);
        }
    }
}

int Layout::Distance(int *cx, int *cy)
{

    int i;
    int sum=0;
    int dx,dy;
    int f,t;
    for (i=0;i<(edge_n);i++)
    {
        f=EdgeF(_edges[i]);
        t=EdgeT(_edges[i]);


        dx=(cx[f]-cx[t]);
        dy=(cy[f]-cy[t]);


        printf("Edge e%d between v%d and v%d: [%d %d] \n", i,  f, t, dx, dy);

        if(dx<0){dx=(-dx);}
        if(dy<0){dy=(-dy);}

        sum=sum+dx+dy;

    }

    return sum;
}


