#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}


void Board::DrawBoardBorder()
{
	gfx.DrawBorder(xMin, yMin, xMax, yMax, borderColor);
}


void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y < height);
	assert(loc.y >= 0);
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c);
}

void Board::DrawCellBorder(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y < height);
	assert(loc.y >= 0);
	gfx.DrawBorder(loc.x * dimension, loc.y * dimension, loc.x * dimension + dimension, loc.y * dimension + dimension, c);
}
void Board::DrawCellPattern(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y < height);
	assert(loc.y >= 0);
	gfx.DrawPattern(loc.x * dimension, loc.y * dimension, loc.x * dimension + dimension, loc.y * dimension + dimension, c);
}



int Board::GetGridWidth()
{
	return width;
}

int Board::GetGridHeight()
{
	return height;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

int Board::GetDimension()
{
	return dimension;
}
