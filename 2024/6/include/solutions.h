#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

int firstSolution(std::string fileName);
int secondSolution(std::string fileName);

enum Direction { NORTH, EAST, SOUTH, WEST };
enum Object {
    SPACE,
    OBSTICLE,
};

struct Pos {
    Pos(const int& row, const int& col) : row(row), col(col) {}
    int row;
    int col;

    bool operator<(const Pos& other) const {
        return row < other.row || (row == other.row && col < other.col);
    }
};

class Matrix {
   public:
    Matrix(std::ifstream& file) : file(file) {
        std::vector<char> d1Vector;
        std::string line;
        int row = 0;
        while (std::getline(this->file, line)) {
            int col = 0;  // Current position in matrix
            for (auto& c : line) {
                if (this->directionMap.find(c) != this->directionMap.end()) {
                    this->guardPos = Pos(row, col);
                    this->visitedPos.insert(this->guardPos);
                    this->setDirection(c);
                }
                d1Vector.push_back(c);
                col++;
            }
            this->data.push_back(d1Vector);
            d1Vector.clear();
            row++;
        }
        matrixSize = {this->data.size(), this->data[0].size()};
    };

    /**
     * @brief Move the guardian if possible
     *
     * @return flase until the next step is out of the matrix
     */
    const bool guardStep() {
        int newRow, newCol;
        switch (this->direction) {
            case Direction::NORTH:
                newRow = this->guardPos.row - 1;
                newCol = this->guardPos.col;
                if (newRow < 0) return false;
                break;
            case Direction::EAST:
                newRow = this->guardPos.row;
                newCol = this->guardPos.col + 1;
                if (newCol > this->matrixSize.first - 1) return false;
                break;
            case Direction::SOUTH:
                newRow = this->guardPos.row + 1;
                newCol = this->guardPos.col;
                if (newRow > this->matrixSize.first - 1) return false;
                break;
            case Direction::WEST:
                newRow = this->guardPos.row;
                newCol = this->guardPos.col - 1;
                if (newCol < 0) return false;
                break;
        }
        this->moveOrRotate(newRow, newCol);
        return true;
    }

    // Cout the entire matrix
    void cout() {
        for (auto& rows : this->data) {
            for (auto& columns : rows) {
                std::cout << columns;
            }
            std::cout << std::endl;
        }
    }

    // Cout the dimensions: (rows, columns)
    void coutDim() {
        std::cout << this->matrixSize.first << ", " << this->matrixSize.second << std::endl;
    }

    // Draw where we've been
    void visitedCout() {}

    std::set<Pos> visitedPos;

   private:
    std::vector<std::vector<char>> data;
    std::pair<int, int> matrixSize;
    std::ifstream& file;

    Pos guardPos = Pos(0, 0);  // Initialize to random pos
    Direction direction;
    std::unordered_map<char, Direction> directionMap{
        {'^', Direction::NORTH},
        {'>', Direction::EAST},
        {'v', Direction::SOUTH},
        {'<', Direction::WEST},
    };

    std::unordered_map<char, Object> objectMap{
        {'.', Object::SPACE},
        {'#', Object::OBSTICLE},
    };

    // Set direction based on char as enum
    void setDirection(const char& c) {
        this->direction = this->directionMap[c];
    }

    const Object getObjectAhead(const int& row, const int& col) {
        char c = this->data[row][col];
        return objectMap[c];
    }

    void rotateDirection() {
        switch (this->direction) {
            case Direction::NORTH:
                this->direction = Direction::EAST;
                break;
            case Direction::EAST:
                this->direction = Direction::SOUTH;
                break;
            case Direction::SOUTH:
                this->direction = Direction::WEST;
                break;
            case Direction::WEST:
                this->direction = Direction::NORTH;
                break;
        }
    }

    void moveOrRotate(const int& newRow, const int& newCol) {
        Object objectAhead = this->getObjectAhead(newRow, newCol);
        if (objectAhead == Object::SPACE) {
            this->guardPos = Pos(newRow, newCol);
            this->visitedPos.insert(this->guardPos);
            // For debug only
            /* this->data[newRow][newCol] = 'X'; */
        } else {
            this->rotateDirection();
        }
    }
};

class FileOps {
   public:
    FileOps(const std::string& fileName) : file(fileName) {
        if (!file) {
            std::cout << "Failed to read file: " << fileName << std::endl;
        }
    };

    // Get the file contents as is
    std::ifstream& getFile() {
        return file;
    };

    // Get all lines from the file as one string
    const std::string getFileContentAsOneString() {
        std::string line(
            (std::istreambuf_iterator<char>(this->file)), std::istreambuf_iterator<char>());
        return line;
    };

   private:
    std::ifstream file;
};
