/*The Goertzel algorithm detects a specific, predetermined frequency in a signal. 
This can be used to analyze a sound source for the presence of a particular tone. 
The algorithm is simpler than an FFT and therefore a candidate for small embedded systems.*/

//analyze an array of samples for a given frequency
double goertzelFilter(int samples[], double freq, int N)
{
	double s_prev = 0.0;
	double s_prev2 = 0.0;
	double coeff, normalizedfreq, power, s;
	normalizedfreq = freq / SAMPLEFREQUENCY;
	coeff = 2 * cos(2 * M_PI * normalizedfreq);//pi == acos(-1.0)
	for (int i = 0; i < N; i++)
	{
		s = samples[i] + coeff * s_prev - s_prev2;//s(n) = x(n) + 2 * cos(2 * pi * f) * s(n - 1) - s(n - 2)
		s_prev2 = s_prev;
		s_prev = s;
	}
//|y(N)| ^ 2 = s(N - 1) ^ 2 + s(N - 2) ^ 2 - 2 cos(2 * pi * K / N) * s(N - 1) * s(N - 2)
	power = s_prev2 * s_prev2 + s_prev * s_prev - coeff * s_prev * s_prev2;
	return power;
}

/*However, there are two issues with that approach: first, the samples need to be stored, 
which requires a lot of RAM memory that might not be easily available on a microcontroller. Second, 
the detection of a signal might be delayed until the sample buffer is full and gets analyzed.
As an improvement, we can formulate the filter also as a real time algorithm that analyzes one sample at a time:*/
double RTgoertzelFilter(int sample, double freq)
{
	static double s_prev = 0.0;
    static double s_prev2 = 0.0;  
    static double totalpower = 0.0;  
    static int N = 0;
    double coeff, normalizedfreq, power, s;
    normalizedfreq = freq / SAMPLEFREQUENCY;
    coeff = 2 * cos(2 * M_PI * normalizedfreq);
    s = sample + coeff * s_prev - s_prev2;
    s_prev2 = s_prev;
    s_prev = s;
    N++;
    power = s_prev2 * s_prev2 + s_prev * s_prev - coeff * s_prev * s_prev2;
    totalpower += sample * sample;
    if(0 == totalpower)
    	totalpower = 1;
    return power / totalpower / N;
}

/*Note that the initialization of the static variables takes place only at the first time 
when the function is called. The return value has been normalized using the total power and number of samples.
This filter delivers a result after each sample without storing the samples, 
but it considers the whole history of the signal. If you want to detect the sudden presence of a tone, 
it is better to limit the history of the filter. This can be done using the tandemRTgoertzelFilter:*/
double tandemRTgoertzelFilter(int sample,double freq)
{
	static double s_prev[2] = {0.0, 0.0};
	static double s_prev2[2] = {0.0, 0.0};
	static double totalpower[2] = {0.0, 0.0};
	static int N = 0;
	double coeff, normalizedfreq, power, s;
	int active;
	static int n[2] = {0, 0};
	normalizedfreq = freq / SAMPLEFREQUENCY;
	coeff = 2 * cos(2 * M_PI * normalizedfreq);
    s = sample + coeff * s_prev[0] - s_prev2[0];
    s_prev2[0] = s_prev[0];
    s_prev[0] = s;
    n[0]++;
    s = sample + coeff * s_prev[1] - s_prev2[1];
    s_prev2[1] = s_prev[1];
    s_prev[1] = s;    
    n[1]++;
    N++;
    active = (N / RESETSAMPLES) & 0x01;
    if(n[1 - active] >= RESETSAMPLES)
    {//reset inactive
    	s_prev[1 - active] = 0.0;
    	s_prev2[1 - active] = 0.0;
        totalpower[1 - active] = 0.0;
        n[1 - active] = 0;
    }
    totalpower[0] += sample * sample;
    totalpower[1] += sample * sample;
    power = s_prev2[active] * s_prev2[active] + s_prev[active] * s_prev[active]-coeff * s_prev[active] * s_prev2[active];
    return power / (totalpower[active] + 1e-7) / n[active];
}

/*The tandem filter is the combination of two real-time filters, 
which are reset alternatively every RESETSAMPLES. Except for the 
first RESETSAMPLES, the active filter always has a history between 
RESETSAMPLES and 2 * RESETSAMPLES samples. Meanwhile the inactive 
filter is building up its history again. This is necessary because 
the algorithm needs some time to reach a steady state. In my test 
runs, I successfully used a value of 200 samples for RESETSAMPLES 
in order to detect a 440 Hz signal in a 44kHz audio sample. Even 
for an 8 bit Microcontroller without an FPU, the tandem implementation 
is fast enough. For high performance computation, I further recommend 
to translate the algorithm to fixed point arithmetic.*/