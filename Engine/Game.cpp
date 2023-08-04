/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Keyboard.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 2,2 }),
	goal(rng, brd, snake)
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameIsOver) {
		if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
			delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_UP)) {
			delta_loc = { 0,-1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
			delta_loc = { -1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
			delta_loc = { 1,0 };
		}


		++snakeMoveCounter;
		if (snakeMoveCounter >= snakeMovePeriod) {
			snakeMoveCounter = 0;
			Location next = snake.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) || (snake.IsInTile(next))) {
				gameIsOver = true;
			}
			else {
				const bool eating = next == goal.GetLocation();
				if (eating) {
					snake.Grow();
					grubol++;
					if (grubol == 3) {
						snakeMovePeriod -= 1;
						grubol = 0;
					}
				}
				snake.MoveBy(delta_loc);
				if (eating) {
					goal.Respawn(rng, brd, snake);
				}
			}
		}
	}
}
void Game::ComposeFrame()
{
	if (!start) SpriteCodex::DrawTitle(300, 300, gfx);
	if (wnd.kbd.KeyIsPressed(VK_CONTROL)) {
		start = true;
	}
	if (start) {
		snake.Draw(brd);
		goal.Draw(brd);
		brd.DrawBoardBorder();
		if (gameIsOver) {
			SpriteCodex::DrawGameOver(200, 300, gfx);
		}
	}
	/*std::uniform_int_distribution<int> colorDist(0, 255);

	for (int y = 0; y < brd.GetGridHeight(); y++) {

		for (int x = 0; x < brd.GetGridWidth(); x++) {
			Location loc = { x,y };
			Color c (colorDist(rng), colorDist(rng), colorDist(rng));
			brd.DrawCell(loc, c);
		}
	}*/
}
