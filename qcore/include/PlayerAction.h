#ifndef Header_qcore_PlayerAction
#define Header_qcore_PlayerAction

#include <stdint.h>
#include <string>

#include "Qcore_API.h"

namespace qcore
{
   typedef uint8_t PlayerId;

   const uint8_t BOARD_SIZE = 9;

   enum class Direction
   {
      Down,
      Right,
      Up,
      Left
   };

   /** Rotates all coordinates counterclockwise for a number of steps */
   Direction rotate(const Direction d, const uint8_t rotations);

   enum class Orientation
   {
      Vertical,
      Horizontal
   };

   enum class ActionType
   {
      Invalid,
      Move,
      Wall
   };

   struct QCODE_API Position
   {
      int8_t x;
      int8_t y;

      Position() : x(0), y(0) {}
      Position(const Position& p) : x(p.x), y(p.y) {}
      Position(int8_t x, int8_t y) : x(x), y(y) {}

      bool operator==(const Position& p) const;
      Position operator=(const Position& p) const;

      /** Computes the distance between 2 positions */
      uint8_t dist(const Position& p) const;

      /** Multiplies each coordinate with the given factor */
      Position operator*(uint8_t m) const;
      Position operator/(uint8_t m) const;

      /** Moves the coordinates in the specified direction */
      Position& operator+=(const Direction direction);
      Position operator+(const Direction direction) const;

      Position operator+(const Position& p) const;
      Position operator-(const Position& p) const;
      Position operator-() const;

      /** Rotates all coordinates counterclockwise for a number of steps */
      Position rotate(const uint8_t rotations) const;
   };

   /** Description of a wall on the board */
   struct QCODE_API WallState
   {
      Position position;
      Orientation orientation;

      /** Rotates all coordinates counterclockwise for a number of steps */
      WallState rotate(const uint8_t rotations) const;
   };

   /** Description of a player on the board */
   struct QCODE_API PlayerState
   {
      Direction initialState;
      Position position;
      uint8_t wallsLeft;

      /** Rotates all coordinates counterclockwise for a number of steps */
      PlayerState rotate(const uint8_t rotations) const;
   };

   struct QCODE_API PlayerAction
   {
      PlayerId playerId = 0xFF;
      ActionType actionType = ActionType::Invalid;

      WallState wallState;
      Position playerPosition;

      bool isValid() const { return actionType == ActionType::Invalid or playerId < 4; }

      /** Rotates all coordinates counterclockwise for a number of steps */
      PlayerAction rotate(const uint8_t rotations) const;

      std::string serialize() const;
      void deserialize(const std::string& s);
   };

   namespace literals
   {
      QCODE_API Position operator "" _x(unsigned long long int x);
      QCODE_API Position operator "" _y(unsigned long long int y);
   }
}

#endif // Header_qcore_PlayerAction
