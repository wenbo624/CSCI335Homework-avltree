// Name: Wen Bo
// Main file for Part2(c) of  Homework 2.

#include "avl_tree_modified.h"
// You will have to add #include "sequence_map.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;


namespace {
bool GetNextRegocnitionSequence(const string &in_line, string &reco_seq, int &count)
{
  
  //Store next reco_seq
  if(in_line[count] == '/')
    return false;
  while(in_line[count] != '/')
  {
    reco_seq += in_line[count];
    count++;
  }

  count++;
  return true;

}


// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)  

  //1.construct a search tree
  
  string db_line;
  ifstream in_file;
  in_file.open(db_filename);

  string junk;
  for(int i = 0; i < 10; i++)
  {
    getline(in_file, junk);
  }

  int j;
  while(getline(in_file, db_line) && db_line != "")
  {
    j = 0;
    string an_enz_acro;

    while(db_line[j] != '/')
    {
      an_enz_acro += db_line[j];
      j++;
    }

    j++;
    string a_reco_seq;

   
    while(GetNextRegocnitionSequence(db_line, a_reco_seq, j))
    {
      SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
      a_tree.insert(new_sequence_map);
      a_reco_seq = "";
    }
  }

  

  //2.print the number of nodes in tree.
  int n = a_tree.countnode();
  cout << "2: " << a_tree.countnode() << endl;

  //3.get the internal path length
  int length = a_tree.pathLength();

  //compute the average depth and ratio 
  float ave_depth = (float)length/n;
  float ratio_ave_depth = ave_depth/log2(n);
 
  cout << "3a: " << ave_depth << endl;
  cout << "3b: " << ratio_ave_depth << endl;

  //4.find the tree for string in sequence.txt  
  //and counts the total number of recursive calls for all executions of find().
  //read sequence file
  string str;
  ifstream in_seq;
  in_seq.open(seq_filename);

  int totalRecursive = 0;
  int num_str_found = 0;

  while(getline(in_seq, str)&&str != "")
  {
    
    SequenceMap new_sequence_map1(str, "an_enz_acro");
    bool found_str = a_tree.find1(new_sequence_map1, totalRecursive);

    if(found_str == true){
        num_str_found++;
    }
        
  }

  in_seq.close();
  //cout << totalRecursive << endl;

  float ave_rec = (float)totalRecursive/num_str_found;
  cout << "4a: " << num_str_found << endl;
  cout << "4b: " << ave_rec << endl;

  //5.remove every other sequence node from the tree and counts the
  //total number of recursion calls for all executions of remove().
  string str1;
  ifstream in_seq1;
  in_seq1.open(seq_filename);

  int num = 0;
  int num_remove_rec = 0;
  int num_remove_node = 0;
  int x = 1;
  while(getline(in_seq1, str1)&&str1 != "")
  {
    if(x % 2 != 0){
      SequenceMap new_sequence_map2(str1, "an_enz_acro");
      bool found_str1 = a_tree.find1(new_sequence_map2, num);

      if(found_str1 == true)
          { 
            SequenceMap to_delete_node = a_tree.findnode(new_sequence_map2);

            a_tree.remove(to_delete_node, num_remove_rec);
            num_remove_node++;
          }
      x++;
    }
    else
      x++;  
  }

  float ave_remove = (float)num_remove_rec/num_remove_node;
  cout << "5a: " << num_remove_node << endl;
  cout << "5b: " << ave_remove << endl;


  //6.redo step2 and step3
  int n1 = a_tree.countnode();
  cout << "6a: " << n1 << endl;

  int length1 = a_tree.pathLength();
  float ave_depth1 = (float)length1/n1;
  float ratio_ave_depth1 = ave_depth1/log2(n1);
 
  cout << "6b: " << ave_depth1 << endl;
  cout << "6c: " << ratio_ave_depth1 << endl;
}



}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  return 0;
}
