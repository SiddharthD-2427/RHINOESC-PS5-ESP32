#include <Arduino.h>
#include <ps5Controller.h>

// =====================================================
// RHINO ESC SETTINGS
// =====================================================

#define ESC_PIN        18
#define ESC_CHANNEL    0

#define ESC_FREQUENCY  50
#define ESC_RESOLUTION 16

#define ESC_MIN        1000
#define ESC_NEUTRAL    1500
#define ESC_MAX        2000

#define DEADZONE       15


// =====================================================
// SEND PWM TO ESC
// =====================================================

void setESC(int pulse_us)
{
  pulse_us = constrain(
    pulse_us,
    ESC_MIN,
    ESC_MAX
  );

  uint32_t duty =
    ((uint64_t)pulse_us * 65535ULL) / 20000ULL;

  ledcWrite(ESC_CHANNEL, duty);
}


// =====================================================
// STOP MOTOR
// =====================================================

void stopMotor()
{
  setESC(ESC_NEUTRAL);
}


// =====================================================
// CONTROL ESC USING PS5 LEFT STICK Y
// =====================================================

void controlMotor()
{
  int y = ps5.LStickY();

  // Stick UP = negative
  // Stick DOWN = positive
  //
  // Reverse the value so:
  // UP   = forward
  // DOWN = reverse

  y = -y;


  // ---------------------------------------------------
  // DEADZONE
  // ---------------------------------------------------

  if (abs(y) < DEADZONE)
  {
    stopMotor();
    return;
  }


  // ---------------------------------------------------
  // FORWARD
  // ---------------------------------------------------

  if (y > 0)
  {
    int pulse = map(
      y,
      DEADZONE,
      127,
      ESC_NEUTRAL,
      ESC_MAX
    );

    pulse = constrain(
      pulse,
      ESC_NEUTRAL,
      ESC_MAX
    );

    setESC(pulse);
  }


  // ---------------------------------------------------
  // REVERSE
  // ---------------------------------------------------

  else
  {
    int pulse = map(
      y,
      -DEADZONE,
      -128,
      ESC_NEUTRAL,
      ESC_MIN
    );

    pulse = constrain(
      pulse,
      ESC_MIN,
      ESC_NEUTRAL
    );

    setESC(pulse);
  }
}


// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(921600);

  // ---------------------------------------------------
  // ESC PWM
  // ---------------------------------------------------

  ledcSetup(
    ESC_CHANNEL,
    ESC_FREQUENCY,
    ESC_RESOLUTION
  );

  ledcAttachPin(
    ESC_PIN,
    ESC_CHANNEL
  );

  // Start at neutral
  stopMotor();


  // ---------------------------------------------------
  // PS5
  // ---------------------------------------------------

  Serial.println();
  Serial.println("==============================");
  Serial.println(" RHINO ESC + PS5 CONTROLLER");
  Serial.println("==============================");

  Serial.println();

  Serial.println("ESC Settings:");
  Serial.println("GPIO       : 18");
  Serial.println("PWM        : 50 Hz");
  Serial.println("Reverse    : 1000 us");
  Serial.println("Neutral    : 1500 us");
  Serial.println("Forward    : 2000 us");

  Serial.println();

  Serial.println("Starting PS5...");

  // Your working PS5 connection
  ps5.begin("YOUR_PS5_MAC_ADDRESS");

  Serial.println("Ready.");
  Serial.println("Waiting for PS5 controller...");
}


// =====================================================
// LOOP
// =====================================================

void loop()
{
  // ---------------------------------------------------
  // PS5 NOT CONNECTED
  // ---------------------------------------------------

  if (ps5.isConnected() == false)
  {
    stopMotor();

    Serial.println("PS5 controller not connected");

    delay(300);

    return;
  }


  // ---------------------------------------------------
  // PS5 CONNECTED
  // ---------------------------------------------------

  controlMotor();


  // ---------------------------------------------------
  // SERIAL MONITOR
  // ---------------------------------------------------

  static unsigned long lastPrint = 0;

  if (millis() - lastPrint >= 200)
  {
    lastPrint = millis();

    Serial.printf(
      "PS5 Connected | LY: %4d\n",
      ps5.LStickY()
    );
  }


  delay(20);
}
