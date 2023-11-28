#define is_down(b) (input->buttons[b].is_down && !input->buttons[b].changed)
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

internal void Simulate_Game2(Input* input, float time) {
	//Aston is a stinky
}