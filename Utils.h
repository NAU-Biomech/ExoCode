#ifndef UTILITES_HEADER
#define UTILITES_HEADER

class Average{
private:
  double avg;
  double count;
public:
  void update(double value);
  double getAverage();
  void reset();
};

class FixedAverage{
private:
	double* previous_values;
	double average;
	int size;
public:
	FixedAverage(int size);
	double updateAverage(double value);
	double getAverage();
};

class Clamp{
private:
	double upper;
	double lower;
public:
	Clamp(double upper, double lower);
	double clamp(double value);
};

class Threshold{
private:
	double upper_threshold;
	int crossed_threshold_max;
	int crossed_threshold_count;
	bool state;
public:
	Threshold(bool starting_state, double threshold_value, int crossed_threshold_max);
	bool getState(double value);
};

void updateMax(double* max_val, double val);

#endif
