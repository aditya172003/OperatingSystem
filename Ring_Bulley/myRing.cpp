#include<bits/stdc++.h>
#include <unistd.h>

using namespace std;



class ElectionAlgorithms
{
    public:
    vector<bool>node;
    int coordinator ;
    int nodes;

    public:
        ElectionAlgorithms()
        {
          

        }

        void initialize()
        {
            cout<<"Enter the number of nodes in the system : ";
            cin>>nodes;
            node.resize(nodes,true);
            cout<<"Enter the id of initial Co-ordinator : ";
            cin>>coordinator;
        }


        void failNode()
        {
            int nod = rand()%nodes;
            while(node[nod]==false)nod= rand()%nodes;
            node[nod]=false;
            cout<<"NODE "<<nod<<" FAILED"<<endl;
        }

        void failCoordinator()
        {
           cout<<"COORDINATOR "<<coordinator<<" FAILED"<<endl;
            node[coordinator]=false;
            coordinator =-1;

        }

        
        void startElectionRing()
        {
            int starter = rand()%nodes;
            while(node[starter]==false) starter = rand()%nodes;

            cout<<"NODE : "<<starter<<" DETECTS AN FAILURE"<<endl;
            int init = starter;
            vector<int>results;
       
            do
            {
                int nxt = (starter+1)%nodes;

                if(node[starter]==true)
                {
                    cout<<starter<<" Elects to "<<nxt<<endl;
                    usleep(1000000);
                    results.push_back(starter);
                }
                starter  =nxt;


                /* code */
            } while (starter !=init);

            cout<<"ELECTION RESULTS"<<endl;

            for(auto i : results)cout<<i<<" ";
            cout<<endl;

            coordinator = *max_element(results.begin(),results.end());

            cout<<"NODE "<< coordinator<<" ELECTED AS NEW COORDINATOR"<<endl;
            
        }

        bool nxtAcksend(int nod)
        {
            usleep(1000000);
            if(node[nod]==false)return false;
            bool result = false;
            for(int i= nod+1;i<nodes;i++)
            {
                cout<<nod<<" SENDS ACK TO NODE : "<<i<<endl;
                result = result|nxtAcksend(i);
                if(result==true)return true;
            }

            if(result == false)
            {
                cout<<"NEW COORDINATOR ELECTED : "<<nod<<endl;
                coordinator = nod;

                return true;

            }
            return result;

        }

        void startElectionBulley()
        {
            int starter = rand()%nodes;
            while(node[starter]==false) starter = rand()%nodes;

            starter = 2;
            cout<<"NODE : "<<starter<<" DETECTS AN FAILURE"<<endl;
            int init = starter;


            nxtAcksend(init);

        }

};


int main()
{
    ElectionAlgorithms r ;
    r.initialize();
    r.failCoordinator();
    r.failNode();
    r.failNode();
    r.failNode();
    r.failNode();
    r.failNode();
    r.failNode();

// here are the two options to choose the algorithms


    //r.startElectionRing();
    r.startElectionBulley();
}