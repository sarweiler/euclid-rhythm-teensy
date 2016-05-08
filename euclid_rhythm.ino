const int leds[8] = {11, 12, 13, 14, 15, 16, 17, 18};
const int pulse_pin = 19;
const int pulse_length = 50;
const int step_length = 300;
String seq;

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(pulse_pin, OUTPUT);
  seq = distribute(5,8);
}

void loop() {
  display_seq(seq);
  send_pulse(seq[0]);
  advance_seq();
  delay(step_length - pulse_length);
}

void advance_seq() {
  seq = shift_string(seq);
}

String distribute(int pulses, int steps) {
  int pauses = steps - pulses;
  int per_pulse = pauses / pulses;
  int remainder = pauses % pulses;

  Serial.print("PAUSES: " + String(pauses) + "\n");
  Serial.print("PER PULSE: " + String(per_pulse) + "\n");
  Serial.print("REMAINDER: " + String(remainder) + "\n");

  String rhythm = "";
  for(int i = 0; i < pulses; i++) {
    rhythm += "1";
    for(int j = 0; j < per_pulse; j++) {
      rhythm += "0";
    }
    if(i < remainder) {
      rhythm += "0";
    }
  }

  //Serial.print(rhythm);
  return rhythm;
}

String shift_string(String seq) {
  int seq_length = seq.length();
  int pos;
  String shifted_seq = seq;
  for(int i = 0; i < seq_length; i++) {
    pos = i + 1;
    if(pos < seq_length) {
      shifted_seq[pos] = seq[i];
    } else {
      shifted_seq[0] = seq[i];
    }
  }
  return shifted_seq;
}

void display_seq(String seq) {
  //int seq_length = seq.length();
  for(int i = 0; i < 8; i++) {
    if(seq[i] == '1') {
      digitalWrite(leds[i], HIGH);
    } else {
      digitalWrite(leds[i], LOW);
    }
  }
}

void send_pulse(char pulse) {
  if(pulse == '1') {
    digitalWrite(pulse_pin, HIGH);
  }
  delay(pulse_length);
  digitalWrite(pulse_pin, LOW);
}

