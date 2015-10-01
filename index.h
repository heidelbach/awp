#ifndef index_h
#define index_h

template<typename T> class Index
{
private:
    Index(Index const &);

    Index(Index *);

    T *container;

    unsigned int *nextIndex;

    unsigned short const sizeX_, sizeY_;

public:
    Index(unsigned short sizeX, unsigned short sizeY);

    ~Index();

    /**
     * @param index
     *      0 <= index < sizeX
     */
    void add(unsigned short index, T const element);

    /**
     * @param index
     *      0 <= index < sizeX
     */
    T get(unsigned short index, unsigned short pos);

};
#endif // ifdef index_h

#include <cstdio>
#include <cstdlib>
#include <cstring>

template <typename T> Index<T>::Index(unsigned short sizeX, unsigned short sizeY) :
        sizeX_(sizeX), sizeY_(sizeY)
{
    size_t size = sizeof(T *);
    size *= sizeX;
    size *= sizeY;
    nextIndex = (unsigned int *) malloc(sizeof(unsigned int) * sizeX);
    container = (T *) malloc(size);
    unsigned int nextIndex_i = 0;
    for (int i = 0; i < sizeX; ++i)
    {
        nextIndex[i] = nextIndex_i;
        nextIndex_i += sizeY;
    }
    memset(container, 0, size);
}

template <typename T> Index<T>::~Index()
{
    free(container);
    free(nextIndex);
}

template <typename T> void Index<T>::add(unsigned short index, T const element)
{
    if (index < 0 || index >=sizeX_)
    {
        fprintf(stderr, "Index::add(index, element)\nInvalid index: %d\n", index);
        abort();
    }
    index = nextIndex[index]++;
    container[index] = element;
}

template <typename T> T Index<T>::get(unsigned short index, unsigned short pos)
{
    if (index < 0 || index >= sizeX_)
    {
        fprintf(stderr, "Index::get(index, pos)\nInvalid index: %d\n", index);
        abort();
    }
    if (pos < 0 || pos >= sizeY_)
    {
        fprintf(stderr, "Index::get(index, pos)\nInvalid pos: %d\n", pos);
        abort();
    }
    unsigned int offset = index * sizeY_ + pos;
    return container[offset];
}
