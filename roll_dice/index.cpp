#include "index.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

Index::Index(unsigned short numPlayers, unsigned short numRolls,
        char **names, unsigned short min, unsigned short max) :
        sizeX_(numPlayers), sizeY_(numRolls), minResult_(1), maxResult_(max)
{
    if (min > max)
    {
        fprintf(stderr, "\rERROR on initializing Index\n"
                "min > max\n");
        abort();
    }
    size_t size = sizeof(struct T_Player);
    size *= numPlayers;
    container_ = (struct T_Player *) malloc(size);
    memset(container_, 0,size);
    for (int i = 0; i < numPlayers; ++i)
    {
        container_[i].name = (char *) malloc(sizeof(char) * (strlen(names[i] + 1)));
        memcpy(container_[i].name, names[i], sizeof(char) * (strlen(names[i]) + 1));
        container_[i].results = (int *) malloc(sizeof(int) * numRolls);
        container_[i].count = (int *) malloc(sizeof(int) * (maxResult_ - minResult_ + 1));
        memset(container_[i].results, 0, sizeof(int) * numRolls);
        memset(container_[i].count, 0, sizeof(int) * (maxResult_ - minResult_ + 1));
        container_[i].rank = container_[i].idx = i + 1;
    }
}

Index::~Index()
{
    for (int i = 0; i < sizeX_; ++i)
    {
        free(container_[i].name);
        free(container_[i].results);
        free(container_[i].count);
    }
    free(container_);
}

bool Index::addRoll(unsigned short player, unsigned short pos, int roll,
        bool unique)
{
    if (player < 0 || player >=sizeX_)
    {
        fprintf(stderr, "Index::addRoll()\nInvalid player: %d\n", player);
        abort();
    }
    if (pos < 0 || pos >= sizeY_)
    {
        fprintf(stderr, "Index::get(index, pos)\nInvalid pos: %d\n", pos);
        abort();
    }
    if (roll < minResult_ || roll > maxResult_)
    {
        fprintf(stderr, "Index::get(index, pos)\nInvalid roll: %d\n", roll);
        abort();
    }
    struct T_Player *const player_ = &container_[player];
    int *const result = &(player_->count[roll - minResult_]);
    if (unique && *result != 0)
    {
        // refuse add result already counted
        return false;
    }
    ++(*result);
    player_->results[pos] = roll;
    player_->sum += roll;
    return true;
}

int Index::getRoll(unsigned short player, unsigned short pos)
{
    if (player < 0 || player >=sizeX_)
    {
        fprintf(stderr, "Index::addRoll()\nInvalid player: %d\n", player);
        abort();
    }
    if (pos < 0 || pos >= sizeY_)
    {
        fprintf(stderr, "Index::get(index, pos)\nInvalid pos: %d\n", pos);
        abort();
    }
    return container_[player].results[pos];
}

char *Index::name(unsigned short player)
{
    if (player < 0 || player >=sizeX_)
    {
        fprintf(stderr, "Index::name()\nInvalid player: %d\n", player);
        abort();
    }
    return container_[player].name;
}

void Index::printResults()
{
    printf("%-30s\n", "pos  id  name");

    for (int player = 0; player < sizeX_; ++player)
    {
        printf("%-3d (%2d): %-30s\n", container_[player].rank,
                container_[player].idx,
                container_[player].name);
        for (int roll = 0; roll < sizeY_; ++roll)
        {
            printf("%s%d", roll == 0 ? " " : roll % 20 == 0 ? "\n " : ",",
                container_[player].results[roll]);
        }
        printf("\n \033[41;38mtotal: %d\033[0m\n\n", container_[player].sum);
    }
}

void Index::printTable()
{
    int const digits = (int)(log(maxResult_) / log(10)) + 1;
    char padding[32];

    sprintf(padding, "%%%ds", digits);
    printf(padding, "");
    printf("\\ ");
    for (int player = 0; player < sizeX_; ++player)
    {
        printf("%4d ", container_[player].idx);
    }
    printf("|\n");

    printf(padding, "");
    printf(" \\");

    for (int player = 0; player < sizeX_; ++player)
    {
        printf("-----");
    }
    printf("|\n");

    sprintf(padding, "%%%dd |", digits);
    for (int result = minResult_, offset = 0; result <= maxResult_; ++offset, ++result)
    {
        printf(padding, result);
        for (int player = 0; player < sizeX_; ++player)
        {
            printf("%4d ", container_[player].count[offset]);
        }
        printf("|\n");
    }
    for (int i = 0; i < digits; ++i)
        printf("-");
    printf("-+");
    for (int player = 0; player < sizeX_; ++player)
    {
        printf("-----");
    }
    printf("|\n");

    sprintf(padding, "%%%ds |", digits);
    printf(padding, "S");

    for (int player = 0; player < sizeX_; ++player)
    {
        printf("%4d ", container_[player].sum);
    }
    printf("|\n\n");
}

unsigned short Index::getRank(unsigned short player)
{
    if (player < 0 || player >=sizeX_)
    {
        fprintf(stderr, "Index::getRank()\nInvalid player: %d\n", player);
        abort();
    }
    return container_[player].rank;
}

unsigned short Index::getIdx(unsigned short player)
{
    if (player < 0 || player >=sizeX_)
    {
        fprintf(stderr, "Index::getIdx()\nInvalid player: %d\n", player);
        abort();
    }
    return container_[player].idx;
}

void Index::swap(signed int a, signed int b)
{
    if (a == b)
        return;
    struct T_Player h = container_[a];
    container_[a] = container_[b];
    container_[b] = h;
}

void Index::sortBySum_(signed int from,
        signed int to)
{
    if (from >= to)
        return;
    unsigned int i = from;
    int pivotS = container_[to - 1].sum;
    int pivotI = container_[to - 1].idx;
    for (int j = from; j < to; ++j)
    {
        if (container_[j].sum > pivotS)
            swap(i++, j);
        else if (container_[j].sum == pivotS && container_[j].idx < pivotI)
            swap(i++, j);
    }
    swap(i, to - 1);
    sortBySum_(from, i);
    sortBySum_(i + 1, to);
}

void Index::sortBySum()
{
    sortBySum_(0, sizeX_);
    for (int i = 0;i < sizeX_; ++i)
    {
        if (i == 0)
            container_[0].rank = 1;
        else
            if (container_[i - 1].sum != container_[i].sum)
                container_[i].rank = i + 1;
            else
                container_[i].rank = container_[i - 1].rank;
    }
}
