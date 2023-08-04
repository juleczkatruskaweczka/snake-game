#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--) { //>0 because we dont want to process head
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax) {
		segments[nSegments].InitBody();
		nSegments++;
	}
}

void Snake::Draw(Board& brd)
{
	for (int i = 0; i < nSegments; i++) {
		segments[i].Draw(brd);
	}
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

bool Snake::IsInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < nSegments - 1; i++) {			//nSegments-1, poniewaz konca ogona nie bierzemy pod uwage
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const Location& target) const
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}
void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody()
{
	c = Snake::bodyColor;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
	brd.DrawCellBorder(loc, borderColor);
	brd.DrawCellPattern(loc, patternColor);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
