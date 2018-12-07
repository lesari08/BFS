/*======================================================================

   Implementation of BFS on a graph that is not assumed to be connected

   12/6/18 
   Left off
   realized that unordered map may not be the best way to represent
   adjacency lists since the char,vector pairs arent guararenteed to
   be in a particular order so if we're going from adjlist.begin, we
   cant guareentee that begin element will be the root of a tree
   or map would probably be better or even better, perhaps a vector of
   pairs <char, vector> ...tbd
======================================================================*/

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include<map>
#include <queue>
#include <string>



using AdjacencyListConstItr = std::map<char, std::vector<char> >::const_iterator;
using CharacterBooleanPairVector = std::vector< std::pair<char, bool> >;
class Graph
{
public:
    Graph();
 
    void addVertex(const char& vertex);

    //  Prints all vertices in the graph
    void printVertices() const;

    //  Prints the direct neighbors of a given vertex
    void printNeighbors(char vertex) const;

    //  Fill the graph with values for
    //  example purposes 
    void initializeGraph();

    void BFS();

    //  The first parameter is a vector that keeps track of 
    //  the vertices visited. The second parameter is an iterator 
    //  pointing to the current vertex to start the transversal from 
    void BFSHelper(std::unordered_map<char, bool> &visited, std::unordered_map<char, bool>::iterator visitedItr, const AdjacencyListConstItr adjListConstItr);

    //  Explicitly defining the copy constructor and destructor
    //  because of the rule of 3
    Graph(const Graph& OtherGraph) = delete;
    ~Graph() = default;

private:

    int numberOfVertices;
    std::map<char, std::vector<char> > adjList;
    std::map<char, std::vector<char> >::const_iterator adjListItr;

};

Graph::Graph()
{
    numberOfVertices = 9;
}
void Graph::addVertex(const char& vertexName)
{
    std::vector<char> directNeigborsVector;

    adjList.insert(make_pair(vertexName, directNeigborsVector));

}


void Graph::printVertices() const
{
    std::map<char, std::vector<char> >::const_iterator itr;

    for (itr = adjList.begin(); itr != adjList.end(); ++itr)
    {
        std::cout << itr->first << std::endl;
    }

}

void Graph::printNeighbors(char vertex) const
{
    if (adjList.find(vertex) != adjList.end())
    {
        std::vector<char>::const_iterator vecItr;

        std::cout << "Neighbors of " << vertex << ":";
        if (adjList.at(vertex).size() > 0)
        {
            for (vecItr = adjList.at(vertex).begin(); vecItr != adjList.at(vertex).end(); ++vecItr)
            {
                std::cout << *vecItr << " ";
            }

            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "vertex not found" << std::endl;
    }
}

void Graph::initializeGraph()
{
    for (int idx = 0; idx < numberOfVertices; idx++)
    {
        char vertex = '1' + idx;
        addVertex(vertex);
    }

    adjList['1'].push_back('2');
    adjList['1'].push_back('3');

    adjList['2'].push_back('1');
    adjList['2'].push_back('4');
    adjList['2'].push_back('5');

    adjList['3'].push_back('1');
    adjList['3'].push_back('6');
    adjList['4'].push_back('2');

    adjList['5'].push_back('2');

    adjList['6'].push_back('3');
    adjList['6'].push_back('7');
    adjList['7'].push_back('6');

    adjList['8'].push_back('9');
    adjList['9'].push_back('8');
    
}



void Graph::BFS()
{
    if(numberOfVertices == 0)
        return;
   
    //  This vector will keep track of which vertices
    //  Have been visited during transversal
    std::unordered_map<char, bool> visited;

    visited.reserve(numberOfVertices);

    for (adjListItr = adjList.begin(); adjListItr != adjList.end(); adjListItr++)
    {
        visited.insert(std::make_pair(adjListItr->first, false));

    }


    std::unordered_map<char, bool>::iterator visitedItr;

    adjListItr = adjList.begin();
    for (visitedItr = visited.begin(); visitedItr != visited.end(); visitedItr++)
    {
        bool isVisited = visitedItr->second;

        if (!isVisited)
        {
            std::cout << "calling helper with" << visitedItr->first << std::endl;
            visitedItr->second = true;
            BFSHelper(visited, visitedItr, adjListItr);
        }

        ++adjListItr;
    }

}



void Graph::BFSHelper(std::unordered_map<char, bool> &visited, std::unordered_map<char, bool>::iterator visitedItr, const AdjacencyListConstItr adjListConstItr)
{
    std::queue<char> que;
    char currentVertex = adjListConstItr->first;
    que.push(currentVertex);

    std::pair<char, bool> searchPair;

   
    while (!que.empty())
    {
        currentVertex = que.front();

        que.pop();
        std::cout << "Unvisited Neighbors of: " << currentVertex << " : ";
        //  for each neighbor of our current vertex
        for (char vertex : adjList[currentVertex])
        {
            //  Look for the current vertex in the visited vector
            visitedItr = visited.find(vertex);

            //  If the vertex is found in the visited vector and its boolean value 
            //  is false, change the value to true and push the vertex in our que
            if ( (visitedItr != visited.end()) && !visitedItr->second)
            {
                std::cout << vertex <<" ";
                visitedItr->second = true;
                que.push(visitedItr->first);
            }
        }
        std::cout << std::endl;

      
       
    }

    



}








int main()
{

    Graph graph;
    graph.initializeGraph();
    graph.BFS();


    
    int x;
    std::cin >> x;
}

