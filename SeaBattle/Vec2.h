struct Vec2 {
	int x = 0;
	int y = 0;
	Vec2(int x = 0, int y = 0) : x(x), y(y) {}
	bool operator==(const Vec2& other) {
		return x == other.x && y == other.y;
	}
	bool operator!=(const Vec2& other) {
		return !(*this == other);
	}
	Vec2 operator+(const Vec2& other) {
		return { x + other.x, y + other.y };
	}
	Vec2 operator+=(const Vec2& other) {
		*this = *this + other;
		return *this;
	}
	Vec2 operator-(const Vec2& other) {
		return { x - other.x, y - other.y };
	}
	Vec2 operator-=(const Vec2& other) {
		*this = *this - other;
		return *this;
	}
	Vec2 operator*(int k) {
		return { x * k, y * k };
	}
	Vec2 operator*=(int k) {
		*this = *this * k;
		return *this;
	}
};