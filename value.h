// FUNCTIONS FOR VALUE ITERATION
void conditionPhi(int, int, int, vector<float> &, vector<float> &);
void conditionTheta(int, int, int, vector<float> &, vector<float> &);
void conditionR(int, int, int, vector<float> &, vector<float> &);
void computeTotalCost(vector<float> &, vector<float> &);
float computeNewValue(vector<float> &);
char computeNewPolicy(vector<float> &);
void valueIteration(vector<float> &, vector<float> &, vector<float> &, vector<char> &, vector<float> &);
