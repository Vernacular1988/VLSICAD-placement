/* Copyright (c) 2004 ACM/SIGDA
   Prepared by Valavan Manohararajah, vmanohar@altera.com
   Modifications by Florian Krohm, fkrohm@us.ibm.com
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ifstream>
#include<vector>


#define MAX_GATE_TYPES	10
#define MAX_GATE_INPUTS	2
#define MAX_CELL_TYPES	20
#define MAX_DAG_NODES	100000



/* Data structure declarations: */
//class Gate
//{
//	private:	
//		int _in;
//		int _delay;
//	public:
//		Gate(int i, int d): _in(i), _delay(d) {};
//		~Gate() {};
//
//		int I() {return _in;};
//		int D() {return _delay;};
//}; 

//Nodes

class node
{
	public:
	int degree_in;
	int type;
	int delay;
	int opt_delay; //optimized root delay
	int stage; //0-input level; 1-middle; 2-end
	vector<int>  node_in; // input node;

	node () {};
	node (int i, int t, int d, int s) 
	{
		degree_in=i; 
		type=t;  
		delay=d; 
		stage=s;
		opt_delay=0;
	};

	~node () {};
	void Connect(int idx) { node_in.push_back(idx)};
//	void Optimize();
}


int main (int argc, char *argv[])
{
  int max_delay = 0;


  /* Make sure there's a file name argument: */
  if (argc != 2) {
    fprintf (stderr, "usage: main filename\n");
    exit (1);
  }

  /* Open the file: */
  //fp = fopen (argv[1], "r");
  //if (fp == NULL) {
  //  fprintf (stderr, "cannot open %s\n", argv[1]);
  //  exit (1);
  //}

  int G,C; // types # of simple gate and complex gate
  int I,N;  // Node #
  int i,j;
  int t,r;
  vector<node> netlist;


  // read input data;i6trdx
  ifstream fin(argv[]);

  fin>>G;

  int type_s[G][2]; //simple gate [0]input nodes #, [1]delay

  for (i=0;i<G;i++)
  {
	  fin>>type_s[i][0];
	  fin>>type_s[i][1];
  }

  fin>>C;
	
  int type_c[C][2]; //complex gate

  for (i=0;i<C;i++)
  {
	  fin>>type_c[i][0];
	  fin>>type_c[i][1];
	  fin>>type_c[i][2];
	  fin>>type_c[i][3];
  }

  fin>>I; fin>>N;

  for (i=0;i<I;i++) 
  {
	  netlist.push_back(node(0,0,0,0));
  }

  for (i=I;i<I+N;i++) 
  {
	  t=0;
	  fin>>t;
	  netlist.push_back(node(type_s[t][0],t,type_s[t][1],2));
	  for (j=0;j<netlist[i].degree_in;j++)
	  {
		  fin>>r;
		  netlist[i].node_in.push_back(r);
		  if (netlist[r].stage==2) {netlist[r].stage=1;}
	  }
  }



  fin.close();





 






  /* Read in gate info */

  /* ... */

  /* Read in cell info */

  /* ... */

  /* Read in the DAG */

  /* ... */

  /* Done with reading the input: */
  

  /* Compute the best delay solution at each node.
   * Traversal is in topological order.
   */

  /* ... */

  /* Print the solution: */
  printf ("%d\n", max_delay);

  return 0;
}
