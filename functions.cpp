uint8_t widenHarmony(uint8_t& note1, uint8_t& note2) {
  //  Disallows intervals smaller than a minor third, and instead moves the second note up an octave instead.  
  if (abs(note1 - note2) < 3) {
    note2 += 12;
  }
  return note2;
}

 //  often used to process the clock counters for gate sequences
int incrementAndWrapCount(u_int8_t& count, u_int8_t maxSize) {           
  count++;
  if (count > maxSize) {
    count = 0;
  }
}

