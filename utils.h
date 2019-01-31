#ifndef UTILS_H
#define UTILS_H


template<typename T> class Iterator{
public:
    virtual T& current() const = 0;
    virtual bool isDone() const = 0;
    virtual void next() = 0;

};

class AppException{
public:
    const QString message;
public:

    AppException(const QString msg) : message(msg) {}
};


#endif // UTILS_H
