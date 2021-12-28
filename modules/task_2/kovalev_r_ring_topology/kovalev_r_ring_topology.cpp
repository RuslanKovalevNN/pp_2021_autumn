// Copyright 2021 Kovalev Ruslan
#include <mpi.h>

#include "../../../modules/task_2/kovalev_r_ring_topology/kovalev_r_ring_topology.h"


MPI_Comm getRingTopology(const MPI_Comm comm) {
  int graph_size;
  MPI_Comm_size(comm, &graph_size);

  int* index = new int[graph_size];
  int* edges = new int[graph_size];

  for (int i = 0; i < graph_size; i++) {
    index[i] = 1;
  }

  for (int i = 0; i < graph_size; i++) {
    edges[i] = (i + 1) % (graph_size );
  }

  MPI_Comm ring;

  MPI_Graph_create(comm, graph_size, index, edges, 0, &ring);

  return ring;
}
