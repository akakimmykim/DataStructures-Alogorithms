#ifndef GRAPH_H
#define GRAPH_H

#include <cmath>
#include <list>
#include <ostream>
#include <string>
#include "hash.h"
#include "heap.h"

class Graph {
	 private:
			//Make Graph from file
			void makeGraph(std::string source, std::string sink, int cost);

			//Dijkstra's Algorithm
			void dijkstra(std::string source);

			//Constructor
			Graph();
			//Destructor
			~Graph();
	 private:
	 
	 //Vertex class
	 class Vertex{
			public:	
	 }



};:wq

