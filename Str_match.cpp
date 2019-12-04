#include<bits/stdc++.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

#define ll long long
#define A 256
#define P 101

ll count_plag_lines = 0,arr[1000] = {0};;

/**Robin-Karp Algorith starts here**/                                                 //It takes O(mn) time in worst case
void RobinKarp_Algorithm(string test,string source,ll count1,ll count2,string file){
    fstream fout;
    fout.open("results.txt",ios::in|ios::out|ios::trunc);

    ll M=test.size();                                
    ll N=source.size();
    ll i,j,p=0,t=0,k=1;                     //p is the hash value of pattern, t is hash value of sample text file's line

    for(i=0;i<M-1;i++)
        k=(k*A)%P;                          //k->pow(A,M-1)::A->256(base)
    for(i=0;i<M;i++){
        p=(A*p + test[i])%P;
        t=(A*t + source[i])%P;
    }
    for(i=0;i<=N-M;i++){
        if(p==t){    
            for(j=0;j<M;j++){
                if(source[i+j]!=test[j])
                    break;
            }
            if(j==M){
                cout<<"\nLine "<<count1<<" of given file is 100% copied from Line "<<count2<<" of "<<file<<"!"<<endl;
                fout<<"\nLine "<<count1<<" of given file is 100% copied from Line "<<count2<<" of "<<file<<"!"<<endl;
                arr[count1] = 1;

            }
        }
        /**Rolling hash function works here!**/
        if(i<N-M){
            t=(A*(t-source[i]*k) + source[i+M])%P;
            if(t<0)
                t=t+P;                      
        }
    }
    fout.close();
}

void Plagiarism_RobinKarp(string samplefiles[]){
    ll count1=0,count2=0,countlines=0;
    string pattern,source,temp;
    fstream finp,fins;
    finp.open("file.txt",ios::in);

    while(getline(finp,temp)){
        ++countlines;
    }
    finp.close();--countlines;//--countlines;
    finp.open("file.txt",ios::in);
  for(int i=0;i<6;i++){
      count1=0;
    finp.close();
    finp.open("file.txt",ios::in);
    fins.open(samplefiles[i],ios::in);
    while(finp.good()){
        count2=0;
        ++count1;
        getline(finp,pattern);

        if(count1>countlines)
            break;
        fins.clear();
        fins.seekg(0,ios::beg);

        while(fins.good()){
            getline(fins,source);
            ++count2;
            RobinKarp_Algorithm(pattern,source,count1,count2,samplefiles[i]);     //calling the main Rabin karp algo
        }
    }
    fins.close();
  }
  finp.close();
}

/**Naive Algorithm starts here**/                            //It takes O(mn) time
void Naive_Algorithm(string test,string source,ll count1,ll count2,string file){
    fstream fout;
    fout.open("results.txt",ios::in|ios::out|ios::trunc);
    ll M=test.size();
    ll N=source.size();
    ll i,j;
    for(i=0;i<=N-M;i++){
        for(j=0;j<M;j++){
            if(source[i+j]!=test[j])
                break;
        }
        if(j==M){
            cout<<"\nLine "<<count1<<" of given file is 100% copied from Line "<<count2<<" of "<<file<<"!"<<endl;
            fout<<"\nLine "<<count1<<" of given file is 100% copied from Line "<<count2<<" of "<<file<<"!"<<endl;
            arr[count1] = 1;

        }
    }
    fout.close();
}

void Plagiarism_Naive(string samplefiles[]){
    ll count1=0,count2=0,countlines=0;
    string pattern,source,temp;
    fstream finp,fins;
    finp.open("file.txt",ios::in);

    while(getline(finp,temp)){
        ++countlines;
    }
    finp.close();--countlines;
    finp.open("file.txt",ios::in);
  for(int i=0;i<6;i++){
    count1=0;
    finp.close();
    finp.open("file.txt",ios::in);
    fins.open(samplefiles[i],ios::in);
    while(finp.good()){
        count2=0;
        ++count1;
        getline(finp,pattern);

        if(count1>countlines)
            break;
        fins.clear();
        fins.seekg(0,ios::beg);

        while(fins.good()){
            getline(fins,source);
            ++count2;
            Naive_Algorithm(pattern,source,count1,count2,samplefiles[i]);
        }
    }
    fins.close();
  }
  finp.close();
}



/**Function to calculate lps array for KMP algorithm of string matching**/
void find_lps(string patt,ll pattlen,ll *lps){

    ll len = 0;   ///len of index declared as 0

    lps[0] = 0;   ///lps[0] will always be 0,start of pattern

    ll i = 1;

    /**Start filling the lps array**/

    while(i < pattlen){

        if(patt[i] == patt[len]){

            ++len;
            lps[i] = len;
            ++i;

        }

        else{

            if(len != 0)
                len = lps[len-1];

            else{
                lps[i] = 0;
                ++i;
            }
        }
    }///end of while loop
}


/********Main KMP Function**********/                              //It takes O(m+n) time in all cases

void Plag_KMP(string sample[]){
    /*count1 -> plag file,count2 -> source file,countlines -> plag file*/
    ll count1 = 0,count2 = 0,countlines = 0;
    string patt,samp,temp;                   ///patt is to be searched in samp of source file
    fstream fin,fio,fout;                    ///fin->for plag file,fio->for source file,fout->for result file

    /*Open the file to be checked and result file*/
    fin.open("file.txt",ios::in);

    fout.open("results.txt",ios::in|ios::out|ios::trunc);
    //fio.seekg(0,ios::beg);

    while(getline(fin,temp)){
        ++countlines;
    }
    fin.close();--countlines;

    fin.open("file.txt",ios::in);
    /*Loop for the given 5 source files*/
    for(ll index = 0;index<6;++index){
    fio.open(sample[index],ios::in);                      //open the respective source file
    count1 = 0;
    fin.close();
    fin.open("file.txt",ios::in);


    //--countlines;
    //cout<<countlines<<endl;



    /*Loop for the file to be checked*/
    while(fin.good()){

        count2 = 0;
        ++count1;         ///lines of fin,input
        getline(fin,patt);  ///ead a line
        //if(!fin.good()) break;
        ll patlen = patt.size();
        ll lps[patlen];

        /*Create the LPS table*/
        find_lps(patt,patlen,lps);

        if(count1 > countlines) break;

        fio.clear();
        fio.seekg(0,ios::beg);



        /*Loop for the source file*/
        while(fio.good()){


            getline(fio,samp);
            ++count2;
           // if(patlen < 4) continue;

            ll i = 0;   ///for sample file
            ll j = 0;   ///for pattern file

            while(i < samp.size()){

                /*if(patt[j] == ' ') ++j;
                if(samp[i] == ' ') ++i;*/
                if(patt[j] == samp[i]){
                    ++j;
                    ++i;
                }

                if(j == patlen){
                    //cout<<"Copied at index: \n"<<i - j<<"OF LINE "<<count1<<"-"<<count2 ;
                    cout<<"\nLine "<<count1<<" of given file is 100% copied from Line "<<count2<<" of "<<sample[index]<<"!"<<endl;
                    fout<<"\nLine "<<count1<<" of given file is 100% copied from Line "<<count2<<" of "<<sample[index]<<"!"<<endl;
                    j = lps[j-1];
                    arr[count1] = 1;
                }

                else if(i < samp.size() && patt[j] != samp[i]){

                    if(j != 0)
                        j = lps[j-1];

                    else ++i;
                }
            }
          }

    }
    fio.close();
    }
/*Close all the files*/

fin.close();
for(ll i = 0;i<1000;++i){
    if(arr[i] == 1) ++count_plag_lines;
}
double percent = (double)(count_plag_lines)/(countlines) *(100.0);
cout<<"\n************************************************************************"<<endl;
cout<<"\n************************************************************************"<<endl;
cout<<"\n---->"<<percent<<" % of document is plaigiarised!!\n";
fout<<"\n---->"<<percent<<" % of document is plaigiarised!!!!\n";
fout.close();
}


int main(){

    cout<<"\n******************************************************************\n";
    cout<<"\nWelcome to the menu of simple plaigiarism detector: \n";

    cout<<"\n1: Using A Naive Algorithm.\n";
    cout<<"\n2: Using Knutth-Morris Pratt Algorithm.\n";
    cout<<"\n3: Using Robin-Karp Algorithm.\n";
    cout<<"\n***************************"<<endl;
    cout<<"\nWe will check the plaigiarsm in your files by using the above mentioned algorithms.\n";
    cout<<"Also (.txt) file will be generated containg the result of plaigiarism of the entered file.\n";
    cout<<"\n***************************"<<endl;
    cout<<"\nOur database contains six files to which the document is going to be tested against.\n";

    string sample[6];
    sample[0] = "sample1.txt";sample[1] = "sample2.txt";
    sample[2] = "sample3.txt";sample[3] = "sample4.txt";
    sample[4] = "sample5.txt";sample[5] = "sample6.txt";


    cout<<"\n**************Results of naive algorithm**************\n";
    auto start = high_resolution_clock::now();
    Plagiarism_Naive(sample);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"\n******************************************************************\n";
    cout << "\n******Time taken by Naive Algorithm in micro_sec: " << duration.count() << endl;
    cout<<"\n******************************************************************\n";


    cout<<"\n**************Results of Robin-Karp algorithm*********\n";
    auto start1 = high_resolution_clock::now();
    Plagiarism_RobinKarp(sample);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout<<"\n******************************************************************\n";
    cout << "\n******Time taken by Robin-Karp Algorithm in micro_sec: " <<  duration1.count() << endl;
    cout<<"\n******************************************************************\n";


    cout<<"\n**************Results of KMP algorithm****************\n";
    auto start2 = high_resolution_clock::now();
    Plag_KMP(sample);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout<<"\n******************************************************************\n";
    cout << "\n******Time taken by KMP Algorithm in micro_sec: " << duration2.count() << endl;
    cout<<"\n******************************************************************\n";







}
