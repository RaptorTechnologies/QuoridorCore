#include "VCPlayer.h"
#include "QcoreUtil.h"
#include "GameController.h"

#include <queue>
#include <sstream>
#include <iomanip>
#include <chrono>

#include <algorithm>
#include <iostream>
#include <vector>

namespace
{
    /** Log domain */
    const char* const DOM = "qplugin::VC";
}

namespace qplugin
{
    bool VCPlayer::checkBlockedPathLeft(qcore::Position playerPos)
    {
        qcore::Position horizWallPos;
        qcore::Position vertWallPos;
        qcore::Position vertWallPos2;

	    uint8_t lastY = 0;
	    uint8_t oldLastY = 0;
	    uint8_t lastX = 0;
	    uint8_t oldLastX = 0;

	    bool previousWallHoriz = true;
        bool previousWallVert = true;

        bool positionBlocked = false;
	
	    std::list<qcore::WallState> walls = qcore::Player::getBoardState()->getWalls(getId());
	    qcore::WallState *wall;
        int listSize = walls.size();

	    qcore::Player::getBoardState()->createBoardMap(baseMap, qcore::Player::getId());

        for (int x = 0; x <= playerPos.x; x++)
        {
	        if (positionBlocked == false)
	        {
		        for (int y = 0; y < 4; y++)
		        {
			        horizWallPos.x = x;
			        horizWallPos.y = y * 2;

			        for (int k = 0; k < listSize; k++)
			        {	
				        auto it = std::next(walls.begin(), k);
				        wall = &*it;

				        if ((horizWallPos.x == wall->position.x) and (horizWallPos.y == wall->position.y) and (wall->orientation == qcore::Orientation::Horizontal) and (previousWallHoriz == true))
				        {
					        lastY = y * 2 + 2;
				        }
			        }
			
			        if (lastY > oldLastY)
			        {
				        oldLastY = lastY;
				        previousWallHoriz = true;
			        }
			        else
			        {
				         previousWallHoriz = false;
			        }
		        }

		        if (lastY > playerPos.y)
		        {
		            for (int i = x; i <= playerPos.x; i++)
		            {
		                vertWallPos.x = i;
		                vertWallPos.y = lastY;
			            vertWallPos2.x = i - 1;
		                vertWallPos2.y = lastY;

			            for (int k = 0; k < listSize; k++)
			            {	
				            auto it = std::next(walls.begin(), k);
    				        wall = &*it;

				            if (((vertWallPos.x == wall->position.x) and (vertWallPos.y == wall->position.y) and (wall->orientation == qcore::Orientation::Vertical))  and (previousWallVert == true))
				            {
					            lastX = vertWallPos.x + 2;
				            }
				            else if (((vertWallPos2.x == wall->position.x) and (vertWallPos2.y == wall->position.y) and (wall->orientation == qcore::Orientation::Vertical)) and (previousWallVert == true))
				            {
					            lastX = vertWallPos2.x + 2;
				            }
			            }
			
			            if (lastX > oldLastX)
		                {
				            oldLastX = lastX;
				            previousWallVert = true;
			            }
			            else
			            {
				            previousWallVert = false;
			            }
			            i++;
		            }
		        }

		        if (lastX > playerPos.x) 
		        {
			        positionBlocked = true;
		        }
		        else
		        {
			        positionBlocked = false;
		        }
	        }
	    previousWallHoriz = true;
        }
	return positionBlocked;
    }

    bool VCPlayer::checkBlockedPathRight(qcore::Position playerPos)
    {
        qcore::Position horizWallPos;
        qcore::Position vertWallPos;
        qcore::Position vertWallPos2;

	    uint8_t lastY = 8;
	    uint8_t oldLastY = 8;
	    uint8_t lastX = 0;
	    uint8_t oldLastX = 0;

	    bool previousWallHoriz = true;
        bool previousWallVert = true;

        bool positionBlocked = false;
	
	    std::list<qcore::WallState> walls = qcore::Player::getBoardState()->getWalls(getId());
	    qcore::WallState *wall;
        int listSize = walls.size();
        
        qcore::Player::getBoardState()->createBoardMap(baseMap, qcore::Player::getId());

        for (int x = 0; x <= playerPos.x; x++)
        {
	        if (positionBlocked == false)
	        {
		        for (int y = 4; y > 0; y--)
		        {
			        horizWallPos.x = x;
			        horizWallPos.y = y * 2;

			        for (int k = 0; k < listSize; k++)
			        {	
				        auto it = std::next(walls.begin(), k);
                        wall = &*it;

				        if ((horizWallPos.x == wall->position.x) and (horizWallPos.y == wall->position.y) and (wall->orientation == qcore::Orientation::Horizontal) and (previousWallHoriz == true))
				        {
					        lastY = y * 2 - 2;
				        }
			        }
			
			        if (lastY < oldLastY)
			        {
				        oldLastY = lastY;
				        previousWallHoriz = true;
			        }
			        else
			        {
				        previousWallHoriz = false;
			        }
		        }

		        if (lastY <= playerPos.y)
		        {
		            for (int i = x; i <= playerPos.x; i++)
		            {
		                vertWallPos.x = i;
		                vertWallPos.y = lastY;
			            vertWallPos2.x = i - 1;
		                vertWallPos2.y = lastY;

			            for (int k = 0; k < listSize; k++)
			            {	
				            auto it = std::next(walls.begin(), k);
                            wall = &*it;

				            if (((vertWallPos.x == wall->position.x) and (vertWallPos.y == wall->position.y) and (wall->orientation == qcore::Orientation::Vertical))  and (previousWallVert == true))
				            {
					            lastX = vertWallPos.x + 2;
				            }
				            else if (((vertWallPos2.x == wall->position.x) and (vertWallPos2.y == wall->position.y) and (wall->orientation == qcore::Orientation::Vertical)) and (previousWallVert == true))
				            {
					            lastX = vertWallPos2.x + 2;
				            }
			            }
			
			            if (lastX > oldLastX)
		                {
				            oldLastX = lastX;
				            previousWallVert = true;
			            }
			            else
			            {
				            previousWallVert = false;
			            }
			        i++;
		            }
		        }

		        if (lastX > playerPos.x) 
		        {
			        positionBlocked = true;
		        }
		        else
		        {
			        positionBlocked = false;
		        }
	       }
	    previousWallHoriz = true;
        }
	return positionBlocked;
    }


    qplugin::VCPlayer::nextMove VCPlayer::getNextPosition(uint8_t optIndex, qcore::Position playerPos)
    {
        qplugin::VCPlayer::nextMove nextMoveInfo;
        switch (optIndex)
        {
        case 0: nextMoveInfo.direction = qcore::Direction::Up;
                nextMoveInfo.nextPos.x = playerPos.x - 1;
                nextMoveInfo.nextPos.y = playerPos.y;
            break;
        case 1: nextMoveInfo.direction = qcore::Direction::Down;
                nextMoveInfo.nextPos.x = playerPos.x + 1;
                nextMoveInfo.nextPos.y = playerPos.y;
            break;
        case 2: nextMoveInfo.direction = qcore::Direction::Left;
                nextMoveInfo.nextPos.x = playerPos.x;
                nextMoveInfo.nextPos.y = playerPos.y - 1;
            break;
        case 3: nextMoveInfo.direction = qcore::Direction::Right;
                nextMoveInfo.nextPos.x = playerPos.x;
                nextMoveInfo.nextPos.y = playerPos.y + 1;
            break;
        default: /* do nothing */
            break;
        }

        return nextMoveInfo;
    }

    bool VCPlayer::defineWallPos(qplugin::VCPlayer::nextMove nextMoveInfo, qcore::Position myPos, qcore::Position opPos)
    {
        qcore::WallState wall;
	    bool outputVal;

        switch (nextMoveInfo.direction)
        {
        case qcore::Direction::Down:
            wall.orientation = qcore::Orientation::Horizontal;
            wall.position.x = opPos.x;
            wall.position.y = opPos.y;
            if (isValid(wall))
            {
                placeWall(wall);
                outputVal = true;
            }
            else
            {
                wall.position.x = opPos.x;
                wall.position.y = opPos.y - 1;
                if (isValid(wall))
                {
                    placeWall(wall);
                    outputVal = true;
                }
                else
                {
                    outputVal = false;
                }
            }
            break;

        case qcore::Direction::Up:
            if ((myPos.x - opPos.x == 1) && (myPos.y == opPos.y))
            {
                wall.orientation = qcore::Orientation::Horizontal;
                wall.position.x = myPos.x + 1;
                wall.position.y = myPos.y;
                if (isValid(wall))
                {
                    placeWall(wall);
                    outputVal = true;
                }
                else
                {
                    wall.position.x = myPos.x + 1;
                    wall.position.y = myPos.y - 1;
                    if (isValid(wall))
                    {
                        placeWall(wall);
                        outputVal = true;
                    }
                    else
                    {
                        outputVal = false;
                    }
                }
            }
            else
            {
                wall.orientation = qcore::Orientation::Horizontal;
                wall.position.x = opPos.x + 1;
                wall.position.y = opPos.y;
                if (isValid(wall))
                {
                    placeWall(wall);
                    outputVal = true;
                }
                else
                {
                    wall.position.x = opPos.x + 1;
                    wall.position.y = opPos.y - 1;
                    if (isValid(wall))
                    {
                        placeWall(wall);
                        outputVal = true;
                    }
                    else
                    {
                        outputVal = false;
                    }
                }
            }
            break;

        case qcore::Direction::Left:
            wall.orientation = qcore::Orientation::Vertical;
            wall.position.x = opPos.x;
            wall.position.y = opPos.y;
            if (isValid(wall))
            {
                placeWall(wall);
                outputVal = true;
            }
            else
            {
                wall.position.x = opPos.x - 1;
                wall.position.y = opPos.y;
                if (isValid(wall))
                {
                    placeWall(wall);
                    outputVal = true;
                }
                else
                {
                    outputVal = false;
                }
            }

            break;
        case qcore::Direction::Right:
            wall.orientation = qcore::Orientation::Vertical;
            wall.position.x = opPos.x;
            wall.position.y = opPos.y + 1;
            if (isValid(wall))
            {
                placeWall(wall);
                outputVal = true;
            }
            else
            {
                wall.position.x = opPos.x - 1;
                wall.position.y = opPos.y + 1;
                if (isValid(wall))
                {
                    placeWall(wall);
                    outputVal = true;
                }
                else
                {
                    outputVal = false;
                }
            }
            break;
        default: /* do nothing */
            break;
        }
	return outputVal;
    }


    qcore::Position VCPlayer::checkWallDetection(qcore::Position playerPos, qcore::Direction direction)
    {
	    auto walls = qcore::Player::getBoardState()->getWalls(getId());
        bool wallDetected = false;
	    qcore::Position wallPos;

        for (auto& w : walls)
        {
            if (wallDetected != true)
            {
                switch (direction)
                {
                case qcore::Direction::Up:
                    if ((((w.position.y == playerPos.y) && (w.position.x <= playerPos.x)) || ((w.position.y == playerPos.y - 1) && (w.position.x <= playerPos.x))) && (w.orientation == qcore::Orientation::Horizontal))
                    {
                        wallPos = w.position;
                        wallDetected = true;
                    }
                    else
                    {
                        wallPos.x = 0;
                        wallPos.y = playerPos.y;
                    }
                    break;

                case qcore::Direction::Down:
                    if ((((w.position.y == playerPos.y) && (w.position.x > playerPos.x)) || ((w.position.y == playerPos.y - 1) && (w.position.x > playerPos.x))) && (w.orientation == qcore::Orientation::Horizontal))
                    {
                        wallPos = w.position;
                        wallDetected = true;
                    }
                    else
                    {
                        wallPos.x = 8;
                        wallPos.y = playerPos.y;
                    }
                    break;

                case qcore::Direction::Left:
                    if ((((w.position.x == playerPos.x) && (w.position.y <= playerPos.y)) || ((w.position.x == playerPos.x - 1) && (w.position.y <= playerPos.y))) && (w.orientation == qcore::Orientation::Vertical))
                    {
                        wallPos = w.position;
                        wallDetected = true;
                    }
                    else
                    {
                        wallPos.x = playerPos.x;
                        wallPos.y = 0;
                    }
                    break;

                case qcore::Direction::Right:
                    if ((((w.position.x == playerPos.x) && (w.position.y > playerPos.y)) || ((w.position.x == playerPos.x - 1) && (w.position.y > playerPos.y))) && (w.orientation == qcore::Orientation::Vertical))
                    {
                        wallPos = w.position;
                        wallDetected = true;
                    }
                    else
                    {
                        wallPos.x = playerPos.x;
                        wallPos.y = 8;
                    }
                    break;
                }
            }
        }
	    return wallPos;
    }

    /* function which calculates my optimal path*/
    qplugin::VCPlayer::calcResult VCPlayer::calculateOptimalPath(qcore::Position playerPos)
    {
        uint8_t pathLenLeft = 0;
        uint8_t pathLenRight = 0;
        qplugin::VCPlayer::calcResult calculationResult;
        qcore::Position wallDetectedPos;
        qcore::Position wallDetectedPosLevel2;
        qcore::Position leftWallPos;
        qcore::Position rightWallPos;
        qcore::Position playerPosLevel2;
        
        /* Check optimal path */
        wallDetectedPos = checkWallDetection(playerPos, qcore::Direction::Up);
        if (wallDetectedPos.x == 0)
        {
            calculationResult.levelNo = 1;
            calculationResult.optimalPathLen = playerPos.x;
        }
        else
        {
            calculationResult.levelNo = 2;
            calculationResult.optimalPathLen = playerPos.x - wallDetectedPos.x;

            /*check second path to left*/
            playerPosLevel2.x = wallDetectedPos.x;
            playerPosLevel2.y = playerPos.y;
            leftWallPos.x = wallDetectedPos.x - 1;
            leftWallPos.y = playerPos.y;

            if ((!baseMap.isWall(playerPosLevel2)) && (!baseMap.isWall(leftWallPos)))
            {
                playerPosLevel2.y--;
                wallDetectedPosLevel2 = checkWallDetection(playerPosLevel2, qcore::Direction::Up);
                pathLenLeft = calculationResult.optimalPathLen + (wallDetectedPos.x - wallDetectedPosLevel2.x);
            }

            /*check second path to right*/
            playerPosLevel2 = playerPos;
            playerPosLevel2.x = wallDetectedPos.x;
            playerPosLevel2.y++;
            rightWallPos.x = playerPosLevel2.x - 1;
            rightWallPos.y = playerPosLevel2.y;

            if ((!baseMap.isWall(playerPosLevel2)) && (!baseMap.isWall(rightWallPos)))
            {
                wallDetectedPosLevel2 = checkWallDetection(playerPosLevel2, qcore::Direction::Up);
                pathLenRight = calculationResult.optimalPathLen + (wallDetectedPos.x - wallDetectedPosLevel2.x);
            }

            if (pathLenLeft > pathLenRight)
            {
                calculationResult.optimalPathLen = pathLenLeft;
            }
            else
            {
                calculationResult.optimalPathLen = pathLenRight;
            }

        }
        return calculationResult;
    }

    /* function which calculates oponent optimal path*/
    qplugin::VCPlayer::calcResult VCPlayer::calculateOponentOptimalPath(qcore::Position playerPos)
    {
        uint8_t pathLenLeft = 0;
        uint8_t pathLenRight = 0;
        qplugin::VCPlayer::calcResult calculationResult;
        qcore::Position wallDetectedPos;
        qcore::Position wallDetectedPosLevel2;
        qcore::Position leftWallPos;
        qcore::Position rightWallPos;
        qcore::Position playerPosLevel2;

        /* Check optimal path */
        wallDetectedPos = checkWallDetection(playerPos, qcore::Direction::Down);
        if (wallDetectedPos.x == 8)
        {
            calculationResult.levelNo = 1;
            calculationResult.optimalPathLen = 8 - playerPos.x;
        }
        else
        {
            calculationResult.levelNo = 2;
            calculationResult.optimalPathLen = wallDetectedPos.x - playerPos.x;

            /*check second path to left*/
            playerPosLevel2.x = wallDetectedPos.x - 1;
            playerPosLevel2.y = playerPos.y;
            leftWallPos.x = wallDetectedPos.x - 2;
            leftWallPos.y = playerPos.y;

            if ((!baseMap.isWall(playerPosLevel2)) && (!baseMap.isWall(leftWallPos)))
            {
                playerPosLevel2.y--;
                wallDetectedPosLevel2 = checkWallDetection(playerPosLevel2, qcore::Direction::Down);
                pathLenLeft = calculationResult.optimalPathLen + (wallDetectedPosLevel2.x - wallDetectedPos.x);
            }

            /*check second path to right*/
            playerPosLevel2 = playerPos;
            playerPosLevel2.x = wallDetectedPos.x - 1;
            playerPosLevel2.y++;
            rightWallPos.x = playerPosLevel2.x - 1;
            rightWallPos.y = playerPosLevel2.y;

            if ((!baseMap.isWall(playerPosLevel2)) && (!baseMap.isWall(rightWallPos)))
            {
                wallDetectedPosLevel2 = checkWallDetection(playerPosLevel2, qcore::Direction::Down);
                pathLenRight = calculationResult.optimalPathLen + (wallDetectedPosLevel2.x - wallDetectedPos.x);
            }

            if (pathLenLeft > pathLenRight)
            {
                calculationResult.optimalPathLen = pathLenLeft;
            }
            else
            {
                calculationResult.optimalPathLen = pathLenRight;
            }

        }
        return calculationResult;
    }

    /* function which finds my next optimal move*/
    qplugin::VCPlayer::nextMove VCPlayer::findNextOptimalMove(qcore::Position playerPos, bool disableSecondTry)
    {
        qplugin::VCPlayer::nextMove nextMoveInfo;
        qplugin::VCPlayer::nextMove nextMoveInfoPos;

        qplugin::VCPlayer::nextMove secondNextMoveInfo;
        qplugin::VCPlayer::nextMove secondNextMoveInfoPos;

        qplugin::VCPlayer::calcResult myPathLenUp;
        qplugin::VCPlayer::calcResult myPathLenDown;
        qplugin::VCPlayer::calcResult myPathLenDownL;
        qplugin::VCPlayer::calcResult myPathLenDownR;
        qplugin::VCPlayer::calcResult myPathLenLeft;
        qplugin::VCPlayer::calcResult myPathLenRight;
        qcore::Position leftPos;
        qcore::Position rightPos;

	    qplugin::VCPlayer::optNextMove outNextMove;

        std::vector<int> pathsLevelNo = { 0 };
        std::vector<int> optPaths = { 0 };

        std::vector<int> optPathsLevel1 = { 0 };
        std::vector<int> pathDirectionLevel1 = { 0 };
        uint8_t optPathsLevel1Index = 0;

        std::vector<int> optPathsLevel2 = { 0 };
        std::vector<int> pathDirectionLevel2 = { 0 };
        uint8_t optPathsLevel2Index = 0;

        std::vector<int> optPathsSecondTry = { 0 };
        std::vector<int> pathDirectionSecondTry = { 0 };
        uint8_t optPathsSecondTryIndex = 0;

	    uint8_t optimalPathIndex;
	    uint8_t optimalPath;

	    uint8_t optPathIndex;
	    uint8_t secondTryOptPathIndex;

        bool level1Flag = false;
        bool secondTryEnabled = false;

        qcore::Position initPos = playerPos;

        /*check Optimal path if next step is FORWARD*/
        playerPos.x--;
        if ((isValid(playerPos) or (baseMap.isPawn(playerPos))) and ((!checkBlockedPathLeft(playerPos)) and (!checkBlockedPathRight(playerPos))))
        {
            myPathLenUp = qplugin::VCPlayer::calculateOptimalPath(playerPos);
        }
        else
        {
            myPathLenUp.optimalPathLen = 0xFF;
	        myPathLenUp.levelNo = 0xFF;
        }

        /*check Optimal path if next step is BACKWARD*/
        playerPos = initPos;
        playerPos.x++;
        if (isValid(playerPos) or (baseMap.isPawn(playerPos)))
        {
            myPathLenDown.optimalPathLen = 1;

            /* check Back-Left path*/
            leftPos.x = playerPos.x - 1;
            leftPos.y = playerPos.y;
            if ((!baseMap.isWall(playerPos)) && (!baseMap.isWall(leftPos)))
            {
                playerPos.y--;
                if ((!checkBlockedPathLeft(playerPos)) and (!checkBlockedPathRight(playerPos)))
                {
                    myPathLenDownL = qplugin::VCPlayer::calculateOptimalPath(playerPos);
                }
                else
                {
                    myPathLenDownL.levelNo = 0xFF;
                    myPathLenDownL.optimalPathLen = 0xFF;
                }
            }
            else
            {
                myPathLenDownL.levelNo = 0xFF;
                myPathLenDownL.optimalPathLen = 0xFF;
            }

            /* check Back-right path*/
            playerPos.y = playerPos.y + 2;
            rightPos.x = playerPos.x--;
            rightPos.y = playerPos.y;
            if (((!baseMap.isWall(playerPos)) && (!baseMap.isWall(rightPos))) && ((!checkBlockedPathLeft(playerPos)) and (!checkBlockedPathRight(playerPos))))
            {
                myPathLenDownR = qplugin::VCPlayer::calculateOptimalPath(playerPos);
            }
            else
            {
                myPathLenDownR.levelNo = 0xFF;
                myPathLenDownL.optimalPathLen = 0xFF;
            }
	    
	        if(myPathLenDownL.levelNo == 1)
	        {
		        myPathLenDown.levelNo = myPathLenDownL.levelNo;
                myPathLenDown.optimalPathLen += myPathLenDownL.optimalPathLen;
	        }
	        else if (myPathLenDownR.levelNo == 1)
	        {
		        myPathLenDown.levelNo = myPathLenDownR.levelNo;
                myPathLenDown.optimalPathLen += myPathLenDownR.optimalPathLen;
            }
	        else if (((myPathLenDownL.optimalPathLen > myPathLenDownR.optimalPathLen) && (myPathLenDownL.levelNo != 0xFF) && (myPathLenDownR.levelNo != 0xFF)) ||
                     ((myPathLenDownL.levelNo != 0xFF) && (myPathLenDownR.levelNo == 0xFF)))
	        {
		        myPathLenDown.levelNo = myPathLenDownL.levelNo;
                myPathLenDown.optimalPathLen += myPathLenDownL.optimalPathLen;
	        }
	        else if (((myPathLenDownL.optimalPathLen < myPathLenDownR.optimalPathLen) && (myPathLenDownL.levelNo != 0xFF) && (myPathLenDownR.levelNo != 0xFF)) ||
                     ((myPathLenDownL.levelNo == 0xFF) && (myPathLenDownR.levelNo != 0xFF)))
	        {
                myPathLenDown.levelNo = myPathLenDownR.levelNo;
                myPathLenDown.optimalPathLen += myPathLenDownR.optimalPathLen;
            }

            myPathLenDown.levelNo = 2;  // one step back cannot be considered as levelNo = 1
        }
        else
        {
            myPathLenDown.optimalPathLen = 0xFF;
	        myPathLenDown.levelNo = 0xFF;
        }

        /*check Optimal path if next step is LEFT*/
        playerPos = initPos;
        playerPos.y--;
        if ((isValid(playerPos) or (baseMap.isPawn(playerPos))) and ((!checkBlockedPathLeft(playerPos)) and (!checkBlockedPathRight(playerPos))))
        {
            myPathLenLeft = qplugin::VCPlayer::calculateOptimalPath(playerPos);
        }
        else
        {
            myPathLenLeft.optimalPathLen = 0xFF;
	        myPathLenLeft.levelNo = 0xFF;
        }

        /*check Optimal path if next step is RIGHT*/
        playerPos = initPos;
        playerPos.y++;
        if ((isValid(playerPos) or (baseMap.isPawn(playerPos))) and ((!checkBlockedPathLeft(playerPos)) and (!checkBlockedPathRight(playerPos))))
        {
            myPathLenRight = qplugin::VCPlayer::calculateOptimalPath(playerPos);
        }
        else
        {
            myPathLenRight.optimalPathLen = 0xFF;
	        myPathLenRight.levelNo = 0xFF;
        }

        /*check if board end is reached in level1*/
        pathsLevelNo[0] = myPathLenUp.levelNo;
        pathsLevelNo[1] = myPathLenDown.levelNo;
        pathsLevelNo[2] = myPathLenLeft.levelNo;
        pathsLevelNo[3] = myPathLenRight.levelNo;

        optPaths[0] = myPathLenUp.optimalPathLen;
        optPaths[1] = myPathLenDown.optimalPathLen;
        optPaths[2] = myPathLenLeft.optimalPathLen;
        optPaths[3] = myPathLenRight.optimalPathLen;

	    for (int i = 0; i < 4; i++)
	    {
		    if (pathsLevelNo[i] == 1)
		    {
			    optPathsLevel1[optPathsLevel1Index] = optPaths[i];
			    pathDirectionLevel1[optPathsLevel1Index] = i;
			    optPathsLevel1Index++;
			    level1Flag = true;
		    }	
	    }

	    for (int j = 0; j < 4; j++)
	    {
		    if (pathsLevelNo[j] == 2)
		    {
			    optPathsLevel2[optPathsLevel2Index] = optPaths[j];
			    pathDirectionLevel2[optPathsLevel2Index] = j;
			    optPathsLevel2Index++;
		    }	
	    }

	    if (level1Flag == true)
	    {
            nextMoveInfo.levelNo = 1;
		    optimalPath = 0xFF;
		    for (int i = 0; i < optPathsLevel1Index; i++)
		    {
			    if (optPathsLevel1[i] < optimalPath)
			    {
				    optimalPath = optPathsLevel1[i];
				    optPathIndex = pathDirectionLevel1[i];
                    nextMoveInfo.levelNo = 1;
			    }
		    }
	    }
	    else
	    {
		    nextMoveInfo.levelNo = 2;
		    optimalPath = optPathsLevel2[0];
		    optimalPathIndex = 0;
		    optPathIndex = pathDirectionLevel2[0];
		    for (int i = 1; i < optPathsLevel2Index; i++)
		    {
			    if ((optPathsLevel2[i] < optimalPath) && (optPathsLevel2[i] != 0xFF))
			    {
				    optPathsSecondTry[optPathsSecondTryIndex] = optimalPath;
			         pathDirectionSecondTry[optPathsSecondTryIndex] = pathDirectionLevel2[optimalPathIndex];
				    optPathsSecondTryIndex++;

				    optimalPath = optPathsLevel2[i];
				    optimalPathIndex = i;
				    optPathIndex = pathDirectionLevel2[i];
			    }
			    else
			    {
				    optPathsSecondTry[optPathsSecondTryIndex] = optPathsLevel2[i];
				    pathDirectionSecondTry[optPathsSecondTryIndex] = pathDirectionLevel2[i];
				    optPathsSecondTryIndex++;
			    }
                secondTryEnabled = true;
		    }

	    }
	
	    nextMoveInfo.nextPathLen = optimalPath;
        playerPos = initPos;

        nextMoveInfoPos = getNextPosition(optPathIndex, playerPos);
        nextMoveInfo.nextPos = nextMoveInfoPos.nextPos;
        nextMoveInfo.direction = nextMoveInfoPos.direction;

        if (secondTryEnabled)
        {
            secondNextMoveInfo.nextPathLen = 0;
            for (int j = 0; j < optPathsSecondTryIndex; j++)
            {
                if ((optPathsSecondTry[j] >= secondNextMoveInfo.nextPathLen) && (optPathsSecondTry[j] != 0xFF))
                {
                    secondNextMoveInfo.nextPathLen = optPathsSecondTry[j];
                    secondTryOptPathIndex = pathDirectionSecondTry[j];
                }
            }

            playerPos = initPos;

            secondNextMoveInfoPos = getNextPosition(secondTryOptPathIndex, playerPos);
            secondNextMoveInfo.nextPos = secondNextMoveInfoPos.nextPos;
            secondNextMoveInfo.direction = secondNextMoveInfoPos.direction;
        }

	    if ((!disableSecondTry) and (secondTryEnabled))
	    {
		    return secondNextMoveInfo;
	    }
	    else
	    {
		    return nextMoveInfo;
	    }

    }

    /* function which finds oponent next optimal move*/
    qplugin::VCPlayer::nextMove VCPlayer::findNextOponentOptimalMove(qcore::Position playerPos)
    {
        qplugin::VCPlayer::nextMove nextMoveInfo;
        qplugin::VCPlayer::nextMove nextMoveInfoPos;

        qplugin::VCPlayer::calcResult myPathLenUp;
        qplugin::VCPlayer::calcResult myPathLenDown;
        qplugin::VCPlayer::calcResult myPathLenDownL;
        qplugin::VCPlayer::calcResult myPathLenDownR;
        qplugin::VCPlayer::calcResult myPathLenLeft;
        qplugin::VCPlayer::calcResult myPathLenRight;
        qcore::Position leftPos;
        qcore::Position rightPos;

        std::vector<int> pathsLevelNo = { 0 };
        std::vector<int> optPaths = { 0 };

        std::vector<int> optPathsLevel1 = { 0 };
        std::vector<int> pathDirectionLevel1 = { 0 };
        uint8_t optPathsLevel1Index = 0;

        std::vector<int> optPathsLevel2 = { 0 };
        std::vector<int> pathDirectionLevel2 = { 0 };
        uint8_t optPathsLevel2Index = 0;

        uint8_t optimalPath;
        uint8_t optPathIndex;

        bool level1Flag = false;

        qcore::Position initPos = playerPos;

        /*check Optimal path if next step is FORWARD*/
        playerPos.x++;
        if (isValid(playerPos) or (baseMap.isPawn(playerPos)))
        {
            myPathLenUp = qplugin::VCPlayer::calculateOponentOptimalPath(playerPos);
        }
        else
        {
            myPathLenUp.optimalPathLen = 0xFF;
            myPathLenUp.levelNo = 0xFF;
        }

        /*check Optimal path if next step is BACKWARD*/
        playerPos = initPos;
        playerPos.x--;
        if (isValid(playerPos) or (baseMap.isPawn(playerPos)))
        {
            myPathLenDown.levelNo = 2;  // one step back cannot be considered as levelNo = 1
            myPathLenDown.optimalPathLen = 1;

            /* check Back-Left path*/
            leftPos.x = playerPos.x - 1;
            leftPos.y = playerPos.y;
            if ((!baseMap.isWall(playerPos)) && (!baseMap.isWall(leftPos)))
            {
                playerPos.y--;
                myPathLenDownL = qplugin::VCPlayer::calculateOponentOptimalPath(playerPos);
            }
            else
            {
                myPathLenDownL.levelNo = 0xFF;
                myPathLenDownL.optimalPathLen = 0xFF;
            }

            /* check Back-right path*/
            playerPos.y = playerPos.y + 2;
            rightPos.x = playerPos.x--;
            rightPos.y = playerPos.y;
            if ((!baseMap.isWall(playerPos)) && (!baseMap.isWall(rightPos)))
            {
                myPathLenDownR = qplugin::VCPlayer::calculateOponentOptimalPath(playerPos);
            }
            else
            {
                myPathLenDownR.levelNo = 0xFF;
                myPathLenDownL.optimalPathLen = 0xFF;
            }

            if (myPathLenDownL.levelNo == 1)
            {
                myPathLenDown.levelNo = myPathLenDownL.levelNo;
                myPathLenDown.optimalPathLen += myPathLenDownL.optimalPathLen;
            }
            else if (myPathLenDownR.levelNo == 1)
            {
                myPathLenDown.levelNo = myPathLenDownR.levelNo;
                myPathLenDown.optimalPathLen += myPathLenDownR.optimalPathLen;
            }
            else if (((myPathLenDownL.optimalPathLen > myPathLenDownR.optimalPathLen) && (myPathLenDownL.levelNo != 0xFF) && (myPathLenDownR.levelNo != 0xFF)) ||
                ((myPathLenDownL.levelNo != 0xFF) && (myPathLenDownR.levelNo == 0xFF)))
            {
                myPathLenDown.levelNo = myPathLenDownL.levelNo;
                myPathLenDown.optimalPathLen += myPathLenDownL.optimalPathLen;
            }
            else if (((myPathLenDownL.optimalPathLen < myPathLenDownR.optimalPathLen) && (myPathLenDownL.levelNo != 0xFF) && (myPathLenDownR.levelNo != 0xFF)) ||
                ((myPathLenDownL.levelNo == 0xFF) && (myPathLenDownR.levelNo != 0xFF)))
            {
                myPathLenDown.levelNo = myPathLenDownR.levelNo;
                myPathLenDown.optimalPathLen += myPathLenDownR.optimalPathLen;
            }
        }
        else
        {
            myPathLenDown.optimalPathLen = 0xFF;
            myPathLenDown.levelNo = 0xFF;
        }

        /*check Optimal path if next step is LEFT*/
        playerPos = initPos;
        playerPos.y--;
        if (isValid(playerPos) or (baseMap.isPawn(playerPos)))
        {
            myPathLenLeft = qplugin::VCPlayer::calculateOponentOptimalPath(playerPos);
        }
        else
        {
            myPathLenLeft.optimalPathLen = 0xFF;
            myPathLenLeft.levelNo = 0xFF;
        }

        /*check Optimal path if next step is RIGHT*/
        playerPos = initPos;
        playerPos.y++;
        if (isValid(playerPos) or (baseMap.isPawn(playerPos)))
        {
            myPathLenRight = qplugin::VCPlayer::calculateOponentOptimalPath(playerPos);
        }
        else
        {
            myPathLenRight.optimalPathLen = 0xFF;
            myPathLenRight.levelNo = 0xFF;
        }

        /*check if board end is reached in level1*/
        pathsLevelNo[0] = myPathLenUp.levelNo;
        pathsLevelNo[1] = myPathLenDown.levelNo;
        pathsLevelNo[2] = myPathLenLeft.levelNo;
        pathsLevelNo[3] = myPathLenRight.levelNo;

        optPaths[0] = myPathLenUp.optimalPathLen;
        optPaths[1] = myPathLenDown.optimalPathLen;
        optPaths[2] = myPathLenLeft.optimalPathLen;
        optPaths[3] = myPathLenRight.optimalPathLen;

        for (int i = 0; i < 4; i++)
        {
            if (pathsLevelNo[i] == 1)
            {
                optPathsLevel1[optPathsLevel1Index] = optPaths[i];
                pathDirectionLevel1[optPathsLevel1Index] = i;
                optPathsLevel1Index++;
                level1Flag = true;
            }
        }

        for (int j = 0; j < 4; j++)
        {
            if (pathsLevelNo[j] == 2)
            {
                optPathsLevel2[optPathsLevel2Index] = optPaths[j];
                pathDirectionLevel2[optPathsLevel2Index] = j;
                optPathsLevel2Index++;
            }
        }

        if (level1Flag == true)
        {
            nextMoveInfo.levelNo = 1;
            optimalPath = 0xFF;
            for (int i = 0; i < optPathsLevel1Index; i++)
            {
                if (optPathsLevel1[i] < optimalPath)
                {
                    optimalPath = optPathsLevel1[i];
                    optPathIndex = pathDirectionLevel1[i];
                    nextMoveInfo.levelNo = 1;
                }
            }
        }
        else
        {
            nextMoveInfo.levelNo = 2;
            optimalPath = optPathsLevel2[0];
            optPathIndex = 0;
            for (int i = 1; i < optPathsLevel2Index; i++)
            {
                if ((optPathsLevel2[i] > optimalPath) && (optPathsLevel2[i] != 0xFF))
                {
                    optimalPath = optPathsLevel2[i];
                    optPathIndex = pathDirectionLevel2[i];
                    nextMoveInfo.levelNo = 2;
                }
            }
        }

        nextMoveInfo.nextPathLen = optimalPath;
        playerPos = initPos;
        nextMoveInfoPos = getNextPosition(optPathIndex, playerPos);
        nextMoveInfo.nextPos = nextMoveInfoPos.nextPos;
        nextMoveInfo.direction = nextMoveInfoPos.direction;

        return nextMoveInfo;
    }

    VCPlayer::VCPlayer(qcore::PlayerId id, const std::string& name, qcore::GamePtr game) :
        qcore::Player(id, name, game),
        mMoves(0)
    {
    }

    void VCPlayer::doNextMove()
    {
        qplugin::VCPlayer::nextMove myNextMoveInfo;
        qplugin::VCPlayer::nextMove myNextMoveInfoSecondTry;
        qplugin::VCPlayer::nextMove opNextMoveInfo;

        bool wallPlaced;

        qcore::PlayerId myPlayer = qcore::Player::getId();
        qcore::PlayerId opPlayer = qcore::Player::getId() ^ 1;

        qcore::Position myPos = qcore::Player::getBoardState()->getPlayers(myPlayer).at(myPlayer).position;
        qcore::Position opPos = qcore::Player::getBoardState()->getPlayers(myPlayer).at(opPlayer).position;

	    qcore::Player::getBoardState()->createBoardMap(baseMap, myPlayer);

	    secondOptLength = 0;

        if (mMoves > 2 and getWallsLeft())
        {
            myNextMoveInfo = qplugin::VCPlayer::findNextOptimalMove(myPos, true);
	        secondOptLength = 0;

            opNextMoveInfo = qplugin::VCPlayer::findNextOponentOptimalMove(opPos);
	        secondOptLength = 0;

            if (((myNextMoveInfo.levelNo == 1) and (opNextMoveInfo.levelNo == 1) and (myNextMoveInfo.nextPathLen < opNextMoveInfo.nextPathLen)) or
                ((myNextMoveInfo.levelNo == 2) and (opNextMoveInfo.levelNo == 2) and (myNextMoveInfo.nextPathLen < opNextMoveInfo.nextPathLen)) or
                ((myNextMoveInfo.levelNo == 1) and (opNextMoveInfo.levelNo == 2)))
            {
	            myPreviousPos.x = myPos.x;
	            myPreviousPos.y = myPos.y;
                move(myNextMoveInfo.nextPos);

            }
            else if (((myNextMoveInfo.levelNo == 1) and (opNextMoveInfo.levelNo == 1) and (myNextMoveInfo.nextPathLen >= opNextMoveInfo.nextPathLen)) or
                ((myNextMoveInfo.levelNo == 2) and (opNextMoveInfo.levelNo == 2) and (myNextMoveInfo.nextPathLen >= opNextMoveInfo.nextPathLen)) or
                ((myNextMoveInfo.levelNo == 2) and (opNextMoveInfo.levelNo == 1)))
            {
                wallPlaced = defineWallPos(opNextMoveInfo, myPos, opPos);
                if (!wallPlaced)
                {  
			        if ((myNextMoveInfo.nextPos.x != myPreviousPos.x) or (myNextMoveInfo.nextPos.y != myPreviousPos.y))
			        {
	                    myPreviousPos.x = myPos.x;
	                    myPreviousPos.y = myPos.y;
                        move(myNextMoveInfo.nextPos);
			        }
			        else
			        {
			            myNextMoveInfo = qplugin::VCPlayer::findNextOptimalMove(myPos, false);
                        secondOptLength = 0;
	                    myPreviousPos.x = myPos.x;
	                    myPreviousPos.y = myPos.y;
                        move(myNextMoveInfo.nextPos);
			        }

                }
            }
 	        else
	        {
                myNextMoveInfo = qplugin::VCPlayer::findNextOptimalMove(myPos, false);
                secondOptLength = 0;
	            myPreviousPos.x = myPos.x;
	            myPreviousPos.y = myPos.y;
                move(myNextMoveInfo.nextPos);
	        }
        }
        else
        {
            myPos.x--;
            move(myPos);
        }
        mMoves++;
    }
}
