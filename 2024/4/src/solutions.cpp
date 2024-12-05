#include "solutions.h"
#include <numeric>
#include <vector>

void Matrix::cout() {
    for (auto &rows : this->data) {
        for (auto &columns : rows) {
            std::cout << columns;
        }
        std::cout << std::endl;
    }
}

// Cout the dimensions: (rows, columns)
void Matrix::coutDim() {
    std::cout << this->matrixSize.first << ", " << this->matrixSize.second << std::endl;
}

const int Matrix::countNrPat() {
    int searchFounds = 0;
    for (int row=0; row<this->matrixSize.first; row++) {
        for (int col=0; col<this->matrixSize.second; col++) {
            if (this->data[row][col] == 'X') {
                searchFounds += this->countAroundCharPat(row, col);
            }
        }
    }
    return searchFounds;
}

const int Matrix::countNrStar(const int &marginal) {
    int searchFounds = 0;
    for (int row=0+marginal; row<this->matrixSize.first-marginal; row++) {
        for (int col=0+marginal; col<this->matrixSize.second-marginal; col++) {
            if (this->data[row][col] == 'A') {
                searchFounds += this->countAroundCharStar(row, col);
            }
        }
    }
    return searchFounds;
}

const int Matrix::checkString(const std::vector<int> &rows, const std::vector<int> &cols) {
    std::string s;
    for (int i=0; i<this->patLength; i++) {
        s += this->data[rows[i]][cols[i]];
    }

    // Debug cout of string
    /* std::cout << s << std::endl; */
    if (s == this->pat) return 1;

    return 0;
}

const std::vector<int> Matrix::decrementVec(const int startVal) {
    std::vector<int> v(this->patLength);
    const int smallestValue = startVal - this->patLength + 1;
    std::iota(v.rbegin(), v.rend(), smallestValue);
    return v;
};
const std::vector<int> Matrix::incrementVec(const int startVal) {
    std::vector<int> v(this->patLength);
    std::iota(v.begin(), v.end(), startVal);
    return v;
};

const int Matrix::countAroundCharPat(int &row, int &col) {
    int searchFounds = 0;
    bool safeUp = row > this->marginalUp;
    bool safeDown = row < this->marginalDown;
    bool safeLeft = col > this->marginalLeft;
    bool safeRight = col < this->marginalRight;

    // Up
    if (safeUp) {
        const std::vector<int> rows = this->decrementVec(row);
        const std::vector<int> cols(this->patLength, col);
        searchFounds += this->checkString(rows, cols);

        if (safeRight) {
            searchFounds += this->checkString(rows, this->incrementVec(col));
        }
        if (safeLeft) {
            searchFounds += this->checkString(rows, this->decrementVec(col));
        }
    }
    // Down
    if (safeDown) {
        const std::vector<int> rows = this->incrementVec(row);
        const std::vector<int> cols(this->patLength, col);
        searchFounds += this->checkString(rows, cols);

        if (safeRight) {
            searchFounds += this->checkString(rows, this->incrementVec(col));
        }
        if (safeLeft) {
            searchFounds += this->checkString(rows, this->decrementVec(col));
        }
    }

    // Left
    if (safeLeft) {
        const std::vector<int> rows(this->patLength, row);
        const std::vector<int> cols = this->decrementVec(col);
        searchFounds += this->checkString(rows, cols);
    }
    // Right
    if (safeRight) {
        const std::vector<int> rows(this->patLength, row);
        const std::vector<int> cols = this->incrementVec(col);
        searchFounds += this->checkString(rows, cols);
    }

    return searchFounds;
}
const bool Matrix::starMatch(
    char &rightUpper,
    char &leftUpper,
    char &rightDown,
    char &leftDown) {
    // pat[0] = M, pat[2] = S
    if (
        (rightUpper==this->pat[0] && leftDown==this->pat[2] ||
        rightUpper==this->pat[2] && leftDown==this->pat[0])
        &&
        (rightDown==this->pat[0] && leftUpper==this->pat[2] ||
        rightDown==this->pat[2] && leftUpper==this->pat[0])
    ) return true;

    return false;
}

const int Matrix::countAroundCharStar(int &row, int &col) {
    // Get the "star" around the middle char
    char rightUpper = this->data[row-1][col+1];
    char leftUpper = this->data[row-1][col-1];
    char rightDown = this->data[row+1][col+1];
    char leftDown = this->data[row+1][col-1];

    if (
        this->starMatch(rightUpper, leftUpper, rightDown, leftDown)
    ) return 1;

    return 0;
}

int firstSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();
    std::string pat = "XMAS";
    Matrix matrix(fileContents, pat);

    int resultFirst = 0;
    resultFirst += matrix.countNrPat();

    return resultFirst;
};


int secondSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();
    std::string pat = "MAS";
    Matrix matrix(fileContents, pat);

    int resultSecond = 0;
    const int marginal = 1;
    resultSecond += matrix.countNrStar(marginal);

    return resultSecond;
}
