int x = 0;

int doit() {
	x++;
	if (x > TotalServos)x = 0;
	Print4char0_1(x);
	return x; }

void SetAllServosTo(int argmilli) {
	for (int i = 0; i < TotalServos; i++) {
		ArraServos[i].writeMicroseconds(argmilli);
		}
	}