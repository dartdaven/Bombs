#include <iostream>
#include <vector>

class Bomb
{
public:
    Bomb() : active{ false }, lifetime{ 0 } {}

    void activate() { active = true; }
    void deactivate()
    {
        active = false;
        lifetime = 0;
    }
    
    int getLifetime() const { return lifetime; }
    void increaseLifetime() { ++lifetime; }
    
    char print() const { return active ? 'O' : '.'; }

private:
    bool active;
    int lifetime;
};

class BombsField
{
public:
    BombsField(const int& rows, const int& cols) : rows(rows), cols(cols), field(rows, std::vector<Bomb>(cols)) {}

    void print() const
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                std::cout << field[i][j].print();
            }
            std::cout << std::endl;
        }
    }

    void activateBomb(int x, int y) { field[x][y].activate(); }
    
    //void energizeBomb(int x, int y) 
    //{ 
    //    field[x][y].increaseLifetime();
    //    field[x][y].increaseLifetime();
    //    field[x][y].increaseLifetime();
    //}


    void explodeBomb(int x, int y)
    {
        field[x][y].deactivate();

        if (x != 0)
        {
            if (field[x - 1][y].getLifetime() >= 3) { explodeBomb(x - 1, y); }
            else { field[x - 1][y].deactivate(); }
        }
        if (y != 0)
        {
            if (field[x][y - 1].getLifetime() >= 3) { explodeBomb(x, y - 1); }
            else { field[x][y - 1].deactivate(); }
        }
        if (x != rows - 1)
        {
            if (field[x + 1][y].getLifetime() >= 3) { explodeBomb(x + 1, y); }
            else { field[x + 1][y].deactivate(); }
        }
        if (y != cols - 1)
        {
            if (field[x][y + 1].getLifetime() >= 3) { explodeBomb(x, y + 1); }
            else { field[x][y + 1].deactivate(); }
        }
    }


    void explodeStroke()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (field[i][j].print() == 'O') { field[i][j].increaseLifetime(); }

            }
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (field[i][j].getLifetime() >= 3) { explodeBomb(i, j); }
            }
        }

    }

    void fillStroke()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (field[i][j].print() == 'O') { field[i][j].increaseLifetime(); }
                else { field[i][j].activate(); }
            }
        }
    }

    void firstStroke()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (field[i][j].print() == 'O') { field[i][j].increaseLifetime(); }
            }
        }
    }

private:
    int rows, cols;
    std::vector<std::vector<Bomb>> field;
};

int main()
{
    int rows{ 0 }, cols{ 0 }, secs{ 0 };
    std::cin >> rows >> cols >> secs;

    BombsField bombsField(rows, cols);

    std::string temp;

    for (int i = 0; i < rows; ++i)
    {
        std::cin >> temp;
        for (int j = 0; j < cols; ++j)
        {
            if (temp[j] != '.')
            {
                bombsField.activateBomb(i, j);
            }
        }
    }

    bombsField.firstStroke();
    --secs;

    for (int i = 0; i < secs; ++i)
    {
        if (i % 2 == 0) { bombsField.fillStroke(); }
        else bombsField.explodeStroke();
    }

    std::cout << std::endl;

    bombsField.print();
}