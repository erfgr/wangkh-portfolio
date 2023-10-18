#include <iostream>
#include <string>
#include <cmath>
class Expr_node {
 public:
  Expr_node() = default;
  virtual double eval() const = 0;
  virtual std::string to_string() const = 0;
  virtual ~Expr_node() = default;
  Expr_node(const Expr_node &) = delete;
  Expr_node &operator=(const Expr_node &) = delete;
};

class Number_node : public Expr_node {
  friend Number_node *make_number(double);
  double value;
  Number_node(double val) : value(val) {}
  virtual double eval() const;
  virtual std::string to_string() const;
};

//The class ‘Negation node’ represents the node of negation, and has a data member ‘Expr node *operand’ that points to the operand.
class Negation_node : public Expr_node {
  friend Negation_node *make_negation(Expr_node *);
  Expr_node *operand;
  Negation_node(Expr_node *op) : operand(op) {}
  virtual double eval() const;
  virtual std::string to_string() const;
  ~Negation_node() { delete operand; }
};

/*The classes ‘Plus node’, ‘Minus node’,
‘Multiply node’ and ‘Divide node’ represent the binary operations, and they all have two operands
pointed by ‘Expr node *lhs’ and ‘Expr node *rhs’, so we can make them derived from another class
called ‘Binary node’.*/
class Binary_node : public Expr_node {
 protected:
  Expr_node *lhs, *rhs;
  Binary_node(Expr_node *l, Expr_node *r) : lhs(l), rhs(r) {}
  virtual ~Binary_node() { delete lhs; delete rhs; }
};
class Plus_node : public Binary_node {
  friend Plus_node *make_plus(Expr_node *, Expr_node *);
  Plus_node(Expr_node *l, Expr_node *r) : Binary_node(l, r) {}
  virtual double eval() const;
  virtual std::string to_string() const;
  ~Plus_node() {}
};
class Minus_node : public Binary_node {
  friend Minus_node *make_minus(Expr_node *, Expr_node *);
  Minus_node(Expr_node *l, Expr_node *r) : Binary_node(l, r) {}
  virtual double eval() const;
  virtual std::string to_string() const;
  ~Minus_node() {}
};
class Multiply_node : public Binary_node {
  friend Multiply_node *make_multiply(Expr_node *, Expr_node *);
  Multiply_node(Expr_node *l, Expr_node *r) : Binary_node(l, r) {}
  virtual double eval() const;
  virtual std::string to_string() const;
  ~Multiply_node() {}
};
class Divide_node : public Binary_node {
  friend Divide_node *make_divide(Expr_node *, Expr_node *);
  Divide_node(Expr_node *l, Expr_node *r) : Binary_node(l, r) {}
  virtual double eval() const;
  virtual std::string to_string() const;
  ~Divide_node() {}
};

////////////////Part Ⅱ//////////////////
class Sin_node : public Expr_node {
  friend Sin_node *make_sin(Expr_node *);
  Expr_node *operand;
  Sin_node(Expr_node *op) : operand(op) {}
  virtual double eval() const;
  virtual std::string to_string() const;
  ~Sin_node() { delete operand; }
};
class Cos_node : public Expr_node {
  friend Cos_node *make_cos(Expr_node *);
  Expr_node *operand;
  Cos_node(Expr_node *op) : operand(op) {}
  virtual double eval() const;
  virtual std::string to_string() const;
  ~Cos_node() { delete operand; }
};
class Tan_node : public Expr_node {
  friend Tan_node *make_tan(Expr_node *);
  Expr_node *operand;
  Tan_node(Expr_node *op) : operand(op) {}
  virtual double eval() const;
  virtual std::string to_string() const;
  ~Tan_node() { delete operand; }
};
class Exp_node : public Expr_node {
  friend Exp_node *make_exp(Expr_node *);
  Expr_node *operand;
  Exp_node(Expr_node *op) : operand(op) {}
  virtual double eval() const;
  virtual std::string to_string() const;
  ~Exp_node() { delete operand; }
};
class Log_node : public Expr_node {
  friend Log_node *make_log(Expr_node *);
  Expr_node *operand;
  Log_node(Expr_node *op) : operand(op) {}
  virtual double eval() const;
  virtual std::string to_string() const;
  ~Log_node() { delete operand; }
};
//////////eval()函数/////////////////////////////////////////
double Number_node::eval() const { return value; }
double Negation_node::eval() const { return -operand->eval(); }
double Plus_node::eval() const { return lhs->eval() + rhs->eval(); }
double Minus_node::eval() const { return lhs->eval() - rhs->eval(); }
double Multiply_node::eval() const { return lhs->eval() * rhs->eval(); }
double Divide_node::eval() const { return lhs->eval() / rhs->eval(); }
double Sin_node::eval() const { return sin(operand->eval()); }
double Cos_node::eval() const { return cos(operand->eval()); }
double Tan_node::eval() const { return tan(operand->eval()); }
double Exp_node::eval() const { return exp(operand->eval()); }
double Log_node::eval() const { return log(operand->eval()); }

///////////////////////////////////////////////////////////////
inline Number_node *make_number(double value) {
  return new Number_node(value);
}
inline Negation_node *make_negation(Expr_node *operand) {
  return new Negation_node(operand);
}
inline Plus_node *make_plus(Expr_node *lhs, Expr_node *rhs) {
  return new Plus_node(lhs, rhs);
}
inline Minus_node *make_minus(Expr_node *lhs, Expr_node *rhs) {
  return new Minus_node(lhs, rhs);
}
inline Multiply_node *make_multiply(Expr_node *lhs, Expr_node *rhs) {
  return new Multiply_node(lhs, rhs);
}
inline Divide_node *make_divide(Expr_node *lhs, Expr_node *rhs) {
  return new Divide_node(lhs, rhs);
}
inline Sin_node *make_sin(Expr_node *operand) {
  return new Sin_node(operand);
}
inline Cos_node *make_cos(Expr_node *operand) {
  return new Cos_node(operand);
}
inline Tan_node *make_tan(Expr_node *operand) {
  return new Tan_node(operand);
}
inline Exp_node *make_exp(Expr_node *operand) {
  return new Exp_node(operand);
}
inline Log_node *make_log(Expr_node *operand) {
  return new Log_node(operand);
}

//to_string()函数/////////////////////////////////////////////////////////////////////
std::string Number_node::to_string() const {
  if (value<0)
    return "(" + std::to_string(value) + ")";
  else
    return std::to_string(value);
}
std::string Negation_node::to_string() const {
  return "(-" + operand->to_string() + ")";
}
std::string Plus_node::to_string() const {
  return "(" + lhs->to_string() + " + " + rhs->to_string() + ")"; 
}
std::string Minus_node::to_string() const {
  return "(" + lhs->to_string() + " - " + rhs->to_string() + ")"; 
}
std::string Multiply_node::to_string() const {
  return "(" + lhs->to_string() + " * " + rhs->to_string() + ")"; 
}
std::string Divide_node::to_string() const {
  return "(" + lhs->to_string() + " / " + rhs->to_string() + ")"; 
}
std::string Sin_node::to_string() const {
  if (operand->to_string()[0] == '(')
    return "sin" + operand->to_string();
  else
    return "sin(" + operand->to_string() + ")";
}
std::string Cos_node::to_string() const {
  if (operand->to_string()[0] == '(')
    return "cos" + operand->to_string();
  else
    return "cos(" + operand->to_string() + ")";
}
std::string Tan_node::to_string() const {
  if (operand->to_string()[0] == '(')
    return "tan" + operand->to_string();
  else
    return "tan(" + operand->to_string() + ")";
}
std::string Exp_node::to_string() const {
  if (operand->to_string()[0] == '(')
    return "exp" + operand->to_string();
  else
    return "exp(" + operand->to_string() + ")";
}
std::string Log_node::to_string() const {
  if (operand->to_string()[0] == '(')
    return "log" + operand->to_string();
  else
    return "log(" + operand->to_string() + ")";
}

//////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  Expr_node *expr_tree = make_divide(
      make_plus(make_number(3), make_multiply(make_number(4), make_number(5))),
      make_number(6));
  std::cout << expr_tree->eval() << std::endl;
  std::cout << expr_tree->to_string() << std::endl;
  delete expr_tree;
  Expr_node *bonus_tree =
      make_plus(make_exp(make_sin(make_number(3))), make_number(1));
  std::cout << bonus_tree->eval() << std::endl;
  std::cout << bonus_tree->to_string() << std::endl;
  delete bonus_tree;
  return 0;
}