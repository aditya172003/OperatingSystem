#include<bits/stdc++.h>

using namespace std;









int main()
{   

    // opent the input file 
    ifstream fin ;
    fin.open("source2.txt;");


    // open the output file 
     
    ofstream fout ;
    fout.open("output.txt");


  

    ofstream mntout ;
    mntout.open("mnt.txt");


    ofstream mdtout;    
    mdtout.open("mdt.txt");

    ofstream pntout;
    pntout.open("pnt.txt");

    ofstream kpdout;
    kpdout.open("kpd.txt");





    string line,word;
    bool started=false;
    bool macrostarted = false;
    int p =1;


    // macro name , pp ,kp,mdtp , kpdt
    vector<array<string,5>>mnttab; 
    map<string,string> kpdtab;
    map<string,int>pnttab;
   

    while(getline(fin,line))
    {
        
        stringstream st (line);
        st>>word;
        if(word == "MACRO")
        {
            macrostarted = true;
            continue;
        }

        if(started)
        {
             if (word != "END")
            {
                fout << word << " ";
                while (st >> word)
                {
                    /* code */
                    fout << word << " ";
                }
                fout << endl;
            }
            continue;
        }
        

        if(macrostarted)
        {
            array<string,5>a;
            mnttab.push_back(a);
            int i = mnttab.size()-1;

            mnttab[i][0] = word;
            mnttab[i][3] = to_string(p);
            int pp=0;
            int kp=0;
            pntout<<"-----------PNTAB FOR "<<word<<" MACRO ---------------\n";

            while(st>>word)
            {
                if(word[word.length()-1]==',')
                {
                    word = word.substr(1,word.length()-2);
                }
                else{
                    word = word.substr(1,word.length()-1);
                }

                int equal=-1;

                for(int i =0;i<word.size();i++)
                {
                    if(word[i] == '=')

                    {
                        equal = i;
                        break;
                    }
                }
                 string before = word;
                if(equal != -1)
                {
                    kp++;
                    before = word.substr(0,equal);
                    string after  = word.substr(equal+1);

                    kpdtab[before]= after; 
                }
                 else{
                   pp++;
                 }
                pnttab[before] =pnttab.size();
                pntout<<pnttab[before]<<" , "<<before<<endl;


            }

            mnttab[i][1]=to_string(pp);
            mnttab[i][2]=to_string(kp);

            if(kp!=0)
            {
                mnttab[i][4]= to_string(kpdtab.size()-kp+1);
            }
            else{
                mnttab[i][4]='-';
            }
            macrostarted = false;
            continue;

        }

        // working with mdt

        if(word =="MEND")
        {
            mdtout<<"MEND"<<endl;
            pnttab.clear();
        }
        else if(word=="START")
        {
            started=true;
        }
        else 
        {
            mdtout<<word<<" ";

            while(st>>word)
            {
                if(word[0]=='&')
                {
                    word = word.substr(1);
                    if(word[word.size()-1]==',')
                    {
                        word= word.substr(0,word.size()-1);

                    }

                    mdtout<<"( p ,"<<pnttab[word]<<" ) ,";
                }
                else{

                    if(word[word.size()-1]==',')
                    {
                        word= word.substr(0,word.size()-1);

                    }
                    mdtout<<word<<",";
                }
         


            }

            mdtout<<endl;


        }

        p++;

    }

    fin.close();

    for(int i =0;i<mnttab.size();i++)
    {
        for(int j=0;j<5;j++)
        {
            mntout<<mnttab[i][j]<<" ";
        
        }
        mntout<<endl;
    }
    for(auto i : kpdtab)
    {
        kpdout<<i.first<<" "<<i.second<<endl;
    }
    mntout.close();
    cout<<"\n program executed"<<endl;
    


}