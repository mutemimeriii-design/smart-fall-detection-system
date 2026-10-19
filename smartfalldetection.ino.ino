#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

Adafruit_MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// NodeMCU ESP8266 Pins
const int ledPin = D6;       // GPIO12
const int buzzerPin = D7;    // GPIO13

// Fall Detection Thresholds
const float FREE_FALL = 5.0;   // m/s²
const float IMPACT = 25.0;     // m/s²

bool waitingForImpact = false;
unsigned long fallTimer = 0;

void setup() {
  Serial.begin(115200);

  // Initialize I2C and LCD first
  Wire.begin(D1, D2);
  lcd.init();
  lcd.backlight();

  // Connect to WiFi
  WiFi.begin(ssid, password);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Connecting");
lcd.setCursor(0, 1);

unsigned long wifiStart = millis();

while (WiFi.status() != WL_CONNECTED &&
       millis() - wifiStart < 15000) {
  delay(500);
  Serial.print(".");
  lcd.print(".");
}

if (WiFi.status() == WL_CONNECTED) {
  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  delay(1500);
} else {
  Serial.println();
  Serial.println("WiFi unavailable");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi unavailable");
  delay(1500);
}

lcd.clear();

Serial.println();
Serial.println("WiFi Connected!");
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("WiFi Connected");
delay(1500);
lcd.clear();

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // ESP8266 I2C
 // SDA = D1, SCL = D2

  lcd.setCursor(0, 0);
  lcd.print("SMART FALL");
  lcd.setCursor(0, 1);
  lcd.print("INITIALIZING");

  if (!mpu.begin()) {
    lcd.clear();
    lcd.print("MPU NOT FOUND");

    while (1) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(300);
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(300);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(1000);
  lcd.clear();
}

void loop() {

  sensors_event_t a, g, temp;

  mpu.getEvent(&a, &g, &temp);

  float totalAccel = sqrt(
    a.acceleration.x * a.acceleration.x +
    a.acceleration.y * a.acceleration.y +
    a.acceleration.z * a.acceleration.z
  );

  Serial.print("Acceleration: ");
  Serial.println(totalAccel);

  // Detect free fall
  if (totalAccel < FREE_FALL && !waitingForImpact) {
    waitingForImpact = true;
    fallTimer = millis();
  }

  // Detect impact
  if (waitingForImpact) {

    if (totalAccel > IMPACT) {

      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FALL DETECTED");
      lcd.setCursor(0, 1);
      lcd.print("HELP NEEDED!");

      delay(5000);

      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);

      waitingForImpact = false;
    }

    if (millis() - fallTimer > 1500) {
      waitingForImpact = false;
    }
  }

  if (!waitingForImpact) {
    lcd.setCursor(0, 0);
    lcd.print("SYSTEM NORMAL ");
    lcd.setCursor(0, 1);
    lcd.print("MONITORING... ");
  }

  delay(100);
}
