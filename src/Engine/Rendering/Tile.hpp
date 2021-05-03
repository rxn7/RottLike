namespace RottEngine{
    struct Tile{
        // Position in the tile set
        unsigned int x,y;

        Tile(unsigned int x, unsigned int y) : x(x), y(y) { }
    };
}