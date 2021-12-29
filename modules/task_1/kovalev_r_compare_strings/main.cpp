// Copyright 2018 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./compare_strings.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Compare_two_string_with_different_size) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  std::string first_string;
  std::string second_string;
  if (rank == 0) {
    first_string = getRandomString(6);
    second_string = getRandomString(6);
  }
  int global_compare = getParallelOperations(first_string, second_string);
  if (rank == 0) {
    int local_compare = getSequentialOperations(first_string, second_string);
    ASSERT_EQ(local_compare, global_compare);
  }
}

TEST(Parallel_Operations_MPI, Compare_two_string_with_different_size_1) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  std::string first_string;
  std::string second_string;
  if (rank == 0) {
    first_string = getRandomString(12);
    second_string = getRandomString(12);
  }
  int global_compare = getParallelOperations(first_string, second_string);
  if (rank == 0) {
    int local_compare = getSequentialOperations(first_string, second_string);
    ASSERT_EQ(local_compare, global_compare);
  }
}

TEST(Parallel_Operations_MPI, Compare_two_string_with_different_size_2) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  std::string first_string;
  std::string second_string;
  if (rank == 0) {
    first_string = getRandomString(18);
    second_string = getRandomString(18);
  }
  int global_compare = getParallelOperations(first_string, second_string);
  if (rank == 0) {
    int local_compare = getSequentialOperations(first_string, second_string);
    ASSERT_EQ(local_compare, global_compare);
  }
}

TEST(Parallel_Operations_MPI, Compare_two_string_with_different_size_3) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  std::string first_string;
  std::string second_string;
  if (rank == 0) {
    first_string = "abcabc";
    second_string = "aaaaac";
  }
  int global_compare = getParallelOperations(first_string, second_string);
  if (rank == 0) {
    int local_compare = getSequentialOperations(first_string, second_string);
    ASSERT_EQ(local_compare, global_compare);
  }
}

TEST(Parallel_Operations_MPI, Compare_two_string_with_different_size_6) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  std::string first_string;
  std::string second_string;
  if (rank == 0) {
    first_string = getRandomString(8);
    second_string = getRandomString(8);
  }
  int global_compare = getParallelOperations(first_string, second_string);
  if (rank == 0) {
    int local_compare = getSequentialOperations(first_string, second_string);
    ASSERT_EQ(local_compare, global_compare);
  }
}

TEST(Parallel_Operations_MPI, Compare_two_string_with_different_size_7) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  std::string first_string;
  std::string second_string;
  if (rank == 0) {
    first_string = getRandomString(8);
    second_string = getRandomString(11);
  }
  int global_compare = getParallelOperations(first_string, second_string);
  if (rank == 0) {
    int local_compare = getSequentialOperations(first_string, second_string);
    ASSERT_EQ(local_compare, global_compare);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);
  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
    ::testing::UnitTest::GetInstance()->listeners();
  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());
  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
