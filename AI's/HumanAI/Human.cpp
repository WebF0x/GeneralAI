#include "Human.h"

using namespace std;

Human::Human()
{
    //ctor
}

Human::~Human()
{
    //dtor
}

void Human::run()
{
    cout<<"Inputs:"<<endl;
    for(unsigned int i=0; i<inputSize(); ++i)
    {
        cout<<"\t"<<input(i)<<endl;
    }

    int output = 0;
    cout<<"Output: ";
    cin>>output;
    setOutput(0,output);
}

void Human::load(vector<int> data)
{
    cout<<"Memoire"<<endl
        <<"=========="<<endl;

    for(unsigned int i=0; i<data.size(); ++i)
    {
        //cout<<"Data #"<<i<<": "<<data[i]<<endl;
        cout<< char(data[i]);
    }
}

vector<int> Human::getData()
{
    cout<<"Quoi garder en memoire"<<endl;

    string str;
    getline(cin, str);

    vector<int> v;

    for(unsigned int i=0;i<str.length();++i)
    {
        v.push_back(str[i]);
    }

    return v;
}
