#ifndef SCORE_HPP_
# define SCORE_HPP_

struct Score
{
  long unsigned int score;
  long unsigned int botKilled;
  long unsigned int botCreated;

  static constexpr int const BOT_KILLED = 200;
  static constexpr int const BOT_CREATED = 100;
  static constexpr int const BOT_FRAME = 1;
};

#endif /* !SCORE_HPP_ */
