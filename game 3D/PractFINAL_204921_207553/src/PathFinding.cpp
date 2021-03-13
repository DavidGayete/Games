#include "Entity.h"
extern Image floor_image;

bool compare_colors(Vector3 current_color, Vector3 color_franja) {
	if (current_color.x == color_franja.x && current_color.y == color_franja.y && current_color.z == color_franja.z)
		return true;
	return false;
}

/*
This function checks if there's a direct path (straight line) between the zombies and the player.
*/
bool simple_pathfinding(int x0, int y0, int x1, int y1, Vector3 color_franja)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2; /* error value e_xy */
	for (;;) {  /* loop */
		if (x0 >= 0 && y0 >= 0 && x0 < 1024 && y0 < 1024) {
			Vector3 current_color = floor_image.getPixel(x0, y0).toVector4().xyz;
			if (compare_colors(current_color, color_franja) == false) {
				return false;
			}
		}

		if (x0 == x1 && y0 == y1)
			return true;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}
float velocity_tanh(float dist) {
	return tanh(dist / 100) * 5 + 1;
}