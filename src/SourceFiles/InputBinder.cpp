#include "InputBinder.h"

InputPacket InputBinder::getInputPacket()
{
	InputPacket pkg;
	b2Vec2 dir = getAimDir();
	pkg.packetId = 'I';

	pkg.holdGrab = holdGrab();
	pkg.releaseGrab = releaseGrab();
	pkg.pressThrow = pressThrow();
	pkg.pressPick = pressPick();
	pkg.holdImpulse = holdImpulse();
	pkg.pressImpulse = pressImpulse();

	pkg.aimDirX = dir.x;
	pkg.aimDirY = dir.y;

	pkg.releaseImpulse = releaseImpulse();
	pkg.pressAttack = pressAttack();
	pkg.menuForward = menuForward();
	pkg.menuBack = menuBack();
	pkg.pressPause = pressPause();
	
	if (menuMove(Up))
		pkg.menuMove = pkg.menuMove | Up;
	if (menuMove(Down))
		pkg.menuMove = pkg.menuMove | Down;
	if (menuMove(Left))
		pkg.menuMove = pkg.menuMove | Left;
	if (menuMove(Right))
		pkg.menuMove = pkg.menuMove | Right;

	return pkg;
}