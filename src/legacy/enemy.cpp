#include "enemy.h"


#include "random.h"
#include "map.h"
#include "log.h"


#include <vector>
#include <tuple>


#define MOVELIMIT 3
#define AIDIST 1
#define AIMOVEDISTANCE 10


const std::map<Enemy::Name, Enemy::EnemyData> Enemy::ENEMYDATAS
{{
    {Enemy::Name::DRAGON, Enemy::EnemyData{"❦", "❦", Player::Element::NONE, [](int position)
    {
        std::vector<int> possibleMoves;
        int pos;
        // pos = Map::Move(position, -1,  0); // L
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  1,  0); // R
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  0, -1); // U
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  0,  1); // D
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);

        return possibleMoves;
    }}},
    {Enemy::Name::PAWN,   Enemy::EnemyData{"♙", "♟", Player::Element::A, [](int position)
    {
        std::vector<int> possibleMoves;
        int pos;
        // pos = Map::Move(position, -1,  0); // L
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  1,  0); // R
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  0, -1); // U
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  0,  1); // D
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);

        return possibleMoves;
    }}},
    {Enemy::Name::KNIGHT, Enemy::EnemyData{"♘", "♞", Player::Element::B, [](int position)
    {
        std::vector<int> possibleMoves;

        int pos;
        // pos = Map::Move(position, -2, -1); // LLU
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position, -2,  1); // LLD
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position, -1, -2); // LUU
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position, -1,  2); // LDD
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  2, -1); // RRU
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  2,  1); // RRD
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  1, -2); // RUU
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  1,  2); // RDD
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);

        return possibleMoves;
    }}},
    {Enemy::Name::BISHOP, Enemy::EnemyData{"♗", "♝", Player::Element::B, [](int position)
    {
        std::vector<int> possibleMoves;

        // for ( // LU
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos, -1, -1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // LD
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos, -1,  1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // RD
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos,  1, -1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // RD
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos,  1,  1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);

        return possibleMoves;
    }}},
    {Enemy::Name::ROOK,   Enemy::EnemyData{"♖", "♜", Player::Element::A, [](int position)
    {
        std::vector<int> possibleMoves;

        // for ( // L
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos, -1,  0)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // R
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos,  1,  0)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // U
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos,  0, -1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // D
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos,  0,  1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);

        return possibleMoves;
    }}},
    {Enemy::Name::QUEEN,  Enemy::EnemyData{"♕", "♛", Player::Element::C, [](int position)
    {
        std::vector<int> possibleMoves;

        // for ( // L
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos, -1,  0)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // R
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos,  1,  0)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // U
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos,  0, -1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // D
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos,  0,  1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // LU
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos, -1, -1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // LD
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos, -1,  1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // RD
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos,  1, -1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);
        // for ( // RD
        //     int limit = 0, pos = position; 
        //     limit < AIMOVEDISTANCE && Map::IsNotObstacle(Map::Move(&pos,  1,  1)); 
        //     limit ++
        // ) possibleMoves.push_back(pos);

        return possibleMoves;
    }}},
    {Enemy::Name::KING,   Enemy::EnemyData{"♔", "♚", Player::Element::C, [](int position)
    {
        std::vector<int> possibleMoves;

        int pos;
        // pos = Map::Move(position, -1,  0); // L
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  1,  0); // R
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  0, -1); // U
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  0,  1); // D
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position, -1, -1); // LU
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position, -1,  1); // LD
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  1, -1); // RU
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);
        // pos = Map::Move(position,  1,  1); // RD
        // if (Map::IsNotObstacle(pos)) possibleMoves.push_back(pos);

        return possibleMoves;
    }}},
}};


std::vector<Enemy> Enemy::enemies;
int Enemy::lastId = 0;


Enemy::Enemy(Name name, int position, double difficulty)
    : id(++lastId), name(name), difficulty(difficulty), position(position)
{
}

const char* Enemy::GetVisual()
{
    if (!isAttacking) return (*ENEMYDATAS.find(name)).second.visual_idle;
    else return (*ENEMYDATAS.find(name)).second.visual_attk;
}

// void Enemy::Turn(int targetPosition, double difficulty_mod)
// {
//     if (stunTime > 0)
//     {
//         isChasing = false;
//         isAttacking = false;
//         stunTime--;
//     }

//     bool isTurning = Random::Get() - (0.2 * isChasing) < difficulty * difficulty_mod;
//     bool isInLOS = Map::IsLineOfSight(this->position, targetPosition);


//     // Attack
//     if (isAttacking){
//         if (isChasing) Attack(targetPosition);
//         else Attack(this->position);
//     }
//     else if (isTurning) isAttacking = true;


//     // LOS
//     if (isInLOS) isChasing = true;
//     else if (isChasing && !isTurning && Random::Get() - 0.5 < difficulty * difficulty_mod) isChasing = false;

// }

// bool Enemy::Kill(Player::Element __damage_type)
// {
//     if (ENEMYDATAS.at(name).Type != __damage_type) return false;

//     auto e_it = std::find_if(enemies.begin(), enemies.end(), [this](Enemy e){ return e.id == this->id; });
//     if (e_it == enemies.end())
//     {
//         Log::Out("--ERR: Killing a ghost");
//         return false;
//     }
//     enemies.erase(e_it);
//     return true;
// }


// void Enemy::Attack(int targetPosition)
// {
//     Log::Out("--LOG: Enemy::Attack is called by "
//          + std::to_string(name)
//          + " from " + std::to_string(position)
//          + " to " + std::to_string(targetPosition));

//     // King spawn
//     if (!isChasing && name == Name::KING && Random::Get() < 0.3) 
//     {
//         int direction = Random::Get() * 4;
//         switch (direction)
//         {
//         case 0:
//             if (Map::IsNotObstacle(Map::Move(position,  0,  1))) Enemy::Create(Map::Move(position,  0,  1), 0.2);
//             return;
        
//         case 1:
//             if (Map::IsNotObstacle(Map::Move(position,  0, -1))) Enemy::Create(Map::Move(position,  0, -1), 0.2);
//             return;
        
//         case 2:
//             if (Map::IsNotObstacle(Map::Move(position,  1,  0))) Enemy::Create(Map::Move(position,  1,  0), 0.2);
//             return;
        
//         case 3:
//             if (Map::IsNotObstacle(Map::Move(position, -1,  0))) Enemy::Create(Map::Move(position, -1,  0), 0.2);
//             return;
        
//         default:
//             Log::Out("--ERR: King spawn direction");
//             return;
//         }
//     }

//     int bestMove = position;
//     double bestWeight = -1;

//     for (auto newPosition : ENEMYDATAS.at(name).GetMoves(position))
//     {

//         // void-kill protection
//         if (!isChasing && newPosition == targetPosition) continue;

//         // get weight of this move
//         double posWeight = Random::Get()
//              + (isChasing ? GetDepth(newPosition, targetPosition, MOVELIMIT) : 0);

//         // is better?
//         if (posWeight < bestWeight || bestWeight == -1)
//         {
//             bestWeight = posWeight;
//             bestMove = newPosition;
//         }
//     }
    
//     position = bestMove;

//     isAttacking = false;
// }

// double Enemy::GetDepth(int position, int targetPosition, int moveLimit)
// {
//     // target
//     if (position == targetPosition) return 0;

//     // limit -> break recursion and return distance to target
//     if (moveLimit <= 0) return sqrt(
//              + std::pow(std::min(
//                 abs(Map::X(position) - Map::X(targetPosition)),
//                 abs(Map::X(position) + Map::X(targetPosition) - Map::MX)), 2)
//              + std::pow(std::min(
//                 abs(Map::Y(position) - Map::Y(targetPosition)),
//                 abs(Map::Y(position) + Map::Y(targetPosition) - Map::MY)), 2)
//             );

//     int bestDepth = -1;

//     // find best depth
//     for (auto newPosition : ENEMYDATAS.at(name).GetMoves(position))
//     {

//         // if target -> break recursion
//         if (newPosition == targetPosition) return 1;

//         // get that depth
//         int newPosDepth = GetDepth(newPosition, targetPosition, moveLimit -1);
//         if (newPosDepth < bestDepth || bestDepth == -1)
//             bestDepth = newPosDepth;

//     }
    
//     // return
//     bestDepth ++;
//     return bestDepth;
// }


// +++CREATION AND MODIFICATION+++
Enemy Enemy::Create(int position, double difficulty_mod)
{
    Log::Out("--LOG: Enemy Create");
    // if (!Map::IsNotObstacle(position)) return false;

    double value = Random::Get();
    if (value >= 1) Log::Out("--ERR: Enemy::Create >=1 ");

    // enemies.push_back(
    //     value == 0   ? Enemy(Name::DRAGON, position, 0.9                 ) :
    //     value < 0.40 ? Enemy(Name::PAWN,   position, 0.1 * difficulty_mod) :
    //     value < 0.60 ? Enemy(Name::KNIGHT, position, 0.1 * difficulty_mod) :
    //     value < 0.80 ? Enemy(Name::BISHOP, position, 0.2 * difficulty_mod) :
    //     value < 0.90 ? Enemy(Name::ROOK,   position, 0.2 * difficulty_mod) :
    //     value < 0.95 ? Enemy(Name::QUEEN,  position, 0.1 * difficulty_mod) :
    //     value < 1    ? Enemy(Name::KING,   position, 0.1 * difficulty_mod)
    //                  : Enemy(Name::DRAGON, position, 0.9                 )
    // );

    return
        value == 0   ? Enemy(Name::DRAGON, position, 0.9                 ) :
        value < 0.40 ? Enemy(Name::PAWN,   position, 0.1 * difficulty_mod) :
        value < 0.60 ? Enemy(Name::KNIGHT, position, 0.1 * difficulty_mod) :
        value < 0.80 ? Enemy(Name::BISHOP, position, 0.2 * difficulty_mod) :
        value < 0.90 ? Enemy(Name::ROOK,   position, 0.2 * difficulty_mod) :
        value < 0.95 ? Enemy(Name::QUEEN,  position, 0.1 * difficulty_mod) :
        value < 1    ? Enemy(Name::KING,   position, 0.1 * difficulty_mod)
                     : Enemy(Name::DRAGON, position, 0.9                 );
}