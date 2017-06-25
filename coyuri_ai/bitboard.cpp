#include "types.hpp"

u8_t OccupiedBitBoard::get_kiki_hash(PiP pip_p)
{
	u8_t x = pip_p.point.x, y = pip_p.point.y + 1;
	y *= 0.3;
	u32_t working = field[y];

	return ((working >> 1) >> ((pip_p.point.y % 3) - 2)) & 0b01111111;

}