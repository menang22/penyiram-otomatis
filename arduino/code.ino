const int sensor = A0; // Port sensor kelembaban tanah
const int ldr = A1; // Port LDR (sensor cahaya)

const int rly = 13; // pin relay
const int ind = 12; // pin lampu indikator (invers dari rly)
const int minVal = 50; // konstanta minimal tingkat kelembaban (0-100)
const int maxVal = 75; // konstanta maksimal tingkat kelembaban (0-100)
const int minLdr = 60; // konstanta minimal tingkat cahaya (0-100)

int sensorValue;
int LDRValue = 0;

void setup(){
 Serial.begin(9600); 
 pinMode(rly, OUTPUT);
 pinMode(ind, OUTPUT);
}

void loop(){
 sensorValue = analogRead(sensor); // membaca nilai dari sensor kelembaban
 sensorValue = map(sensorValue, 0, 1023, 0, 100); // mengubah nilai sensor ke 0-100
 LDRValue = analogRead(ldr); // membaca nilai dari sensor cahaya
 LDRValue = map(LDRValue, 0, 1023, 0, 100);
 
 Serial.println(String("LDR : ") + String(LDRValue));
 Serial.println(String("Kelembaban : ") + String(sensorValue));
 
 if (sensorValue < minVal) {
   Serial.println(String("Status : Lembab"));
   rlyOff();
 }
 else if (sensorValue > minVal && sensorValue < maxVal) {
   Serial.println(String("Status : Kering"));
   if (LDRValue > minLdr) {
    rlyOn();
   }
 }
 else {
   Serial.println(String("Status : Sangat Kering"));
   if (LDRValue > minLdr) {
    rlyOn();
   }
 }
 
 delay(500); // delay update
}

// fungsi untuk menghidupkan relay
void rlyOn () {
  Serial.println("Pompa dinyalakan");
  digitalWrite(rly, LOW);
  digitalWrite(ind, HIGH);
}

// fungsi untuk mematikan relay
void rlyOff () {
 Serial.println("Pompa dimatikan");
 digitalWrite(rly, HIGH); 
 digitalWrite(ind, LOW);
}
