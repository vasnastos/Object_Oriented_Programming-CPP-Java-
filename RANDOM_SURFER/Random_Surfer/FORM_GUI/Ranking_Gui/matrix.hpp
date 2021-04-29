#include "pagerankstruct.hpp"
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <queue>

class matrix
{
    protected:
       int rows;
       int cols;
       int **p;
       int *visits;
       std::priority_queue <pagerank> rank;
       int previous_top_rank;
    public:
     static std::vector <pagerank> ranking;
      matrix(int number_of_rows_cols);
      ~matrix();
      int size();
      void add_visits(int page);
      int* get(int r);
      std::vector <int> getNeibourghs(int r);
      void find_rank();
      void print_ranking();
      friend std::ostream &operator<<(std::ostream &os,const matrix &m);
};