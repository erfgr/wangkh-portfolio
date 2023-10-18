#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

// This class is quite simple with only some getters and setters.
// Finish the definitions of these functions first.
class Grade {
 public:
  // This constructor initializes the members with the parameters.
  Grade(const std::string &name, int number, double grade):m_name(name), m_number(number), m_grade(grade){}
  std::string getName() const { return m_name; }
  void setName(const std::string &name) { m_name = name; }
  int getNumber() const { return m_number; }
  void setNumber(int number) { m_number = number; }
  double getGrade() const { return m_grade; }
  void setGrade(double grade) { m_grade = grade; }
  Grade(const Grade &other) = default;

 private:
  std::string m_name;
  int m_number;
  double m_grade;
};

struct NameComparator {
  bool operator()(const Grade &a, const Grade &b) const {
    return a.getName() < b.getName();
  }
};

struct NumberComparator {
  bool operator()(const Grade &a, const Grade &b) const {
    return a.getNumber() < b.getNumber();
  }
};

struct GradeComparator {
  bool operator()(const Grade &a, const Grade &b) const{
    return a.getGrade() > b.getGrade();
  }
};

class Gradesheet {
  friend std::ostream &operator<<(std::ostream &os, const Gradesheet &sheet){
    os << "/" << std::string(30, '-') << "\\" << std::endl;
    os << "|" << std::left << std::setw(10) << "Name" << std::setw(10) << "Number" << std::setw(10) << "Grade" << "|" << std::endl;
    os << "|" << std::string(30, '-') << "|" << std::endl;
    for (const auto &grade : sheet.m_grades) {
      os << "|" << std::left << std::setw(10) << grade.getName() << std::setw(10) << grade.getNumber() << std::setprecision(3) << std::setw(10) << grade.getGrade() << "|" << std::endl;
    }
    os << "\\" << std::string(30, '-') << "/" << std::endl;
    return os;
  }

 public:
  Gradesheet(){
    m_grades.reserve(10);
  }
  ~Gradesheet(){
    m_grades.clear();
  }
  std::size_t size() const{
    return m_grades.size();
  }
  double average() const{
    double sum = 0;
    for (auto &grade : m_grades) {
      sum += grade.getGrade();
    }
    return sum / m_grades.size();
  }
  bool addGrade(const Grade &grade){
    for (auto &g : m_grades) {
      if (g.getName() == grade.getName() || g.getNumber() == grade.getNumber()) {
        return false;
      }
    }
    m_grades.push_back(grade);
    return true;
  }
  double findByName(const std::string &name) const{
    for (auto &g : m_grades) {
      if (g.getName() == name) {
        return g.getGrade();
      }
    }
    return -1;
  }
  double findByNumber(int number) const{
    for (auto &g : m_grades) {
      if (g.getNumber() == number) {
        return g.getGrade();
      }
    }
    return -1;
  }
  Grade &operator[](std::size_t i){
    return m_grades[i];
  }
  const Grade &operator[](std::size_t i) const{
    return m_grades[i];
  }
  void sortByName(){
    std::sort(m_grades.begin(), m_grades.end(), NameComparator());
  }
  void sortByNumber(){
    std::sort(m_grades.begin(), m_grades.end(), NumberComparator());
  }
  void sortByGrade(){
    std::sort(m_grades.begin(), m_grades.end(), GradeComparator());
  }

 private:
  std::vector<Grade> m_grades;
};

int main() {
  Gradesheet sheet;
  sheet.addGrade(Grade("Bob", 1, 95));
  sheet.addGrade(Grade("Carl", 2, 100));
  sheet.addGrade(Grade("Alex", 3, 90));
  sheet.sortByName();
  std::cout << "size == " << sheet.size() << "\n" << sheet;
  return 0;
}