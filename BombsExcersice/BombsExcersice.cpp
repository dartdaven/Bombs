#include <iostream>
#include <vector>
#include <fstream>
#include <string>

enum Type {Empty, Bomb, Wall};

class Cell
{
public:
    Cell() : type{ Empty }, lifetime{ 0 }, maxLifetime{ 3 } {}

    void setType(Type t) { type = t; }
    Type getType() const { return type; }

    void becomeEmpty()
    {
        type = Empty;
        lifetime = 0;
    }
    
    int getLifetime() const { return lifetime; }
    int getMaxLifetime() const { return maxLifetime; }
    void increaseLifetime() { ++lifetime; }

private:
    Type type;
    int lifetime;
    int maxLifetime;
};

class BombsField
{
public:
    BombsField(const int& rows, const int& cols) : rows(rows), cols(cols), field(rows, std::vector<Cell>(cols)) {}

    void print() const
    {
        std::ofstream outputFile("output.txt");

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {   
                switch (field[i][j].getType())
                {
                    case Empty: outputFile << '.'; break;
                    case Bomb: outputFile << 'O'; break;
                    case Wall: outputFile << '#'; break;
                }
            }
            outputFile << std::endl;
        }
        outputFile.close();
    }

    void setBomb(int x, int y) { field[x][y].setType(Bomb); }
    void setWall(int x, int y) { field[x][y].setType(Wall); }

    void explodeBomb(int x, int y)
    {
        field[x][y].becomeEmpty();

        if (x != 0)
        {
            if (field[x - 1][y].getLifetime() >= field[x - 1][y].getMaxLifetime()) { explodeBomb(x - 1, y); }
            else if (field[x - 1][y].getType() == Bomb) { field[x - 1][y].becomeEmpty(); }
        }
        if (y != 0)
        {
            if (field[x][y - 1].getLifetime() >= field[x][y - 1].getMaxLifetime()) { explodeBomb(x, y - 1); }
            else if (field[x][y - 1].getType() == Bomb) { field[x][y - 1].becomeEmpty(); }
        }
        if (x != rows - 1)
        {
            if (field[x + 1][y].getLifetime() >= field[x + 1][y].getMaxLifetime()) { explodeBomb(x + 1, y); }
            else if (field[x + 1][y].getType() == Bomb) { field[x + 1][y].becomeEmpty(); }
        }
        if (y != cols - 1)
        {
            if (field[x][y + 1].getLifetime() >= field[x][y + 1].getMaxLifetime()) { explodeBomb(x, y + 1); }
            else if (field[x][y + 1].getLifetime() == Bomb) { field[x][y + 1].becomeEmpty(); }
        }
    }

    void waitASec()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (field[i][j].getType() == Bomb ) { field[i][j].increaseLifetime(); }
            }
        }
    }
 
    void fillStroke()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (field[i][j].getType() == Bomb) { field[i][j].increaseLifetime(); }
                else if (field[i][j].getType() == Empty) { field[i][j].setType(Bomb); }
            }
        }
    }

    void explodeStroke()
    {
        waitASec();

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (field[i][j].getType() == Bomb && field[i][j].getLifetime() >= field[i][j].getMaxLifetime()) { explodeBomb(i, j); }
            }
        }
    }

private:
    int rows, cols;
    std::vector<std::vector<Cell>> field;
};

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile) 
    { 
        std::cout << "Can't find input.txt" << std::endl;
        std::cout << "Make sure that input.txt is in the same folder with .exe" << std::endl;
        return 1;
    }

    int rows{ 0 }, cols{ 0 }, secs{ 0 };
    inputFile >> rows >> cols >> secs;

    BombsField bombsField(rows, cols);

    std::string temp;

    for (int i = 0; i < rows; ++i)
    {
        inputFile >> temp;
        for (int j = 0; j < cols; ++j)
        {
            if (temp[j] != '.')
            {
                bombsField.setBomb(i, j);
            }
        }
    }

    //проверка на стену
    //bombsField.setWall(3, 1);

    inputFile.close();

    bombsField.waitASec();
    --secs;

    for (int i = 0; i < secs; ++i)
    {
        if (i % 2 == 0) { bombsField.fillStroke(); }
        else bombsField.explodeStroke();
    }

    bombsField.print();

    return 1;
}