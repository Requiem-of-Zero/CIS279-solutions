#ifndef ADJACENCYLISTGRAPH_H
#define ADJACENCYLISTGRAPH_H

#include "DirectedGraph.h"
#include "AdjacencyListVertex.h"
using namespace std;
class AdjacencyListGraph : public DirectedGraph {
protected:
   vector<AdjacencyListVertex*> vertices;
   
public:    
   virtual ~AdjacencyListGraph() {
      for (AdjacencyListVertex* vertex : vertices) {
         delete vertex;
      }
   }

   // Creates and adds a new vertex to the graph, provided a vertex with the
   // same label doesn't already exist in the graph. Returns the new vertex on
   // success, nullptr on failure.
   virtual Vertex* AddVertex(string newVertexLabel) override {
      if(GetVertex(newVertexLabel) != nullptr){
         return nullptr;
      }

      AdjacencyListVertex* v = new AdjacencyListVertex(newVertexLabel);
      vertices.push_back(v);
      return v;
   }
    
   // Adds a directed edge from the first to the second vertex. If the edge
   // already exists in the graph, no change is made and false is returned.
   // Otherwise the new edge is added and true is returned.
   virtual bool AddDirectedEdge(Vertex* fromVertex, Vertex* toVertex) override {
      AdjacencyListVertex* fromV = dynamic_cast<AdjacencyListVertex*>(fromVertex);
      AdjacencyListVertex* toV = dynamic_cast<AdjacencyListVertex*>(toVertex);
      if(!fromV || !toV){
         return false;
      }
      
      for(Vertex* adj : fromV->adjacent){
         if(adj == toV){
            return false;
         }
      }

      fromV->adjacent.push_back(toV);
      return true;
   }
    
   // Returns a vector of edges with the specified fromVertex.
   virtual vector<Edge> GetEdgesFrom(Vertex* fromVertex) override {
      vector<Edge> out;
      AdjacencyListVertex* fromV = dynamic_cast<AdjacencyListVertex*>(fromVertex);
      if(!fromV) return out;
      for(Vertex* adj : fromV->adjacent){
         out.emplace_back(fromVertex, adj);
      }
      return out;
   }
    
   // Returns a vector of edges with the specified toVertex.
   virtual vector<Edge> GetEdgesTo(Vertex* toVertex) override {
      vector<Edge> out;
      for(AdjacencyListVertex* v : vertices){
         for(Vertex* adj : v->adjacent){
            if(adj == toVertex){
               out.emplace_back(v, toVertex);
            }
         }
      }
      return out;
   }
    
   // Returns a vertex with a matching label, or nullptr if no such vertex
   // exists
   virtual Vertex* GetVertex(string vertexLabel) override {
      for(AdjacencyListVertex* v: vertices){
         if(v->GetLabel() == vertexLabel){
            return v;
         }
      }
      return nullptr;
   }
    
   // Returns true if this graph has an edge from fromVertex to toVertex
   virtual bool HasEdge(Vertex* fromVertex, Vertex* toVertex) override {
      AdjacencyListVertex* fromV = dynamic_cast<AdjacencyListVertex*>(fromVertex);
      if(!fromV) return false;
      for(Vertex* adj : fromV->adjacent){
         if(adj == toVertex){
            return true;
         }
      }
      return false;
   }
};

#endif