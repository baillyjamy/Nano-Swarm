#ifndef FPS_COUNTER_HPP
# define FPS_COUNTER_HPP

class FPSCounter
{
private:
  long last;
  int frames;
public:
  FPSCounter();
  void tick();
};

#endif //! FPS_COUNTER_HPP
