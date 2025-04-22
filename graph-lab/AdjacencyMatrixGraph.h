#ifndef ADJACENCYMATRIXGRAPH_H
#define ADJACENCYMATRIXGRAPH_H

#include "DirectedGraph.h"
using namespace std;
class AdjacencyMatrixGraph : public DirectedGraph {
protected:
   vector<Vertex*> vertices;
   
   // If matrixRows[X][Y] is true, then an edge exists from vertices[X] to
   // vertices[Y]
   vector<vector<bool>> matrixRows;
   
   
public:    
   virtual ~AdjacencyMatrixGraph() {
      for (Vertex* vertex : vertices) {
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
      
      Vertex* v = new Vertex(newVertexLabel);
      vertices.push_back(v);

      for(auto& row : matrixRows){
         row.push_back(false);
      }

      matrixRows.push_back(vector<bool>(vertices.size(), false));

      return v;
   }
   
   // Adds a directed edge from the first to the second vertex. If the edge
   // already exists in the graph, no change is made and false is returned.
   // Otherwise the new edge is added and true is returned.
   virtual bool AddDirectedEdge(Vertex* fromVertex, Vertex* toVertex) override {
      int fromIdx = -1, toIdx = -1;
      for(int i=0; i < (int)vertices.size(); ++i){
         if(vertices[i] == fromVertex) fromIdx = i;
         if(vertices[i] == toVertex) toIdx = i;
      }
      if(fromIdx < 0 || toIdx < 0) return false;

      if(matrixRows[fromIdx][toIdx]){
         return false;
      }

      matrixRows[fromIdx][toIdx] = true;
      return true;
   }
    
   // Returns a vector of edges with the specified fromVertex.
   virtual vector<Edge> GetEdgesFrom(Vertex* fromVertex) override {
      vector<Edge> out;
      int fromIdx = -1;
      for(int i=0; i < (int)vertices.size(); ++i){
         if(vertices[i] == fromVertex){
            fromIdx = i;
            break;
         }
      }
      if(fromIdx < 0) return out;
      
      for(int j=0; j < (int)vertices.size(); ++j){
         if(matrixRows[fromIdx][j]){
            out.emplace_back(fromVertex, vertices[j]);
         }
      }
      return out;
   }
    
   // Returns a vector of edges with the specified toVertex.
   virtual vector<Edge> GetEdgesTo(Vertex* toVertex) override {
      vector<Edge> out;
      int toIdx = -1;
      for (int i = 0; i < (int)vertices.size(); ++i) {
         if (vertices[i] == toVertex) {
            toIdx = i;
            break;
         }
      }
      if (toIdx < 0) return out;

      for (int i = 0; i < (int)vertices.size(); ++i) {
         if (matrixRows[i][toIdx]) {
            out.emplace_back(vertices[i], toVertex);
         }
      }
      return out;
   }
    
   // Returns a vertex with a matching label, or nullptr if no such vertex
   // exists
   virtual Vertex* GetVertex(string vertexLabel) override {
      for (Vertex* v : vertices) {
         if (v->GetLabel() == vertexLabel) {
            return v;
         }
      }
      return nullptr;
   }
    
   // Returns true if this graph has an edge from fromVertex to toVertex
   virtual bool HasEdge(Vertex* fromVertex, Vertex* toVertex) override {
      int fromIdx = -1, toIdx = -1;
      for (int i = 0; i < (int)vertices.size(); ++i) {
         if (vertices[i] == fromVertex) fromIdx = i;
         if (vertices[i] == toVertex)   toIdx   = i;
      }
      if (fromIdx < 0 || toIdx < 0) return false;
      return matrixRows[fromIdx][toIdx];
   }
};

#endif