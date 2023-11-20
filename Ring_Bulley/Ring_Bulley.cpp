#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
class Ring {
public:
    int coordinator;
    std::vector<bool> process;

    Ring(int n) {
        for (int i = 0; i < n; i++) {
            process.push_back(true);
        }

        int id;
        std::cout << "Enter the coordinator: ";
        std::cin >> id;
        this->coordinator = id;
    }

    void failCoordinator() {
        process[this->coordinator - 1] = false;
        std::cout << "Node " << this->coordinator << " failed.\n" << std::endl;
    }

    void startElection() {
        int n = process.size();
        int detector = rand() % n;
        while (process[detector] == false) {
            detector = rand() % n;
        }

        std::cout << "\nNode " << detector << " detected failure.\n" << std::endl;
        usleep(500000);

        int receiver = detector + 1;
        int sender = detector;

        std::vector<int> tempCoord;
        tempCoord.push_back(sender);
        while (receiver != detector) {
            if (process[receiver] == true) {
                std::cout << sender << " elects to " << receiver << std::endl;
               
                tempCoord.push_back(receiver);
                sender = receiver;
                receiver = (receiver + 1) % (n +1);
            }
            else
            {
                receiver = (receiver + 1) % (n +1);
                 
            }
        }
        
        if (!tempCoord.empty()) {
            std::cout << "\nElection result: ";
            for (auto i : tempCoord) {
                std::cout << i << " ";
            }
            this->coordinator = *max_element(tempCoord.begin(), tempCoord.end());
            std::cout << "\nNode " << this->coordinator << " is selected as the new coordinator." << std::endl;
        } else {
            std::cout << "\nNo active nodes for election." << std::endl;
        }

        usleep(500000);
    }
};



class Bully{
    public:
    int coordinator;
    vector<bool> process;
    Bully(int n)
    {
        for(int i=0;i<n;i++)
        {
            process.push_back(true);
        }
        
        int id;
        cout<<"Enter the coordinator ";
        cin>>id;
        this->coordinator = id;
    }
    
    void failCoordinator()
    {
        process[this->coordinator - 1] = false;
        cout<<"Node " << this->coordinator << " faild.\n"<<endl;
    }
    
    void startElection()
    {
        int n = process.size();
        int detector = rand() % n;
        while(process[detector] == false)
        {
            detector = rand() % n;
        }
        
        cout << "\nNode " << detector + 1 << " detected failure.\n"
         << endl;
        usleep(500000);
        
        for (int i = detector; i < n; i++)
    {
        int ACKcnt = 0;

        for (int j = i + 1; j <= n; j++)
        {
            cout << "Node " << i + 1 << " elects to " << j + 1 << endl;
            usleep(500000);
            if (process[j] == true)
            {
                ACKcnt++;
                cout << "Ok received from " << j + 1 << endl;
                cout << endl;
                usleep(500000);
            }
            else
            {
                cout << "Ack lost from " << j + 1 << endl;
                cout << endl;
                usleep(500000);
            }
        }

        if (ACKcnt == 0)
        {
            // new co-or found
            cout << "\nNew co-ordinator elected: " << i + 1 << endl;
            this->coordinator = i+1;
            cout << endl;
            usleep(500000);
            break;
        }
    }
    }
    
};

int main()
{
    // Bully b(7);
    // cout<<b.coordinator<<endl;
    // b.failCoordinator();
    // b.startElection();
    // cout<<b.coordinator<<endl;
    // cout << endl;
    // ring();
    
    Ring r(7);
    cout<<r.coordinator<<endl;
    r.failCoordinator();
    r.startElection();
    cout<<endl;
    return 0;
}