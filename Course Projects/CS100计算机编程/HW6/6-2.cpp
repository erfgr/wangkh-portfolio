#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
class Alarm;

class AlarmClock {
public:
  // Your constructors and destructor.

  void AddAlarm(Alarm* alarm);
  void Input();
  void TimeElapse();
  ~AlarmClock(){
    for(int i=0;i<m_alarms.size();i++){
      delete m_alarms[i];
    }
  }
private:
  std::vector<Alarm*> m_alarms;
  int newhour=0;
  int newminute=0;
};

class Alarm {
public:
  // Your constructors and destructor.
  Alarm(std::string m_name, int m_hour, int m_minute) : name(m_name), hour(m_hour), minute(m_minute) {}
  ~Alarm() {}
  virtual void Trigger() = 0; 
  virtual int SetHour() = 0;
  virtual int SetMinute() = 0;
  
protected:
  // Declare protected members so that child classes have access to them.
  std::string name;
  int hour=0;
  int minute=0;
  std::string m_name;
  int m_hour=0;
  int m_minute=0;
};

class RepeatableAlarm : public Alarm {
public:
  // Your constructors and destructor.
  RepeatableAlarm(std::string name, int hour, int minute): Alarm(name, hour, minute) {};
  virtual ~RepeatableAlarm() {}
  int SetHour() {return hour;}
  int SetMinute() {return minute;}
  void Trigger(){
    std::cout << "Alarm " << name << " has triggered at ";
    printf("%02d:%02d.\n", hour, minute);
  }
};

class SnoozeableAlarm : public Alarm {
public:
  // Your constructors and destructor.
  SnoozeableAlarm(std::string name, int hour, int minute): Alarm(name, hour, minute) {}; 
  virtual ~SnoozeableAlarm() {}
  int SetHour() {return hour;}
  int SetMinute() {return minute;}
  void Trigger(){
    std::cout << "Alarm " << name << " has triggered at " ;
    printf("%02d:%02d. Snooze? (Y/N)\n", hour, minute);
    std::string input;
    std::getline(std::cin, input);
    if(input == "Y"){
      if(minute + 10 >= 60){
        hour += 1;
        minute = minute + 10 - 60;
        if(hour == 24){hour = 0;}
      }
      else{minute += 10;}
    }
    else{
      hour=25;
      minute=70;
    }
  }
};



/**************** Implementations ******************/
void AlarmClock::AddAlarm(Alarm* alarm) {
  m_alarms.push_back(alarm);
}

void AlarmClock::Input() {
  std::string line;
  std::getline(std::cin, line);
  int N = std::stoi(line);
  for (int i = 0; i < N; i++) {
    std::getline(std::cin, line);
    char type = line[0];
    int hour = std::stoi(line.substr(2, 2));
    int minute = std::stoi(line.substr(5, 2));
    std::string name = line.substr(8);
    if (type == 'R') {
      RepeatableAlarm* alarm = new RepeatableAlarm(name, hour, minute);
      AddAlarm(alarm);
    } else if (type == 'S') {
      SnoozeableAlarm* alarm = new SnoozeableAlarm(name, hour, minute);
      AddAlarm(alarm);
    }
  }
}

void AlarmClock::TimeElapse() {
  for(int i=0;i<m_alarms.size();i++){
    if(newminute == m_alarms[i]->SetMinute() && newhour == m_alarms[i]->SetHour()){
      m_alarms[i]->Trigger();
    }
  }
  newminute++;
  if(newminute==60){
    newminute=0;
    newhour++;
    if(newhour==24){
      newhour=0;
    }
  }  
}

// ...

int main() {
  AlarmClock clock;
  for (int days = 0; days < 3; days++) {
    std::cout << "Do you want to add any alarms?" << std::endl;
    clock.Input();
    for (int minute = 0; minute < 24 * 60; minute++) {
      clock.TimeElapse();
    }
    std::cout << "A day has elapsed." << std::endl;
  }
}