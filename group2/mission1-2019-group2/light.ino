int light(byte n, byte r, byte g, byte b){
  //Checking if the numbers are correct - no bs here.
  if(n>NUMPIXELS/4 || n<=0){
    return 1;
  }
  //Clearing the LED strip
  pixels.clear();
  int tempReg;
  //Inverting the inputs - yonatan why not make this correct from the start?
  int num=map(n,1,4,4,1);
  // working at the individual LED level
  // j represents 
  for(int j =0; j<NUMPIXELS/4-(num-1); j++){
    // working at the strip level
    // i represents the LED number, and is based on j
    if (REVERSED == true){
      tempReg = map(j,0,3,3,0);
      for(int i=tempReg;i<NUMPIXELS;i+=4){
        pixels.setPixelColor(i, pixels.Color(r,g,b));
        pixels.show();
        delay(1); 
      }
    } else {
      for(int i=j;i<NUMPIXELS;i+=4){
        pixels.setPixelColor(i, pixels.Color(r,g,b));
        pixels.show();
        delay(1); 
      }
      }
  }
  return 0;
}
