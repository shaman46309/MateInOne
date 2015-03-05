#include "common.h"

namespace chess {


// We should implement king > queen > rook > bishop > knight > pawn
// TODO(pankajm): This works for inserting in set but not very useful.
bool operator< (const ChessPiece& c1, const ChessPiece& c2) {
    return c1.kind < c2.kind;
}
}
