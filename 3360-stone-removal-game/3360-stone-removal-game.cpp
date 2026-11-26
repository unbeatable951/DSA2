class Solution {
public:
    bool canAliceWin(int n) {
        int remove = 10;
        bool aliceTurn = true;

        while (n >= remove) {
            n -= remove;
            remove--;
            aliceTurn = !aliceTurn;
        }

        // aliceTurn now points to the player who CANNOT move,
        // so the previous player (who just moved) won.
        return !aliceTurn;
    }
};