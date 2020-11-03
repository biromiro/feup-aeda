# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
    std::stack<T> st;
    std::stack<T> minSt;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

template <class T> 
bool StackExt<T>::empty() const
{
    return st.empty();
}

template <class T> 
T& StackExt<T>::top()
{
    return st.top();
}

template <class T> 
void StackExt<T>::pop()
{
    if(minSt.top() == st.top())
        minSt.pop();
    st.pop();
}

template <class T> 
void StackExt<T>::push(const T & val)
{
    st.push(val);
    if(minSt.empty())
        minSt.push(val);
    else if(minSt.top() >= val)
        minSt.push(val);
}

template <class T> 
T& StackExt<T>::findMin()
{
    return minSt.top();
}

