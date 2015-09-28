#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include <vector>
#include <algorithm>

// progress indicator to report the progress, which should 
// derived from this interface and regist to an Observable class.
class ProgressIndicator
{
public:
  virtual void report(int size, int totalSize) = 0;
protected:
  virtual ~ProgressIndicator() {}
};

// observable utility class, it provides the regist and remove 
// functions, this implementation is not thread-safed.
class Observable
{
protected:
  // It's not good practice for keeping raw pointer.
  // vector<weak_ptr<T>> would be perferred.
  std::vector<ProgressIndicator *> obsevers;

  void notifyAll(int size, int totalSize) {
    // for thread safe, should synchronized copy the overall vector, 
    // then iterates the copied one.
    for (std::vector<ProgressIndicator *>::iterator it = std::begin(obsevers); 
      it != std::end(obsevers); ++it) {
        (*it)->report(size, totalSize);
    }
  }
  
  virtual ~Observable() {}

public:
  void regist(ProgressIndicator *o) {
    // for thread safe, should synchronize this.
    std::cout << "[Observable] " << "regist" << std::endl;
    obsevers.push_back(o);
  }

  void remove(ProgressIndicator *o) {
    // for thread safe, should synchronize this.
    std::cout << "[Observable] " << "remove" << std::endl;
    const std::vector<ProgressIndicator *>::iterator position = 
      std::find(obsevers.begin(), obsevers.end(), o);
    if (position != obsevers.end())
      obsevers.erase(position);
  }
};


#endif // __OBSERVABLE_H__