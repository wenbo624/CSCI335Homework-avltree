// Name: Wen Bo
// Date: 3/12/2019
// Assigment: Assignment 2

#ifndef SEQUENCE_MAP_H_
#define SEQUENCE_MAP_H_

#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

class SequenceMap{
 public:
 	//default constructor
 	SequenceMap() = default;
 
 	//Copy-constructor
 	SequenceMap(const SequenceMap &rhs) = default;
 	
 	//Copy-assignment
 	SequenceMap& operator=(const SequenceMap &rhs) = default;


 	//Move-constructor
 	SequenceMap(SequenceMap &&rhs) = default;
 	
 	//Move-assignment
 	SequenceMap& operator=(SequenceMap &&rhs) = default;

 	//Destructor
 	~SequenceMap() = default;
 	
 	//Parameter construtor
 	SequenceMap(const string &a_rec_seq, const string &an_enz_acro)
 	{	
 		recognition_sequence_ = a_rec_seq;	
 		enzyme_acronyms_.push_back(an_enz_acro);		
 	}

 	//Compare two string
 	bool operator<(const SequenceMap &rhs) const
 	{
 		if(recognition_sequence_ < rhs.recognition_sequence_)
 			return true;
 		else 
 			return false;
 	}

 	//overload the operator <<.
 	friend std::ostream &operator<<(std::ostream &out, const SequenceMap &some_SequenceMap)
 	{
 		for(size_t i = 0; i < some_SequenceMap.enzyme_acronyms_.size(); i++)
 			out << some_SequenceMap.enzyme_acronyms_[i] << " ";

 		out << "\n";
 						
 		return out;
 	}

 	
 	void Merge(const SequenceMap &other_sequence)
 	{
 		for(size_t i = 0; i < other_sequence.enzyme_acronyms_.size(); i++)
 			enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
 	}

  private:
  	string recognition_sequence_ ; 
  	vector<string> enzyme_acronyms_;

};

#endif