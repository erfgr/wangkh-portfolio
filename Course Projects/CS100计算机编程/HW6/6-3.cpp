#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
//REMOVE THIS CLASS WHEN SUBMITTING!!!
class Point {
  double x{0}, y{0};
  std::string label;

 public:
  Point(double x0, double y0, const std::string &l = "")
      : x(x0), y(y0), label(l) {}
  Point() = default;
  double get_x() const {
    return x;
  }
  double get_y() const {
    return y;
  }
  std::string get_label() const {
    return label;
  }
  Point &set_x(double x0) {
    x = x0;
    return *this;
  }
  Point &set_y(double y0) {
    y = y0;
    return *this;
  }
  Point &set_label(const std::string &l) {
    label = l;
    return *this;
  }
};

class Point_counted {
  friend class Point_handle;
  // All the members are private.

  Point p;
  unsigned cnt;
  // Define some helper member functions if you need.
  //三个对应构造函数
  Point_counted() = default;
  Point_counted(const Point &p0) : p(p0){};
  Point_counted(double x, double y, const std::string &l = ""):p(x,y,l){};
};

class Point_handle {
  Point_counted *ptr;
  // Your code here.
public:
  Point_handle(const Point_handle &ph2) : ptr(ph2.ptr) {
    ptr->cnt++;
  } 
  Point_handle() {
    ptr = new Point_counted();
    ptr->cnt=1;
  }
  Point_handle(const Point &p) {
    ptr = new Point_counted(p);
    ptr->cnt=1;
  }
  Point_handle(double x, double y, const std::string &l = "") {
    ptr = new Point_counted(Point(x,y,l));
    ptr->cnt=1;
  }
  /////////////////////////////////////////////////////
  Point_handle &operator=(const Point_handle &ph2) {
    if(this!=&ph2){
      ptr->cnt--;
      if(ptr->cnt==0){
        delete ptr;
      }
      ptr=ph2.ptr;
      ptr->cnt++;
    }
    return *this;
  }
  ~Point_handle() {
    ptr->cnt--;
    if(ptr->cnt==0){
      delete ptr;
    }
  }
 
  double ref_count() const{
    return ptr->cnt;
  }
  double get_x() const{
    return ptr->p.get_x();
  }
  double get_y() const{
    return ptr->p.get_y();
  }
  std::string get_label() const{
    return ptr->p.get_label();
  }
  /////////////////////////////////////////////////////
  Point_handle &set_x(double x) {
    if(ptr->cnt==1){
      ptr->p.set_x(x);
    }
    else{
      Point_counted *tmp=new Point_counted;
      tmp->p=ptr->p;
      tmp->cnt=1;
      ptr->cnt--;
      if(ptr->cnt==0){
        delete ptr;
      }
      ptr=tmp;
      ptr->p.set_x(x);
    }
    return *this;
  }
  Point_handle &set_y(double y) {
    if(ptr->cnt==1){
      ptr->p.set_y(y);
    }
    else{
      Point_counted *tmp=new Point_counted;
      tmp->p=ptr->p;
      tmp->cnt=1;
      ptr->cnt--;
      if(ptr->cnt==0){
        delete ptr;
      }
      ptr=tmp;
      ptr->p.set_y(y);
    }
    return *this;
  }
  Point_handle &set_label(const std::string &l) {
    if(ptr->cnt==1){
      ptr->p.set_label(l);
    }
    else{
      Point_counted *tmp=new Point_counted;
      tmp->p=ptr->p;
      tmp->cnt=1;
      ptr->cnt--;
      if(ptr->cnt==0){
        delete ptr;
      }
      ptr=tmp;
      ptr->p.set_label(l);
    }
    return *this;
  }
};
