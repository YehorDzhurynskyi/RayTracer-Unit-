
unsigned int svpng_u8c(int u, FILE* fp, unsigned int c)
{
	fputc(u, fp);
	c ^= (u);
	c = (c >> 4) ^ t[c & 15];
	c = (c >> 4) ^ t[c & 15];
	return(c);
}// SVPNG_U8C(u) do { SVPNG_PUT(u); c ^= (u); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0)

void save_png(FILE* fp, unsigned w, unsigned h, const unsigned char* img, int alpha)
{
	unsigned int a = 1, b = 0, c, p = w * (alpha ? 4 : 3) + 1, x, y, i;
	i = 0;
	while (i < 8)
	{
		fputc(("\x89PNG\r\n\32\n")[i], fp);
		i++;
	}
	fputc((13) >> 24, fp);
	fputc(((13) >> 16) & 255, fp);
	fputc(((13) >> 8) & 255, fp);
	fputc((13) & 255, fp);
	c = ~0U;
	for (i = 0; i < 4; i++)
	{
		fputc(("IHDR")[i], fp);
		c ^= (("IHDR")[i]);
		c = (c >> 4) ^ t[c & 15];
		c = (c >> 4) ^ t[c & 15];
	}
	// do {
	// 	fputc((w) >> 24, fp);
	// 	c ^= ((w) >> 24);
	// 	c = (c >> 4) ^ t[c & 15];
	// 	c = (c >> 4) ^ t[c & 15];
	// } while(0);
	c = svpng_u8c(((w) >> 24), fp, c);
	do {
		fputc(((w) >> 16) & 255, fp);
		c ^= (((w) >> 16) & 255);
		c = (c >> 4) ^ t[c & 15];
		c = (c >> 4) ^ t[c & 15];
	} while(0);
	do {
		fputc(((w) >> 8) & 255, fp);
		c ^= (((w) >> 8) & 255);
		c = (c >> 4) ^ t[c & 15];
		c = (c >> 4) ^ t[c & 15];
	} while(0);
	do {
		fputc((w) & 255, fp);
		c ^= ((w) & 255);
		c = (c >> 4) ^ t[c & 15];
		c = (c >> 4) ^ t[c & 15];
	} while(0);
	do {
		fputc((h) >> 24, fp);
		c ^= ((h) >> 24);
		c = (c >> 4) ^ t[c & 15];
		c = (c >> 4) ^ t[c & 15];
	} while(0);
	do {
		fputc(((h) >> 16) & 255, fp);
		c ^= (((h) >> 16) & 255);
		c = (c >> 4) ^ t[c & 15];
		c = (c >> 4) ^ t[c & 15]; 
	} while(0);
	do {
		fputc(((h) >> 8) & 255, fp);
		c ^= (((h) >> 8) & 255);
		c = (c >> 4) ^ t[c & 15];
		c = (c >> 4) ^ t[c & 15];
	} while(0);
	do {
		fputc((h) & 255, fp);
		c ^= ((h) & 255);
		c = (c >> 4) ^ t[c & 15];
		c = (c >> 4) ^ t[c & 15];
	} while(0);

	do { fputc(8, fp); c ^= (8); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); do { fputc(alpha ? 6 : 2, fp); c ^= (alpha ? 6 : 2); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0);
    for (i = 0; i < 3; i++) do { fputc(("\0\0\0")[i], fp); c ^= (("\0\0\0")[i]); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0);
    do { fputc((~c) >> 24, fp); fputc(((~c) >> 16) & 255, fp); fputc(((~c) >> 8) & 255, fp); fputc((~c) & 255, fp); } while(0);
    do { do { fputc((2 + h * (5 + p) + 4) >> 24, fp); fputc(((2 + h * (5 + p) + 4) >> 16) & 255, fp); fputc(((2 + h * (5 + p) + 4) >> 8) & 255, fp); fputc((2 + h * (5 + p) + 4) & 255, fp); } while(0); c = ~0U; for (i = 0; i < 4; i++) do { fputc(("IDAT")[i], fp); c ^= (("IDAT")[i]); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); } while(0);
    for (i = 0; i < 2; i++) do { fputc(("\x78\1")[i], fp); c ^= (("\x78\1")[i]); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0);
    for (y = 0; y < h; y++) {
        do { fputc(y == h - 1, fp); c ^= (y == h - 1); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0);
        do { do { fputc((p) & 255, fp); c ^= ((p) & 255); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); do { fputc(((p) >> 8) & 255, fp); c ^= (((p) >> 8) & 255); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); } while(0); do { do { fputc((~p) & 255, fp); c ^= ((~p) & 255); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); do { fputc(((~p) >> 8) & 255, fp); c ^= (((~p) >> 8) & 255); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); } while(0);
        do { do { fputc(0, fp); c ^= (0); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); a = (a + (0)) % 65521; b = (b + a) % 65521; } while(0);
        for (x = 0; x < p - 1; x++, img++)
            do { do { fputc(*img, fp); c ^= (*img); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); a = (a + (*img)) % 65521; b = (b + a) % 65521; } while(0);
    }
    do { do { fputc(((b << 16) | a) >> 24, fp); c ^= (((b << 16) | a) >> 24); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); do { fputc((((b << 16) | a) >> 16) & 255, fp); c ^= ((((b << 16) | a) >> 16) & 255); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); do { fputc((((b << 16) | a) >> 8) & 255, fp); c ^= ((((b << 16) | a) >> 8) & 255); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); do { fputc(((b << 16) | a) & 255, fp); c ^= (((b << 16) | a) & 255); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); } while(0);
    do { fputc((~c) >> 24, fp); fputc(((~c) >> 16) & 255, fp); fputc(((~c) >> 8) & 255, fp); fputc((~c) & 255, fp); } while(0);
    do { do { fputc((0) >> 24, fp); fputc(((0) >> 16) & 255, fp); fputc(((0) >> 8) & 255, fp); fputc((0) & 255, fp); } while(0); c = ~0U; for (i = 0; i < 4; i++) do { fputc(("IEND")[i], fp); c ^= (("IEND")[i]); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); } while(0); do { fputc((~c) >> 24, fp); fputc(((~c) >> 16) & 255, fp); fputc(((~c) >> 8) & 255, fp); fputc((~c) & 255, fp); } while(0);
	//do { do { fputc((13) >> 24, fp); fputc(((13) >> 16) & 255, fp); fputc(((13) >> 8) & 255, fp); fputc((13) & 255, fp); } while(0); c = ~0U; 
		//for (i = 0; i < 4; i++) do { fputc(("IHDR")[i], fp); c ^= (("IHDR")[i]); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0); } while(0);
}
