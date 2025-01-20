#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <AdaFruit_GFX.h>


// Pin definitions
#define LED_RED 19         // Red LED connected to GPIO19 (D19)
#define LED_YELLOW 18      // Yellow LED connected to GPIO18 (D18)
#define LED_GREEN 5        // Green LED connected to GPIO5 (D5)
#define BUZZER_PIN 17      // Buzzer connected to GPIO17 (D17)
#define BUTTON_PIN 22      // Button connected to GPIO22 (D22)
#define SCREEN_WIDTH 128   // OLED width
#define SCREEN_HEIGHT 64   // OLED height



// Initialize OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Variables for control
bool ledState = false;      // LED status
bool buzzerState = false;   // Buzzer status
bool buttonPressed = false; // For button debounce detection

void setup() {
  // Initialize Serial (for debugging)
  Serial.begin(115200);

  // Configure pins
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button with internal pull-up resistor

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not detected!");
    while (1); // Halt the program if OLED initialization fails
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Display the initial status on the OLED
  displayStatus();
}

void loop() {
  // Read the button state
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50); // Debounce delay
    if (!buttonPressed) {
      buttonPressed = true;

      // Toggle LED and buzzer status
      ledState = !ledState;
      buzzerState = ledState;

      // Control LEDs and buzzer
      digitalWrite(LED_RED, ledState);
      digitalWrite(LED_YELLOW, ledState);
      digitalWrite(LED_GREEN, ledState);
      digitalWrite(BUZZER_PIN, buzzerState ? HIGH : LOW);

      // Update OLED display
      displayStatus();
    }
  } else {
    buttonPressed = false;
  }
}

void displayStatus() {
  display.clearDisplay();
  display.setCursor(0, 0);

  // Display the name "Girii"
  display.setTextSize(2);
  display.println("Girii"); // Name
  display.setTextSize(1);
  display.println("--------------------");

  // Display LED and buzzer status
  display.print("LED: ");
  display.println(ledState ? "ON" : "OFF");
  display.print("Buzzer: ");
  display.println(buzzerState ? "ON" : "OFF");

  // Send data to the OLED screen
  display.display();
}
