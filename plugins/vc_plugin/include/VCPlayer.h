#ifndef Header_qcore_VCPlayer
#define Header_qcore_VCPlayer

#include "Player.h"

namespace qplugin
{


    class VCPlayer : public qcore::Player
    {
        int mMoves;
        qcore::BoardMap baseMap;
        const qcore::Position noWallsDetected = { 0, 0 };
        int secondOptLength = 0;
	qcore::Position myPreviousPos;

        enum BestMove : int8_t
        {
            GoForward = 0x01,
            GoBackward = 0x02,
            GoLeft = 0x03,
            GoRight = 0x04,
            PlaceHorizWall = 0x05,
            PlaceVertWall = 0x06,
            Invalid = 0xF
        };
       
        struct LevelInfo
        {
            int8_t myPathLen;
            qcore::Position wallPosition;
        };


        struct nextMove
        {
            qcore::Direction direction;
	        qcore::Position nextPos;
            uint8_t nextPathLen;
            uint8_t levelNo;
        };

	    struct optNextMove
	    {
		    nextMove firstNextMove;
		    nextMove secondNextMove;
	    };

        struct calcResult
        {
            uint8_t optimalPathLen;
            uint8_t levelNo;
        };


    public:
        bool checkBlockedPathLeft(qcore::Position playerPos);
        bool checkBlockedPathRight(qcore::Position playerPos);

        qplugin::VCPlayer::nextMove getNextPosition(uint8_t optIndex, qcore::Position playerPos);
        bool defineWallPos(qplugin::VCPlayer::nextMove nextMoveInfo, qcore::Position myPos, qcore::Position opPos);

        qplugin::VCPlayer::calcResult calculateOptimalPath(qcore::Position playerPos);
        qplugin::VCPlayer::calcResult calculateOponentOptimalPath(qcore::Position playerPos);

        qplugin::VCPlayer::nextMove findNextOptimalMove(qcore::Position playerPos, bool disableSecondTry);
        qplugin::VCPlayer::nextMove findNextOponentOptimalMove(qcore::Position playerPos);

        qcore::Position checkWallDetection(qcore::Position playerPos, qcore::Direction direction);

        VCPlayer(qcore::PlayerId id, const std::string& name, qcore::GamePtr game);
        void doNextMove() override;
    };
}

#endif // Header_qcore_VCPlayer
