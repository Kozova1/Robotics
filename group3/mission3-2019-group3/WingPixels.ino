void lightLEDByWing (byte num, byte red, byte green, byte blue) {
	pixels.clear ();
	for (int i = 0; i < NEOPIXELS/4; i++) {
		pixels.setPixelColor (i + (4 * num), green, red, blue);
	}
	pixels.show ();
}
