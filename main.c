#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
typedef uint8_t byte;
static char table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
static char *is_even[2] = {"", " "};
static byte buf[2];

void putb(byte b) {
	putchar(table[(b & 0xF0) >> 4]);
	putchar(table[(b & 0x0F)]);
}

int main() {
	size_t bytes_read;
	uint32_t row;
	byte *rowb;
	setmode(fileno(stdin), O_BINARY);
	for (row = 0; (bytes_read = fread(buf, 1, 16, stdin)); row += 16) {
		rowb = (byte*)&row;
		putb(rowb[3]);
		putb(rowb[2]);
		putb(rowb[1]);
		putb(rowb[0]);
		putchar(' ');
		for (size_t i = 0; i < bytes_read; i++) {
			putb(buf[i]);
			fputs(is_even[i % 2], stdout);
		}
		putchar('\n');
	}
	return 0;
}
