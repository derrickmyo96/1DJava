#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

const char* ssid="Your own wifi ssid";
const char* password="Your own wifi password";
const char* firebase_host = "Your own firebase Host";
const char* firebase_auth = "Your own firebase Authentication Key";
//Get the firebase_auth in Firebase.com=>Settings=>Service Accounts
//=>Database Secrets=>Secret
int ledPin = 16;
int inputPin1 = 14;
int inputPin2 = 12;
int inputPin3 = 5;
int inputPin4 = 4;
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int nextState1 = 0;
int nextState2 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);
  pinMode(inputPin3, INPUT);
  pinMode(inputPin4, INPUT);

  Serial.begin(115200);
  WiFi.disconnect();
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Wifi Connected Successfully!");
  Serial.print("NODEMCU IP address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(firebase_host, firebase_auth);
  Firebase.setString("/scratch/block_55/washers/W01/btnCollect", "0");
  Firebase.setString("/scratch/block_55/washers/W01/btnStart", "0");
  Firebase.setString("/scratch/block_55/washers/W02/btnCollect", "0");
  Firebase.setString("/scratch/block_55/washers/W02/btnStart", "0");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  val1 = digitalRead(inputPin1);
  val2 = digitalRead(inputPin2);
  val3 = digitalRead(inputPin3);
  val4 = digitalRead(inputPin4);
  
  if(val1 == LOW && nextState1 == 0){
    Firebase.setString("/scratch/block_55/washers/W01/btnStart","1");
    digitalWrite(ledPin, HIGH);
    nextState1 = 1;
    Serial.println(Firebase.getInt("/scratch/block_55/washers/W01/btnStart"));
    delay(1000);
  }

  else if(val1 == HIGH && nextState1 == 1) {
    Firebase.setString("/scratch/block_55/washers/W01/btnStart","1");
    digitalWrite(ledPin, HIGH);
    nextState1 = 1;
    Serial.println(Firebase.getInt("/scratch/block_55/washers/W01/btnStart"));
    delay(1000);
  }

  if(val2 == LOW && nextState1 == 1) {
    Firebase.setString("/scratch/block_55/washers/W01/btnCollect","1");
    digitalWrite(ledPin, LOW);
    nextState1 = 0;
    Serial.println(Firebase.getInt("/scratch/block_55/washers/W01/btnCollect"));
    delay(1000);
  }
/*
  else if(val2 == HIGH && nextState == 1) {
    Firebase.setString("/BtnPress/CollectClothes","Clothes have been collected");
    digitalWrite(ledPin, LOW);
    nextState = 0;
    Serial.println(Firebase.getInt("/BtnPress/CollectClothes"));
    Serial.println("Switch is released");
    delay(1000);
  }
  */

  if(val3 == LOW && nextState2 == 0){
    Firebase.setString("/scratch/block_55/washers/W02/btnStart","1");
    digitalWrite(ledPin, HIGH);
    nextState2 = 1;
    Serial.println(Firebase.getInt("/scratch/block_55/washers/W01/btnStart"));
    delay(1000);
  }

  else if(val3 == HIGH && nextState2 == 1) {
    Firebase.setString("/scratch/block_55/washers/W02/btnStart","1");
    digitalWrite(ledPin, HIGH);
    nextState2 = 1;
    Serial.println(Firebase.getInt("/scratch/block_55/washers/W01/btnStart"));
    delay(1000);
  }

  if(val4 == LOW && nextState2 == 1) {
    Firebase.setString("/scratch/block_55/washers/W02/btnCollect","1");
    digitalWrite(ledPin, LOW);
    nextState2 = 0;
    Serial.println(Firebase.getInt("/scratch/block_55/washers/W01/btnCollect"));
    delay(1000);
  }
}
