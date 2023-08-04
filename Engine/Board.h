#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>
#include "Graphics.h"

class Board {

public:
	Board(Graphics& gfx);
	void DrawBoardBorder();
	void DrawCell(const Location& loc, Color c);
	void DrawCellBorder(const Location& loc, Color c);
	void DrawCellPattern(const Location& loc, Color c);
	int GetGridWidth();
	int GetGridHeight();
	bool IsInsideBoard(const Location& loc) const;
	int GetDimension();
private:
	static constexpr int dimension = 20;
	static constexpr int width = 30;
	static constexpr int height = 25;
	static constexpr int xMin = 0;
	static constexpr int yMin = 0;
	static constexpr int xMax = width * dimension;
	static constexpr int yMax = height * dimension;
	Color borderColor = Colors::White;
	Graphics& gfx;
};