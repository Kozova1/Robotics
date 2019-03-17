bool closeBytes(int fail, byte num1, byte num2, byte num3){

  if(abs(num1-num2)<fail){
    if(abs(num2-num3)<fail){
      if(abs(num1-num3)<fail){
        return true;
      }
    }
  }
  return false;
}
