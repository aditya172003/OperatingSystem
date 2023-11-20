#include <bits/stdc++.h>
using namespace std;

int main()
{

    ifstream fin;
    fin.open("source2.txt;");

    ofstream fout;
    fout.open("output.txt");

    ofstream mntout;
    mntout.open("mnt.txt");

    ofstream mdtout;
    mdtout.open("mdt.txt");

    ofstream pntout;
    pntout.open("pnt.txt");

    ofstream kpdout;
    kpdout.open("kpd.txt");

    string line, word;
    int p = 1;
    bool started = false;
    bool macrostart = false;

    vector<array<string, 5>> mnttab;
    vector<pair<string, string>> kpdtab;
    map<string, int> pnttab;

    while (getline(fin, line))
    {
        stringstream st(line);
        st >> word;
        if (word == "MACRO")
        {
            macrostart = true;
            continue;
        }
        if (started)
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
        if (macrostart)
        {
            array<string, 5> a;
            mnttab.push_back(a);
            int i = mnttab.size() - 1;
            mnttab[i][0] = word;
            mnttab[i][3] = to_string(p);
            int pp = 0;
            int kp = 0;
            pntout << "---------PNTAB FOR " << word << " MACRO-------\n";
            while (st >> word)
            {
                if (word[word.length() - 1] == ',')
                {
                    word = word.substr(1, word.length() - 2);
                }
                else
                {
                    word = word.substr(1, word.length() - 1);
                }
                int equalindex = -1;

                for (int j = 0; j < word.length(); j++)
                {
                    if (word[j] == '=')
                    {
                        equalindex = j;
                        break;
                    }
                }
                if (equalindex == -1)
                {
                    pp++;
                    pnttab[word] = pnttab.size() + 1;
                    pntout << pnttab[word] << ". " << word << endl;
                }
                else
                {
                    kp++;
                    string beforeequal, afterequal;
                    beforeequal = word.substr(0, equalindex);
                    afterequal = word.substr(equalindex + 1);
                    kpdtab.push_back({beforeequal, afterequal});
                    pnttab[beforeequal] = pnttab.size() + 1;
                    pntout << pnttab[beforeequal] << ". " << beforeequal << endl;
                }
            }
            mnttab[i][1] = to_string(pp);
            mnttab[i][2] = to_string(kp);
            if (kp != 0)
            {
                mnttab[i][4] = to_string(kpdtab.size() - kp + 1);
            }
            else
            {
                mnttab[i][4] = '-';
            }
            macrostart = false;
            continue;
        }
        if (word == "MEND")
        {
            mdtout << "MEND" << endl;
            // cout << "MEND OCCURED : PNTAB : \n";
            // for (auto i : pnttab)
            // {
            //     cout << i.first << " " << i.second << "\n";
            // }
            pnttab.clear();
        }
        else if (word == "START")
        {
            started = true;
        }
        else
        {
            mdtout << word << " ";
            // bool start = true;
            while (st >> word)
            {

                if (word[0] == '&')
                {
                    word = word.substr(1);
                    if (word[word.size() - 1] == ',')
                    {
                        word = word.substr(0, word.size() - 1);
                    }
                    mdtout << "(P," << pnttab[word] << "), ";
                    // cout << "\nWord in pntab : " << word << endl;
                }
                else
                {
                    if (word[word.size() - 1] == ',')
                    {
                        word = word.substr(0, word.size() - 1);
                    }
                    mdtout << word << ", ";
                }
                // start = false;
            }
            mdtout << endl;
        }
        p++;
    }

    fin.close();
    for (int i = 0; i < mnttab.size(); i++)
    {
        /* code */
        for (int j = 0; j < 5; j++)
        {
            /* code */
            mntout << mnttab[i][j] << " ";
            cout << mnttab[i][j] << " ";
        }
        mntout << endl;
    }

    for (auto i : kpdtab)
    {
        kpdout << i.first << " " << i.second << endl;
    }

    cout << "\nProgram Executed\n";
    return 0;
}