int light(byte n, byte g, byte r, byte b){
  if(n>NUMPIXELS/4 || n<=0){
    return 1;
  }
  pixels.clear();
  int num=map(n,1,4,4,1);
  for(int j =0; j<NUMPIXELS/4-(num-1); j++){
    for(int i=j;i<NUMPIXELS;i+=4){
      pixels.setPixelColor(i, pixels.Color(r,g,b));
      delay(1); 
    }
  }
  pixels.show();
  return 0;
}
