#include <windows.h>
#include <cmath>
#include "Utilities.cpp"

u32 DefWidth = 1280;
u32 DefHeight = 720;

global_variable bool running = true;

struct Render_State {
	int height, width;
	void* memory;

	BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;

#include "Renderer.cpp"
#include "platform_common.cpp"
#include "JGame.cpp"
#include "AGame.cpp"

LRESULT CALLBACK Window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY:
			running = false;
			break;

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);

			render_state.width = rect.right - rect.left;
			render_state.height = rect.bottom - rect.top;

			int size = render_state.width * render_state.height * sizeof(u32);

			if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
			render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
			render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
			render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
			render_state.bitmap_info.bmiHeader.biPlanes = 1;
			render_state.bitmap_info.bmiHeader.biBitCount = 32;
			render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
		}break;
	
			
		default: {
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// Create Window Class																															 
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = Window_callback;
	// Register Class
	RegisterClass(&window_class);
	// Create Window
	HWND window = CreateWindow(window_class.lpszClassName, L"Epic window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, DefWidth, DefHeight, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	Input input = {};

	float delta_time = 0.0166666f;
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	float performance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
		
	}



	while (running) {
		
		// Input
		MSG message;
		
		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
				case WM_KEYUP:
				case WM_KEYDOWN: {
					u32 vk_code = (u32)message.wParam;
					bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b,vk) \
case (vk) : { \
    (input.buttons[b].is_down != is_down) ? input.buttons[b].changed = true : input.buttons[b].changed = false; \
    input.buttons[b].is_down = is_down; \
}break;

					switch (vk_code) {
						process_button(BUTTON_UP, VK_UP);
						process_button(BUTTON_DOWN, VK_DOWN);
						process_button(BUTTON_LEFT, VK_LEFT);
						process_button(BUTTON_RIGHT, VK_RIGHT);

						process_button(BUTTON_A, 0x41);
						process_button(BUTTON_B, 0x42);
						process_button(BUTTON_C, 0x43);
						process_button(BUTTON_D, 0x44);
						process_button(BUTTON_E, 0x45);
						process_button(BUTTON_F, 0x46);
						process_button(BUTTON_G, 0x47);
						process_button(BUTTON_H, 0x48);
						process_button(BUTTON_I, 0x49);
						process_button(BUTTON_J, 0x50);
						process_button(BUTTON_K, 0x51);
						process_button(BUTTON_L, 0x52);
						process_button(BUTTON_M, 0x53);
						process_button(BUTTON_N, 0x54);
						process_button(BUTTON_O, 0x55);
						process_button(BUTTON_P, 0x56);
						process_button(BUTTON_Q, 0x57);
						process_button(BUTTON_R, 0x58);
						process_button(BUTTON_S, 0x59);
						process_button(BUTTON_T, 0x60);
						process_button(BUTTON_U, 0x61);
						process_button(BUTTON_V, 0x62);
						process_button(BUTTON_W, 0x63);
						process_button(BUTTON_X, 0x64);
						process_button(BUTTON_Y, 0x65);
						process_button(BUTTON_Z, 0x66);

					}
				}break;

				

				default: {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
		}

		// Simulate
		Simulate_Game1(&input,delta_time);
		//Simulate_Game2(&input, delta_time);

		
		// Render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;


	}
}
