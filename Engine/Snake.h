#pragma once
#include "Board.h"

class Snake {

private:
	class Segment {
	public:
		void InitHead(const Location& in_loc);
		void InitBody();
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd);
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
		Color borderColor = Colors::Red;
	};
public:
	Snake(const Location& loc);
	void MoveBy(Location& delta_loc);
	void Grow();
	void Draw(Board& brd);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
private:
	static constexpr Color headColor = Colors::Cyan;
	static constexpr Color bodyColor = Colors::Yellow;
	static constexpr Color patternColor = Colors::Blue;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;

};