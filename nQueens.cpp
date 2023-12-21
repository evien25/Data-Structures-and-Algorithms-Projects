/*
 * Eric Vien
 * 11/20/2023
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool checkPlacement(int r, int c, const vector<int> &rowVec) {
    int vertDistance, horizDistance;

    for (int e = 0; e < r; ++e) {
        vertDistance = abs(r - e);
        horizDistance = abs(c - rowVec[e]);

        if (rowVec[e] == c || vertDistance == horizDistance) {
            return false;
        }
    }

    return true;
}

void calculateQueens(int n, int r, int &sum, vector<int> rowVec) {
    if (r == n) {
        sum++;
        return;
    }

    for (int c = 0; c < n; ++c) {
        if (checkPlacement(r, c, rowVec)) {
            rowVec.push_back(c);

            calculateQueens(n, r + 1, sum, rowVec);

            rowVec.pop_back();
        }
    }
}

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n) {
    vector<int> rowVec;
    int sum = 0, halfN = n / 2;

    for (int c = 0; c < halfN; ++c) {
        rowVec = {c};

        calculateQueens(n, 1, sum, rowVec);
    }

    sum *= 2; //account for second half of board
    if (n % 2 != 0) {
        rowVec = {halfN};

        calculateQueens(n, 1, sum, rowVec);
    }

    return sum;
}

int main() {
    int test = nQueens(12);
    //ASSERT_EQ(nQueens(12),14200);
    if (test != 14200)
    {
        std::cout << "expected/correct value for nQueens(12) is 14200, actual value when testing " << test << ".\n";
        return 1;
    }
    std::cout << "Passed" << std::endl;
    return 0;
}
