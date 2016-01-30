const byte inputPin = A0;
const int messPerBlock = 10;
const int microDelayMess = 150;
const int numberBlocks = 10;

int Thres =0;
void setup() {
  Serial.begin(115200);
  Serial.println(inputPin);
  Thres = getThreshold();
  Serial.println(Thres);
}

void loop() {
  if (analogRead(inputPin) > Thres) {
    Serial.println("trigger");
  }
}

int getThreshold() {
  int Max = 0;
  int average[numberBlocks];
  int l=0;
  int ln=0;
  int h=0;
  int hn=0;

  int t = 0;
  Max = 0;
  int tempAver = 0;
  for (int i=0;i<numberBlocks;i++) {
    for (int j=0;j<messPerBlock;j++) {
      t += analogRead(inputPin);
    }
    average[i] = int(t/messPerBlock);
    if (average[i] > Max) {
      Max = average[i];
    }
    tempAver += average[i];
    t=0;
  }
  tempAver = int(tempAver/numberBlocks);
  int tempThres = ((Max-tempAver)/2)+tempAver;
  for (int i=0;i<numberBlocks;i++) {
    if (average[i] > tempThres) {
      hn++;
      h+=average[i];
    } else {
      ln++;
      l+=average[i];
    }
  }
  l = int(l/ln);
  h = int(h/hn);
  return int(((h-l)/2)+l);


}


