uint8_t widenHarmony(uint8_t& note1, uint8_t& note2) {
  //  Disallows intervals smaller than a minor third, and instead moves the second note up an octave instead.  
  if (abs(note1 - note2) < 3) {
    note2 += 12;
  }
  return note2;
}


class SmoothADCReader
{
  public:
    SmoothADCReader()
    : sample_rate_(48000.0f),
      frequency_(0.0f),
      phase_(
          1.0f), // Initialize phase to 1.0f to ensure immediate update on first trigger
      from_(0.0f),
      to_(0.0f),
      interval_(0.0f)
    {
    }

    void Init(float sample_rate)
    {
        sample_rate_ = sample_rate;
        SetFreq(
            1.0f); // Set the frequency of ADC updates, 
        phase_
            = 1.0f; // Ensure that we're ready to accept a trigger immediately
        from_     = 0.0f;
        to_       = 0.0f;
        interval_ = 0.0f;
    }

    // Process is now also checking for a trigger
    float Process(float newAdcValue, float clowny, bool trigger)
    {
        if(trigger)
        {
            from_
                = this->CurrentValue(); // Start from the current interpolated value
            to_    = newAdcValue;       // Set the new target value
            phase_ = 0.0f;              // Reset phase to start interpolation
            interval_
                = to_ - from_; // Calculate the new interval for interpolation
        }

        if(phase_ < 1.0f)
        {
            // Only interpolate if phase is less than 1
            phase_ += frequency_;
            float t = phase_ * phase_ * (clowny - 2.0f * phase_);     // smoothStep algo
            return from_ + interval_ * t;
        }
        else
        {
            return to_; // Once interpolation is complete, stick to the target value
        }
    }

    void SetFreq(float freq)
    {
        freq       = freq / sample_rate_;
        frequency_ = fclamp(
            freq,
            0.f,
            1.f); // Adjust frequency for interpolation speed, if needed
    }

    // Helper method to get the current interpolated value without advancing the phase
    float CurrentValue() const
    {
        if(phase_ < 1.0f)
        {
            float t = phase_ * phase_ * (3.0f - 2.0f * phase_);
            return from_ + interval_ * t;
        }
        else
        {
            return to_;
        }
    }

  private:
    float sample_rate_;
    float frequency_;
    float phase_;

    float from_;
    float to_; // Added to hold the target value
    float interval_;


}; // namespace SmoothADCReader
SmoothADCReader adcReader;
 //  often used to process the clock counters for gate sequences
int incrementAndWrapCount(u_int8_t& count, u_int8_t maxSize) {           
  count++;
  if (count > maxSize) {
    count = 0;
  }
}

