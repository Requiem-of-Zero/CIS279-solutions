#ifndef COURSEGRADEBOOK_H
#define COURSEGRADEBOOK_H
using namespace std;

#include <string>
#include <algorithm>
#include "Gradebook.h"
#include <vector>
#include <cmath>

class CourseGradebook : public Gradebook {
protected:
   int courseId;
   vector<Gradebook*> assignments;
   int numAssignments;
   // Key: assignmentName, Value: studentId map 
   unordered_map<string, unordered_map<int, double>> scores;
public:

   CourseGradebook() : courseId(0), numAssignments(0){}

   CourseGradebook(int courseId, int numAssignments) : courseId(courseId), numAssignments(numAssignments){}

   virtual ~CourseGradebook() {
      for(Gradebook* gb : assignments){
         delete gb;
      }
   }

   unordered_map<int, double> GetAssignmentScores(string assignmentName) override {
      if(scores.find(assignmentName) != scores.end()){
         return scores[assignmentName];
      }
      return {};
   }

   double GetScore(string assignmentName, int studentID) override {
      if (scores.find(assignmentName) != scores.end()) {
         if (scores[assignmentName].find(studentID) != scores[assignmentName].end()) {
            return scores[assignmentName][studentID];
         }
      }
      return NAN;  // Return NAN if score doesn't exist
   }

   vector<string> GetSortedAssignmentNames() override {
      vector<string> assignmentNames;
      for(const auto& entry : scores){
         assignmentNames.push_back(entry.first);
      }
      sort(assignmentNames.begin(), assignmentNames.end());
      return assignmentNames;
   }
   
   // GetSortedStudentIDs() returns a vector with all distinct student IDs,
   // sorted in ascending order.
   vector<int> GetSortedStudentIDs() override {
      vector<int> studentIds;
      for(const auto& assignment : scores){
        for(const auto& student : assignment.second){
            if(find(studentIds.begin(), studentIds.end(), student.first) == studentIds.end()){
               studentIds.push_back(student.first);
            }
        } 
      }
      sort(studentIds.begin(), studentIds.end());
      return studentIds;
   }
   
   // GetStudentScores() gets all scores that exist in the gradebook for the
   // student whose ID equals the studentID parameter. Scores are returned as
   // an unordered_map that maps an assignment name to the student's
   // corresponding score for that assignment.
   unordered_map<string, double> GetStudentScores(int studentID) override {
      unordered_map<string, double> studentScores;
      for(const auto& assignment: scores){
         if (assignment.second.find(studentID) != assignment.second.end()) {
            studentScores[assignment.first] = assignment.second.at(studentID);
         }
      }
      return studentScores;
   }

   void SetScore(string assignmentName, int studentID, double score) override {
	  // Your code here
     scores[assignmentName][studentID] = score;
     numAssignments++;
   }
};

#endif