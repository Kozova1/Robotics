int light(byte n, byte r, byte g, byte b){
  if(n>NUMPIXELS/4 || n<=0){
    return 1;
  }
  pixels.clear();
  int num=map(n,1,4,4,1);
  for(int j =0; j<NUMPIXELS/4-(num-1); j++){
    for(int i=j;i<NUMPIXELS;i+=4){
      pixels.setPixelColor(i, pixels.Color(r,g,b));
      pixels.show();
      delay(1); 
    }
  }
  return 0;
}
