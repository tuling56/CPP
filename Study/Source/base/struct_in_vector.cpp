#include <vector>
#include <iostream>

using namespace std;

/*[方式二]  结构体放入堆中，vector中放指针---------------------*/
typedef struct student{
   char* school_name;
   char gender;
   int age;
   bool is_absent;
} StudentInfo;

typedefstd::vector<StudentInfo*> StudentInfoPtrVec;

void print(StudentInfoPtrVec*stduentinfoptrvec){
   for (int j=0;j<(*stduentinfoptrvec).size();j++)
    {
       std::cout<<
           (*stduentinfoptrvec)[j]->school_name<<"\t"<<
           (*stduentinfoptrvec)[j]->gender<<"\t"<<
           (*stduentinfoptrvec)[j]->age<<"\t"<<
           (*stduentinfoptrvec)[j]->is_absent<<"\t"<<std::endl;
    }
   return;
}

int main(){

   StudentInfoPtrVec studentinfoptrvec;

   char* p_char_1=NULL;
   p_char_1=new char[100];
   strcpy(p_char_1,"Micheal");
   StudentInfo* p_student_1=new StudentInfo;
   p_student_1->school_name=p_char_1;
   p_student_1->gender='m';
   p_student_1->age=18;
   p_student_1->is_absent=false;
   studentinfoptrvec.push_back(p_student_1);

   char* p_char_2=NULL;
   p_char_2=new char[100];
   strcpy(p_char_2,"Cherry");
   StudentInfo* p_student_2=new StudentInfo;
    p_student_2->school_name=p_char_2;
   p_student_2->gender='f';
   p_student_2->age=16;
   p_student_2->is_absent=false;
   studentinfoptrvec.push_back(p_student_2);

   print(&studentinfoptrvec);
   delete p_char_1;
   delete p_student_1;
   delete p_char_2;
   delete p_student_2;
   return 0;

}