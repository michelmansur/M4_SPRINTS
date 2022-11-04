int listadeLeds[4] = {15,17,18,10};
int botao1 = 35;
int salvarcoisa1 = LOW;
int botao2 = 36;
int limpeza = LOW;
int LuzRight_ = 0;
int LuzesGeral[50] = {};
int positionvo = 0;
int SomIrritante = 6;
int converter(int value, int min, int max) {
  int jaconvertido = 0;
  int a = value - min;
  float b = max - min;
  jaconvertido = float((a / b)*15);
  return jaconvertido;
}
void setup() {
  Serial.begin(115200);
  for (int i = 0; i<4; i++){
  pinMode(listadeLeds[i], OUTPUT);
  }
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(SomIrritante, OUTPUT);
}
void loop() {
  salvarcoisa1 = digitalRead(botao1);
  if (salvarcoisa1 == LOW){
    LuzRight_ = converter(analogRead(4),64,4063);
    Serial.println(LuzRight_);
    int acender[4]= {0,0,0,0};
    for (int i = 0; i<4; i++){
      acender[i] = (1&LuzRight_>>i);
      if (acender[i] == 1){
        digitalWrite(listadeLeds[i],HIGH);
      }
    }
  tone(SomIrritante,100+(150*LuzRight_),3000);
  LuzesGeral[positionvo] = LuzRight_;
  positionvo += 1;
  delay(2500);
    for (int i = 0; i<4; i++){
      digitalWrite(listadeLeds[i],LOW);
    }
  }
  limpeza = digitalRead(botao2);
  if (limpeza == LOW){
    int acender_2[4]= {0,0,0,0};
    for (int h = 0; h< positionvo; h++){
      LuzRight_ = LuzesGeral[h];
      Serial.println(LuzRight_);
      for (int i = 0; i<4; i++){
        acender_2[i] = (1&LuzRight_>>i);
        if (acender_2[i] == 1){
          digitalWrite(listadeLeds[i],HIGH);
        }
      }
      tone(SomIrritante,(100+(150*LuzesGeral[h])),3000);
      LuzesGeral[h] = 0;
      delay(5000);
      for (int i = 0; i<4; i++){
        digitalWrite(listadeLeds[i],LOW);
          }
    }
    positionvo = 0;
  }
}