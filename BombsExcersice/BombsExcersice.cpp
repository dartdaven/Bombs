#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>

enum class Type { Empty, Bomb };

std::unordered_map<Type, char> typeCharMap
{
    { Type::Empty, '.' },
    { Type::Bomb, 'O' }
};

class Cell
{
public:
    Cell(Type type = Type::Empty, int maxLifetime = 3) : type{ type }, maxLifetime{ maxLifetime }, lifetime{ 0 } {}

    void setType(Type t) { type = t; }
    Type getType() const { return type; }

    void becomeEmpty()
    {
        type = Type::Empty;
        lifetime = 0;
    }
    
    int getLifetime() const { return lifetime; }
    int getMaxLifetime() const { return maxLifetime; }
    void incrementLifetime(int value) { lifetime += value; }

private:
    Type type;
    int maxLifetime;
    int lifetime;
};

class BombsField
{
public:
    BombsField(const int& rows, const int& cols) : rows(rows), cols(cols), field(rows, std::vector<Cell>(cols)) {}

    void print(std::ostream& ostream) const
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {   
                ostream << typeCharMap.at(field[i][j].getType());
            }
            ostream << std::endl;
        }
    }

    void setType(Type type, int x, int y) { field[x][y].setType(type); }

    void explodeBomb(int x, int y)
    {
        for (int i = std::max(y - 1, 0); i <= std::min(y + 1, cols - 1); ++i)
        {
            if (field[x][i].getLifetime() >= field[x][i].getMaxLifetime() && i != y) { explodeBomb(x, i); }
            else if (field[x][i].getType() == Type::Bomb) { field[x][i].becomeEmpty(); }
        }

        for (int i = std::max(x - 1, 0); i <= std::min(x + 1, rows - 1); ++i)
        {
            if (field[i][y].getLifetime() >= field[i][y].getMaxLifetime() && i != x) { explodeBomb(i, y); }
            else if (field[i][y].getType() == Type::Bomb) { field[i][y].becomeEmpty(); }
        }
    }

    void waitSomeTime(int value)
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (field[i][j].getType() == Type::Bomb ) { field[i][j].incrementLifetime(value); }
            }
        }
    }
 
    void fillStroke()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (field[i][j].getType() == Type::Bomb) { field[i][j].incrementLifetime(1); }
                else if (field[i][j].getType() == Type::Empty) { field[i][j].setType(Type::Bomb); }
            }
        }
    }

    void explodeStroke()
    {
        waitSomeTime(1);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (field[i][j].getType() == Type::Bomb && field[i][j].getLifetime() >= field[i][j].getMaxLifetime()) { explodeBomb(i, j); }
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
            for (const auto& pair : typeCharMap)
            {
                if (pair.second == temp[j]) { bombsField.setType(pair.first, i, j); break; }
            }
        }
    }

    inputFile.close();

    bombsField.waitSomeTime(1);
    --secs;

    for (int i = 0; i < secs; ++i)
    {
        if (!(i % 2)) { bombsField.fillStroke(); }
        else bombsField.explodeStroke();
    }

    std::ofstream outputFile("output.txt");
    if (outputFile.is_open())
    {
        bombsField.print(outputFile);
        outputFile.close();
    }
    else { std::cout << "Could not create output file" << std::endl; }

    return 1;
}