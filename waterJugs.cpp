/*
 * Eric Vien
 * 12/4/2023
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

void build_graph(void)
{
  const int SIZE_A = 3;
  const int SIZE_B = 4;

  for (int jugA = 0; jugA <= SIZE_A; jugA++) {
      for (int jugB = 0; jugB <= SIZE_B; jugB++) {
          state curr = make_pair(jugA, jugB);

          if (jugA < SIZE_A) {
              state nbr = make_pair(SIZE_A, jugB);

              nbrs[curr].push_back(nbr);

              edge_label[make_pair(curr, nbr)] = actions[0];
          }

          if (jugB < SIZE_B) {
              state nbr = make_pair(jugA, SIZE_B);

              nbrs[curr].push_back(nbr);

              edge_label[make_pair(curr, nbr)] = actions[1];
          }

          if (jugA > 0) {
              state nbr = make_pair(0, jugB);

              nbrs[curr].push_back(nbr);

              edge_label[make_pair(curr, nbr)] = actions[2];
          }

          if (jugB > 0) {
              state nbr = make_pair(jugA, 0);

              nbrs[curr].push_back(nbr);

              edge_label[make_pair(curr, nbr)] = actions[3];
          }

          if (jugA > 0 && jugB < SIZE_B) {
              int waterAmt;
              if (jugA < SIZE_B - jugB) waterAmt = jugA;
              else waterAmt = SIZE_B - jugB;

              state nbr = make_pair(jugA - waterAmt, jugB + waterAmt);

              nbrs[curr].push_back(nbr);

              edge_label[make_pair(curr, nbr)] = actions[4];
          }

          if (jugB > 0 && jugA < SIZE_A) {
              int waterAmt;
              if (jugB < SIZE_A - jugA) waterAmt = jugB;
              else waterAmt = SIZE_A - jugA;

              state nbr = make_pair(jugA + waterAmt, jugB - waterAmt);

              nbrs[curr].push_back(nbr);

              edge_label[make_pair(curr, nbr)] = actions[5];
          }
      }
  }
}

int main(void)
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
