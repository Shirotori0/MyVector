#include<iostream>
#include<vector>

template <typename T>
class MyVector
{
private:
    T* head_ptr;
    T* tail_ptr;
    T* guild_ptr;

    bool IhasSpace()
    {
        return !(tail_ptr==guild_ptr);
    }

    size_t ImemorySize()
    {
        return (guild_ptr-head_ptr);
    }

    void IcallMemoryDoubleCopyDelete()
    {
        if(ImemorySize()==0)
        {
            head_ptr=(T*)new T[1];
            tail_ptr=head_ptr;
            guild_ptr=head_ptr+1;
            return;
        }

        T* temp=(T*)new T[ImemorySize()*2];
        guild_ptr=temp+ImemorySize()*2;

        for(int i=0;i<size();++i)
        {
            temp[i]=head_ptr[i];
        }
        tail_ptr=temp+size();

        delete[] head_ptr;
        head_ptr=std::move(temp);
    }



public:

    MyVector()
    {
        head_ptr=nullptr;
        tail_ptr=nullptr;
        guild_ptr=nullptr;
    }

    MyVector(size_t init_size,const T& init_data)//带初始值构造，初始化列表实现需要借助std::initializer_list或手动实现，先不搞
    {
        if(init_size!=0)
        {
            head_ptr=(T*)new T[init_size];
            tail_ptr=head_ptr;
            for (size_t i = 0; i < init_size; ++i)
            {
                *tail_ptr=init_data;
                ++tail_ptr;
            }
            guild_ptr=tail_ptr;
        }
        else
        {
            MyVector();
        }
    }
    
    ~MyVector()
    {
        delete[] head_ptr;
    }

    size_t size()
    {
        return (tail_ptr-head_ptr);
    }

    void add(T data)
    {
        if(!IhasSpace())
        {
            IcallMemoryDoubleCopyDelete();
        }
        *tail_ptr=data;
        ++tail_ptr;
    }

    void pop(size_t index=-1)
    {
        if(index==-1)
        {
            --tail_ptr;
            *tail_ptr=(T)0;
        }
        else
        {
            for (size_t i = 0; i < size()-index-1; ++i)
            {
                head_ptr[index+i]=head_ptr[index+i+1];
            }
            --tail_ptr;
            *tail_ptr=(T)0;
        }
    }

    T& operator[](size_t index)
    {
        if(index>size()-1)
        {
            //throw std::out_of_range("out of range");
        }
        return head_ptr[index];
    }
    const T& operator[](size_t index) const
    {
        if(index>size()-1)
        {
            //throw std::out_of_range("out of range");
        }
        return head_ptr[index];
    }

    void getSize()
    {
        std::cout<<"size:"<<size()<<std::endl;
        std::cout<<"memorysize:"<<ImemorySize()<<std::endl;

    }

    class MyIterator;
    MyIterator begin()
    {
        return MyIterator(head_ptr);
    }
    MyIterator end()
    {
        return MyIterator(tail_ptr);
    }
};

template<typename T>
class MyVector<T>::MyIterator
{
private:
    T* ptr;
public:
    MyIterator(T*ptr)
    :ptr(ptr)
    {
    }

    T& operator*()
    {
        return *ptr;
    }

    T* operator->()
    {
        return ptr;
    }

    MyIterator& operator++()
    {
        ++ptr;
        return *this;
    }

    MyIterator operator++(int)
    {
        T* temp=this;
        ++ptr;
        return temp;
    }

    void operator+=(int data)
    {
        ptr+=data;
    }

    void operator-=(int data)
    {
        ptr-=data;
    }

    bool operator==(const MyIterator& other)
    {
        return ptr==other.ptr;
    }

    bool operator!=(const MyIterator& other)
    {
        return ptr!=other.ptr;
    }

    T& operator[](int index) const
    {
        return ptr[index];
    }

};

int main(){
    std::vector<int>t;t.begin();

MyVector<int>v;
for (size_t i = 0; i < 10; ++i)
{
    v.add(i);
}

v.pop(0);

for (auto& i:v)
{
    std::cout<<i<<std::endl;
}


std::cout<<"check"<<std::endl;


std::cin.get();
}