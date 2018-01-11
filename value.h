// FUNCTIONS FOR VALUE ITERATION
void conditionPhi(int, int, int, vector<double> &, vector<double> &);
void conditionTheta(int, int, int, vector<double> &, vector<double> &);
void conditionR(int, int, int, vector<double> &, vector<double> &);
void computeTotalCost(vector<double> &, vector<double> &);
double computeNewValue(vector<double> &);
char computeNewPolicy(vector<double> &);
void valueIteration(vector<double> &, vector<double> &, vector<double> &, vector<char> &, vector<double> &);
