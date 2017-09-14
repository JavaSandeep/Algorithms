#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <new>

using namespace std;

class Coords
{
private:
    int xcoord, ycoord;
public:
    void setxcoord(int x)
    {xcoord=x;}
    void setycoord(int y)
    {ycoord=y;}
    int retxcoord()
    {return xcoord;}
    int retycoord()
    {return ycoord;}
};

class Manager
{
private:
    Coords * foo[22];
    queue<int> sizequeue;
    queue<int> listme;
public:
    Manager()
    {
        listme.push(0);
    }
    int ShowlistSize()
    {
        return listme.size();
    }
    void Getdata(string file_name);
    void Kmeans();
    void FreePointer(Coords * tent);
    void ShowCluster();
    void FreeQueue();
    void Rearrange();
    int CalcDist(int x1, int y1, int x2, int y2, int x3, int y3);
};

void Manager::Rearrange()
{

}

void Manager::ShowCluster()
{
    int x,y;
    for(int j=0; j<=listme.size();j++)
    {
        for(int t=0; t<sizequeue.front();t++)
        {
            x=foo[listme.front()][t].retxcoord();
            y=foo[listme.front()][t].retycoord();
            cout<<"("<<x<<","<<y<<")"<<endl;
        }
        cout<<endl;
        cout<<endl;
        FreePointer(foo[listme.front()]);
        FreeQueue();
    }
}
void Manager::Getdata(string file_name)
{
    int COUNTER=0;
    int COUNTER1=0;
    foo[0] = new (nothrow) Coords[100];
    if (foo == nullptr)
        cout << "Error: memory could not be allocated";
    else
    {
        ifstream input_stream(file_name.c_str());

	if(input_stream == '\0')
    {
        cout<<"Could not open file";
        exit(0);
    }

    string tempt[2];
    string line;

    while(getline(input_stream,line))
    {
        int countme=0;
        stringstream  lineStream(line);
        string        cell;

        while(getline(lineStream,cell,','))
        {
            tempt[countme]=cell;
            countme++;
        }
        if(COUNTER>0)
        {
            foo[0][COUNTER1].setxcoord(atof(tempt[0].c_str()));
            foo[0][COUNTER1].setycoord(atof(tempt[1].c_str()));
            COUNTER1++;
        }
        COUNTER++;
    }
    sizequeue.push(100);//needs to be reworked

    }
}

int Manager::CalcDist(int x1, int y1, int x2, int y2, int x3, int y3)
{
    float dist1= (float(x1-x3)*float(x1-x3))+(float(y1-y3)*float(y1-y3));

    float dist2= (float(x2-x3)*float(x2-x3))+(float(y2-y3)*float(y2-y3));
    if(dist1<dist2)
        return 0;
    else
        return 1;
}

void Manager::Kmeans()
{
    int NO_end=sizequeue.front();
    int counterr=listme.front();
    int arr[NO_end];
    int x1tmp, y1tmp;
    int x2tmp, y2tmp;
    int rannd[2];
    int tmprslt;
    int counter1, counter2;
    int total1=0;
    int total2=0;
    srand(time(NULL));
    for(int x=0;x<2;x++)
    {
        rannd[x]=rand()%NO_end;
    }
    x1tmp=foo[counterr][rannd[0]].retxcoord();
    y1tmp=foo[counterr][rannd[0]].retycoord();
    x2tmp=foo[counterr][rannd[1]].retxcoord();
    y2tmp=foo[counterr][rannd[1]].retycoord();
    counter1=listme.back()+1;
    counter2=listme.back()+2;
    for(int loop=0; loop<NO_end; loop++)
    {
        tmprslt=CalcDist(x1tmp,y1tmp,x2tmp,y2tmp,foo[counterr][loop].retxcoord(),foo[counterr][loop].retycoord());
        arr[loop]=tmprslt;
        if(tmprslt==0)
            total1++;
        else
            total2++;
    }
    foo[counter1]=new Coords[total1];
    foo[counter2]=new Coords[total2];
    listme.push(counter1);
    listme.push(counter2);
    sizequeue.push(total1);
    sizequeue.push(total2);
    int loop1=0;
    int loop2=0;
    for(int xt=0; xt<NO_end; xt++)
    {
        if(arr[xt]==0)
        {
            foo[counter1][loop1].setxcoord(foo[counterr][xt].retxcoord());
            foo[counter1][loop1].setycoord(foo[counterr][xt].retycoord());
            loop1++;
        }
        else
        {
            foo[counter2][loop2].setxcoord(foo[counterr][xt].retxcoord());
            foo[counter2][loop2].setycoord(foo[counterr][xt].retycoord());
            loop2++;
        }
    }
    FreeQueue();
    FreePointer(foo[counterr]);
}

void Manager::FreeQueue()
{
    if(!listme.empty())
        listme.pop();
    if(!sizequeue.empty())
        sizequeue.pop();
}

void Manager::FreePointer(Coords * tent)
{
    delete[] tent;
}

int main()
{
    string input_file;
    Manager _manager;
    cout << "Give name of input file : ";
	cin >> input_file;

   _manager.Getdata(input_file);

    while(_manager.ShowlistSize() < 10)
    {
        _manager.Kmeans();
        _manager.Rearrange();
    }
    _manager.ShowCluster();
}
