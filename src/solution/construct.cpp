#include "solution.h"

struct QuadTree {
  std::vector<std::vector<int>> &grid;
  Node *zero = new Node(false, true);
  Node *one = new Node(true, true);

  QuadTree(std::vector<std::vector<int>> &grid) : grid(grid) {}
  Node *construct() { return construct(0, 0, grid.size()); }
  Node *construct(unsigned row, unsigned col, unsigned dim);
};

Node *QuadTree::construct(unsigned row, unsigned col, unsigned dim) {
  if (dim == 1) {
    return grid[row][col] == 1 ? one : zero;
  } else {
    dim /= 2;
    Node *top_left = construct(row, col, dim);
    Node *top_right = construct(row, col + dim, dim);
    Node *bottom_right = construct(row + dim, col + dim, dim);
    Node *bottom_left = construct(row + dim, col, dim);
    if (top_right == top_left && top_left == bottom_left &&
        bottom_left == bottom_right) {
      return top_right;
    }
    return new Node(false, false, top_left, top_right, bottom_left,
                    bottom_right);
  }
}

Node *Solution::construct(std::vector<std::vector<int>> &grid) {
  return QuadTree(grid).construct();
}
