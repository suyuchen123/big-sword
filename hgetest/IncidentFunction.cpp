#include "IncidentFunction.h"
#include <math.h>

Direction changDirection(Direction dir)
{
	if(dir==Right)
		return Left;
	if(dir==Left)
		return Right;
	if(dir==Up)
		return Down;
	if(dir==Down)
		return Up;
};

Direction collisionConvert(CollisionType cType)
{
	if(cType==RightCollision)
		return Right;
	if(cType==LeftCollision)
		return Left;
	if(cType==UpCollision)
		return Up;
	if(cType==DownCollision)
		return Down;
	return NoDirection;
}

double gaussrand()

{
    static double V1, V2, S;
    static int phase = 0;
    double X;
	if ( phase == 0 ) {
		 do {
            double U1 = (double)rand()/RAND_MAX;
            double U2 = (double)rand()/RAND_MAX;
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);       
        X = V1 * sqrt(-2 * log(S) / S);
    } 
	else		   
		X = V2 * sqrt(-2 * log(S) / S);
	phase = 1 - phase;
    return X;
}

bool isInRange(int x,int y,Position center)
{
	if((x<center.x+180)&&(x>center.x-180)&&(y<center.y+10)&&(y>center.y-10))
		return 1;
	else
		return 0;
}