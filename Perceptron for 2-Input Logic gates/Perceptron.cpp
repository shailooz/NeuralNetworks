#include <iostream>
#include<time.h>
#include<cstdlib>
#include<iomanip>

using namespace std;

class Perceptron
{
    
    float w1,w2,theta;
    int iter;
    public : 
        Perceptron(int);
        void fit(float[][2],float[]);
        float* predict(float[][2]);
        void describe();
        void printPrediction(float[], float[]);
        
    private:
    
        float unit_step(float);
        int random(int min, int max);
        float getRandom();
        float evaluate(float[]);
};
Perceptron::Perceptron(int it=100)
{
    w1 = getRandom();
    w2 = getRandom();
    theta = getRandom();
    iter=it;
}
float Perceptron::evaluate(float x[])
{
    return w1*x[0]+w2*x[1]-theta;
}
float Perceptron::unit_step(float val)
{
    if(val>0)
        return 1.0;
    return 0.0;
}
int Perceptron::random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}
float Perceptron::getRandom()
{
    return random(1,10);
    
}
void Perceptron::printPrediction(float pred[],float y[])
{
	cout<<"\n\n\tPREDICTIONS\n\n";
	cout<<setw(10)<<"  actual   |"<<setw(10)<<"   predicted"<<endl;
	cout<<setw(10)<<"-----------|"<<setw(10)<<"------------"<<endl;
    for(int i=0;i<4;i++)
        cout<<setw(6)<<y[i]<<"     |"<<setw(8)<<"   "<<pred[i]<<endl;
}

void Perceptron::fit(float X[][2],float y[])
{
    int j=0;
    while(j<iter)
    {
        int nochange=0;
        j++;
        for(int i=0;i<4;i++)
        {
            float ypred = evaluate(X[i]);
            if(ypred>0 && y[i]==0)
            {
                w1-=X[i][0];
                w2-=X[i][1];
            }
            else if(ypred<0 && y[i]==1)
            {
                w1+=X[i][0];
                w2+=X[i][1];
            }
            else
            {
                nochange++;
            }
        }
        if(nochange==4)
            break;

    }
}
float* Perceptron::predict(float X[][2])
{
    float* y_pred=new float[4];
    for(int i=0;i<4;i++)
    {
        y_pred[i]=unit_step(evaluate(X[i]));
    }
    return y_pred;
}
void Perceptron::describe()
{
	cout<<"\n\n\tMODEL PARAMS";
    cout<<"\n\ncoefficients : ["<<w1<<", "<<w2<<"] , intercept : "<<theta;
}
int main()
{
    float X[][2]={{0,0},{0,1},{1,0},{1,1}};
    float y[]={0,0,0,1};
    float* y_pred;
    
    
    Perceptron model;
    model.fit(X,y);
    model.describe();
    y_pred = model.predict(X);
    model.printPrediction(y_pred,y);
    
    return 0;
    
}
