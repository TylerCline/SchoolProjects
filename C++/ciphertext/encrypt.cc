#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <climits>
using namespace std;

int main(int argc,char *argv[]) {
  string key;
  vector<int> standardFrequencies;
  vector<int> freqIndeces;
  vector<string> words;
  int n, m, lines;

  // cin >> key; // Assuming key has no spaces
  ifstream freqIn, wordIn;
  freqIn.open("standard_freq.dat");
  wordIn.open("words");

  if(freqIn.fail()){
    cout << "Failed to open standar_freq.dat" << endl;
    exit(-1);
  }
  else if(wordIn.fail()){
    cout << "Failed to open words" << endl;
    exit(-1);
  }
  
  int cnt = 0;
  
  //Populating the standarFrequencies vector
  freqIn >> n;
  while(freqIn >> n >> m){
      standardFrequencies.push_back(m);
      freqIndeces.push_back(n);
    }
  freqIn.close();

  string w;
  //filling up an array full of words
  while(wordIn >> w){
    words.push_back(w);
  }
  wordIn.close();

  //Beginning of the original code
  //This takes all of the words in the dictionary file, runs them on the encrypted file
  //,produces a plaintext and pushes the plaintext into a vector called plainText.
 string key2;
 int min = INT_MAX;
 vector<int> pFreq;
 
 for(int i = 0; i < words.size(); i++){
       //initializing the plaintext vector to be all 0's so I can
       //increment values later
       int count = 0;
       for(int l = 0; l < 256; l++){
	 pFreq.push_back(0);
       }

       key = words[i];
      
       ifstream fin;
       fin.open(argv[1]);
       
       if (fin.fail()) {
	 cout << "Failed to open " << argv[1] << endl;
	 exit(-1);
       }
       
       while (!fin.eof()) {
	 unsigned char c;
	 c = fin.get();
	 if (!fin.fail()){
	   int x = char(c^key[count%key.size()]);
	   pFreq[x]+=1;
	 }
	 if(count > 1000){
	   fin.close();
	   break;
	 }
	 count++;
       }
       fin.close();

       //code which calculates the sum from 0 to 255 of the plaintext frequencies and standard
       //frequencies
       int fd = 0;
       for(int q = 0; q < 256; q++){
	 fd += ((pFreq[q] - standardFrequencies[q])*(pFreq[q] - standardFrequencies[q]));
	 // cout << "bbbbb" <<endl;
       }
       //If the sum is samller than the previous sum, min will become fd and key2 will become the
       //word which produced the decrypted message with the minimal sum
       if(fd < min){
	 min = fd;
	 key2 = words[i];
	 //cout << "Key : " <<key2<< " :  Equation Value : " << fd << endl;
       }
       pFreq.clear();
 }


//take the word which produced the smallest sum and decrypt the message
 fstream fin;
 fin.open(argv[1]);
 cout << "Password : " << key2 <<endl<<"Message:"<<endl;
 int counter = 0;
 while (!fin.eof()) {
   char c;
   c = fin.get();
   if (!fin.fail()) {
     cout << char(c^key2[counter%key2.size()]);
   }
   counter++;
   }

 cout << "*********PASSWORD********* "<<endl<<"*********" << key2 << "*********"<<endl;
       
}

