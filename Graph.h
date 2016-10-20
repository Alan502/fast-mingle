#ifndef MINGLE_GRAPH_H
#define MINGLE_GRAPH_H

#include "ANN/ANN.h"
#include <unordered_set>
#include <cmath>

/**
 * Represents the 4-dimensional graph, Γ, that has all the edges.
 */
class Graph {
public:
    Graph() {}
    ~Graph() {}
    /**
     * Reads the edges from a file.
     */
    void readEdgesFromFile(const char *edgesFilePath);

    /**
     * Mingles the nodes stored in this graph.
     */
    void doMingle();

    /**
     * Estimates the ink saved when two edges are bundled.
     */
    double estimateSavedInkWhenTwoEdgesBundled(Edge *node1, Edge *node2);

private:
    /**
     * These two members are needed by the ANN library
     * to make the search
     * annPoints stores the points in the graph.
     * annTree stores the points as a graph to perform the search.
     */
    ANNpointArray annPoints = nullptr;
    ANNkd_tree *annTree = nullptr;

    /**
     * The list of the top-level nodes in this graph.
     */
    std::vector<Edge*> _edges;

    /**
     * Reads the next line of a file.
     */
    void readNextEdgeInFile(FILE *filePointer);

    /**
     * Rebuilds the ANN index to include all the root nodes. This allows us
     * to search with the new list of root nodes.
     */
    void rebuildAnnIndex();

    /**
     * Gets the centroid of the first points of node 1 and node 2.
     */
    PointOrStar getCentroidForPoints(PointOrStar *point1, PointOrStar *point2) {
    	int combinedWeight = point1->getWeight() + point2->getWeight();
    	double x = (point1->getX() * point1->getWeight() + point2->getX() * point2->getWeight()) / combinedWeight;
    	double y = (point1->getY() * point1->getWeight() + point2->getY() * point2->getWeight()) / combinedWeight;
    }
    /**
     *
     */
    double getInkToDrawEdgesBetweenNodeAndChildren(P *node, std::vector<Point*> children);

    double getDistanceBetweenPoints(PointOrStar point1, PointOrStar point2) {
    	return sqrt((point1.getX() - point2.getX())^2 + (point1.getY() - point2.getY())^2);
    }


    /**
     *
     */

    const double LOOKUP_RANGE = 0.25;

    const double TOLERANCE_RANGE = 0.01;

    const double GOLD_RATIO = 1.618034;

    const int GOLD_SECTION_SEARCH_MAX_LOOPS = 10;

};

#endif //MINGLE_GRAPH_H
