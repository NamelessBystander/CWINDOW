

global_variable float renderscale = 0.01f;
internal void Fill_Screen(u32 colour) {
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = colour;
		}
	}
}

internal void Draw_Rect_size(int x0, int y0, int x1, int y1, u32 colour) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = colour;
		}
	}
}

internal void Draw_Rect(int xs, int ys, int xp, int yp, u32 colour) {
	int start_x = 0 + xp;
	int start_y = 0 + yp;
	int end_x = xs + xp;
	int end_y = ys + yp;

	Draw_Rect_size(start_x, start_y, end_x, end_y, colour);
}


internal void Draw_Line(int x0, int y0,int x1,int y1,int thickness,u32 colour) {
	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int	error = dx + dy;

		
	while (true)
	{
		if (dy == 0) {
			for (int i = 0; i <= thickness; i++) {
				u32* pixel = (u32*)render_state.memory + (x0+thickness/2)+(y0 - i / 2) * render_state.width;
				*pixel++ = colour;
				pixel = (u32*)render_state.memory + (x0 - thickness / 2) + (y0 - i / 2) * render_state.width;
				*pixel++ = colour;
				pixel = (u32*)render_state.memory + (x0 + thickness / 2) + (y0 + (i / 2)) * render_state.width;
				*pixel++ = colour;
				pixel = (u32*)render_state.memory + (x0 - thickness / 2) + (y0 + (i / 2)) * render_state.width;
				*pixel++ = colour;
			}
		}
		else if (dx == 0)
		{
			for (int i = 0; i <= thickness; i++) {
				u32* pixel = (u32*)render_state.memory + (x0 + i / 2) + y0 * render_state.width;
				*pixel++ = colour;
				pixel = (u32*)render_state.memory + (x0 - i / 2) + y0 * render_state.width;
				*pixel++ = colour;
			}
		}
		else
		{
			for (int i = 0; i <= thickness; i++) {
				u32* pixel = (u32*)render_state.memory + (x0 + i/4) + (y0 - i/2) * render_state.width;
				*pixel++ = colour;
				pixel = (u32*)render_state.memory + (x0 - i/4) + (y0 + i/2) * render_state.width;
				*pixel++ = colour;
			}
		}

		if (x0 == x1 && y0 == y1) break;

		int e2 = 2 * error;

		if (e2 >= dy) {
			if (x0 == x1) break;
			error += dy;
			x0 += sx;
		}
		else if (e2 <= dx)
		{
			if (y0 == y1) break;
			error += dx;
			y0 += sy;
		}
	}
}