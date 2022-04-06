//звуки
#define beep_sound_len 2
uint8_t beep_sound[] = {200, 100};
uint16_t beep_sound_durations[] =  {120, 10};

#define exclamation_sound_len 2
uint8_t exclamation_sound[] = {200, 10};
uint16_t exclamation_sound_durations[] =  {120, 200};

#define fail_sound_len 3
uint8_t fail_sound[] = { 100, 255, 100 };
uint16_t fail_sound_durations[] = { 200, 50, 600 };

// мини-класс
class Speaker {
  public:
    Speaker(byte pin) {
      _pin = pin;
      _noteIndex = 0;
      _melodyLength = 0;
      _currentMelody = NULL;
      pinMode(_pin, OUTPUT);
      digitalWrite(_pin, HIGH);
    }

    void update() {
      if(_noteIndex < _melodyLength) {
        if(!_notePauseTime) {
          analogWrite(_pin, _currentMelody[_noteIndex]);
          _notePauseTime = _melodyDurations[_noteIndex];
          _startTime = millis();
        }

        if ((unsigned long)(millis() - _startTime) >= _notePauseTime) {
          digitalWrite(_pin, HIGH);
          _notePauseTime = 0;
          _noteIndex++;
        }
      }
      else {
        digitalWrite(_pin, HIGH);
        _currentMelody = NULL;
      }
    }

    void playMelody(byte len, uint8_t *melody, uint16_t *durations) { 
      _noteIndex = 0;
      _melodyLength = len;
      _currentMelody = melody;
      _melodyDurations = durations;
      _notePauseTime = 0;
      _startTime = millis();
    }

    bool isPlaying(){
      if(_currentMelody) return true;
      else return false;
    }

  private:
    uint8_t _pin;
    uint32_t _notePauseTime;
    uint32_t _startTime;
    uint16_t _noteIndex;
    uint16_t _melodyLength;
    uint8_t *_currentMelody;
    uint16_t *_melodyDurations;
};
