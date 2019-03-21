// Name: Wen Bo
// Main file for Part2(a)  of Homework 2.

#include "avl_tree.h"
// You will have to add #include "sequence_map.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace {
bool GetNextRegocnitionSequence(string &in_line, string & reco_seq)
{
  
  int count = 0;
  if(in_line[count] == '/')
    return false;

  while(in_line[count] != '/')
  {
    reco_seq += in_line[count];
    count++;
  }
  count++;
  //cout <<count<<endl;

  in_line = in_line.substr(count);
  return true;

}

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  // Code for running Part2(a)
  // You can use public functions of TreeType. For example:
  
  string db_line;
  ifstream in_file;
  in_file.open(db_filename);



  string junk;
  for(int i = 0; i < 10; i++)
  {
    getline(in_file, junk);
  }
  

  int i;
  while(getline(in_file, db_line)&&db_line!="")
  {
    i= 0;
    string an_enz_acro;
    while(db_line[i] != '/')
    {
      an_enz_acro += db_line[i];
      i++;
    }
    i++;
    db_line = db_line.substr(i);

    string a_reco_seq;

    while(GetNextRegocnitionSequence(db_line, a_reco_seq)){   
          SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
           a_tree.insert(new_sequence_map);
          a_reco_seq="";
       }     
  }    



  string str1, str2, str3;
  cin >> str1 >> str2 >> str3;


  SequenceMap new_sequence_map2(str1, "an_enz_acro");
  a_tree.find(new_sequence_map2);


  SequenceMap new_sequence_map3(str2, "an_enz_acro");
  a_tree.find(new_sequence_map3);

  SequenceMap new_sequence_map4(str3, "an_enz_acro");
  a_tree.find(new_sequence_map4);
  
} 

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  cout << "Input filename is " << db_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);

  
  return 0;
}
