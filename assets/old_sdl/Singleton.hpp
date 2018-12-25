#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

template <class Type>
class Singleton
{
protected:
   Singleton(){}
   Singleton(const Singleton & one){}
   Singleton & operator = (const Singleton & one)
   {
      return *this;
   }

public:
   virtual ~Singleton(){};
   static Type * instance();
};

template <class Type>
Type * Singleton<Type>::instance()
{
   static Type inst;
   return &inst;
}

#endif
