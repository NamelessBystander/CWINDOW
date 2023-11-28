#define is_down(b) (input->buttons[b].is_down && !input->buttons[b].changed)
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

int speed = 1000;

int pos_y = 100;
int pos_x = 100;

int x, y;
internal void Simulate_Game1(Input* input, float time) {
	Fill_Screen(0xffffff);
	Draw_Rect(100,100,pos_x,pos_y,0x000000);
	pos_x += x * time * speed;
	pos_y += y * time * speed;

	if (pressed(BUTTON_UP)) {
		y += 1;
	}
	if (released(BUTTON_UP)) {
		y -= 1;
	}
	if (pressed(BUTTON_DOWN)) {
		y -= 1;
	}
	if (released(BUTTON_DOWN)) {
		y += 1;
	}
	if (pressed(BUTTON_RIGHT)) {
		x += 1;
	}
	if (released(BUTTON_RIGHT)) {
		x -= 1;
	}
	if (pressed(BUTTON_LEFT)) {
		x -= 1;
	}
	if (released(BUTTON_LEFT)) {
		x += 1;
	}
}