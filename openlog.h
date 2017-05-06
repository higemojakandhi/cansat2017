/**
* @file openlog.h
* @author Kandai Watanabe
* @date Created: 20170506
*/
#ifndef _OPENLOG_H_
#define _OPENLOG_H_

class Openlog {
public:
  Openlog(int resetPin);
  ~Openlog();
  void saveDataOnSD();
  void initOpenlog();

private:
  void clear();

  int _resetPin;
};

#endif


