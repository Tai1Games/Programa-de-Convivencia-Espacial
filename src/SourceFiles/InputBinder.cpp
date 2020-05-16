#include "InputBinder.h"

InputPacket InputBinder::getInputPacket()
{
	InputPacket pkg;
	b2Vec2 dir = getAimDir();
	pkg.aimDirX = dir.x;
	pkg.aimDirY = dir.y;
	pkg.holdGrab = holdGrab();
	pkg.holdImpulse = holdImpulse();
	pkg.menuBack = menuBack();
	pkg.menuForward = menuForward();
	if (menuMove(Up))
		pkg.menuMove = pkg.menuMove | Up;
	if (menuMove(Down))
		pkg.menuMove = pkg.menuMove | Down;
	if (menuMove(Left))
		pkg.menuMove = pkg.menuMove | Left;
	if (menuMove(Right))
		pkg.menuMove = pkg.menuMove | Right;

	pkg.pressAttack = pressAttack();
	pkg.pressImpulse = pressImpulse();
	pkg.pressPause = pressPause();
	pkg.pressPick = pressPick();
	pkg.pressThrow = pressThrow();
	pkg.releaseGrab = releaseGrab();
	pkg.releaseImpulse = releaseImpulse();

	return pkg;
}