// Copyright 2021 Kovalev Ruslan
#include <mpi.h>
#include "../../../modules/task_2/kovalev_r_ring_topology/kovalev_r_ring_topology.h"


MPI_Comm getRingTopology(const MPI_Comm comm) {
  int graph_size;
  MPI_Comm_size(comm, &graph_size);

  int* index_of_graph = new int[graph_size];
  int* edges_of_graph = new int[graph_size];

  for (int i = 0; i < graph_size; i++) {
    index_of_graph[i] = 1;
  }

  for (int i = 0; i < graph_size; i++) {
    edges_of_graph[i] =(i + 1)%(graph_size);
  }

  MPI_Comm ring;

  MPI_Graph_create(comm, graph_size, index_of_graph, edges_of_graph, 0, &ring);

  return ring;
}
