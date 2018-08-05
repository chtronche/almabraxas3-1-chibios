// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

class LinearMapper {
 public:
  LinearMapper(int from0, float to0, int from1, float to1);
  float convert(int v) { return a * v + b; }

 private:
  float a, b;
};
