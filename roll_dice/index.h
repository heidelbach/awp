#ifndef index_h
#define index_h

struct T_Player
{
    char *name;
    int *results;
    int *count;
    int sum;
    unsigned short idx;
    unsigned short rank;
};

class Index
{
private:
    Index(Index const &);

    Index(Index *);

    struct T_Player *container_;

    unsigned short const sizeX_, sizeY_;

    unsigned short const minResult_, maxResult_;

    void swap(signed int, signed int);

    void sortBySum_(signed int, signed int);

public:
    Index(unsigned short numPlayers, unsigned short numRolls, char **names,
            unsigned short min, unsigned short max);

    ~Index();

    bool addRoll(unsigned short player, unsigned short pos, int result,
            bool unique = false);

    int getRoll(unsigned short player, unsigned short pos);

    char *name(unsigned short player);

    void printTable();

    void printResults();

    void sortBySum();

    unsigned short getRank(unsigned short player);

    unsigned short getIdx(unsigned short player);
};
#endif // ifdef index_h
