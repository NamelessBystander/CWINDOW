inline int clamp(int min, int val, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

double length(int x,int y) {
    return sqrt(x * x + y * y);
}

inline void normalize(int x, int y) {
    // Calculate the length of the vector
    double len = length(x,y);

    // If the length is not zero, divide each component by the length
    if (len != 0) {
        x = x / len;
        y = y / len;
    }
}

#define global_variable static;
#define internal static;

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;