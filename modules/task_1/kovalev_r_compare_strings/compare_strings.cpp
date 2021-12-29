// Copyright 2021 Kovalev Ruslan
#include "../../../modules/task_1/kovalev_r_compare_strings/compare_strings.h"
#include <mpi.h>
#include <algorithm>
#include <random>
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>

std::string getRandomString(int sz) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::string str(sz, 'c');
  for (int i = 0; i < sz; i++) {
    str[i] = static_cast<char> (gen() % 52+97);
  }
  return str;
}

int Abs(int x) { return x < 0 ? -1 * x : x; }

int getSequentialOperations(std::string a, std::string b) {
  int size = std::min(a.size(), b.size());
  int count = 0;
  for (int i = 0; i <size; i++) {
    if (a[i] != b[i]) {
      count++;
    }
  }
  return count+Abs(a.length()-b.length());
}

int getParallelOperations(std::string first_string, std::string second_string) {
  int size, rank;
  int diff = Abs(first_string.length() - second_string.length());
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int delta, rem;

  if (first_string.length() > second_string.length()) {
    while (first_string.length() > second_string.length()) {
      first_string.pop_back();
    }
  }

  if (second_string.length() > first_string.length()) {
    while (second_string.length() > first_string.length()) {
      second_string.pop_back();
    }
  }

  if (first_string.length() % size != 0) {
    for (int i = 0;
      i < size -static_cast<int>(first_string.length() % size); i++) {
      first_string += "3";
      second_string += "3";
    }
  }

  if (rank == 0) {
    delta = first_string.length() / size;
    rem = second_string.length() % size;
  }

  MPI_Bcast(&delta, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&rem, 1, MPI_INT, 0, MPI_COMM_WORLD);

  char* buffer = new char[delta + 1];
  MPI_Scatter(first_string.data() + rem, delta, MPI_CHAR, buffer, delta,
              MPI_CHAR, 0, MPI_COMM_WORLD);
  MPI_Scatter(second_string.data() + rem, delta, MPI_CHAR, buffer, delta,
    MPI_CHAR, 0, MPI_COMM_WORLD);

  std::string local_string = buffer;

  int global_num = 0;
  int local_num = getSequentialOperations(first_string, second_string);

  MPI_Reduce(&local_num, &global_num, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  return global_num+diff;
}
