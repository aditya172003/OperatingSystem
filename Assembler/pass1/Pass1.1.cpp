#include<bits/stdc++.h>

using namespace std;


int main()
{   
    cout<<"PROGRAM STARTED"<<endl;
    map<string,pair<string,string>>opcode;

      opcode["STOP"] = {"IS", "00"};
    opcode["ADD"] = {"IS", "01"};
    opcode["SUB"] = {"IS", "02"};
    opcode["MULT"] = {"IS", "03"};
    opcode["MOVER"] = {"IS", "04"};
    opcode["MOVEM"] = {"IS", "05"};
    opcode["COMP"] = {"IS", "06"};
    opcode["BC"] = {"IS", "07"};
    opcode["DIV"] = {"IS", "08"};
    opcode["READ"] = {"IS", "09"};
    opcode["PRINT"] = {"IS", "10"};
    
    opcode["START"] = {"AD", "01"};
    opcode["END"] = {"AD", "02"};
    opcode["ORIGIN"] = {"AD", "03"};
    opcode["EQU"] = {"AD", "04"};
    opcode["LTORG"] = {"AD", "05"};
    opcode["DC"] = {"DL", "01"};
    opcode["DS"] = {"DL", "02"};

    opcode["AREG"] = {"1", ""};
    opcode["BREG"] = {"2", ""};
    opcode["CREG"] = {"3", ""};
    opcode["DREG"] = {"4", ""};

    opcode["LT"] = {"1", ""};
    opcode["LE"] = {"2", ""};
    opcode["EQ"] = {"3", ""};
    opcode["GT"] = {"4", ""};
    opcode["GE"] = {"5", ""};
    opcode["ANY"] = {"6", ""};

    ifstream fin;
    fin.open("input2.txt");

    ofstream fout;
    fout.open("output2.txt");


    // symbol table 
    map<string,pair<int,string>>symtab;

    // literal table 
    vector<pair<string,int>>littab;
    int littindex = 0;
    
    // pool tab
    vector<string>pooltab;

    string line,word;
    int lc =-1;
    
    // start scanning 

    while(getline(fin,line))
    {
        // get word;

        stringstream st(line);
        st>>word;

        string label="";

        // check for symbol 
        if(opcode.count(word)==0)
        {
            // this is the symbol 
            if(symtab.count(word)==0)
            {
                symtab[word ]= {lc,to_string(symtab.size()+1)};
            }
            else{
                symtab[word].first = lc;
            }
            label = word;
            st>>word;
        }

        // check if oprations 

        // first print the intremediate code for each
        string operation = word;

        // check if start 
        if(operation == "START")
        {

            fout<<"    ";
            fout<<"("<<opcode[operation].first<<","<<opcode[operation].second<<")";
            st>>word;
            fout<<"(C"<<","<<word<<")"<<endl;

            lc = stoi(word);
            continue;
        }
    
        // check if end
        else if (operation =="END")
        {   


            
            // process literal table 

            pooltab.push_back("#"+to_string(littindex));

            for(;littindex<littab.size();littindex++)
            {
                fout << lc << " ";
                littab[littindex].second = lc;
                lc++;
                fout<<"("<<opcode["DC"].first<<","<<opcode["DC"].second<<")";
                fout<<"(C"<<","<<littab[littindex].first.substr(2,littab[littindex].first.size()-3)<<")"<<endl;

                
            }
            fout<<"    ";
            fout<<"("<<opcode[operation].first<<","<<opcode[operation].second<<")"<<endl;;


        }

        // check if ltorg
        else if(operation=="LTORG")
        {
            fout<<"    ";
            fout<<"("<<opcode[operation].first<<","<<opcode[operation].second<<")"<<endl;

            // process literal table 

            pooltab.push_back("#"+to_string(littindex));

            for(;littindex<littab.size();littindex++)
            {
                 fout << lc << " ";
                littab[littindex].second = lc;
                lc++;
                fout<<"("<<opcode["DC"].first<<","<<opcode["DC"].second<<")";
                fout<<"(C"<<","<<littab[littindex].first.substr(2,littab[littindex].first.size()-3)<<")"<<endl;

                
            }
           
        }
       
        //check if equ 
        else if(operation == "EQU")
        {
            // 
            fout<<"     ";
            fout<<"No IC";
            fout<<endl;
            st>>word;
            int pms = -1;
            char sign ='=';
            for(int i=0;i<word.size();i++)
            {
                if(word[i]=='+'||word[i]=='-')
                {
                    sign  =word[i];
                    pms = i;
                    break;
                }
            }

            string before = word;
            string after ;
            
            if(pms!=-1)
            {
                before = word.substr(0,pms);
                after  = word.substr(pms+1); 
            }

            symtab[label].first += symtab[before].first;
            if(pms!=-1)
            {
                if(sign=='-'){
                     symtab[label].first -= symtab[after].first;
                }
                else{
                    symtab[label].first += symtab[after].first;
                }
            }


        }

        // check if origin 
        else if(operation=="ORIGIN")
        {
            fout<<"     ";
            fout<<"("<<opcode[operation].first<<","<<opcode[operation].second<<")";
            fout<<endl;
            st>>word;
            int pms = -1;
            char sign ='=';
            for(int i=0;i<word.size();i++)
            {
                if(word[i]=='+'||word[i]=='-')
                {
                    sign  =word[i];
                    pms = i;
                    break;
                }
            }

            string before = word;
            string after ;
            
            if(pms!=-1)
            {
                before = word.substr(0,pms);
                after  = word.substr(pms+1); 
            }

            lc += symtab[before].first;
            if(pms!=-1)
            {
                if(sign=='-'){
                     lc -= stoi(after);
                }
                else{
                    lc+= stoi(after);
                }
            }
             
            continue;

        }
        // else 
        else 
        {
            fout << lc << " ";
            fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";

            while(st>>word)
            {
                     // DS 
                if(operation == "DS")
                {
                    
                    fout << "(C, " << word << ") ";
                    lc += stoi(word) - 1;
                    
                }

                // DC
                else if(operation=="DC")
                {
                    word = word.substr(1,word.size()-2);
                    fout << "(C, " << word << ") ";
                }

                // OPCODE

                else if(opcode.count(word)>0)
                {
                    fout << "(" << opcode[word].first << ", "<<opcode[word].second<<")";
                }
                // LITERAL
                else if(word[0]=='=')
                {
                    littab.push_back({word, lc});
                    fout << "(L, " << littab.size() << ") ";
                }
                // SYMBOL
                else
                {

                    if (symtab.count(word) == 0)
                    {
                        symtab[word] = {lc, to_string(symtab.size() + 1)};
                    }
                    fout << "(S, " << symtab[word].second << ") ";
                }

                
            }
           lc++;

        }

        fout<<endl;

    }
    fin.close();
    fout.close();


    ofstream sout;
    sout.open("SYMBOL_TABLE.txt");

    for(auto i  : symtab)
    {
        sout<<i.second.second<< " " <<i.second.first<<" "<<i.first<<endl;
    }

    sout.close();

    ofstream lout;
    sout.open("LITERAL_TABLE.txt");

    for(auto i  : littab)
    {
        sout<<i.first<<" "<<i.second<<endl;
    }

    sout.close();
    
    ofstream pout;
    sout.open("POOL_TABLE.txt");

    for(auto i  : pooltab)
    {
        sout<<i<<endl;
    }

    sout.close();

    cout<<"INTERPRETED SUCCESSFULLY"<<endl;




}