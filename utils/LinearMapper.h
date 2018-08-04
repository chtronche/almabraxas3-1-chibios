class LinearMapper {
 public:
  LinearMapper(int from0, float to0, int from1, float to1);
  float convert(int v) { return a * v + b; }

 private:
  float a, b;
};
